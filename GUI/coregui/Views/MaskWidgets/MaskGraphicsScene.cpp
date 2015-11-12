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
#include "MaskEditorActivity.h"
#include "MaskItems.h"
#include "item_constants.h"
#include <QItemSelection>
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
    , m_activityType(MaskEditorActivity::SELECTION_MODE)
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

void MaskGraphicsScene::onActivityModeChanged(MaskEditorActivity::Flags value)
{
    qDebug() << "MaskGraphicsScene::onActivityModeChanged(int mode) ->" << value;
    m_activityType = value;
    if(m_activityType.testFlag(MaskEditorActivity::PAN_ZOOM_MODE)) {
        m_proxy->setSendSignalsToColormap(true);
    } else {
        m_proxy->setSendSignalsToColormap(false);
    }

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
        deleteView(itemIndex); // deleting all child items
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
    Q_ASSERT(isDrawingInProgress() == false);

    if(isAllowedToStartDrawing(event)) {
        setDrawingInProgress(true);
    } else {
        QGraphicsScene::mousePressEvent(event);
    }
}

void MaskGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "MaskGraphicsScene::mouseMoveEvent()" << m_activityType;
    if(isDrawingInProgress()) {
        qDebug() << "   DRAWING_IN_PROGESS";
        if(m_activityType.testFlag(MaskEditorActivity::RECTANGLE_MODE)) {
            processRectangleItem(event);
        }
    } else {
        QGraphicsScene::mouseMoveEvent(event);
    }
//    QPointF buttonDownScenePos = event->buttonDownScenePos(Qt::LeftButton);
//    qDebug() << "   XXX" << event->scenePos() << buttonDownScenePos;
//    if(event->buttons() & Qt::LeftButton) {
//        qDebug() << "   XXX still pressed";
//    }

}

//! Finalizes item drawing or pass events to other items
void MaskGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "MaskGraphicsScene::mouseReleaseEvent() -> before" << m_activityType;
    if(isDrawingInProgress()) {
        clearSelection();
        if(m_currentItem) {
            // drawing ended up with item drawn, let's make it selected
            if(IMaskView *view = m_ItemToView[m_currentItem]) {
                view->setSelected(true);
            }
            m_currentItem = 0;
        } else {
            // drawing ended without item to be draw (too short mouse move)
            // making item beneath of mouse release position to be selected
//            makeTopViewSelected(event);
            if(QGraphicsItem *graphicsItem = itemAt(event->scenePos(), QTransform())) {
                graphicsItem->setSelected(true);
            }
        }

        setDrawingInProgress(false);
        qDebug() << "       after" << m_activityType;
    } else {
        QGraphicsScene::mouseReleaseEvent(event);
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
    updateViews(m_rootIndex);
}

void MaskGraphicsScene::updateViews(const QModelIndex &parentIndex)
{
    Q_ASSERT(m_model);
    qDebug() << "MaskGraphicsScene::updateViews()";

    updateProxyWidget(parentIndex);
    qDebug() << "       XXX after proxy updated";

    for (int i_row = 0; i_row < m_model->rowCount(parentIndex); ++i_row) {
        qDebug() << "       i_row" << i_row;
        QModelIndex itemIndex = m_model->index(i_row, 0, parentIndex);

        if (ParameterizedItem *item = m_model->itemForIndex(itemIndex)) {
            qDebug() << "aaa:" << item->modelType();
            addViewForItem(item);
        }
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

void MaskGraphicsScene::deleteView(const QModelIndex &itemIndex)
{
    qDebug() << "MaskGraphicsScene::deleteView" << itemIndex << m_model->itemForIndex(itemIndex);
    QMap<ParameterizedItem *, IMaskView *>::iterator it =
            m_ItemToView.find(m_model->itemForIndex(itemIndex));
    if(it!=m_ItemToView.end()) {
        IMaskView *view = it.value();
        qDebug() << "   about to delete view ";
        view->setSelected(false);
        m_ItemToView.erase(it);
        qDebug() << "   view deleted";
//        emit view->aboutToBeDeleted();
//        view->deleteLater();
//        update();
        delete view;
    }
}

//! Returns true if it is allowed to start drawing: all conditions below are fulfilled
//! 1) It was left mouse button click
//! 2) scene's activity is not one of (SELECTION_MODE, PAN_ZOOM_MODE)
//! 3) mouse cursor is not on top of SizeHandleElement
bool MaskGraphicsScene::isAllowedToStartDrawing(QGraphicsSceneMouseEvent *event)
{
    bool result(true);
    if( !(event->buttons() & Qt::LeftButton)) result = false;
    if(m_activityType.testFlag(MaskEditorActivity::SELECTION_MODE) ||
       m_activityType.testFlag(MaskEditorActivity::PAN_ZOOM_MODE)) result = false;
    QList<QGraphicsItem *> items_beneath = this->items(event->scenePos());
    foreach(QGraphicsItem *graphicsItem, items_beneath) {
        if(graphicsItem->parentItem()) result = false;
    }
    return result;
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
    return m_activityType.testFlag(MaskEditorActivity::DRAWING_IN_PROGRESS);
}


void MaskGraphicsScene::setDrawingInProgress(bool value)
{
    if(value) {
        m_activityType |= MaskEditorActivity::DRAWING_IN_PROGRESS;
    } else {
        m_activityType &= ~MaskEditorActivity::DRAWING_IN_PROGRESS;
    }
}

//! Makes top graphics item under mouse point selected.
void MaskGraphicsScene::makeTopViewSelected(QGraphicsSceneMouseEvent *event)
{
    QList<QGraphicsItem *> items_beneath = this->items(event->scenePos());
    foreach(QGraphicsItem *graphicsItem, items_beneath) {
        if(graphicsItem->parentItem() == 0) {
            graphicsItem->setSelected(true);
            break;
        }
    }

}

IMaskView *MaskGraphicsScene::addViewForItem(ParameterizedItem *item)
{
    Q_ASSERT(item);
    qDebug() << "AAA";
    qDebug() << "AAA";
    qDebug() << "AAA";
    qDebug() << "AAA";
    qDebug() << "MaskGraphicsScene::addViewForItem() ->" << item->modelType();

    IMaskView *view = m_ItemToView[item];
    if (!view) {
        qDebug() << "       DesignerScene::addViewForItem() -> Creating view for item"
                 << item->modelType();
        view = MaskViewFactory::createMaskView(item, m_adaptor.data());
        if (view) {
            m_ItemToView[item] = view;
            qDebug() << "       ---> adding to scene";
            addItem(view);
            qDebug() << "       <--- added to scene";
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
//! of this item if mouse keep moving.
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
        m_currentItem = m_model->insertNewItem(Constants::RectangleMaskType, m_rootIndex);
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
