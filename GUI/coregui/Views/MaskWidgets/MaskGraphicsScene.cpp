// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaskWidgets/MaskGraphicsScene.cpp
//! @brief     Implements class MaskGraphicsScene
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MaskGraphicsScene.h"
#include "SessionModel.h"
#include "IntensityDataItem.h"
#include "MaskGraphicsProxy.h"
#include "ParameterizedItem.h"
#include "IMaskView.h"
#include "ISceneAdaptor.h"
#include "ColorMapSceneAdaptor.h"
#include "MaskViewFactory.h"
#include "MaskEditorFlags.h"
#include "MaskItems.h"
#include "PolygonView.h"
#include "item_constants.h"
#include <QItemSelection>
#include <QGraphicsItem>
#include <QLineF>
#include <QDebug>

namespace {
const QRectF default_scene_rect(0, 0, 800, 600);
const qreal min_distance_to_create_rect = 10;
//const QRectF default_scene_rect(0, 0, 2.0, 2.0);
}

MaskGraphicsScene::MaskGraphicsScene(QObject *parent)
    : QGraphicsScene(parent)
    , m_model(0)
    , m_selectionModel(0)
    , m_proxy(0)
    , m_block_selection(false)
//    , m_activityType(MaskEditorActivity::SELECTION_MODE)
    , m_currentItem(0)
{
    setSceneRect(default_scene_rect);
    connect(this, SIGNAL(selectionChanged()), this, SLOT(onSceneSelectionChanged()));
}

//! Sets the model containing IntensityDataItem and uderlying masks.
//!
void MaskGraphicsScene::setModel(SessionModel *model, const QModelIndex &rootIndex)
{
    if (model != m_model || m_rootIndex != rootIndex) {

        if (m_model) {
            disconnect(m_model, SIGNAL(modelAboutToBeReset()), this, SLOT(resetScene()));
            disconnect(m_model, SIGNAL(rowsInserted(QModelIndex, int, int)), this,
                       SLOT(onRowsInserted(QModelIndex, int, int)));
            disconnect(m_model, SIGNAL(rowsAboutToBeRemoved(QModelIndex, int, int)), this,
                       SLOT(onRowsAboutToBeRemoved(QModelIndex, int, int)));
            disconnect(m_model, SIGNAL(rowsRemoved(QModelIndex, int, int)), this,
                       SLOT(onRowsRemoved(QModelIndex, int, int)));
            disconnect(m_model, SIGNAL(modelReset()), this, SLOT(updateScene()));
        }

        m_model = model;
        m_rootIndex = rootIndex;

        if(m_model) {
            connect(m_model, SIGNAL(modelAboutToBeReset()), this, SLOT(resetScene()));
            connect(m_model, SIGNAL(rowsInserted(QModelIndex, int, int)), this,
                SLOT(onRowsInserted(QModelIndex, int, int)));
            connect(m_model, SIGNAL(rowsAboutToBeRemoved(QModelIndex, int, int)), this,
                SLOT(onRowsAboutToBeRemoved(QModelIndex, int, int)));
            connect(m_model, SIGNAL(rowsRemoved(QModelIndex, int, int)), this,
                SLOT(onRowsRemoved(QModelIndex, int, int)));
            connect(m_model, SIGNAL(modelReset()), this, SLOT(updateScene()));
        }

        resetScene();
        updateScene();
    }

}

void MaskGraphicsScene::setSelectionModel(QItemSelectionModel *model)
{
    Q_ASSERT(model);

    if (model != m_selectionModel) {

        if (m_selectionModel) {
            disconnect(m_selectionModel, SIGNAL(selectionChanged(QItemSelection, QItemSelection)),
                       this, SLOT(onSessionSelectionChanged(QItemSelection, QItemSelection)));
        }

        m_selectionModel = model;

        if (m_selectionModel) {
            connect(m_selectionModel, SIGNAL(selectionChanged(QItemSelection, QItemSelection)), this,
                SLOT(onSessionSelectionChanged(QItemSelection, QItemSelection)));
        }
    }

}

void MaskGraphicsScene::onActivityModeChanged(MaskEditorFlags::Activity value)
{
    qDebug() << "MaskGraphicsScene::onActivityModeChanged(int mode) ->" << value;
    m_context.setActivityType(value);
    if(m_context.isInZoomMode()) {
        m_proxy->setInZoomMode(true);
    } else {
        m_proxy->setInZoomMode(false);
    }

}

void MaskGraphicsScene::onMaskValueChanged(MaskEditorFlags::MaskValue value)
{
    qDebug() << "MaskGraphicsScene::onMaskValueChanged" << value;
    m_context.setMaskValue(value);
}

//! returns ColorMap view to original state (axes, zoom)
void MaskGraphicsScene::onResetViewRequest()
{
    m_proxy->resetView();
}

void MaskGraphicsScene::onRowsInserted(const QModelIndex &parent, int first, int last)
{
    Q_UNUSED(parent);
    Q_UNUSED(first);
    Q_UNUSED(last);
    qDebug() << "ZZZ";
    qDebug() << "ZZZ";
    qDebug() << "ZZZ";
    qDebug() << "MaskGraphicsScene::onRowsInserted()";
    updateScene();
//    makeSelected(parent, first, last);

}

void MaskGraphicsScene::onRowsAboutToBeRemoved(const QModelIndex &parent, int first, int last)
{
    m_block_selection = true;
    qDebug() << "MaskGraphicsScene::onRowsAboutToBeRemoved(), blocking parent:" << parent << "first:" << first << "last:" << last;
    for (int irow = first; irow <= last; ++irow) {
        QModelIndex itemIndex = m_model->index(irow, 0, parent);
        deleteViews(itemIndex); // deleting all child items
    }
    qDebug() << "MaskGraphicsScene::onRowsAboutToBeRemoved(), unblocking";
    m_block_selection = false;
}

void MaskGraphicsScene::onRowsRemoved(const QModelIndex &parent, int first, int last)
{
    qDebug() << "MaskGraphicsScene::onRowsRemoved() ->" << parent << first << last;
    updateScene();
}

void MaskGraphicsScene::deleteSelectedItems()
{
    qDebug() << "XXX";
    qDebug() << "XXX";
    qDebug() << "XXX";
    QModelIndexList indexes = m_selectionModel->selectedIndexes();
    qDebug() << "MaskGraphicsScene::deleteSelectedItems()" << indexes;
    // deleting selected items on model side, corresponding views will be deleted automatically
    // Since we don't know the order of items and their parent/child relationhips, we need this
    while (indexes.size()) {
        m_model->removeRows(indexes.back().row(), 1, indexes.back().parent());
        indexes = m_selectionModel->selectedIndexes();
    }
}

void MaskGraphicsScene::cancelCurrentDrawing()
{
    qDebug() << "MaskGraphicsScene::cancelCurrentDrawing()";
    if(isDrawingInProgress()) {
        Q_ASSERT(m_currentItem);
        QModelIndex index = m_model->indexOfItem(m_currentItem);
        m_model->removeRows(index.row(), 1, index.parent());
        setDrawingInProgress(false);
    }
}

//! every selected mask will be moved according to MaskEditorFlags::Stacking request.
void MaskGraphicsScene::onMaskStackingOrderRequest(MaskEditorFlags::Stacking value)
{
    int change_in_row(0);
    if(value == MaskEditorFlags::BRING_TO_FRONT) change_in_row = -1;
    if(value == MaskEditorFlags::SEND_TO_BACK) change_in_row = 2;

    QModelIndexList indexes = m_selectionModel->selectedIndexes();

    foreach(QModelIndex itemIndex, indexes) {
        if(ParameterizedItem *item =  m_model->itemForIndex(itemIndex)) {
            int new_row = itemIndex.row() + change_in_row;
            if(new_row >= 0 && new_row <= m_model->rowCount(m_rootIndex)) {
                ParameterizedItem *newItem =
                        m_model->moveParameterizedItem(item,
                                                       m_model->itemForIndex(m_rootIndex), new_row);
                m_selectionModel->select(m_model->indexOfItem(newItem),
                                         QItemSelectionModel::Select);
            }
        }
    }

}

//! propagate selection from model to scene
void MaskGraphicsScene::onSessionSelectionChanged(const QItemSelection & /* selected */,
                                              const QItemSelection & /* deselected */)
{
    if (m_block_selection) return;

    qDebug() << "MaskGraphicsScene::onSessionSelectionChanged()";
    m_block_selection = true;

    for (QMap<ParameterizedItem *, IMaskView *>::iterator it = m_ItemToView.begin();
         it != m_ItemToView.end(); ++it) {
        QModelIndex index = m_model->indexOfItem(it.key());
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

//! propagate selection from scene to model
void MaskGraphicsScene::onSceneSelectionChanged()
{
    if (m_block_selection)
        return;

    qDebug() << "MaskGraphicsScene::onSceneSelectionChanged() 1.1 blocking";

    m_block_selection = true;

    m_selectionModel->clearSelection();
    QList<QGraphicsItem *> selected = selectedItems();
    for (int i = 0; i < selected.size(); ++i) {
        IMaskView *view = dynamic_cast<IMaskView *>(selected[i]);
        qDebug() << "AAAA " << i << view;
        if (view) {
            ParameterizedItem *maskItem = view->getParameterizedItem();
            QModelIndex itemIndex = m_model->indexOfItem(maskItem);
            Q_ASSERT(itemIndex.isValid());
            if (!m_selectionModel->isSelected(itemIndex))
                m_selectionModel->select(itemIndex, QItemSelectionModel::Select);
        }
    }

    qDebug() << "MaskGraphicsScene::onSceneSelectionChanged() 1.2 un-blocking";
    m_block_selection = false;
}


void MaskGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "MaskGraphicsScene::mousePressEvent()";

    if(isDrawingInProgress() == false && isAllowedToStartDrawing(event)) {
        setDrawingInProgress(true);
    }

    if(isValidForLineDrawing(event)) {
        processLineItem(event);
        return;
    }

    if(isDrawingInProgress()) {
        if(isValidForPolygonDrawing(event)) {
           processPolygonItem(event);
        } else {
            QGraphicsScene::mousePressEvent(event);
        }

    } else {
        QGraphicsScene::mousePressEvent(event);
    }

}



void MaskGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "MaskGraphicsScene::mouseMoveEvent()";
    if(isDrawingInProgress()) {
        if(m_context.isRectangleMode()) {
            qDebug() << "   DRAWING_IN_PROGESS POLYGON";
            processRectangleItem(event);
        }
        else if(m_context.isPolygonMode()) {
            qDebug() << "   DRAWING_IN_PROGESS POLYGON";
            QGraphicsScene::mouseMoveEvent(event);
        }

    } else {
        QGraphicsScene::mouseMoveEvent(event);
    }
    m_currentMousePosition = event->scenePos();
}

//! Finalizes item drawing or pass events to other items
void MaskGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "MaskGraphicsScene::mouseReleaseEvent() -> before";
    if(isDrawingInProgress()) {

        if (m_context.isRectangleMode()) {
            clearSelection();
            if (m_currentItem) {
                // drawing ended up with item drawn, let's make it selected
                if (IMaskView *view = m_ItemToView[m_currentItem]) {
                    view->setSelected(true);
                }
//                m_currentItem = 0;
            } else {
                // drawing ended without item to be draw (too short mouse move)
                // making item beneath of mouse release position to be selected
                //            makeTopViewSelected(event);
                if (QGraphicsItem *graphicsItem = itemAt(event->scenePos(), QTransform())) {
                    graphicsItem->setSelected(true);
                }
            }

            setDrawingInProgress(false);
        }

//        if (m_activityType.testFlag(MaskEditorActivity::POLYGON_MODE)) {
//            processPolygonItem(event);
//        }



    } else {
        QGraphicsScene::mouseReleaseEvent(event);
    }
}

void MaskGraphicsScene::drawForeground(QPainter *painter, const QRectF &)
{
    if(PolygonView *polygon = getCurrentPolygon()) {
        painter->setPen(QPen(Qt::black, 1, Qt::DashLine));
        painter->drawLine(QLineF(polygon->getLastAddedPoint(), m_currentMousePosition));
        invalidate();
    } else {
        if(m_context.isLineMode()) {
            QRectF plot_scene_rectangle = m_adaptor->getViewportRectangle();
            if(!plot_scene_rectangle.contains(m_currentMousePosition)) return;

            painter->setPen(QPen(Qt::black, 1, Qt::DashLine));
            if(m_context.isVerticalLineMode()) {
                QPointF p1(m_currentMousePosition.x(), plot_scene_rectangle.bottom());
                QPointF p2(m_currentMousePosition.x(), plot_scene_rectangle.top());
                painter->drawLine(QLineF(p1, p2));
            }
            if(m_context.isHorizontalLineMode()) {
                QPointF p1(plot_scene_rectangle.left(), m_currentMousePosition.y());
                QPointF p2(plot_scene_rectangle.right(), m_currentMousePosition.y());
                painter->drawLine(QLineF(p1, p2));
            }
            invalidate();

        }
    }
}

void MaskGraphicsScene::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
        QMenu menu;
        QAction *toggleMaskValueAction = menu.addAction("Toggle mask value");
        QAction *bringToFrontAction = menu.addAction("Rise mask up");
        QAction *sendToBackAction = menu.addAction("Lower mask down");
        menu.addSeparator();
        QAction *removeAction = menu.addAction("Remove mask");

        IMaskView *view = dynamic_cast<IMaskView *>(itemAt(event->scenePos(), QTransform()));
        if(!view) {
            toggleMaskValueAction->setDisabled(true);
            bringToFrontAction->setDisabled(true);
            sendToBackAction->setDisabled(true);
            removeAction->setDisabled(true);
        } else {
            if(isTopMostMask(view)) bringToFrontAction->setDisabled(true);
            if(isBottomMostMask(view)) sendToBackAction->setDisabled(true);

        }

        QAction *selectedAction = menu.exec(event->screenPos());
        if(selectedAction == toggleMaskValueAction) {
            bool old_value = view->getParameterizedItem()->getRegisteredProperty(MaskItem::P_MASK_VALUE).toBool();
            view->getParameterizedItem()->setRegisteredProperty(MaskItem::P_MASK_VALUE, !old_value);
        }
        else if(selectedAction == removeAction) {
            deleteSelectedItems();
        }
        else if(selectedAction == bringToFrontAction) {
            onMaskStackingOrderRequest(MaskEditorFlags::BRING_TO_FRONT);
        }
        else if(selectedAction == sendToBackAction) {
            onMaskStackingOrderRequest(MaskEditorFlags::SEND_TO_BACK);
        }
}


void MaskGraphicsScene::init_scene()
{
    QGraphicsRectItem *b_rect = new QGraphicsRectItem(0, 0, default_scene_rect.width(), default_scene_rect.height());
    b_rect->setPos(0, 0);
    b_rect->setFlag(QGraphicsItem::ItemIgnoresTransformations, true);
    addItem(b_rect);

    qreal offset = 8;
    qreal width = default_scene_rect.width()-offset;
    qreal height = default_scene_rect.height()-offset;
    QGraphicsRectItem *b_rect2 = new QGraphicsRectItem(0, 0,width, height);
    qreal xpos = (default_scene_rect.width() - width)/2.;
    qreal ypos = (default_scene_rect.height() - height)/2.;
    b_rect2->setPos(xpos, ypos);
    b_rect2->setPen(QPen(Qt::red));
    addItem(b_rect2);

}

void MaskGraphicsScene::resetScene()
{
    clear();
    m_ItemToView.clear();
    m_proxy = 0;
    init_scene();
    m_adaptor.reset(new ColorMapSceneAdaptor);
}

void MaskGraphicsScene::updateScene()
{
    if(!m_model) return;
    updateProxyWidget(m_rootIndex);
    updateViews(m_rootIndex);
    setZValues();
}

void MaskGraphicsScene::updateViews(const QModelIndex &parentIndex, IMaskView *parentView)
{
    Q_ASSERT(m_model);

    qDebug() << "DesignerScene::updateVIews()";

    if (!parentIndex.isValid()) {
        qDebug() << "Dumping model";
    }

    IMaskView *childView(0);
    for (int i_row = 0; i_row < m_model->rowCount(parentIndex); ++i_row) {
        QModelIndex itemIndex = m_model->index(i_row, 0, parentIndex);

        if (ParameterizedItem *item = m_model->itemForIndex(itemIndex)) {

            childView = addViewForItem(item);
            if (childView) {
                if (parentView) {
                    qDebug() << "       DesignerScene::updateViews() -> adding child "
                             << item->modelType() << " to parent"
                             << parentView->getParameterizedItem()->modelType();
                    parentView->addView(childView, i_row);
                }
            }

        } else {
            qDebug() << "not a parameterized graphics item";
        }

        updateViews(itemIndex, childView);
    }
}



//! updates proxy widget for intensity data item
void MaskGraphicsScene::updateProxyWidget(const QModelIndex &parentIndex)
{
    if(!m_proxy) {
        m_proxy = new MaskGraphicsProxy;
        m_proxy->setItem(m_model->itemForIndex(parentIndex));
        m_proxy->setSceneAdaptor(m_adaptor.data());
        addItem(m_proxy);
    }
}


void MaskGraphicsScene::deleteViews(const QModelIndex &parentIndex)
{
    qDebug() << " ";
    qDebug() << " ";
    qDebug() << " ";
    qDebug() << " ";
    qDebug() << "DesignerScene::deleteViews()" << parentIndex << m_model->itemForIndex(parentIndex)->modelType();

    for (int i_row = 0; i_row < m_model->rowCount(parentIndex); ++i_row) {
        QModelIndex itemIndex = m_model->index(i_row, 0, parentIndex);

        if (ParameterizedItem *item = m_model->itemForIndex(itemIndex)) {
            qDebug() << "       DesignerScene::deleteViews()" << itemIndex << item->modelType();

            removeItemViewFromScene(item);

        } else {
            qDebug() << "not a parameterized graphics item";
        }
        deleteViews(itemIndex);
    }
    removeItemViewFromScene(m_model->itemForIndex(parentIndex)); // deleting parent item
}

void MaskGraphicsScene::removeItemViewFromScene(ParameterizedItem *item)
{
    qDebug() << "MaskGraphicsScene::removeItemViewFromScene" << item->modelType();
    for (QMap<ParameterizedItem *, IMaskView *>::iterator it = m_ItemToView.begin();
         it != m_ItemToView.end(); ++it) {
        if (it.key() == item) {
            IMaskView *view = it.value();
            view->setSelected(false);
            m_ItemToView.erase(it);
            //emit view->aboutToBeDeleted();
            //view->deleteLater();
            //update();
            delete view;
            break;
        }
    }
}




//! Returns true if it is allowed to start drawing: all conditions below are fulfilled
//! 1) It is not already in drawing mode
//! 2) It was left mouse button click
//! 3) scene's activity is not one of (SELECTION_MODE, PAN_ZOOM_MODE)
//! 4) mouse cursor is not on top of SizeHandleElement
bool MaskGraphicsScene::isAllowedToStartDrawing(QGraphicsSceneMouseEvent *event)
{
    bool result(true);
    if(m_context.isDrawingInProgress()) result = false;
    if( !(event->buttons() & Qt::LeftButton)) result = false;
    if(m_context.isSelectionMode() || m_context.isInZoomMode()) result = false;
    QList<QGraphicsItem *> items_beneath = this->items(event->scenePos());
    foreach(QGraphicsItem *graphicsItem, items_beneath) {
        if(graphicsItem->parentItem()) result = false;
    }
    return result;
}

//! Returns true if the area is valid for drawing. Called from mousePressEvent during
//! polygon drawing process.
bool MaskGraphicsScene::isValidForPolygonDrawing(QGraphicsSceneMouseEvent *event)
{
    if( !(event->buttons() & Qt::LeftButton) ) return false;
//    if(!m_activityType.testFlag(MaskEditorActivity::POLYGON_MODE)) return false;
    if(!m_context.isPolygonMode()) return false;
    return true;
}

bool MaskGraphicsScene::isValidForLineDrawing(QGraphicsSceneMouseEvent *event)
{
    if( !(event->buttons() & Qt::LeftButton) ) return false;
    if(!m_context.isLineMode()) return false;
    return true;
}

//void MaskGraphicsScene::makeSelected(const QModelIndex &parent, int first, int last)
//{
//    for (int i_row = first; i_row < last; ++i_row) {
//        QModelIndex itemIndex = m_model->index(i_row, 0, parent);
//        IMaskView *view = m_ItemToView[m_model->itemForIndex(itemIndex)];
//        if(view)
//            view->setSelected(true);
//    }

//}

bool MaskGraphicsScene::isDrawingInProgress() const
{
    return m_context.isDrawingInProgress();
}


void MaskGraphicsScene::setDrawingInProgress(bool value)
{
    m_context.setDrawingInProgress(value);
    if(value == false) {
        m_currentItem = 0;
    }
}

//! Makes top graphics item under mouse point selected.
//void MaskGraphicsScene::makeTopViewSelected(QGraphicsSceneMouseEvent *event)
//{
//    QList<QGraphicsItem *> items_beneath = this->items(event->scenePos());
//    foreach(QGraphicsItem *graphicsItem, items_beneath) {
//        if(graphicsItem->parentItem() == 0) {
//            graphicsItem->setSelected(true);
//            break;
//        }
//    }

//}




IMaskView *MaskGraphicsScene::addViewForItem(ParameterizedItem *item)
{
    qDebug() << "MaskGraphicsScene::addViewForItem() ->" << item->modelType();
    Q_ASSERT(item);

    IMaskView *view = m_ItemToView[item];
    if (!view) {
        qDebug() << "       MaskGraphicsScene::addViewForItem() -> Creating view for item"
                 << item->modelType();
        view = MaskViewFactory::createMaskView(item, m_adaptor.data());
        if (view) {
            m_ItemToView[item] = view;
            //view->setParameterizedItem(item);
            addItem(view);
//            if(item->modelType() == Constants::PolygonMaskType) view->setSelected(true);
            return view;
        }
    } else {
        qDebug() << "       DesignerScene::addViewForItem() -> View for item exists."
                 << item->modelType();
    }
    return view;
}



//! This function is called from mouse move event, when both DRAWING_IN_PROGRESS and
//! RECTANGLE_MODE flags are active.
//! If the mouse move distance with left button down is larger than certain threshold,
//! new RectangleItem will be created. Further, this function will update size and position
//! of current rectangle if mouse keep moving.
void MaskGraphicsScene::processRectangleItem(QGraphicsSceneMouseEvent *event)
{
    //    QPointF buttonDownScenePos = event->buttonDownScenePos(Qt::LeftButton);
    //    qDebug() << "   XXX" << event->scenePos() << buttonDownScenePos;
    //    if(event->buttons() & Qt::LeftButton) {
    //        qDebug() << "   XXX still pressed";
    //    }

    QPointF click_pos = event->buttonDownScenePos(Qt::LeftButton);
    QPointF mouse_pos = event->scenePos();
    QLineF line(mouse_pos, click_pos);

    if(!m_currentItem && line.length() > min_distance_to_create_rect) {
        m_currentItem = m_model->insertNewItem(Constants::RectangleMaskType, m_rootIndex, 0);
        qDebug() << " ";
        qDebug() << " ";
        qDebug() << " ";
        qDebug() << " " << m_context.getMaskValue();
        m_currentItem->setRegisteredProperty(RectangleItem::P_MASK_VALUE, m_context.getMaskValue());
    }

    if(m_currentItem) {
        qreal xmin = std::min(click_pos.x(), mouse_pos.x());
        qreal xmax = std::max(click_pos.x(), mouse_pos.x());
        qreal ymin = std::min(click_pos.y(), mouse_pos.y());
        qreal ymax = std::max(click_pos.y(), mouse_pos.y());

        m_currentItem->setRegisteredProperty(RectangleItem::P_POSX, m_adaptor->fromSceneX(xmin));
        m_currentItem->setRegisteredProperty(RectangleItem::P_POSY, m_adaptor->fromSceneY(ymin));
        m_currentItem->setRegisteredProperty(
            RectangleItem::P_WIDTH, m_adaptor->fromSceneX(xmax) - m_adaptor->fromSceneX(xmin));
        m_currentItem->setRegisteredProperty(
            RectangleItem::P_HEIGHT, m_adaptor->fromSceneY(ymin) - m_adaptor->fromSceneY(ymax));
    }
}

void MaskGraphicsScene::processPolygonItem(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "MaskGraphicsScene::processPolygonItem";
//    Q_ASSERT(m_activityType.testFlag(MaskEditorActivity::DRAWING_IN_PROGRESS));
//    Q_ASSERT(m_activityType.testFlag(MaskEditorActivity::POLYGON_MODE));
    Q_ASSERT(m_context.isDrawingInProgress());
    Q_ASSERT(m_context.isPolygonMode());

    if(!m_currentItem) {
        m_currentItem = m_model->insertNewItem(Constants::PolygonMaskType, m_rootIndex, 0);
        m_currentItem->setRegisteredProperty(RectangleItem::P_MASK_VALUE, m_context.getMaskValue());
        m_selectionModel->clearSelection();
        m_selectionModel->select(m_model->indexOfItem(m_currentItem), QItemSelectionModel::Select);
    }

    Q_ASSERT(m_currentItem->modelType() == Constants::PolygonMaskType);

    if(PolygonView *currentPolygon = getCurrentPolygon()) {
        if(currentPolygon->closePolygonIfNecessary()) {
            setDrawingInProgress(false);
            return;
        }
    }

    ParameterizedItem *point = m_model->insertNewItem(Constants::PolygonPointType, m_model->indexOfItem(m_currentItem));
    QPointF click_pos = event->buttonDownScenePos(Qt::LeftButton);

    point->setRegisteredProperty(PolygonPointItem::P_POSX, m_adaptor->fromSceneX(click_pos.x()));
    point->setRegisteredProperty(PolygonPointItem::P_POSY, m_adaptor->fromSceneY(click_pos.y()));
}

void MaskGraphicsScene::processLineItem(QGraphicsSceneMouseEvent *event)
{
    m_context.setDrawingInProgress(true);
    QPointF click_pos = event->buttonDownScenePos(Qt::LeftButton);

    if(m_context.isVerticalLineMode())
        processVerticalLineItem(click_pos);
    if(m_context.isHorizontalLineMode())
        processHorizontalLineItem(click_pos);

    m_context.setDrawingInProgress(false);
}

void MaskGraphicsScene::processVerticalLineItem(const QPointF &pos)
{
    m_currentItem = m_model->insertNewItem(Constants::VerticalLineMaskType, m_rootIndex, 0);
    m_currentItem->setRegisteredProperty(VerticalLineItem::P_POSX, m_adaptor->fromSceneX(pos.x()));
}

void MaskGraphicsScene::processHorizontalLineItem(const QPointF &pos)
{
    m_currentItem = m_model->insertNewItem(Constants::HorizontalLineMaskType, m_rootIndex, 0);
    m_currentItem->setRegisteredProperty(HorizontalLineItem::P_POSY, m_adaptor->fromSceneY(pos.y()));
}


//! Update Z-values of all IMaskView to reflect stacking order in SessionModel.
//! Item with irow=0 is the top most on graphics scene.
void MaskGraphicsScene::setZValues()
{
    Q_ASSERT(m_rootIndex.isValid());
    for(int i = 0; i < m_model->rowCount(m_rootIndex); i++) {
        QModelIndex itemIndex = m_model->index(i, 0, m_rootIndex);
        ParameterizedItem *item =  m_model->itemForIndex(itemIndex);
        Q_ASSERT(item);
        if(IMaskView *view = m_ItemToView[item]) {
            view->setZValue(m_model->rowCount(m_rootIndex) -  itemIndex.row() + 1);
        }
    }
}

//! returns polygon which is currently under the drawing
PolygonView *MaskGraphicsScene::getCurrentPolygon() const
{
    PolygonView *result(0);
    if(m_currentItem && m_currentItem->modelType() == Constants::PolygonMaskType) {
        if(IMaskView *view = m_ItemToView[m_currentItem]) {
            result = qobject_cast<PolygonView *>(view);
        }
    }
    return result;
}

//! returns true if current mask is top most in the stask
bool MaskGraphicsScene::isTopMostMask(IMaskView *view)
{
    ParameterizedItem *item = view->getParameterizedItem();
    QModelIndex index = m_model->indexOfItem(item);
    if(index.row() == 0) return true;
    return false;
}

bool MaskGraphicsScene::isBottomMostMask(IMaskView *view)
{
    ParameterizedItem *item = view->getParameterizedItem();
    QModelIndex index = m_model->indexOfItem(item);
    if(index.row() == item->parent()->childItemCount() -1) return true;
    return false;
}


