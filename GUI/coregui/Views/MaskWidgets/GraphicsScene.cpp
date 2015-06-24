#include "GraphicsScene.h"
#include "Rectangle.h"
#include "Ellipse.h"
#include "Polygon.h"
#include "RectangleItem.h"
#include "RectangleView.h"
#include "MaskModel.h"
#include <QItemSelection>
GraphicsScene::GraphicsScene()
    : m_maskModel(new MaskModel)
    , m_rectangleItem(0), m_ellipse(0), m_polygon(0), isFinished(true),
      m_currentMousePosition(QPointF(0, 0)), m_lastAddedPoint(QPointF(0, 0)), m_block_selection(false)
{
    m_drawing = NONE;
    connect(this, SIGNAL(selectionChanged()), this, SLOT(onSceneSelectionChanged()));
    connect(m_maskModel, SIGNAL(modelAboutToBeReset()), this, SLOT(resetScene()));
    connect(m_maskModel, SIGNAL(rowsInserted(QModelIndex, int,int)), this, SLOT(onRowsInserted(QModelIndex, int,int)));
    connect(m_maskModel, SIGNAL(rowsAboutToBeRemoved(QModelIndex, int,int)), this, SLOT(onRowsAboutToBeRemoved(QModelIndex,int,int)));
    connect(m_maskModel, SIGNAL(rowsRemoved(QModelIndex, int,int)), this, SLOT(onRowsRemoved(QModelIndex, int,int)));
    connect(m_maskModel, SIGNAL(modelReset()), this, SLOT(updateScene()));
}

void GraphicsScene::setDrawing(GraphicsScene::Drawing drawing)
{
    m_drawing = drawing;
}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
//    qDebug() << "GraphicsScene::mousePressEvent() ->" << m_drawing << m_rectangle;
    if (m_drawing == RECTANGLE) {
//        m_rectangle = new Rectangle(event->scenePos().x(), event->scenePos().y(), 0, 0);
//        addItem(m_rectangle);
        m_rectangleItem = m_maskModel->insertNewItem(Constants::RectangleType);
        m_rectangleItem->setRegisteredProperty(RectangleItem::P_POSX, event->scenePos().x());
        m_rectangleItem->setRegisteredProperty(RectangleItem::P_POSY, event->scenePos().y());
        resetScene();
        updateScene();
    } else if (m_drawing == ELLIPSE) {
        m_ellipse = new Ellipse(event->scenePos().x(), event->scenePos().y(), 0, 0);
        addItem(m_ellipse);
    } else if (m_drawing == POLYGON) {
        if (isFinished) {
            m_polygon = new Polygon(event->scenePos().x(), event->scenePos().y(), 0, 0);
            addItem(m_polygon);
            m_polygon->setDrawingMode(event->scenePos());
            m_lastAddedPoint = event->scenePos();
            isFinished = false;
        } else {
            m_polygon->setDrawingMode(event->scenePos());;
        }
        isFinished = !m_polygon->getDrawingMode();
    }
    m_lastAddedPoint = event->scenePos();
    QGraphicsScene::mousePressEvent(event);
}

void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
//    qDebug() << "GraphicsScene::mouseMoveEvent() ->" << m_drawing << m_rectangle;
    if (m_drawing == RECTANGLE && m_rectangleItem) {
//        m_rectangle->setWidth(m_rectangle->boundingRect().left() -  event->pos().x());
//        m_rectangle->setHeigth(m_rectangle->boundingRect().top() - event->pos().y());
        m_rectangleItem->setRegisteredProperty(RectangleItem::P_WIDTH, event->scenePos().x() - m_rectangleItem->getRegisteredProperty(RectangleItem::P_POSX).toDouble());
        m_rectangleItem->setRegisteredProperty(RectangleItem::P_HEIGHT, event->scenePos().y() - m_rectangleItem->getRegisteredProperty(RectangleItem::P_POSY).toDouble());
    } else if (m_drawing == ELLIPSE && m_ellipse) {
        m_ellipse->setWidth(event->scenePos().x() - m_ellipse->boundingRect().topLeft().x());
        m_ellipse->setHeigth(event->scenePos().y() - m_ellipse->boundingRect().topLeft().y());
    } else if (m_drawing == POLYGON && m_polygon) {
        if (m_polygon->getFirstPoint().contains(event->scenePos())) {
            m_polygon->setMouseIsOverFirstPoint(true);
        }
        else {
            m_polygon->setMouseIsOverFirstPoint(false);
        }
    } else {
        QGraphicsScene::mouseMoveEvent(event);
    }
    m_currentMousePosition = event->scenePos();
}

void GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
//    qDebug() << "GraphicsScene::mouseReleaseEvent() ->" << m_drawing << m_rectangle;
    m_rectangleItem = 0;
    m_ellipse = 0;

    QGraphicsScene::mouseReleaseEvent(event);
}

void GraphicsScene::drawForeground(QPainter *painter, const QRectF & /* rect */)
{
    if (m_drawing == POLYGON && !isFinished) {
        painter->setPen(QPen(Qt::black, 1, Qt::DashLine));
        painter->drawLine(QLineF(m_lastAddedPoint, m_currentMousePosition));
        invalidate();
    } else {
        m_lastAddedPoint = m_currentMousePosition;
    }
}

void GraphicsScene::updateViews(const QModelIndex &parentIndex)
{
    Q_ASSERT(m_maskModel);

    for( int i_row = 0; i_row < m_maskModel->rowCount( parentIndex ); ++i_row) {
         QModelIndex itemIndex = m_maskModel->index( i_row, 0, parentIndex );

         if (ParameterizedItem *item = m_maskModel->itemForIndex(itemIndex)){
                addViewForItem(item);
         }
    }

}

QGraphicsItem *GraphicsScene::addViewForItem(ParameterizedItem *item)
{
    qDebug() << "QGraphicsItem *GraphicsScene::addViewForItem(ParameterizedItem *item)-> runing";
    RectangleView *view = new RectangleView();
    view->setItem(item);
//    connect(view, SIGNAL(xChanged()), this, SLOT(positionChanged(view)));
    addItem(view);\
    m_ItemToView.insert(item, view);
    return view;
}


void GraphicsScene::setMaskModel(MaskModel *maskModel)
{
    m_maskModel = maskModel;
    connect(m_maskModel, SIGNAL(modelAboutToBeReset()), this, SLOT(resetScene()));
    connect(m_maskModel, SIGNAL(rowsInserted(QModelIndex, int,int)), this, SLOT(onRowsInserted(QModelIndex, int,int)));
    connect(m_maskModel, SIGNAL(rowsAboutToBeRemoved(QModelIndex, int,int)), this, SLOT(onRowsAboutToBeRemoved(QModelIndex,int,int)));
    connect(m_maskModel, SIGNAL(rowsRemoved(QModelIndex, int,int)), this, SLOT(onRowsRemoved(QModelIndex, int,int)));
    connect(m_maskModel, SIGNAL(modelReset()), this, SLOT(updateScene()));

    updateScene();
}

void GraphicsScene::updateScene()
{
    updateViews();
}

void GraphicsScene::resetScene()
{
    qDebug() << "DesignerScene::resetScene()";
    clear();
    m_ItemToView.clear();
}

void GraphicsScene::setListView(QListView *listview)
{
    m_listView = listview;
    m_listView->setModel(m_maskModel);
    m_selectionModel =  m_listView->selectionModel();

    connect(m_selectionModel,
            SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            this,
            SLOT(onSessionSelectionChanged(QItemSelection,QItemSelection)) );

}


void GraphicsScene::onSessionSelectionChanged(const QItemSelection & , const QItemSelection &)
{
    if(m_block_selection) return;

    qDebug() << "GraphicsScene::SelectionChanged()";
    m_block_selection = true;

    for(QMap<ParameterizedItem *, IView *>::iterator it=m_ItemToView.begin(); it!= m_ItemToView.end(); ++it) {
        QModelIndex index = m_maskModel->indexOfItem(it.key());
        if(index.isValid()) {
            if(m_selectionModel->isSelected(index)) {
                it.value()->setSelected(true);
            } else {
                it.value()->setSelected(false);
            }
        }
    }

    m_block_selection = false;
}


void GraphicsScene::onRowsAboutToBeRemoved(const QModelIndex &parent, int first, int last)
{
    m_block_selection = true;
    qDebug() << "GraphicsScene::onRowsAboutToBeRemoved()" << parent << first << last;
    for(int irow = first; irow<=last; ++irow ) {
        QModelIndex itemIndex = m_maskModel->index(irow, 0, parent);
        deleteViews(itemIndex); // deleting all child items
    }
    m_block_selection = false;
}

void GraphicsScene::deleteViews(const QModelIndex & parentIndex)
{
    qDebug() << "GraphicsScene::deleteViews()" << parentIndex;

    for( int i_row = 0; i_row < m_maskModel->rowCount( parentIndex ); ++i_row) {
         QModelIndex itemIndex = m_maskModel->index( i_row, 0, parentIndex );

         if (ParameterizedItem *item = m_maskModel->itemForIndex(itemIndex)){

             removeItemViewFromScene(item);

         } else {
             qDebug() << "not a parameterized graphics item";
         }
         deleteViews( itemIndex);
     }
    removeItemViewFromScene(m_maskModel->itemForIndex(parentIndex)); // deleting parent item
}

//! removes view from scene corresponding to given item
void GraphicsScene::removeItemViewFromScene(ParameterizedItem *item)
{
    qDebug() << "DesignerScene::removeItemFromScene()" << item->modelType();
    for(QMap<ParameterizedItem *, IView *>::iterator it=m_ItemToView.begin(); it!=m_ItemToView.end(); ++it) {
        if(it.key() == item) {
            IView *view = it.value();
            view->setSelected(false);
            m_ItemToView.erase(it);
            emit view->aboutToBeDeleted();
            view->deleteLater();
            update();
            break;
        }
    }
}

void GraphicsScene::onRowsRemoved(const QModelIndex &/* parent */, int /* first */, int /* last */)
{
    updateScene();
}


void GraphicsScene::deleteSelectedItems()
{
    qDebug() << "DesignerScene::deleteSelectedItems() 1.1" << selectedItems().size();

    QModelIndexList indexes = m_selectionModel->selectedIndexes();

    qDebug() << "AAA" << indexes.size();
    QList<IView *> views_which_will_be_deleted;
    foreach(QModelIndex index, indexes) {
        views_which_will_be_deleted.append(m_ItemToView[m_maskModel->itemForIndex(index)]);
    }

    // deleting selected items on model side, corresponding views will be deleted automatically
    // Since we don't know the order of items, we need this
    while(indexes.size()) {
        m_maskModel->removeRows(indexes.back().row(), 1, indexes.back().parent());
        indexes = m_selectionModel->selectedIndexes();
    }
}

//! propagate selection from scene to model
void GraphicsScene::onSceneSelectionChanged()
{
    qDebug() << "DesignerScene::onSceneSelectionChanged() 1.1";
    if(m_block_selection) return;

    m_block_selection = true;

    m_selectionModel->clearSelection();
    QList<QGraphicsItem*> selected = selectedItems();
    for(int i=0; i<selected.size(); ++i) {
        IView *view = dynamic_cast<IView *>(selected[i]);
        if(view) {
            ParameterizedItem *sampleItem = view->getParameterizedItem();
            QModelIndex itemIndex = m_maskModel->indexOfItem(sampleItem);
            Q_ASSERT(itemIndex.isValid());
            if(!m_selectionModel->isSelected(itemIndex))
                m_selectionModel->select(itemIndex, QItemSelectionModel::Select);
            //break; // selection of only one item will be propagated to the model
        }
    }

    m_block_selection = false;
}

void GraphicsScene::onRowsInserted(const QModelIndex &/* parent */, int /* first */, int /* last */ )
{
    updateScene();
}

