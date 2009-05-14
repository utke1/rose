/* -*- C++ -*-
Copyright 2006 Christoph Bonitz <christoph.bonitz@gmail.com>
          2008 Adrian Prantl <adrian@complang.tuwien.ac.at>
*/
#ifndef PROLOGTOROSE_H_
#define PROLOGTOROSE_H_
#include <satire_rose.h>
#include "termite.h"
#include "RoseEnums.h"
#include <iostream>
#include <string>
#include <map>
#include <vector>

/**
 * Class for creating a ROSE-IR (made for unparsing)
 * from its PROLOG term-representation
 */
class PrologToRose {
public:
  PrologToRose() {};
  ~PrologToRose() {};
  void unparse(std::string, std::string, std::string, SgNode*);
  SgNode* toRose(PrologTerm*);
  SgNode* toRose(const char* filename);

private:
  /* enum <-> atom conversion */
  RoseEnums re;
  /* fixups */
  std::vector<SgInitializedName*> initializedNamesWithoutScope;
  std::vector<SgDeclarationStatement*> declarationStatementsWithoutScope;
  /* our own little symbol tables */
  std::map<std::string,SgClassType*> classTypeMap;
  std::vector<SgClassDefinition*> classDefinitions;
  std::map<std::string,SgFunctionDeclaration*> funcDeclMap;
#if 0
  std::map<std::string,SgClassDeclaration*> definingClassDecls;
  std::multimap<std::string,SgClassDeclaration*> nondefiningClassDecls;
#endif
  /* arity specific node generation*/
  SgNode* leafToRose(PrologCompTerm*, std::string);
  SgNode* unaryToRose(PrologCompTerm*, std::string);
  SgNode* binaryToRose(PrologCompTerm*, std::string);
  SgNode* ternaryToRose(PrologCompTerm*, std::string);
  SgNode* quaternaryToRose(PrologCompTerm*, std::string);
  SgNode* listToRose(PrologCompTerm*, std::string);
  /*helpers*/
  void unparseFile(SgSourceFile&, std::string, std::string, SgUnparse_Info*);
  void warn_msg(std::string);
  Sg_File_Info* createFileInfo(PrologTerm*);
  SgType* createType(PrologTerm*);
  SgFunctionType* createFunctionType(PrologTerm*);
  SgMemberFunctionType* createMemberFunctionType(PrologTerm*);
  SgClassType* createClassType(PrologTerm*);
  SgPointerType* createPointerType(PrologTerm*);
  SgEnumType* createEnumType(PrologTerm*);
  SgReferenceType* createReferenceType(PrologTerm*);
  SgArrayType* createArrayType(PrologTerm*);
  PrologCompTerm* retrieveAnnotation(PrologCompTerm*);
  void abort_unless(bool, std::string);
  void debug(std::string);
  bool isValueExp(std::string);
  bool isUnaryOp(std::string);	
  bool isBinaryOp(std::string);
  SgInitializedName* inameFromAnnot(PrologCompTerm*);
  void testFileInfo(Sg_File_Info*);
  SgClassDeclaration* createDummyClassDeclaration(std::string, int);
  SgMemberFunctionDeclaration* createDummyMemberFunctionDeclaration(std::string s,int c_type); /* TODO */
  SgBitVector* createBitVector(PrologTerm*, std::map<std::string, int>);
  int createEnum(PrologTerm*, std::map<std::string, int>);

  SgLabelStatement* makeLabel(Sg_File_Info*, std::string);
  PrologInt* isPrologInt(PrologTerm*);
  PrologList* isPrologList(PrologTerm*);
  PrologCompTerm* isPrologCompTerm(PrologTerm*);
  PrologAtom* isPrologAtom(PrologTerm*);
  //PrologString* isPrologString(PrologTerm*); /* DEPRECATED */
  std::string* toStringP(PrologTerm*);
  int toInt(PrologTerm*);
  void pciDeclarationStatement(SgDeclarationStatement*,PrologTerm*);
  void fakeParentScope(SgDeclarationStatement*);
  void addSymbol(SgGlobal*,  SgDeclarationStatement*);
  void fakeClassScope(std::string, int, SgDeclarationStatement*);
  SgAccessModifier* createAccessModifier(PrologTerm*);
  SgBaseClassModifier* createBaseClassModifier(PrologTerm*);
  SgFunctionModifier* createFunctionModifier(PrologTerm*);
  SgSpecialFunctionModifier* createSpecialFunctionModifier(PrologTerm*);

  SgStorageModifier* createStorageModifier(PrologTerm*);
  SgLinkageModifier* createLinkageModifier(PrologTerm*);
  SgElaboratedTypeModifier* createElaboratedTypeModifier(PrologTerm*);
  SgConstVolatileModifier* createConstVolatileModifier(PrologTerm*);
  SgUPC_AccessModifier* createUPC_AccessModifier(PrologTerm*);
  SgTypeModifier* createTypeModifier(PrologTerm*);
  void setTypeModifier(PrologTerm*, SgTypeModifier*);
  SgDeclarationModifier* createDeclarationModifier(PrologTerm*);
  void setDeclarationModifier(PrologTerm*, SgDeclarationModifier*);
  SgModifierType* createModifierType(PrologTerm*);
  SgFunctionDeclaration* createDummyFunctionDeclaration(std::string*, PrologTerm*);
  SgFunctionSymbol* createDummyFunctionSymbol(std::string*, PrologTerm*);
  SgMemberFunctionSymbol* createDummyMemberFunctionSymbol(PrologTerm*);
  void fakeNamespaceScope(std::string, int, SgDeclarationStatement*);
  SgTypedefType* createTypedefType(PrologTerm*);
  /* type specific node generation */
  /*unary nodes*/
  SgExpression* createValueExp(Sg_File_Info*, SgNode*, PrologCompTerm*);
  SgUnaryOp* createUnaryOp(Sg_File_Info*, SgNode*, PrologCompTerm*);
  SgSourceFile* createFile(Sg_File_Info*, SgNode*, PrologCompTerm*);
  SgReturnStmt* createReturnStmt(Sg_File_Info*, SgNode*, PrologCompTerm*);
  SgFunctionDefinition* createFunctionDefinition(Sg_File_Info*, SgNode*, PrologCompTerm*);
  SgInitializedName* createInitializedName(Sg_File_Info*, SgNode*, PrologCompTerm*);
  SgAssignInitializer* createAssignInitializer(Sg_File_Info*, SgNode*, PrologCompTerm*);
  SgExprStatement* createExprStatement(Sg_File_Info*, SgNode*, PrologCompTerm*);
  SgDefaultOptionStmt* createDefaultOptionStmt(Sg_File_Info*, SgNode*, PrologCompTerm*);
  SgClassDeclaration* createClassDeclaration(Sg_File_Info*, SgNode*, PrologCompTerm*);
  SgDeleteExp* createDeleteExp(Sg_File_Info*, SgNode*, PrologCompTerm*);
  SgVarArgOp* createVarArgOp(Sg_File_Info*, SgNode*, PrologCompTerm*);
  SgVarArgStartOneOperandOp* createVarArgStartOneOperandOp(Sg_File_Info*, SgNode*, PrologCompTerm*);
  SgVarArgEndOp* createVarArgEndOp(Sg_File_Info*, SgNode*, PrologCompTerm*);
  SgAggregateInitializer* createAggregateInitializer(Sg_File_Info*, SgNode*, PrologCompTerm*);
  SgNamespaceDeclarationStatement* createNamespaceDeclarationStatement(Sg_File_Info*, SgNode*, PrologCompTerm*);
  SgSizeOfOp* createSizeOfOp(Sg_File_Info*, SgNode*, PrologCompTerm*);
  SgConstructorInitializer* createConstructorInitializer(Sg_File_Info*, SgNode*, PrologCompTerm*);
  SgPragmaDeclaration* createPragmaDeclaration(Sg_File_Info*, SgNode*, PrologCompTerm*);
	
  /*binary nodes*/
  SgFunctionDeclaration* createFunctionDeclaration(Sg_File_Info*, SgNode*, SgNode*, PrologCompTerm*);
  SgBinaryOp* createBinaryOp(Sg_File_Info*, SgNode*, SgNode*, PrologCompTerm*);
  SgSwitchStatement* createSwitchStatement(Sg_File_Info*, SgNode*, SgNode*, PrologCompTerm*);
  SgDoWhileStmt* createDoWhileStmt(Sg_File_Info*, SgNode*, SgNode*, PrologCompTerm*);
  SgWhileStmt* createWhileStmt(Sg_File_Info*, SgNode*, SgNode*, PrologCompTerm*);
  SgVarArgCopyOp* createVarArgCopyOp(Sg_File_Info*, SgNode*, SgNode*, PrologCompTerm*);
  SgVarArgStartOp* createVarArgStartOp(Sg_File_Info*, SgNode*, SgNode*, PrologCompTerm*);
  SgFunctionCallExp* createFunctionCallExp(Sg_File_Info*, SgNode*, SgNode*, PrologCompTerm*);
  SgTryStmt* createTryStmt(Sg_File_Info*, SgNode*, SgNode*, PrologCompTerm*);
  SgCatchOptionStmt* createCatchOptionStmt(Sg_File_Info*, SgNode*, SgNode*, PrologCompTerm*);
  /*ternary nodes*/
  SgIfStmt* createIfStmt(Sg_File_Info*,  SgNode*,  SgNode*,  SgNode*,  PrologCompTerm*);
  SgCaseOptionStmt* createCaseOptionStmt(Sg_File_Info*, SgNode*, SgNode*, SgNode*, PrologCompTerm*);
  SgMemberFunctionDeclaration* createMemberFunctionDeclaration(Sg_File_Info*, SgNode*, SgNode*, SgNode*, PrologCompTerm*);
  SgNewExp* createNewExp(Sg_File_Info*, SgNode*, SgNode*, SgNode*, PrologCompTerm*);
  SgConditionalExp* createConditionalExp(Sg_File_Info*, SgNode*, SgNode*, SgNode*, PrologCompTerm*);
  /*quaternary nodes*/
  SgForStatement* createForStatement(Sg_File_Info*, SgNode*, SgNode*, SgNode*, SgNode*, PrologCompTerm*);
  /*list nodes*/
  SgFunctionParameterList* createFunctionParameterList(Sg_File_Info*,  std::deque<SgNode*>*);
  SgBasicBlock* createBasicBlock(Sg_File_Info*, std::deque<SgNode*>*);
  SgGlobal* createGlobal(Sg_File_Info*, std::deque<SgNode*>*);
  SgProject* createProject(Sg_File_Info*, std::deque<SgNode*>*);
  SgVariableDeclaration* createVariableDeclaration(Sg_File_Info*, std::deque<SgNode*>*, PrologCompTerm*);
  SgForInitStatement* createForInitStatement(Sg_File_Info*, std::deque<SgNode*>*);
  SgClassDefinition* createClassDefinition(Sg_File_Info*, std::deque<SgNode*>*, PrologCompTerm* t);
  SgCtorInitializerList* createCtorInitializerList(Sg_File_Info*, std::deque<SgNode*>*);
  SgEnumDeclaration* createEnumDeclaration(Sg_File_Info*, std::deque<SgNode*>*, PrologCompTerm*);
  SgExprListExp* createExprListExp(Sg_File_Info*, std::deque<SgNode*>*);
  SgNamespaceDefinitionStatement* createNamespaceDefinitionStatement(Sg_File_Info*, std::deque<SgNode*>*);
  SgCatchStatementSeq* createCatchStatementSeq(Sg_File_Info*, std::deque<SgNode*>*);
  /*leaf nodes*/
  SgVarRefExp* createVarRefExp(Sg_File_Info*, PrologCompTerm*);
  SgBreakStmt* createBreakStmt(Sg_File_Info*, PrologCompTerm*);
  SgContinueStmt* createContinueStmt(Sg_File_Info*, PrologCompTerm*);
  SgLabelStatement* createLabelStatement(Sg_File_Info*, PrologCompTerm*);
  SgGotoStatement* createGotoStatement(Sg_File_Info*, PrologCompTerm*);
  SgRefExp* createRefExp(Sg_File_Info*, PrologCompTerm*);
  SgFunctionRefExp* createFunctionRefExp(Sg_File_Info*, PrologCompTerm*);
  SgMemberFunctionRefExp* createMemberFunctionRefExp(Sg_File_Info*, PrologCompTerm*);
  SgThisExp* createThisExp(Sg_File_Info*, PrologCompTerm*);
  SgTypedefDeclaration* createTypedefDeclaration(Sg_File_Info*, PrologCompTerm*);
  SgPragma* createPragma(Sg_File_Info*, PrologCompTerm*);
  char unescape_char(std::string s);
};
#endif
