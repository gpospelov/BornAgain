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
#include "SessionItem.h"
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
    , m_maskModel(0)
    , m_selectionModel(0)
    , m_proxy(0)
    , m_block_selection(false)
    , m_intensityItem(0)
    , m_currentItem(0)
{
    setSceneRect(default_scene_rect);
    connect(this, SIGNAL(selectionChanged()), this, SLOT(onSceneSelectionChanged()));
}

void MaskGraphicsScene::setMaskContext(SessionModel *model, const QModelIndex &maskContainerIndex,
                    IntensityDataItem *intensityItem)
{
    m_intensityItem = intensityItem;

    if (model != m_maskModel || m_maskContainerIndex != maskContainerIndex) {

        if (m_maskModel) {
            disconnect(m_maskModel,
                       SIGNAL(modelAboutToBeReset()),
                       this,
                       SLOT(resetScene()));
            disconnect(m_maskModel,
                       SIGNAL(rowsInserted(QModelIndex, int, int)),
                       this,
                       SLOT(onRowsInserted(QModelIndex, int, int)));
            disconnect(m_maskModel,
                       SIGNAL(rowsAboutToBeRemoved(QModelIndex, int, int)),
                       this,
                       SLOT(onRowsAboutToBeRemoved(QModelIndex, int, int)));
            disconnect(m_maskModel,
                       SIGNAL(rowsRemoved(QModelIndex, int, int)),
                       this,
                       SLOT(onRowsRemoved(QModelIndex, int, int)));
            disconnect(m_maskModel,
                       SIGNAL(modelReset()),
                       this,
                       SLOT(updateScene()));
        }

        m_maskModel = model;
        m_maskContainerIndex = maskContainerIndex;

        if(m_maskModel) {
            connect(m_maskModel,
                       SIGNAL(modelAboutToBeReset()),
                       this,
                       SLOT(resetScene()));
            connect(m_maskModel,
                       SIGNAL(rowsInserted(QModelIndex, int, int)),
                       this,
                       SLOT(onRowsInserted(QModelIndex, int, int)));
            connect(m_maskModel,
                       SIGNAL(rowsAboutToBeRemoved(QModelIndex, int, int)),
                       this,
                       SLOT(onRowsAboutToBeRemoved(QModelIndex, int, int)));
            connect(m_maskModel,
                       SIGNAL(rowsRemoved(QModelIndex, int, int)),
                       this,
                       SLOT(onRowsRemoved(QModelIndex, int, int)));
            connect(m_maskModel,
                       SIGNAL(modelReset()),
                       this,
                       SLOT(updateScene()));
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
            disconnect(m_selectionModel,
                       SIGNAL(selectionChanged(QItemSelection, QItemSelection)),
                       this,
                       SLOT(onSessionSelectionChanged(QItemSelection, QItemSelection)));
        }

        m_selectionModel = model;

        if (m_selectionModel) {
            connect(m_selectionModel,
                    SIGNAL(selectionChanged(QItemSelection, QItemSelection)),
                    this,
                    SLOT(onSessionSelectionChanged(QItemSelection, QItemSelection)));
        }
    }

}

void MaskGraphicsScene::onActivityModeChanged(MaskEditorFlags::Activity value)
{
    if(!m_proxy) return;

    qDebug() << "XXX MaskGraphicsScene::onActivityModeChanged";
    if(m_context.isActivityRequiresDrawingCancel(value)) {
        cancelCurrentDrawing();
    }

    m_context.setActivityType(value);
    if(m_context.isInZoomMode()) {
        m_proxy->setInZoomMode(true);
    } else {
        m_proxy->setInZoomMode(false);
    }
}

void MaskGraphicsScene::onMaskValueChanged(MaskEditorFlags::MaskValue value)
{
    m_context.setMaskValue(value);
}

//! returns ColorMap view to original state (axes, zoom)
void MaskGraphicsScene::onResetViewRequest()
{
    if(!m_proxy) return;
    m_proxy->resetView();
}

void MaskGraphicsScene::onRowsInserted(const QModelIndex &parent, int first, int last)
{
    Q_UNUSED(parent);
    Q_UNUSED(first);
    Q_UNUSED(last);
    updateScene();
}

void MaskGraphicsScene::onRowsAboutToBeRemoved(const QModelIndex &parent, int first, int last)
{
    m_block_selection = true;
    for (int irow = first; irow <= last; ++irow) {
        QModelIndex itemIndex = m_maskModel->index(irow, 0, parent);
        deleteViews(itemIndex); // deleting all child items
    }
    m_block_selection = false;
}

void MaskGraphicsScene::onRowsRemoved(const QModelIndex &, int , int )
{
    updateScene();
}

void MaskGraphicsScene::cancelCurrentDrawing()
{
    if(isDrawingInProgress()) {
        Q_ASSERT(m_currentItem);
        QModelIndex index = m_maskModel->indexOfItem(m_currentItem);
        m_maskModel->removeRows(index.row(), 1, index.parent());
        setDrawingInProgress(false);
    }
}

void MaskGraphicsScene::resetScene()
{
    clear();
    m_ItemToView.clear();
    m_proxy = 0;
    m_adaptor.reset(new ColorMapSceneAdaptor);
}

void MaskGraphicsScene::updateScene()
{
    if(!m_maskModel) return;
    updateProxyWidget();
    updateViews(m_maskModel->parent(m_maskContainerIndex));
    setZValues();
}

//! Makes invisible all masks in the case of the request for presentation mode
void MaskGraphicsScene::onPresentationTypeRequest(
        MaskEditorFlags::PresentationType presentationType)
{
    bool visibility_flag(true);
    if(presentationType == MaskEditorFlags::MASK_PRESENTER) visibility_flag = false;
    foreach(IMaskView *view, m_ItemToView.values()) {
        Q_ASSERT(view);
        view->setVisible(visibility_flag);
    }
}

//! propagate selection from model to scene
void MaskGraphicsScene::onSessionSelectionChanged(const QItemSelection & /* selected */,
                                              const QItemSelection & /* deselected */)
{
    if (m_block_selection) return;

    m_block_selection = true;

    for (QMap<SessionItem *, IMaskView *>::iterator it = m_ItemToView.begin();
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

//! propagate selection from scene to model
void MaskGraphicsScene::onSceneSelectionChanged()
{
    if (m_block_selection)
        return;

    m_block_selection = true;

    m_selectionModel->clearSelection();
    QList<QGraphicsItem *> selected = selectedItems();
    for (int i = 0; i < selected.size(); ++i) {
        IMaskView *view = dynamic_cast<IMaskView *>(selected[i]);
        if (view) {
            SessionItem *maskItem = view->getParameterizedItem();
            QModelIndex itemIndex = m_maskModel->indexOfItem(maskItem);
            Q_ASSERT(itemIndex.isValid());
            if (!m_selectionModel->isSelected(itemIndex))
                m_selectionModel->select(itemIndex, QItemSelectionModel::Select);
        }
    }
    m_block_selection = false;
}


void MaskGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->buttons() & Qt::RightButton) {
        if(isDrawingInProgress()) {
            cancelCurrentDrawing();
        } else {
            makeViewAtMousePosSelected(event);
        }
        return;
    }

    if(isValidForPolygonDrawing(event)) {
        processPolygonItem(event);
        return;
    }

    if(isValidForLineDrawing(event)) {
        processLineItem(event);
        return;
    }

    if(isValidForMaskAllDrawing(event)) {
        processMaskAllItem(event);
        return;
    }

    if(isValidForRectangleDrawing(event)) {
        processRectangleItem(event);
        return;
    }

    if(isValidForEllipseDrawing(event)) {
        processEllipseItem(event);
        return;
    }

    QGraphicsScene::mousePressEvent(event);
}

void MaskGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(isDrawingInProgress() && m_context.isRectangleMode()) {
        processRectangleItem(event);
        return;
    }

    if(isDrawingInProgress() && m_context.isEllipseMode()) {
        processEllipseItem(event);
        return;
    }

    QGraphicsScene::mouseMoveEvent(event);

    if( (isDrawingInProgress() && m_context.isPolygonMode()) || m_context.isLineMode()) {
        m_currentMousePosition = event->scenePos();
        invalidate();
    }
}

//! Finalizes item drawing or pass events to other items
void MaskGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "MaskGraphicsScene::mouseReleaseEvent() -> before";
    if(isDrawingInProgress()) {
        if (m_context.isRectangleMode() || m_context.isEllipseMode()) {
            clearSelection();
            if (m_currentItem) {
                // drawing ended up with item drawn, let's make it selected
                if (IMaskView *view = m_ItemToView[m_currentItem]) {
                    view->setSelected(true);
                }
            } else {
                // drawing ended without item to be draw (too short mouse move)
                // making item beneath of mouse release position to be selected
                makeViewAtMousePosSelected(event);
            }

            setDrawingInProgress(false);
        }

    } else {
        QGraphicsScene::mouseReleaseEvent(event);
    }
}

void MaskGraphicsScene::drawForeground(QPainter *painter, const QRectF &)
{
    if(PolygonView *polygon = getCurrentPolygon()) {
        painter->setPen(QPen(Qt::black, 1, Qt::DashLine));
        painter->drawLine(QLineF(polygon->getLastAddedPoint(), m_currentMousePosition));
    } else {
        if(m_context.isLineMode()) {
            const QRectF &plot_scene_rectangle = m_adaptor->getViewportRectangle();
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
        }
    }
}

//! creates item context menu if there is IMaskView beneath the mouse right click
void MaskGraphicsScene::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    if(isDrawingInProgress()) return;
    IMaskView *view = dynamic_cast<IMaskView *>(itemAt(event->scenePos(), QTransform()));
    if(view) {
        emit itemContextMenuRequest(event->screenPos());
    }
}

//! updates proxy widget for intensity data item
void MaskGraphicsScene::updateProxyWidget()
{
    Q_ASSERT(m_intensityItem);
    if(!m_proxy) {
        m_proxy = new MaskGraphicsProxy;
        m_proxy->setIntensityItem(m_intensityItem);
        m_proxy->setSceneAdaptor(m_adaptor.data());
        addItem(m_proxy);
    }
}

void MaskGraphicsScene::updateViews(const QModelIndex &parentIndex, IMaskView *parentView)
{
    Q_ASSERT(m_maskModel);
    IMaskView *childView(0);
    for (int i_row = 0; i_row < m_maskModel->rowCount(parentIndex); ++i_row) {
        QModelIndex itemIndex = m_maskModel->index(i_row, 0, parentIndex);
        if (SessionItem *item = m_maskModel->itemForIndex(itemIndex)) {

            if (item && (item->modelType() == Constants::GroupItemType || item->modelType() == Constants::PropertyType)) {
                continue;
            }

            childView = addViewForItem(item);
            if (childView) {
                if (parentView) {
                    qDebug() << "       DesignerScene::updateViews() -> adding child "
                             << item->modelType() << " to parent"
                             << parentView->getParameterizedItem()->modelType();
                    parentView->addView(childView, i_row);
                }
            }
        }
        updateViews(itemIndex, childView);
    }
}

IMaskView *MaskGraphicsScene::addViewForItem(SessionItem *item)
{
    Q_ASSERT(item);
    IMaskView *view = m_ItemToView[item];
    if (!view) {
        view = MaskViewFactory::createMaskView(item, m_adaptor.data());
        if (view) {
            m_ItemToView[item] = view;
            addItem(view);
            return view;
        }
    }
    return view;
}

//! recursive delete of all views corresponding to given index
void MaskGraphicsScene::deleteViews(const QModelIndex &parentIndex)
{
    for (int i_row = 0; i_row < m_maskModel->rowCount(parentIndex); ++i_row) {
        QModelIndex itemIndex = m_maskModel->index(i_row, 0, parentIndex);
        if (SessionItem *item = m_maskModel->itemForIndex(itemIndex)) {
            removeItemViewFromScene(item);
        }
        deleteViews(itemIndex);
    }
    removeItemViewFromScene(m_maskModel->itemForIndex(parentIndex)); // deleting parent item
}

//! removes single view from scene
void MaskGraphicsScene::removeItemViewFromScene(SessionItem *item)
{
    for (QMap<SessionItem *, IMaskView *>::iterator it = m_ItemToView.begin();
         it != m_ItemToView.end(); ++it) {
        if (it.key() == item) {
            IMaskView *view = it.value();
            view->setSelected(false);
            m_ItemToView.erase(it);
            delete view;
            break;
        }
    }
}

//! returns true if left mouse bottom click was inside ColorMap viewport rectangle
bool MaskGraphicsScene::isValidMouseClick(QGraphicsSceneMouseEvent *event)
{
    if(!m_adaptor) return false;

    if(!(event->buttons() & Qt::LeftButton)) return false;
    if(!m_adaptor->getViewportRectangle().contains(event->scenePos())) return false;
    return true;
}

bool MaskGraphicsScene::isValidForRectangleDrawing(QGraphicsSceneMouseEvent *event)
{
    if(isDrawingInProgress()) return false;
    if(!isValidMouseClick(event)) return false;
    if(!m_context.isRectangleMode()) return false;
    if(isAreaContains(event, MaskEditorHelper::SIZEHANDLE)) return false;
    return true;
}

bool MaskGraphicsScene::isValidForEllipseDrawing(QGraphicsSceneMouseEvent *event)
{
    if(isDrawingInProgress()) return false;
    if(!isValidMouseClick(event)) return false;
    if(!m_context.isEllipseMode()) return false;
    if(isAreaContains(event, MaskEditorHelper::SIZEHANDLE)) return false;
    return true;
}

bool MaskGraphicsScene::isValidForPolygonDrawing(QGraphicsSceneMouseEvent *event)
{
    if(!isValidMouseClick(event)) return false;
    if(!m_context.isPolygonMode()) return false;
    if(!isDrawingInProgress()) {
        if(isAreaContains(event, MaskEditorHelper::POLYGONPOINT)) return false;
    }
    return true;
}

bool MaskGraphicsScene::isValidForLineDrawing(QGraphicsSceneMouseEvent *event)
{
    if(!isValidMouseClick(event)) return false;
    if(isDrawingInProgress()) return false;
    if(!m_context.isLineMode()) return false;
    if(QGraphicsItem *graphicsItem = itemAt(event->scenePos(), QTransform())) {
        if(graphicsItem->type() == MaskEditorHelper::VERTICALLINE ||
                graphicsItem->type() == MaskEditorHelper::HORIZONTALLINE) return false;
    }
    return true;
}

//! Returns true if MaskAllItem can be drawn. Only one item of such type is allowed.
bool MaskGraphicsScene::isValidForMaskAllDrawing(QGraphicsSceneMouseEvent *event)
{
    if(!isValidMouseClick(event)) return false;
    if(isDrawingInProgress()) return false;
    if(!m_context.isMaskAllMode()) return false;
    foreach(SessionItem *item, m_ItemToView.keys()) {
        if(item->modelType() == Constants::MaskAllType) return false;
    }
    return true;
}

//! return true if area beneath the mouse contains biews of given type
bool MaskGraphicsScene::isAreaContains(QGraphicsSceneMouseEvent *event,
                                       MaskEditorHelper::EViewTypes viewType)
{
    QList<QGraphicsItem *> items_beneath = this->items(event->scenePos());
    foreach(QGraphicsItem *graphicsItem, items_beneath) {
        if(graphicsItem->type() == viewType) return true;
    }
    return false;
}

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

void MaskGraphicsScene::makeViewAtMousePosSelected(QGraphicsSceneMouseEvent *event)
{
    if(QGraphicsItem *graphicsItem = itemAt(event->scenePos(), QTransform())) {
        graphicsItem->setSelected(true);
    }
}

//! Processes RectangleItem drawing
//! If the mouse move distance with left button down is larger than certain threshold,
//! new RectangleItem will be created. Further, this function will update size and position
//! of current rectangle if mouse keep moving.
//! FIXME Refactor to handle Ellipses and rectangles in single function
void MaskGraphicsScene::processRectangleItem(QGraphicsSceneMouseEvent *event)
{
    if(!isDrawingInProgress()) setDrawingInProgress(true);

    QPointF click_pos = event->buttonDownScenePos(Qt::LeftButton);
    QPointF mouse_pos = event->scenePos();
    QLineF line(mouse_pos, click_pos);

    if(!m_currentItem && line.length() > min_distance_to_create_rect) {
        m_currentItem = m_maskModel->insertNewItem(Constants::RectangleMaskType,
                                                   m_maskContainerIndex, 0);
        m_currentItem->setRegisteredProperty(MaskItem::P_MASK_VALUE,
                                             m_context.getMaskValue());
        setItemName(m_currentItem);
    }

    if(m_currentItem) {
        qreal xmin = std::min(click_pos.x(), mouse_pos.x());
        qreal xmax = std::max(click_pos.x(), mouse_pos.x());
        qreal ymin = std::min(click_pos.y(), mouse_pos.y());
        qreal ymax = std::max(click_pos.y(), mouse_pos.y());

//        m_currentItem->setRegisteredProperty(RectangleItem::P_POSX, m_adaptor->fromSceneX(xmin));
//        m_currentItem->setRegisteredProperty(RectangleItem::P_POSY, m_adaptor->fromSceneY(ymin));
//        m_currentItem->setRegisteredProperty(
//            RectangleItem::P_WIDTH, m_adaptor->fromSceneX(xmax) - m_adaptor->fromSceneX(xmin));
//        m_currentItem->setRegisteredProperty(
//            RectangleItem::P_HEIGHT, m_adaptor->fromSceneY(ymin) - m_adaptor->fromSceneY(ymax));

        m_currentItem->setRegisteredProperty(RectangleItem::P_XLOW, m_adaptor->fromSceneX(xmin));
        m_currentItem->setRegisteredProperty(RectangleItem::P_YLOW, m_adaptor->fromSceneY(ymax));
        m_currentItem->setRegisteredProperty(RectangleItem::P_XUP, m_adaptor->fromSceneX(xmax));
        m_currentItem->setRegisteredProperty(RectangleItem::P_YUP, m_adaptor->fromSceneY(ymin));
    }
}

//! Processes EllipseItem drawing
void MaskGraphicsScene::processEllipseItem(QGraphicsSceneMouseEvent *event)
{
    if(!isDrawingInProgress()) setDrawingInProgress(true);

    QPointF click_pos = event->buttonDownScenePos(Qt::LeftButton);
    QPointF mouse_pos = event->scenePos();
    QLineF line(mouse_pos, click_pos);

    if(!m_currentItem && line.length() > min_distance_to_create_rect) {
        m_currentItem = m_maskModel->insertNewItem(Constants::EllipseMaskType,
                                                   m_maskContainerIndex, 0);
        m_currentItem->setRegisteredProperty(MaskItem::P_MASK_VALUE,
                                             m_context.getMaskValue());
        setItemName(m_currentItem);
    }

    if(m_currentItem) {
        qreal xmin = std::min(click_pos.x(), mouse_pos.x());
        qreal xmax = std::max(click_pos.x(), mouse_pos.x());
        qreal ymin = std::min(click_pos.y(), mouse_pos.y());
        qreal ymax = std::max(click_pos.y(), mouse_pos.y());

        m_currentItem->setRegisteredProperty(EllipseItem::P_XCENTER,
                                             m_adaptor->fromSceneX(xmin + (xmax-xmin)/2.));
        m_currentItem->setRegisteredProperty(EllipseItem::P_YCENTER,
                                             m_adaptor->fromSceneY(ymin + (ymax-ymin)/2.));
        m_currentItem->setRegisteredProperty(
            EllipseItem::P_XRADIUS, (m_adaptor->fromSceneX(xmax) - m_adaptor->fromSceneX(xmin))/2.);
        m_currentItem->setRegisteredProperty(
            EllipseItem::P_YRADIUS, (m_adaptor->fromSceneY(ymin) - m_adaptor->fromSceneY(ymax))/2.);
    }

}

void MaskGraphicsScene::processPolygonItem(QGraphicsSceneMouseEvent *event)
{
    Q_ASSERT(m_context.isPolygonMode());

    if(!m_currentItem) {
        setDrawingInProgress(true);
        m_currentItem = m_maskModel->insertNewItem(Constants::PolygonMaskType,
                                                   m_maskContainerIndex, 0);
        m_currentItem->setRegisteredProperty(MaskItem::P_MASK_VALUE, m_context.getMaskValue());
        m_selectionModel->clearSelection();
        m_selectionModel->select(m_maskModel->indexOfItem(m_currentItem), QItemSelectionModel::Select);
        setItemName(m_currentItem);
    }

    Q_ASSERT(m_currentItem->modelType() == Constants::PolygonMaskType);

    if(PolygonView *currentPolygon = getCurrentPolygon()) {
        if(currentPolygon->closePolygonIfNecessary()) {
            setDrawingInProgress(false);
            return;
        }
    }

    SessionItem *point = m_maskModel->insertNewItem(Constants::PolygonPointType,
                                                          m_maskModel->indexOfItem(m_currentItem));
    QPointF click_pos = event->buttonDownScenePos(Qt::LeftButton);

    point->setRegisteredProperty(PolygonPointItem::P_POSX, m_adaptor->fromSceneX(click_pos.x()));
    point->setRegisteredProperty(PolygonPointItem::P_POSY, m_adaptor->fromSceneY(click_pos.y()));
}

void MaskGraphicsScene::processLineItem(QGraphicsSceneMouseEvent *event)
{
    setDrawingInProgress(true);
    QPointF click_pos = event->buttonDownScenePos(Qt::LeftButton);

    if(m_context.isVerticalLineMode())
        processVerticalLineItem(click_pos);

    if(m_context.isHorizontalLineMode())
        processHorizontalLineItem(click_pos);

    m_selectionModel->clearSelection();
    m_selectionModel->select(m_maskModel->indexOfItem(m_currentItem), QItemSelectionModel::Select);
    setItemName(m_currentItem);
    m_currentItem->setRegisteredProperty(MaskItem::P_MASK_VALUE,
                                         m_context.getMaskValue());

    setDrawingInProgress(false);
}

void MaskGraphicsScene::processVerticalLineItem(const QPointF &pos)
{
    m_currentItem = m_maskModel->insertNewItem(Constants::VerticalLineMaskType,
                                               m_maskContainerIndex, 0);
    m_currentItem->setRegisteredProperty(VerticalLineItem::P_POSX,
                                         m_adaptor->fromSceneX(pos.x()));
}

void MaskGraphicsScene::processHorizontalLineItem(const QPointF &pos)
{
    m_currentItem = m_maskModel->insertNewItem(Constants::HorizontalLineMaskType,
                                               m_maskContainerIndex, 0);
    m_currentItem->setRegisteredProperty(HorizontalLineItem::P_POSY,
                                         m_adaptor->fromSceneY(pos.y()));
}

void MaskGraphicsScene::processMaskAllItem(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    setDrawingInProgress(true);
    m_currentItem = m_maskModel->insertNewItem(Constants::MaskAllType,
                                               m_maskContainerIndex);
    m_selectionModel->clearSelection();
    setDrawingInProgress(false);
}

//! Update Z-values of all IMaskView to reflect stacking order in SessionModel.
//! Item with irow=0 is the top most on graphics scene.
void MaskGraphicsScene::setZValues()
{
    Q_ASSERT(m_maskContainerIndex.isValid());
    for(int i = 0; i < m_maskModel->rowCount(m_maskContainerIndex); i++) {
        QModelIndex itemIndex = m_maskModel->index(i, 0, m_maskContainerIndex);
        SessionItem *item =  m_maskModel->itemForIndex(itemIndex);
        Q_ASSERT(item);
        if(IMaskView *view = m_ItemToView[item]) {
            view->setZValue(m_maskModel->rowCount(m_maskContainerIndex) -  itemIndex.row() + 1);
        }
    }
}

//! returns polygon which is currently under the drawing
PolygonView *MaskGraphicsScene::getCurrentPolygon() const
{
    PolygonView *result(0);
    if(isDrawingInProgress() && m_context.isPolygonMode()) {
        if(m_currentItem) {
//            if(IMaskView *view = m_ItemToView[m_currentItem]) {
//                if(view->type() == MaskEditorHelper::POLYGON)
//                    result = dynamic_cast<PolygonView *>(view);
//            }
              result = dynamic_cast<PolygonView *>(m_ItemToView[m_currentItem]);
        }
    }
    return result;
}

//! Sets item name depending on alreay existent items.
//! If there is already "Rectangle1", the new name will be "Rectangle2"
void MaskGraphicsScene::setItemName(SessionItem *itemToChange)
{
    int glob_index(0);
    for(int i_row = 0; i_row < m_maskModel->rowCount(m_maskContainerIndex); ++i_row) {
         QModelIndex itemIndex = m_maskModel->index( i_row, 0, m_maskContainerIndex );
         if (SessionItem *currentItem = m_maskModel->itemForIndex(itemIndex)){
             if(currentItem->modelType() == itemToChange->modelType()) {
                 QString itemName = currentItem->itemName();
                 if(itemName.startsWith(itemToChange->itemName())) {
                     int item_index = itemName.remove(0, itemToChange->itemName().size()).toInt();
                     if(item_index > glob_index) glob_index = item_index;
                 }
             }
         }
    }
    itemToChange->setItemName(itemToChange->itemName()+QString::number(++glob_index));
}
