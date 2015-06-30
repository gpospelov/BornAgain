#include "GraphicsScene.h"
#include "Rectangle.h"
#include "Ellipse.h"
#include "Polygon.h"
#include "RectangleItem.h"
#include "RectangleView.h"
#include "EllipseItem.h"
#include "EllipseView.h"
#include "PolygonItem.h"
#include "PolygonView.h"
#include "PointItem.h"
#include "MaskModel.h"
#include "SampleViewFactory.h"
#include <QItemSelection>
#include <cmath>
#include <sstream>

GraphicsScene::GraphicsScene()
    : m_maskModel(0), m_rectangleItem(0), m_ellipseItem(0), m_polygonItem(0),
      isDrawing(false), m_currentMousePosition(QPointF(0, 0)), m_lastAddedPoint(QPointF(0, 0)),
      m_block_selection(false), m_numberOfRectangle(0), m_numberOfEllipse(0), m_numberOfPolygon(0)
{
    m_drawing = NONE;
}

void GraphicsScene::setDrawing(GraphicsScene::Drawing drawing)
{
    m_drawing = drawing;
}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && m_drawing == RECTANGLE) {
        m_rectangleItem = m_maskModel->insertNewItem(Constants::RectangleType);
        setItemName(m_rectangleItem);
        m_rectangleItem->setRegisteredProperty(RectangleItem::P_POSX, event->scenePos().x());
        m_rectangleItem->setRegisteredProperty(RectangleItem::P_POSY, event->scenePos().y());
    } else if (event->button() == Qt::LeftButton && m_drawing == ELLIPSE) {
        m_ellipseItem = m_maskModel->insertNewItem(Constants::EllipseType);
        setItemName(m_ellipseItem);
        m_ellipseItem->setRegisteredProperty(EllipseItem::P_POSX, event->scenePos().x());
        m_ellipseItem->setRegisteredProperty(EllipseItem::P_POSY, event->scenePos().y());
    } else if (event->button() == Qt::LeftButton && m_drawing == POLYGON) {
        if (!m_polygonItem && !isDrawing) {
            isDrawing = true;
            m_polygonItem = m_maskModel->insertNewItem(Constants::PolygonType);
            m_polygonItem->setRegisteredProperty(PolygonItem::P_DRAWINGMODE, true);
            setItemName(m_polygonItem);
        }
        if (m_polygonItem && isDrawing && m_polygonItem->childItems().length() > 2) {
            QRectF firstPoint(
                m_polygonItem->childItems()[0]->getRegisteredProperty(PointItem::P_POSX).toReal()
                    - 2.5,
                m_polygonItem->childItems()[0]->getRegisteredProperty(PointItem::P_POSY).toReal()
                    - 2.5,
                5, 5);
            if (firstPoint.contains(event->scenePos())) {
                m_pointItem = m_maskModel->insertNewItem(Constants::PointType,
                                                         m_maskModel->indexOfItem(m_polygonItem));
                m_pointItem->setRegisteredProperty(PointItem::P_POSX, firstPoint.center().x());
                m_pointItem->setRegisteredProperty(PointItem::P_POSY, firstPoint.center().y());
                isDrawing = false;
                m_polygonItem->setRegisteredProperty(PolygonItem::P_DRAWINGMODE, false);
                m_polygonItem = 0;
                m_drawing = NONE;
                emit itemIsDrawn();
            }
        }
        if (m_polygonItem && isDrawing) {
            m_pointItem = m_maskModel->insertNewItem(Constants::PointType,
                                                     m_maskModel->indexOfItem(m_polygonItem));
            m_pointItem->setRegisteredProperty(PointItem::P_POSX, event->scenePos().x());
            m_pointItem->setRegisteredProperty(PointItem::P_POSY, event->scenePos().y());
        }
    } else {
        QGraphicsScene::mousePressEvent(event);
    }
    m_lastAddedPoint = event->scenePos();
}

void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (m_drawing == RECTANGLE && m_rectangleItem) {
        m_rectangleItem->setRegisteredProperty(
            RectangleItem::P_WIDTH,
            event->scenePos().x()
                - m_rectangleItem->getRegisteredProperty(RectangleItem::P_POSX).toReal());
        m_rectangleItem->setRegisteredProperty(
            RectangleItem::P_HEIGHT,
            event->scenePos().y()
                - m_rectangleItem->getRegisteredProperty(RectangleItem::P_POSY).toReal());
    } else if (m_drawing == ELLIPSE && m_ellipseItem) {
        m_ellipseItem->setRegisteredProperty(
            EllipseItem::P_WIDTH,
            event->scenePos().x()
                - m_ellipseItem->getRegisteredProperty(EllipseItem::P_POSX).toReal());
        m_ellipseItem->setRegisteredProperty(
            EllipseItem::P_HEIGHT,
            event->scenePos().y()
                - m_ellipseItem->getRegisteredProperty(EllipseItem::P_POSY).toReal());
    } else if (m_drawing == POLYGON && m_polygonItem) {
        QRectF firstPoint(
            m_polygonItem->childItems()[0]->getRegisteredProperty(PointItem::P_POSX).toReal() - 2.5,
            m_polygonItem->childItems()[0]->getRegisteredProperty(PointItem::P_POSY).toReal() - 2.5,
            5, 5);
        if (firstPoint.contains(event->scenePos())) {
            m_polygonItem->setRegisteredProperty(PolygonItem::P_MOUSEISOVERFIRSTPOINT, true);
        } else {
            m_polygonItem->setRegisteredProperty(PolygonItem::P_MOUSEISOVERFIRSTPOINT, false);
        }
    } else {
        QGraphicsScene::mouseMoveEvent(event);
    }
    m_currentMousePosition = event->scenePos();
}

void GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (m_drawing == RECTANGLE && m_rectangleItem) {
        qreal xDifference = m_rectangleItem->getRegisteredProperty(RectangleItem::P_POSX).toReal()
                            - event->scenePos().x();
        qreal yDifference = m_rectangleItem->getRegisteredProperty(RectangleItem::P_POSY).toReal()
                            - event->scenePos().y();
        if (abs(xDifference) <= 10 && abs(yDifference) <= 10) {
            QModelIndex index = m_maskModel->indexOfItem(m_rectangleItem);
            m_maskModel->removeRows(index.row(), 1, index.parent());
            m_numberOfRectangle--;
        }
    } else if (m_drawing == ELLIPSE && m_ellipseItem) {
        qreal xDifference = m_ellipseItem->getRegisteredProperty(EllipseItem::P_POSX).toReal()
                            - event->scenePos().x();
        qreal yDifference = m_ellipseItem->getRegisteredProperty(EllipseItem::P_POSY).toReal()
                            - event->scenePos().y();
        if (abs(xDifference) <= 10 && abs(yDifference) <= 10) {
            QModelIndex index = m_maskModel->indexOfItem(m_ellipseItem);
            m_maskModel->removeRows(index.row(), 1, index.parent());
            m_numberOfRectangle--;
        }
    }

    if (m_drawing == RECTANGLE || m_drawing == ELLIPSE) {
        m_drawing = NONE;
        m_rectangleItem = 0;
        m_ellipseItem = 0;
        emit itemIsDrawn();
    }
    QGraphicsScene::mouseReleaseEvent(event);
}

void GraphicsScene::drawForeground(QPainter *painter, const QRectF & /* rect */)
{
    if (m_drawing == POLYGON && isDrawing) {
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

    for (int i_row = 0; i_row < m_maskModel->rowCount(parentIndex); ++i_row) {
        QModelIndex itemIndex = m_maskModel->index(i_row, 0, parentIndex);

        if (ParameterizedItem *item = m_maskModel->itemForIndex(itemIndex)) {
            addViewForItem(item);
        }
    }
}

IView *GraphicsScene::addViewForItem(ParameterizedItem *item)
{
    qDebug() << "GraphicsScene::addViewForItem() ->" << item->modelType();
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

void GraphicsScene::updateScene()
{
    updateViews();
}

void GraphicsScene::resetScene()
{
    qDebug() << "GraphicsScene::resetScene()";
    clear();
    m_ItemToView.clear();
}

void GraphicsScene::setTreeView(QTreeView *treeView)
{
    m_treeView = treeView;
    m_treeView->setModel(m_maskModel);
    m_selectionModel = m_treeView->selectionModel();

    connect(m_selectionModel, SIGNAL(selectionChanged(QItemSelection, QItemSelection)), this,
            SLOT(onSessionSelectionChanged(QItemSelection, QItemSelection)));
}

void GraphicsScene::setModel(MaskModel *maskModel)
{
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

void GraphicsScene::onSessionSelectionChanged(const QItemSelection &, const QItemSelection &)
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

void GraphicsScene::onRowsAboutToBeRemoved(const QModelIndex &parent, int first, int last)
{
    m_block_selection = true;
    qDebug() << "GraphicsScene::onRowsAboutToBeRemoved()" << parent << first << last;
    for (int irow = first; irow <= last; ++irow) {
        QModelIndex itemIndex = m_maskModel->index(irow, 0, parent);
        deleteViews(itemIndex); // deleting all child items
    }
    m_block_selection = false;
}

void GraphicsScene::deleteViews(const QModelIndex &parentIndex)
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
void GraphicsScene::removeItemViewFromScene(ParameterizedItem *item)
{
    qDebug() << "GraphicsScene::removeItemFromScene()" << item->modelType();
    for (QMap<ParameterizedItem *, IView *>::iterator it = m_ItemToView.begin();
         it != m_ItemToView.end(); ++it) {
        if (it.key() == item) {
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

void GraphicsScene::onRowsRemoved(const QModelIndex & /* parent */, int /* first */, int /* last */)
{
    //    resetScene();
    updateScene();
}

void GraphicsScene::deleteSelectedItems()
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
void GraphicsScene::onSceneSelectionChanged()
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

void GraphicsScene::onRowsInserted(const QModelIndex & /* parent */, int /* first */,
                                   int /* last */)
{
    updateScene();
}

void GraphicsScene::setItemName(ParameterizedItem *item)
{
    std::string itemName(item->itemName().toStdString());
    std::stringstream ss;
    if (item->itemName() == Constants::RectangleType) {
        ss << itemName << m_numberOfRectangle;
        m_numberOfRectangle++;
    } else if (item->itemName() == Constants::EllipseType) {
        ss << itemName << m_numberOfEllipse;
        m_numberOfEllipse++;
    } else if (item->itemName() == Constants::PolygonType) {
        ss << itemName << m_numberOfPolygon;
        m_numberOfPolygon++;
    }
    item->setItemName(ss.str().c_str());
}
