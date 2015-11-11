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

void MaskGraphicsScene::onActivityModeChanged(int mode)
{
    qDebug() << "MaskGraphicsScene::onActivityModeChanged(int mode) ->" << mode;
    m_activityType = (MaskEditorActivity::EActivityType)mode;
    if(mode == MaskEditorActivity::PAN_ZOOM_MODE) {
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
    Q_UNUSED(parent);
    Q_UNUSED(first);
    Q_UNUSED(last);
    Q_ASSERT(0);
}

void MaskGraphicsScene::onRowsRemoved(const QModelIndex &, int, int)
{
    updateScene();
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
    qDebug() << "MaskGraphicsScene::onSceneSelectionChanged() 1.1";
    if (m_block_selection)
        return;

    m_block_selection = true;

    m_selectionModel->clearSelection();
    QList<QGraphicsItem *> selected = selectedItems();
    for (int i = 0; i < selected.size(); ++i) {
        IMaskView *view = dynamic_cast<IMaskView *>(selected[i]);
        if (view) {
            ParameterizedItem *maskItem = view->getParameterizedItem();
            QModelIndex itemIndex = m_model->indexOfItem(maskItem);
            Q_ASSERT(itemIndex.isValid());
            if (!m_selectionModel->isSelected(itemIndex))
                m_selectionModel->select(itemIndex, QItemSelectionModel::Select);
        }
    }

    m_block_selection = false;
}

void MaskGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "MaskGraphicsScene::mousePressEvent()";
    if(m_activityType.testFlag(MaskEditorActivity::RECTANGLE_MODE)) {
        setDrawingInProgress(true);
    }
    QGraphicsScene::mousePressEvent(event);
}

void MaskGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "MaskGraphicsScene::mouseMoveEvent()" << m_activityType;
    if(isDrawingInProgress()) {
        qDebug() << "   DRAWING_IN_PROGESS";
        if(m_activityType.testFlag(MaskEditorActivity::RECTANGLE_MODE)) {
            processRectangleItem(event);
        }
    }


    QGraphicsScene::mouseMoveEvent(event);
//    QPointF buttonDownScenePos = event->buttonDownScenePos(Qt::LeftButton);
//    qDebug() << "   XXX" << event->scenePos() << buttonDownScenePos;
//    if(event->buttons() & Qt::LeftButton) {
//        qDebug() << "   XXX still pressed";
//    }

}

void MaskGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "MaskGraphicsScene::mouseReleaseEvent() -> before" << m_activityType;
    if(isDrawingInProgress()) {
        Q_ASSERT(m_currentItem);
        clearSelection();
        if(IMaskView *view = m_ItemToView[m_currentItem]) {
            view->setSelected(true);
        }
        setDrawingInProgress(false);
        m_currentItem = 0;
        qDebug() << "       after" << m_activityType;
    }
    QGraphicsScene::mouseReleaseEvent(event);
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

    for (int i_row = 0; i_row < m_model->rowCount(parentIndex); ++i_row) {
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

    if(line.length() > 50) {
        qreal xmin = std::min(click_pos.x(), mouse_pos.x());
        qreal xmax = std::max(click_pos.x(), mouse_pos.x());
        qreal ymin = std::min(click_pos.y(), mouse_pos.y());
        qreal ymax = std::max(click_pos.y(), mouse_pos.y());

        if(!m_currentItem) {
            m_currentItem = m_model->insertNewItem(Constants::RectangleMaskType, m_rootIndex);
        }

        m_currentItem->setRegisteredProperty(RectangleItem::P_POSX, m_adaptor->fromSceneX(xmin));
        m_currentItem->setRegisteredProperty(RectangleItem::P_POSY, m_adaptor->fromSceneY(ymin));
        m_currentItem->setRegisteredProperty(RectangleItem::P_WIDTH,
                                          m_adaptor->fromSceneX(xmax) - m_adaptor->fromSceneX(xmin));
        m_currentItem->setRegisteredProperty(RectangleItem::P_HEIGHT,
                                          m_adaptor->fromSceneY(ymin) - m_adaptor->fromSceneY(ymax));


//        item->setRegisteredProperty(RectangleItem::P_POSX, 0.6);
//        item->setRegisteredProperty(RectangleItem::P_POSY, 1.5);
//        item->setRegisteredProperty(RectangleItem::P_WIDTH, 0.3);
//        item->setRegisteredProperty(RectangleItem::P_HEIGHT, 0.2);


//        RectangleItem *rect = dynamic_cast<RectangleItem *>(m_model->insertNewItem(Constants::RectangleMaskType, m_rootIndex));
//        Q_ASSERT(rect);
//        rect->setRegisteredProperty(RectangleItem::P_POSX, 0.6);
//        rect->setRegisteredProperty(RectangleItem::P_POSY, 1.5);
//        rect->setRegisteredProperty(RectangleItem::P_WIDTH, 0.3);
//        rect->setRegisteredProperty(RectangleItem::P_HEIGHT, 0.2);
//        setDrawingInProgress(false);
    }

}
