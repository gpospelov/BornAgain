#include "ObsoleteMaskGraphicsScene.h"
#include "ObsoleteRectangleItem.h"
#include "ObsoleteRectangleView.h"
#include "ObsoleteEllipseItem.h"
#include "ObsoletePolygonItem.h"
#include "ObsoletePointItem.h"
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

ObsoleteMaskGraphicsScene::ObsoleteMaskGraphicsScene(QObject *parent)
    : QGraphicsScene(parent)
    , m_maskModel(0)
    , m_currentItem(0)
    , m_currentMousePosition(QPointF(0, 0))
    , m_lastAddedPoint(QPointF(0, 0))
    , m_block_selection(false)
    , m_numberOfRectangles(0)
    , m_numberOfEllipses(0)
    , m_numberOfPolygons(0)
{
//    setSceneRect(QRectF(-800, 0, 1600, 1600));
    m_drawingMode = NONE;
}

void ObsoleteMaskGraphicsScene::setDrawing(DrawingMode drawingMode)
{
    m_drawingMode = drawingMode;
}

void ObsoleteMaskGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        if (m_drawingMode == RECTANGLE) {
            m_currentItem = m_maskModel->insertNewItem(Constants::ObsoleteRectangleType);
            setItemName(m_currentItem);
        } else if (m_drawingMode == ELLIPSE) {
            m_currentItem = m_maskModel->insertNewItem(Constants::ObsoleteEllipseType);
            setItemName(m_currentItem);
        } else if (m_drawingMode == POLYGON) {
            if (!m_currentItem) {
                m_currentItem = m_maskModel->insertNewItem(Constants::ObsoletePolygonType);
                m_currentItem->setRegisteredProperty(ObsoletePolygonItem::P_DRAWINGMODE, true);
                setItemName(m_currentItem);
            }
            if (numberOfPoints() > 2 && firstPointContainsMouseClick(event)) {
                m_currentItem->setRegisteredProperty(ObsoletePolygonItem::P_DRAWINGMODE, false);
                m_maskModel->moveParameterizedItem(m_currentItem, 0, 0);
                m_currentItem = 0;
                m_drawingMode = NONE;
                emit itemIsDrawn();
            }
            else if(m_currentItem) {
                ParameterizedItem *pointItem = m_maskModel->insertNewItem(Constants::ObsoletePointType,
                                                         m_maskModel->indexOfItem(m_currentItem));
                pointItem->setRegisteredProperty(ObsoletePointItem::P_POSX, event->scenePos().x());
                pointItem->setRegisteredProperty(ObsoletePointItem::P_POSY, event->scenePos().y());
            }
        }
        else {
            QGraphicsScene::mousePressEvent(event);
        }
    }
    m_lastAddedPoint = event->buttonDownScenePos(Qt::LeftButton);
    m_currentPoint = event->buttonDownScenePos(Qt::LeftButton);
}

void ObsoleteMaskGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (m_drawingMode == RECTANGLE && m_currentItem) {
        drawingDirection(event);
    } else if (m_drawingMode == ELLIPSE && m_currentItem) {
      drawingDirection(event);
    }
    else {
        QGraphicsScene::mouseMoveEvent(event);
    }
    m_currentMousePosition = event->scenePos();
}

void ObsoleteMaskGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    bool drawingToSmall = false;
    if (m_drawingMode == RECTANGLE && m_currentItem) {
        if (std::abs(m_currentItem->getRegisteredProperty(ObsoleteRectangleItem::P_WIDTH).toReal()) <= 10 &&
            std::abs(m_currentItem->getRegisteredProperty(ObsoleteRectangleItem::P_HEIGHT).toReal()) <= 10){
            QModelIndex index = m_maskModel->indexOfItem(m_currentItem);
            m_maskModel->removeRows(index.row(), 1, index.parent());
            m_numberOfRectangles--;
            drawingToSmall = true;
        }
    } else if (m_drawingMode == ELLIPSE && m_currentItem) {
        if (std::abs(m_currentItem->getRegisteredProperty(ObsoleteEllipseItem::P_WIDTH).toReal()) <= 10 &&
                std::abs(m_currentItem->getRegisteredProperty(ObsoleteEllipseItem::P_HEIGHT).toReal()) <= 10) {
            QModelIndex index = m_maskModel->indexOfItem(m_currentItem);
            m_maskModel->removeRows(index.row(), 1, index.parent());
            m_numberOfEllipses--;
            drawingToSmall = true;
        }
    }

    if (m_drawingMode == RECTANGLE || m_drawingMode == ELLIPSE) {
        if(!drawingToSmall && m_currentItem) {
            m_maskModel->moveParameterizedItem(m_currentItem, 0, 0);
            // uncomment this if you want to change to selection mode after drawing an item.
//            emit itemIsDrawn();
        }
        m_currentItem = 0;
    }
    QGraphicsScene::mouseReleaseEvent(event);
}

void ObsoleteMaskGraphicsScene::drawForeground(QPainter *painter, const QRectF & /* rect */)
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

void ObsoleteMaskGraphicsScene::updateViews(const QModelIndex &parentIndex)
{
    Q_ASSERT(m_maskModel);

    for (int i_row = 0; i_row < m_maskModel->rowCount(parentIndex); ++i_row) {
        QModelIndex itemIndex = m_maskModel->index(i_row, 0, parentIndex);

        if (ParameterizedItem *item = m_maskModel->itemForIndex(itemIndex)) {
            addViewForItem(item);
        }
    }
}

IView *ObsoleteMaskGraphicsScene::addViewForItem(ParameterizedItem *item)
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

void ObsoleteMaskGraphicsScene::updateScene()
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

void ObsoleteMaskGraphicsScene::resetScene()
{
    qDebug() << "GraphicsScene::resetScene()";
    clear();
    m_ItemToView.clear();
}

void ObsoleteMaskGraphicsScene::setSelectionModel(QItemSelectionModel *selectionModel)
{
    m_selectionModel = selectionModel;

    connect(m_selectionModel, SIGNAL(selectionChanged(QItemSelection, QItemSelection)), this,
            SLOT(onSessionSelectionChanged(QItemSelection, QItemSelection)));
}

void ObsoleteMaskGraphicsScene::setModel(MaskModel *maskModel)
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

void ObsoleteMaskGraphicsScene::onSessionSelectionChanged(const QItemSelection &, const QItemSelection &)
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

void ObsoleteMaskGraphicsScene::onRowsAboutToBeRemoved(const QModelIndex &parent, int first, int last)
{
    m_block_selection = true;
    qDebug() << "GraphicsScene::onRowsAboutToBeRemoved()" << parent << first << last;
    for (int irow = first; irow <= last; ++irow) {
        QModelIndex itemIndex = m_maskModel->index(irow, 0, parent);
        deleteViews(itemIndex); // deleting all child items
    }
    m_block_selection = false;
}

void ObsoleteMaskGraphicsScene::deleteViews(const QModelIndex &parentIndex)
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
void ObsoleteMaskGraphicsScene::removeItemViewFromScene(ParameterizedItem *item)
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

void ObsoleteMaskGraphicsScene::onRowsRemoved(const QModelIndex &/* parent */, int /* first */, int /* last */)
{
    updateScene();
}

void ObsoleteMaskGraphicsScene::deleteSelectedItems()
{
    qDebug() << "GraphicsScene::deleteSelectedItems() 1.1" << selectedItems().size();

    QModelIndexList indexes = m_selectionModel->selectedIndexes();

    // deleting selected items on model side, corresponding views will be deleted automatically
    // Since we don't know the order of items, we need this

    while(indexes.size()) {
        m_maskModel->removeRows(indexes.back().row(), 1, indexes.back().parent());
        indexes = m_selectionModel->selectedIndexes();
    }
}

//! propagate selection from scene to model
void ObsoleteMaskGraphicsScene::onSceneSelectionChanged()
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

void ObsoleteMaskGraphicsScene::onRowsInserted(const QModelIndex & /* parent */, int /* first */, int /* last */)
{
    updateScene();
}

void ObsoleteMaskGraphicsScene::setItemName(ParameterizedItem *item)
{
    int numberOfItems(0);
    QString name;
    QMap<ParameterizedItem *, IView *>::iterator it;
    for(it = m_ItemToView.begin(); it != m_ItemToView.end(); ++it) {
        if(item->modelType() == it.key()->modelType()) {
            numberOfItems ++;
        }
    }
    if(item->modelType() == "Rectangle") {
        if(numberOfItems <= m_numberOfRectangles) {
            m_numberOfRectangles ++;
        }
        else {
            m_numberOfRectangles = numberOfItems;
        }
        name = item->itemName().append(QString("%1")).arg(m_numberOfRectangles);
    }
    else if(item->modelType() == "Ellipse") {
        if(numberOfItems <= m_numberOfEllipses) {
            m_numberOfEllipses ++;
        }
        else {
            m_numberOfEllipses = numberOfItems;
        }
        name = item->itemName().append(QString("%1")).arg(m_numberOfEllipses);
    }
    else if(item->modelType() == "Polygon") {
        if(numberOfItems <= m_numberOfPolygons) {
            m_numberOfPolygons++;
        }
        else {
            m_numberOfPolygons = numberOfItems;
        }
        name = item->itemName().append(QString("%1")).arg(m_numberOfPolygons);
    }
    item->setItemName(name);
}

int ObsoleteMaskGraphicsScene::numberOfPoints()
{
    if(m_drawingMode == POLYGON) {
        int items = m_currentItem->childItems().length();
        return items;
    }
    return 0;
}

bool ObsoleteMaskGraphicsScene::firstPointContainsMouseClick(QGraphicsSceneMouseEvent *event)
{
    QRectF firstPoint(
        m_currentItem->childItems()[0]->getRegisteredProperty(ObsoletePointItem::P_POSX).toReal() - 2.5,
        m_currentItem->childItems()[0]->getRegisteredProperty(ObsoletePointItem::P_POSY).toReal() - 2.5,
        5, 5);

    if(firstPoint.contains(event->scenePos())) {
        ParameterizedItem *pointItem = m_maskModel->insertNewItem(Constants::ObsoletePointType,
                                                 m_maskModel->indexOfItem(m_currentItem));
        pointItem->setRegisteredProperty(ObsoletePointItem::P_POSX, firstPoint.center().x());
        pointItem->setRegisteredProperty(ObsoletePointItem::P_POSY, firstPoint.center().y());
        return true;
    }

    else {
        return false;
    }
}

void ObsoleteMaskGraphicsScene::onBringToFront()
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

void ObsoleteMaskGraphicsScene::onSendToBack()
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

void ObsoleteMaskGraphicsScene::setZValues()
{
    for(int i = 0; i < m_maskModel->rowCount(QModelIndex()); i++) {
        QModelIndex indexes = m_maskModel->index(i, 0, QModelIndex());
        ParameterizedItem *item =  m_maskModel->itemForIndex(indexes);
        m_ItemToView[item]->setZValue(m_maskModel->rowCount(QModelIndex()) -  indexes.row() + 1);
    }
}

void ObsoleteMaskGraphicsScene::drawingDirection(QGraphicsSceneMouseEvent *event)
{
   qreal xmin = std::min(event->scenePos().x(),m_currentPoint.x());
   qreal xmax = std::max(event->scenePos().x(),m_currentPoint.x());
   qreal ymin = std::min(event->scenePos().y(),m_currentPoint.y());
   qreal ymax = std::max(event->scenePos().y(),m_currentPoint.y());

   m_currentItem->setRegisteredProperty("Width", xmax - xmin);
   m_currentItem->setRegisteredProperty("Height", ymax - ymin);

   m_currentItem->setRegisteredProperty("X position", xmin);
   m_currentItem->setRegisteredProperty("Y position", ymin);


}





