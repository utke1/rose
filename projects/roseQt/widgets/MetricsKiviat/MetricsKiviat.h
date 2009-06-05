
#ifndef ATTRIBUTES_KIVIAT_H
#define ATTRIBUTES_KIVIAT_H


#include <QString>
#include <QList>

#include "KiviatView/KiviatView.h"

class QMouseEvent;
class QListWidget;
class QGraphicsRectItem;
class QGraphicsTextItem;

class SgNode;
class MetricsConfig;
class KiviatInfo;

class MetricsKiviat : public KiviatView
{
   Q_OBJECT

   public:
      MetricsKiviat( QWidget *parent = NULL );

      virtual ~MetricsKiviat();

      typedef QVector<SgNode *>::iterator nodes_iterator;

      nodes_iterator nodesBegin()
      {
          return nodes.begin();
      }
      nodes_iterator nodesEnd()
      {
          return nodes.end();
      }

      int getNodeId( SgNode* node )
      {
          return nodes.indexOf( node );
      }

      SgNode* getNodeFromId( int id )
      {
          return nodes[id];
      }

      void init( SgNode *root );

   signals:
      void clicked( SgNode *astNode );
      void nodeAdded( SgNode *astNode );

   public slots:
      void updateView( SgNode *astNode );
      void updateView( int id );
      
      void addNode( SgNode *astNode );
      void delNode( SgNode *astNode );
      void delNode( int nodeId );
      
      void configureMetrics( bool dialog = true );

   protected:
      virtual void mousePressEvent(QMouseEvent *ev);
      virtual void resizeEvent( QResizeEvent * ev );

   private slots:
       void configChanged()
       { configureMetrics( false ); }

   private:
      void drawData( SgNode *astNode );

      MetricsConfig *metricsConfig;

      SgNode *currentNode;
      QVector<SgNode *> nodes;

      QGraphicsRectItem *legend;
      QList<QGraphicsTextItem *> legendText;
      QList<QGraphicsRectItem *> legendColor;

      friend class KiviatInfo;
};

#endif