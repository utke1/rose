#!/usr/bin/perl
#
# Adds rules to tests/roseTests/binaryTests/Makefile.in so that various tests can be run over the sample binaries found
# in the binaries/samples directory.
use strict;
my $makefile = "tests/roseTests/binaryTests/Makefile.in"; # makefile to be edited in place
my $sampledir = shift || "binaries/samples"; # Name of directory containing sample files
my $condition = "USE_BINARY_ANALYSIS_TESTS_TRUE"; # automake condition for each inserted statement

my @targets; # the list of targets generated by this script
my $seq = "AAAA";
my $make_sampledir =  "\$(top_srcdir)/" unless $sampledir =~ /^\//;
my $config = "\$(srcdir)/testSampleBinaries.conf";

# Get a list of all sample binaries recursively from a list of one or more directories.
sub find_sample_binaries {
  my @dirs = @_;
  my @retval;
  while (@dirs) {
    my $dir = shift @dirs;
    opendir DIR, $dir or die "$0: $dir: $!\n";
    while (my $basename = readdir DIR) {
      my $fullname = "$dir/$basename";
      next if $basename =~ /^\./;    # skip all dot files, including "." and ".."
      next if $basename =~ /\.txt$/;
      next if $basename =~ /^Makefile/;
      if (-d $fullname) {
	unshift @dirs, $fullname;
      } else {
	push @retval, $fullname;
      }
    }
  }
  return sort @retval;
}

# Generate Makefile rules for a single sample binary
sub generate_rule {
  my($sample,$target_for_file,$target_for_base) = @_;
  my($path,$basename) = $sample =~ /(.*)\/(.*)/;
  my($target) = "test_sample$seq.result";
  my($retval);
  $retval .= "$target: $make_sampledir$sample \$(SAMPLE_TEST_DEPS) $target_for_base->{$basename}\n";
  $retval .= "\t\@\$(srcdir)/testSampleBinary.sh $make_sampledir$sample $config >\$\@.tmp\n";
  $retval .= "\t\@mv \$\@.tmp \$\@\n";
  push @targets, $target;
  $target_for_base->{$basename} = $target;
  $target_for_file->{$sample} = $target;
  $seq++;
  return $retval;
};

sub generate_cleanup_rule {
  my($target_for_file) = @_;
  my($retval);
  $retval .= "mostlyclean-binarysamples:\n";
  $retval .= "\trm -f test_sample_binaries.result\n";
  for my $sample (sort keys %$target_for_file) {
    $retval .= "\trm -f $target_for_file->{$sample} $target_for_file->{$sample}.tmp\n";
    $retval .= "\t\$(srcdir)/testSampleBinary.sh --cleanup $make_sampledir$sample $config\n";
  }
  return $retval;
}


# Generate makefile rules
my @samples = find_sample_binaries $sampledir;
my($rules,%target_for_file,%target_for_base);
map {$rules .= generate_rule $_, \%target_for_file, \%target_for_base} @samples;
$rules .= "\ntest_sample_binaries.result: " . join(" ",@targets) . "\n\t\@touch \$\@\n";
$rules .= generate_cleanup_rule \%target_for_file;

# Suck in the whole makefile.
open MAKEFILE, $makefile or die "$0: $makefile: $!\n";
my $content = join "", <MAKEFILE>;
close MAKEFILE;

# Generate new file
$rules =~ s/^/\@$condition\@/mg;
$content =~ s/^\@$condition\@INSERT_SAMPLE_RULES_HERE:/$rules/m or die "$0: cannot insert dynamic rules into $makefile\n";
open MAKEFILE, ">", $makefile or die "$0: $makefile: $!\n";
print MAKEFILE $content;
close MAKEFILE
