#include "MaskGraphicsScene.h"
#include "RectangleItem.h"
#include "RectangleView.h"
#include "EllipseItem.h"
#include "PolygonItem.h"
#include "PointItem.h"
#include "MaskModel.h"
#include "SampleViewFactory.h"
#include <QItemSelection>
#include <cmath>
#include <sstream>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QTreeView>
#include <QPainter>
#include <QGraphicsProxyWidget>

MaskGraphicsScene::MaskGraphicsScene()
    : m_maskModel(0), m_currentItem(0), m_currentMousePosition(QPointF(0, 0)),
      m_lastAddedPoint(QPointF(0, 0)), m_block_selection(false)
{
//    setSceneRect(QRectF(-800, 0, 1600, 1600));
    m_drawingMode = NONE;
}

void MaskGraphicsScene::setDrawing(DrawingMode drawingMode)
{
    m_drawingMode = drawingMode;
}

void MaskGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        if (m_drawingMode == RECTANGLE) {
            m_currentItem = m_maskModel->insertNewItem(Constants::RectangleType);
            m_currentItem->setRegisteredProperty(RectangleItem::P_POSX, event->scenePos().x());
            m_currentItem->setRegisteredProperty(RectangleItem::P_POSY, event->scenePos().y());
            setItemName(m_currentItem);
        } else if (m_drawingMode == ELLIPSE) {
            m_currentItem = m_maskModel->insertNewItem(Constants::EllipseType);
            m_currentItem->setRegisteredProperty(EllipseItem::P_POSX, event->scenePos().x());
            m_currentItem->setRegisteredProperty(EllipseItem::P_POSY, event->scenePos().y());
            setItemName(m_currentItem);
        } else if (m_drawingMode == POLYGON) {
            if (!m_currentItem) {
                m_currentItem = m_maskModel->insertNewItem(Constants::PolygonType);
                m_currentItem->setRegisteredProperty(PolygonItem::P_DRAWINGMODE, true);
                setItemName(m_currentItem);
            }
            if (numberOfPoints() > 2 && firstPointContainsMouseClick(event)) {
                m_currentItem->setRegisteredProperty(PolygonItem::P_DRAWINGMODE, false);
//                m_ItemToView[m_currentItem]->setZValue(m_maskModel->rowCount(QModelIndex()));
                m_maskModel->moveParameterizedItem(m_currentItem, 0, 0);
                m_currentItem = 0;
                m_drawingMode = NONE;
                emit itemIsDrawn();
            }
            else if(m_currentItem) {
                ParameterizedItem *pointItem = m_maskModel->insertNewItem(Constants::PointType,
                                                         m_maskModel->indexOfItem(m_currentItem));
                pointItem->setRegisteredProperty(PointItem::P_POSX, event->scenePos().x());
                pointItem->setRegisteredProperty(PointItem::P_POSY, event->scenePos().y());
            }
        }
        else {
            QGraphicsScene::mousePressEvent(event);
        }
    }
    m_lastAddedPoint = event->scenePos();
}

void MaskGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (m_drawingMode == RECTANGLE && m_currentItem) {
        checkDrawingDirection(event);
    } else if (m_drawingMode == ELLIPSE && m_currentItem) {
      checkDrawingDirection(event);
    }
    else {
        QGraphicsScene::mouseMoveEvent(event);
    }
    m_currentMousePosition = event->scenePos();
}

void MaskGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    bool drawingToSmall = false;
    if (m_drawingMode == RECTANGLE && m_currentItem) {
//        qreal xDifference = m_currentItem->getRegisteredProperty(RectangleItem::P_POSX).toReal()
//                            - event->scenePos().x();
//        qreal yDifference = m_currentItem->getRegisteredProperty(RectangleItem::P_POSY).toReal()
//                            - event->scenePos().y();
        if (std::abs(m_currentItem->getRegisteredProperty(RectangleItem::P_WIDTH).toReal()) <= 10 &&
            std::abs(m_currentItem->getRegisteredProperty(RectangleItem::P_HEIGHT).toReal()) <= 10){
            QModelIndex index = m_maskModel->indexOfItem(m_currentItem);
            m_maskModel->removeRows(index.row(), 1, index.parent());
            drawingToSmall = true;
        }
    } else if (m_drawingMode == ELLIPSE && m_currentItem) {
//        qreal xDifference = m_currentItem->getRegisteredProperty(EllipseItem::P_POSX).toReal()
//                            - event->scenePos().x();
//        qreal yDifference = m_currentItem->getRegisteredProperty(EllipseItem::P_POSY).toReal()
//                            - event->scenePos().y();
        if (std::abs(m_currentItem->getRegisteredProperty(EllipseItem::P_WIDTH).toReal()) <= 10 &&
                std::abs(m_currentItem->getRegisteredProperty(EllipseItem::P_HEIGHT).toReal()) <= 10) {
            QModelIndex index = m_maskModel->indexOfItem(m_currentItem);
            m_maskModel->removeRows(index.row(), 1, index.parent());
            drawingToSmall = true;
        }
    }

    if (m_drawingMode == RECTANGLE || m_drawingMode == ELLIPSE) {
//        m_maskModel->moveParameterizedItem(m_currentItem, 0, 0);
        m_currentItem = 0;
        if(!drawingToSmall) {
            emit itemIsDrawn();
        }
    }
    QGraphicsScene::mouseReleaseEvent(event);
}

void MaskGraphicsScene::drawForeground(QPainter *painter, const QRectF & /* rect */)
{
    if (m_drawingMode == POLYGON && m_currentItem) {
        if(numberOfPoints() == 0) {
            m_lastAddedPoint = m_currentMousePosition;
        }
        painter->setPen(QPen(Qt::black, 1, Qt::DashLine));
        painter->drawLine(QLineF(m_lastAddedPoint, m_currentMousePosition));
        invalidate();
    }
    else {
        m_lastAddedPoint = m_currentMousePosition;
    }

}

void MaskGraphicsScene::updateViews(const QModelIndex &parentIndex)
{
    Q_ASSERT(m_maskModel);

    for (int i_row = 0; i_row < m_maskModel->rowCount(parentIndex); ++i_row) {
        QModelIndex itemIndex = m_maskModel->index(i_row, 0, parentIndex);

        if (ParameterizedItem *item = m_maskModel->itemForIndex(itemIndex)) {
            addViewForItem(item);
        }
    }
}

IView *MaskGraphicsScene::addViewForItem(ParameterizedItem *item)
{
    qDebug() << "GraphicsScene::addViewForItem() ->" << item->modelType() << item;
    Q_ASSERT(item);

    IView *view = m_ItemToView[item];
    if (!view) {
        qDebug() << "       GraphicsScene::addViewForItem() -> Creating view for item"
                 << item->modelType();
        view = SampleViewFactory::createSampleView(item->modelType());
        if (view) {
            m_ItemToView[item] = view;
            view->setParameterizedItem(item);
            addItem(view);
            return view;
        }
    } else {
        qDebug() << "       GraphicsScene::addViewForItem() -> View for item exists."
                 << item->modelType();
    }
    return view;
}

void MaskGraphicsScene::updateScene()
{
    if(this->items().size() > 0) {
        m_colorMap = this->items().at(0);
        updateViews();
        setZValues();
        addItem(m_colorMap);
    }
    else {
        updateViews();
        setZValues();
    }
}

void MaskGraphicsScene::resetScene()
{
    qDebug() << "GraphicsScene::resetScene()";
    clear();
    m_ItemToView.clear();
}

void MaskGraphicsScene::setSelectionModel(QItemSelectionModel *selectionModel)
{
    m_selectionModel = selectionModel;

    connect(m_selectionModel, SIGNAL(selectionChanged(QItemSelection, QItemSelection)), this,
            SLOT(onSessionSelectionChanged(QItemSelection, QItemSelection)));
}

void MaskGraphicsScene::setModel(MaskModel *maskModel)
{
    if(m_maskModel) {
        disconnect(this, SIGNAL(selectionChanged()), this, SLOT(onSceneSelectionChanged()));
        disconnect(m_maskModel, SIGNAL(modelAboutToBeReset()), this, SLOT(resetScene()));
        disconnect(m_maskModel, SIGNAL(rowsInserted(QModelIndex, int, int)), this,
                SLOT(onRowsInserted(QModelIndex, int, int)));
        disconnect(m_maskModel, SIGNAL(rowsAboutToBeRemoved(QModelIndex, int, int)), this,
                SLOT(onRowsAboutToBeRemoved(QModelIndex, int, int)));
        disconnect(m_maskModel, SIGNAL(rowsRemoved(QModelIndex, int, int)), this,
                SLOT(onRowsRemoved(QModelIndex, int, int)));
        disconnect(m_maskModel, SIGNAL(modelReset()), this, SLOT(updateScene()));
    }

    m_maskModel = maskModel;

    connect(this, SIGNAL(selectionChanged()), this, SLOT(onSceneSelectionChanged()));
    connect(m_maskModel, SIGNAL(modelAboutToBeReset()), this, SLOT(resetScene()));
    connect(m_maskModel, SIGNAL(rowsInserted(QModelIndex, int, int)), this,
            SLOT(onRowsInserted(QModelIndex, int, int)));
    connect(m_maskModel, SIGNAL(rowsAboutToBeRemoved(QModelIndex, int, int)), this,
            SLOT(onRowsAboutToBeRemoved(QModelIndex, int, int)));
    connect(m_maskModel, SIGNAL(rowsRemoved(QModelIndex, int, int)), this,
            SLOT(onRowsRemoved(QModelIndex, int, int)));
    connect(m_maskModel, SIGNAL(modelReset()), this, SLOT(updateScene()));

    resetScene();
    updateScene();
}

void MaskGraphicsScene::onSessionSelectionChanged(const QItemSelection &, const QItemSelection &)
{
    if (m_block_selection)
        return;

    qDebug() << "GraphicsScene::SelectionChanged()";
    m_block_selection = true;

    for (QMap<ParameterizedItem *, IView *>::iterator it = m_ItemToView.begin();
         it != m_ItemToView.end(); ++it) {
        QModelIndex index = m_maskModel->indexOfItem(it.key());
        if (index.isValid()) {
            if (m_selectionModel->isSelected(index)) {
                it.value()->setSelected(true);
            } else {
                it.value()->setSelected(false);
            }
        }
    }

    m_block_selection = false;
}

void MaskGraphicsScene::onRowsAboutToBeRemoved(const QModelIndex &parent, int first, int last)
{
    m_block_selection = true;
    qDebug() << "GraphicsScene::onRowsAboutToBeRemoved()" << parent << first << last;
    for (int irow = first; irow <= last; ++irow) {
        QModelIndex itemIndex = m_maskModel->index(irow, 0, parent);
        deleteViews(itemIndex); // deleting all child items
    }
    m_block_selection = false;
}

void MaskGraphicsScene::deleteViews(const QModelIndex &parentIndex)
{
    qDebug() << "GraphicsScene::deleteViews()" << parentIndex;

    for (int i_row = 0; i_row < m_maskModel->rowCount(parentIndex); ++i_row) {
        QModelIndex itemIndex = m_maskModel->index(i_row, 0, parentIndex);

        if (ParameterizedItem *item = m_maskModel->itemForIndex(itemIndex)) {

            removeItemViewFromScene(item);

        } else {
            qDebug() << "not a parameterized graphics item";
        }
        deleteViews(itemIndex);
    }
    removeItemViewFromScene(m_maskModel->itemForIndex(parentIndex)); // deleting parent item
}

//! removes view from scene corresponding to given item
void MaskGraphicsScene::removeItemViewFromScene(ParameterizedItem *item)
{
    qDebug() << "GraphicsScene::removeItemFromScene()" << item->modelType();
    for (QMap<ParameterizedItem *, IView *>::iterator it = m_ItemToView.begin();
         it != m_ItemToView.end(); ++it) {
        if (it.key() == item) {
            IView *view = it.value();
            view->setSelected(false);
            m_ItemToView.erase(it);
            emit view->aboutToBeDeleted();
            delete view;
            update();
            break;
        }
    }
}

void MaskGraphicsScene::onRowsRemoved(const QModelIndex &/* parent */, int /* first */, int /* last */)
{
    updateScene();
}

void MaskGraphicsScene::deleteSelectedItems()
{
    qDebug() << "GraphicsScene::deleteSelectedItems() 1.1" << selectedItems().size();

    QModelIndexList indexes = m_selectionModel->selectedIndexes();

    // deleting selected items on model side, corresponding views will be deleted automatically
    // Since we don't know the order of items, we need this
    while (indexes.size()) {
        m_maskModel->removeRows(indexes.back().row(), 1, indexes.back().parent());
        indexes = m_selectionModel->selectedIndexes();
    }
}

//! propagate selection from scene to model
void MaskGraphicsScene::onSceneSelectionChanged()
{
    qDebug() << "GraphicsScene::onSceneSelectionChanged() 1.1";
    if (m_block_selection)
        return;

    m_block_selection = true;

    m_selectionModel->clearSelection();
    QList<QGraphicsItem *> selected = selectedItems();
    for (int i = 0; i < selected.size(); ++i) {
        IView *view = dynamic_cast<IView *>(selected[i]);
        if (view) {
            ParameterizedItem *sampleItem = view->getParameterizedItem();
            QModelIndex itemIndex = m_maskModel->indexOfItem(sampleItem);
            Q_ASSERT(itemIndex.isValid());
            if (!m_selectionModel->isSelected(itemIndex))
                m_selectionModel->select(itemIndex, QItemSelectionModel::Select);
            // break; // selection of only one item will be propagated to the model
        }
    }

    m_block_selection = false;
}

void MaskGraphicsScene::onRowsInserted(const QModelIndex & /* parent */, int /* first */, int /* last */)
{
    updateScene();
}

void MaskGraphicsScene::setItemName(ParameterizedItem *item)
{
    int numberOfItems(0);
    QMap<ParameterizedItem *, IView *>::iterator it;
    for(it = m_ItemToView.begin(); it != m_ItemToView.end(); ++it) {
        if(item->modelType() == it.key()->modelType()) {
            numberOfItems ++;
        }
    }
    QString name = item->itemName().append(QString("%1")).arg(numberOfItems);
    item->setItemName(name);
}

int MaskGraphicsScene::numberOfPoints()
{
    if(m_drawingMode == POLYGON) {
        int items = m_currentItem->childItems().length();
        return items;
    }
    else {
        return 0;
    }
}

bool MaskGraphicsScene::firstPointContainsMouseClick(QGraphicsSceneMouseEvent *event)
{
    QRectF firstPoint(
        m_currentItem->childItems()[0]->getRegisteredProperty(PointItem::P_POSX).toReal() - 2.5,
        m_currentItem->childItems()[0]->getRegisteredProperty(PointItem::P_POSY).toReal() - 2.5,
        5, 5);

    if(firstPoint.contains(event->scenePos())) {
        ParameterizedItem *pointItem = m_maskModel->insertNewItem(Constants::PointType,
                                                 m_maskModel->indexOfItem(m_currentItem));
        pointItem->setRegisteredProperty(PointItem::P_POSX, firstPoint.center().x());
        pointItem->setRegisteredProperty(PointItem::P_POSY, firstPoint.center().y());
        return true;
    }

    else {
        return false;
    }
}

void MaskGraphicsScene::onBringToFront()
{
    QModelIndexList indexes = m_selectionModel->selectedIndexes();

    for(int i = 0; i < indexes.size(); i++) {
        ParameterizedItem *item =  m_maskModel->itemForIndex(indexes.at(i));
        int row = indexes.at(i).row() -1;

        if(m_maskModel->rowCount(QModelIndex()) == 0) {
            return;
        }
        else {
            qreal x =  m_ItemToView[item]->pos().x();
            qreal y = m_ItemToView[item]->pos().y();
            m_maskModel->moveParameterizedItem(item, 0, row);

            QModelIndex movedItemIndex = m_maskModel->index(row,0,QModelIndex());
            ParameterizedItem *movedItem =  m_maskModel->itemForIndex(movedItemIndex);
            m_ItemToView[movedItem]->setPos(x,y);
        }
    }
}

void MaskGraphicsScene::onSendToBack()
{
    QModelIndexList indexes = m_selectionModel->selectedIndexes();
    qDebug() << "MaskGraphicsScene::onSendToBack()" << indexes.size();
    for(int i = 0; i < indexes.size(); i++) {
        ParameterizedItem *item =  m_maskModel->itemForIndex(indexes.at(i));
        int row = indexes.at(i).row() + 2;

        if(indexes.at(i).row() == m_maskModel->rowCount(QModelIndex()) -1 ) {
            return;
        }
        else {
            qreal x =  m_ItemToView[item]->pos().x();
            qreal y = m_ItemToView[item]->pos().y();
            m_maskModel->moveParameterizedItem(item, 0, row);

            QModelIndex movedItemIndex = m_maskModel->index(row -1 ,0,QModelIndex());
            ParameterizedItem *movedItem =  m_maskModel->itemForIndex(movedItemIndex);
            m_ItemToView[movedItem]->setPos(x,y);
        }

    }
}

void MaskGraphicsScene::setZValues()
{
    for(int i = 0; i < m_maskModel->rowCount(QModelIndex()); i++) {
        QModelIndex indexes = m_maskModel->index(i, 0, QModelIndex());
        ParameterizedItem *item =  m_maskModel->itemForIndex(indexes);
        m_ItemToView[item]->setZValue(m_maskModel->rowCount(QModelIndex()) -  indexes.row() + 1);
    }
}

void MaskGraphicsScene::checkDrawingDirection(QGraphicsSceneMouseEvent *event)
{

   qreal xmin = std::min(m_currentItem->getRegisteredProperty(RectangleItem::P_POSX).toReal(),
                         event->scenePos().x());
   qreal xmax = std::max(m_currentItem->getRegisteredProperty(RectangleItem::P_POSX).toReal(),
                         event->scenePos().x());

   qreal ymin = std::min(m_currentItem->getRegisteredProperty(RectangleItem::P_POSY).toReal(),
                         event->scenePos().y());
   qreal ymax = std::max(m_currentItem->getRegisteredProperty(RectangleItem::P_POSY).toReal(),
                         event->scenePos().y());

   m_currentItem->setRegisteredProperty(RectangleItem::P_WIDTH, xmax - xmin);
   m_currentItem->setRegisteredProperty(RectangleItem::P_HEIGHT, ymax - ymin);
   m_currentItem->setRegisteredProperty(RectangleItem::P_POSX, xmin);
   m_currentItem->setRegisteredProperty(RectangleItem::P_POSY, ymin);


//    // top left corner
//    if(event->scenePos().x() < getTopRightCorner().x() &&
//            event->scenePos().y() <  getBottomLeftCorner().y()) {
//        m_currentItem->setRegisteredProperty(RectangleItem::P_WIDTH,
//                                             getTopRightCorner().x() - event->scenePos().x());
//        m_currentItem->setRegisteredProperty(RectangleItem::P_HEIGHT,
//                                             getBottomLeftCorner().y() - event->scenePos().y());
//        m_currentItem->setRegisteredProperty(RectangleItem::P_POSX, event->scenePos().x());
//        m_currentItem->setRegisteredProperty(RectangleItem::P_POSY, event->scenePos().y());

//    }
//    //bottom right
//    if(event->scenePos().x() > getBottomLeftCorner().x() &&
//            event->scenePos().y() > getTopRightCorner().y()){
//        m_currentItem->setRegisteredProperty(RectangleItem::P_WIDTH, event->scenePos().x()
//                - getTopLeftCorner().x());
//        m_currentItem->setRegisteredProperty(RectangleItem::P_HEIGHT, event->scenePos().y()
//                - getTopLeftCorner().y());
//    }
//    // top right corner
//   if(event->scenePos().x() > getTopLeftCorner().x()
//            && event->scenePos().y() <  getBottomRightCorner().y()) {
//        m_currentItem->setRegisteredProperty(RectangleItem::P_WIDTH, event->scenePos().x()
//                                      -  getTopLeftCorner().x());
//        m_currentItem->setRegisteredProperty(RectangleItem::P_HEIGHT,
//                                       getBottomRightCorner().y() - event->scenePos().y());
//        m_currentItem->setRegisteredProperty(RectangleItem::P_POSY, event->scenePos().y());
//    }
//    // bottom left corner
//    if(event->scenePos().x() <  getBottomRightCorner().x() &&
//            event->scenePos().y() > getTopLeftCorner().y()) {
//        m_currentItem->setRegisteredProperty(RectangleItem::P_WIDTH,
//                                      getTopRightCorner().x() - event->scenePos().x());
//        m_currentItem->setRegisteredProperty(RectangleItem::P_HEIGHT, event->scenePos().y()
//                                      - getTopLeftCorner().y());
//        m_currentItem->setRegisteredProperty(RectangleItem::P_POSX, event->scenePos().x());
//    }

}

QPointF MaskGraphicsScene::getTopLeftCorner()
{
    return QPointF(m_currentItem->getRegisteredProperty("X position").toReal(),
                               m_currentItem->getRegisteredProperty("Y position").toReal());
}

QPointF MaskGraphicsScene::getTopRightCorner()
{
    return QPointF(m_currentItem->getRegisteredProperty("X position").toReal() +
                   m_currentItem->getRegisteredProperty("Width").toReal(),
                   m_currentItem->getRegisteredProperty("Y position").toReal());
}

QPointF MaskGraphicsScene::getBottomLeftCorner()
{
    return QPointF(m_currentItem->getRegisteredProperty("X position").toReal(),
                   m_currentItem->getRegisteredProperty("Y position").toReal() +
                   m_currentItem->getRegisteredProperty("Height").toReal());
}

QPointF MaskGraphicsScene::getBottomRightCorner()
{
    return QPointF(m_currentItem->getRegisteredProperty("X position").toReal() +
                   m_currentItem->getRegisteredProperty("Width").toReal(),
                   m_currentItem->getRegisteredProperty("Y position").toReal() +
                   m_currentItem->getRegisteredProperty("Height").toReal());
}


