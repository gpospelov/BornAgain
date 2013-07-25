#include "LayerDockView.h"

#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDrag>
#include <QCursor>
#include <QApplication>
#include <QMimeData>
#include <QBitmap>
#include <QWidget>
#include <QGradient>
#include <iostream>
#include <QDropEvent>
#include <QStyleOptionGraphicsItem>

#include "LayerView.h"
#include "MultiLayerView.h"
#include "DesignerHelper.h"
#include "DesignerMimeData.h"


//bool sort_layers(QGraphicsItem* left, QGraphicsItem *right) {
//    return left->y() < right->y();
//}


LayerDockView::LayerDockView(QGraphicsItem *parent)
    : ISampleView(parent)
    , m_color(Qt::lightGray)
    , m_rect(0, 0, DesignerHelper::getMultiLayerWidth(), DesignerHelper::getMultiLayerHeight())
{
    setToolTip(QString("LayerDockWidget: drag layers and multi layers on top") );
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, false);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    setAcceptDrops(true);

    connect(this, SIGNAL(childrenChanged()), this, SLOT(updateHeight()));
    updateHeight();
}


void LayerDockView::addLayer(LayerView *layer, QPointF pos)
{
    // adjusting main rectangle othervise item->setPos will not work due to 'LayerView::itemChange'
    m_rect.setHeight(m_rect.height()+layer->boundingRect().height());

    int xpos = (DesignerHelper::getMultiLayerWidth() - DesignerHelper::getLayerWidth())/2.;
    layer->setPos(xpos, pos.y());
    layer->setFixedX();
    connect(layer, SIGNAL(LayerMoved()), this, SLOT(updateHeight()) );
    layer->setParentItem(this);
}


void LayerDockView::addLayer(MultiLayerView *layer, QPointF pos)
{
    // adjusting main rectangle othervise item->setPos will not work due to 'LayerView::itemChange'
    m_rect.setHeight(m_rect.height()+layer->boundingRect().height());

    int xpos = (DesignerHelper::getMultiLayerWidth() - DesignerHelper::getLayerWidth())/2.;
    layer->setPos(xpos, pos.y());
    //layer->setFixedX();
    connect(layer, SIGNAL(LayerMoved()), this, SLOT(updateHeight()) );
    layer->setParentItem(this);
}



// adjusts positions of Layers inside MultiLayer, updates total MultiLayer height
// calculates drop areas for new layers
// called when one of Layer is changed
void LayerDockView::updateHeight()
{
    std::cout << "LayerDockView::updateHeight() " << std::endl;
    // drop areas are rectangles covering the area of layer interfaces
    m_drop_areas.clear();

    QList<QGraphicsItem *> list = childItems();
    qSort(list.begin(), list.end(), DesignerHelper::sort_layers);

    int total_height = 0;
    if( childItems().size() > 0) {
        foreach(QGraphicsItem *item, list) {
            item->setY(total_height);
            total_height += item->boundingRect().height();
            m_drop_areas.append(QRectF(0, item->y() - item->boundingRect().height()/4., boundingRect().width(), item->boundingRect().height()/2.));
        }
        m_drop_areas.append(QRectF(0, list.back()->y() +list.back()->boundingRect().height() - list.back()->boundingRect().height()/4., boundingRect().width(), list.back()->boundingRect().height()/2.));
    } else {
        total_height = DesignerHelper::getMultiLayerHeight();
        m_drop_areas.append(boundingRect());
    }

    m_rect.setHeight(total_height);
    update();
}


bool LayerDockView::isInDropArea(QPointF pos)
{
    foreach(QRectF rect, m_drop_areas) {
        //std::cout << " drop areas " << rect.x() << " " << rect.y() << " " << rect.width() << " " << rect.height() << " point" << pos.x() << " " << pos.y() << std::endl;
        if (rect.contains(pos)) return true;
    }
    return false;
}


QRectF LayerDockView::boundingRect() const
{
    return rect();
}


void LayerDockView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    painter->setPen(Qt::lightGray);
    if (option->state & (QStyle::State_Selected | QStyle::State_HasFocus)) {
        painter->setPen(Qt::DashLine);
    }
    painter->setBrush(DesignerHelper::getLayerGradient(m_color, rect() ) );
    painter->drawRect(rect());
}


void LayerDockView::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    const DesignerMimeData *mimeData = checkDragEvent(event);
    if (mimeData) {
        std::cout << "LayerDockView::dragEnterEvent() -> INSIDE " << std::endl;
    }
}


void LayerDockView::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
    Q_UNUSED(event);
    std::cout << "LayerDockView::dragLeaveEvent() -> " << std::endl;
}


void LayerDockView::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    std::cout << "LayerDockView::dropEvent() -> " << std::endl;
    const DesignerMimeData *mimeData = checkDragEvent(event);
    if (mimeData) {        
        std::cout << "LayerDockView::dropEvent() -> yes" << std::endl;
        if(mimeData->getClassName() == QString("Layer") ) addLayer(new LayerView(), event->pos());
        if(mimeData->getClassName() == QString("MultiLayer") ) addLayer(new MultiLayerView(), event->pos());
        update();
    }
}


void LayerDockView::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    const DesignerMimeData *mimeData = checkDragEvent(event);
    if (mimeData) {
        std::cout << "LayerDockView::dragMoveEvent() -> pos:" << event->pos().x() << " " << event->pos().y() << std::endl;
        update();

    }
}


void LayerDockView::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    std::cout << "LayerDockView::mouseMoveEvent -> " << x() << " " << y() << std::endl;
    QGraphicsObject::mouseMoveEvent(event);
}


void LayerDockView::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    std::cout << "LayerDockView::mousePressEvent -> " << x() << " " << y() << std::endl;
    QGraphicsObject::mousePressEvent(event);
}

void LayerDockView::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    std::cout << "LayerDockView::mouseReleaseEvent -> " << x() << " " << y() << std::endl;
    QGraphicsObject::mouseReleaseEvent(event);
}


const DesignerMimeData *LayerDockView::checkDragEvent(QGraphicsSceneDragDropEvent * event)
{
    std::cout << "LayerDockView::checkDragEvent -> "  << std::endl;
    const DesignerMimeData *mimeData = qobject_cast<const DesignerMimeData *>(event->mimeData());
    if (!mimeData) {
        event->ignore();
        return 0;
    }

    if(mimeData->hasFormat("bornagain/widget")
            && (mimeData->getClassName() == QString("Layer") || mimeData->getClassName() == QString("MultiLayer") )
            && isInDropArea(event->pos()) ) {
        std::cout << "LayerDockView::checkDragEvent -> yes"  << std::endl;
        event->setAccepted(true);
    } else {
        event->setAccepted(false);
    }
    return mimeData;
}

