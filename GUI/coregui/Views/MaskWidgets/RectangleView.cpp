// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaskWidgets/RectangleView.cpp
//! @brief     Implements RectangleView class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "RectangleView.h"
#include "MaskItems.h"
#include "MaskEditorHelper.h"
#include "SizeHandleElement.h"
#include "ISceneAdaptor.h"
#include <QPainter>
#include <QMarginsF>
#include <QGraphicsSceneMouseEvent>
#include <QRegion>
#include <QDebug>

namespace {
const double bbox_margins = 5; // additional margins around rectangle to form bounding box
}


RectangleView::RectangleView()
    : m_block_on_property_change(false)
    , m_activeHandleElement(0)
{
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable );
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    setAcceptHoverEvents(true);
    create_size_handle_elements();
}

void RectangleView::setSceneAdaptor(const ISceneAdaptor *adaptor)
{
    IMaskView::setSceneAdaptor(adaptor);
    for(QMap<SizeHandleElement::EHandleLocation, SizeHandleElement *>::iterator
        it = m_resize_handles.begin(); it!= m_resize_handles.end(); ++it) {
        it.value()->setSceneAdaptor(m_adaptor);
    }

}

void RectangleView::onChangedX()
{
    qDebug() << "RectangleView::onChangedX()";
    m_block_on_property_change = true;
    m_item->setRegisteredProperty(RectangleItem::P_POSX, fromSceneX(this->x()));
    m_block_on_property_change = false;
}

void RectangleView::onChangedY()
{
    qDebug() << "RectangleView::onChangedY()";
    m_block_on_property_change = true;
    m_item->setRegisteredProperty(RectangleItem::P_POSY, fromSceneY(this->y()));
    m_block_on_property_change = false;
}

void RectangleView::onPropertyChange(const QString &propertyName)
{
    qDebug() << "RectangleView::onPropertyChange()";
    if(m_block_on_property_change) return;

    if(propertyName == RectangleItem::P_WIDTH || propertyName == RectangleItem::P_HEIGHT) {
        update_bounding_rect();
    }
    else if(propertyName == RectangleItem::P_POSX) {
        setX(toSceneX(RectangleItem::P_POSX));
    }
    else if(propertyName == RectangleItem::P_POSY) {
        setY(toSceneY(RectangleItem::P_POSY));
    }
//    else if(propertyName == RectangleItem::P_ANGLE) {
//        qDebug() << "   ";
//        qDebug() << "   ";

//        QTransform transform;
//        QPointF center = m_bounding_rect.center();
//        qDebug() << "translating" << center << par(RectangleItem::P_ANGLE);
//        transform.translate(center.x(), center.y());
//        transform.rotate(par(RectangleItem::P_ANGLE));
//        transform.translate(-center.x(), -center.y());
//        setTransform(transform);
//        update();
//    }

}

//! triggered by SizeHandleElement
void RectangleView::onSizeHandleElementRequest(bool going_to_resize)
{
    qDebug() << "RectangleView::onSizeHandleElementRequest()";
    if(going_to_resize) {
        setFlag(QGraphicsItem::ItemIsMovable, false);
        m_activeHandleElement = qobject_cast<SizeHandleElement *>(sender());
        Q_ASSERT(m_activeHandleElement);
        SizeHandleElement::EHandleLocation oposite_corner
                = m_activeHandleElement->getOppositeHandleLocation();
        m_resize_opposite_origin = m_resize_handles[oposite_corner]->scenePos();
        //qDebug() << "       m_resize_opposite_origin:" << m_resize_opposite_origin;
    } else {
        setFlag(QGraphicsItem::ItemIsMovable, true);
        m_activeHandleElement = 0;
    }
}

void RectangleView::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
//    qDebug() << "RectangleView::paint" << getParameterizedItem() << m_adaptor->getViewportRectangle();

//    QPolygonF clip_polygon = mapFromScene(m_adaptor->getViewportRectangle());
//    painter->setClipRegion(QRegion(clip_polygon.toPolygon()));

    painter->setRenderHints(QPainter::Antialiasing);
    prepareGeometryChange();

    clipPainter(painter);

    bool mask_value = m_item->getRegisteredProperty(MaskItem::P_MASK_VALUE).toBool();
    painter->setBrush(MaskEditorHelper::getMaskBrush(mask_value));
    painter->setPen(MaskEditorHelper::getMaskPen(mask_value));
//    painter->drawRect(QRectF(0.0, 0.0, width(), height()));
    painter->drawRect(m_mask_rect);


}

//! Track if item selected/deselected and show/hide size handles
QVariant RectangleView::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    qDebug() << "RectangleView::itemChange" << change << value;
    if(change == QGraphicsItem::ItemSelectedChange) {
        for(QMap<SizeHandleElement::EHandleLocation, SizeHandleElement *>::iterator
            it = m_resize_handles.begin(); it!= m_resize_handles.end(); ++it) {
            it.value()->setVisible(!this->isSelected());
        }
    }
//    return QGraphicsItem::itemChange(change, value);
    return value;
}

void RectangleView::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "RectangleView::mousePressEvent";
    IMaskView::mousePressEvent(event);
}

void RectangleView::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "RectangleView::mouseMoveEvent" << event->scenePos();

    if(m_activeHandleElement) {

//        QPointF opposite = m_resize_handles[m_activeHandleElement->getOppositeHandleLocation()]->scenePos();
        qDebug() << "   opposite_origin:" << m_resize_opposite_origin;

        qreal xmin = std::min(event->scenePos().x(),m_resize_opposite_origin.x());
        qreal xmax = std::max(event->scenePos().x(),m_resize_opposite_origin.x());
        qreal ymin = std::min(event->scenePos().y(),m_resize_opposite_origin.y());
        qreal ymax = std::max(event->scenePos().y(),m_resize_opposite_origin.y());

        if(m_activeHandleElement->getHandleType() == SizeHandleElement::RESIZE) {
            m_item->setRegisteredProperty(RectangleItem::P_POSX, fromSceneX(xmin));
            m_item->setRegisteredProperty(RectangleItem::P_POSY, fromSceneY(ymin));
            m_item->setRegisteredProperty(RectangleItem::P_WIDTH,
                                          fromSceneX(xmax) - fromSceneX(xmin));
            m_item->setRegisteredProperty(RectangleItem::P_HEIGHT,
                                          fromSceneY(ymin) - fromSceneY(ymax));

        } else if(m_activeHandleElement->getHandleType() == SizeHandleElement::RESIZE_HEIGHT) {
            m_item->setRegisteredProperty(RectangleItem::P_POSY, fromSceneY(ymin));
            m_item->setRegisteredProperty(RectangleItem::P_HEIGHT,
                                          fromSceneY(ymin) - fromSceneY(ymax));

        } else if(m_activeHandleElement->getHandleType() == SizeHandleElement::RESIZE_WIDTH) {
            m_item->setRegisteredProperty(RectangleItem::P_POSX, fromSceneX(xmin));
            m_item->setRegisteredProperty(RectangleItem::P_WIDTH,
                                          fromSceneX(xmax) - fromSceneX(xmin));
        }
    } else {
        IMaskView::mouseMoveEvent(event);
    }
}


//void RectangleView::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
//{
//    qDebug() << "EllipseView::mouseMoveEvent" << event->scenePos();

//    if(m_activeHandleElement) {
//        qDebug() << "   opposite_origin:" << m_resize_opposite_origin << event->pos();
//        QPointF opposPos = mapFromScene(m_resize_opposite_origin);
//        qreal xmin = std::min(event->pos().x(),opposPos.x());
//        qreal xmax = std::max(event->pos().x(),opposPos.x());
//        qreal ymin = std::min(event->pos().y(),opposPos.y());
//        qreal ymax = std::max(event->pos().y(),opposPos.y());
//        qreal width = xmax-xmin;
//        qreal height = ymax-ymin;

//        qreal xcenter = xmin + (xmax-xmin)/2.;
//        qreal ycenter = ymin + (ymax-ymin)/2.;

//        QPointF center(xcenter, ycenter);
//        QPointF centerInScene = mapToScene(center);

//        qDebug() << "   opposite_origin:" << width << height << "center:" << center << " centerInScene" << centerInScene;


//        if(m_activeHandleElement->getHandleType() == SizeHandleElement::RESIZE) {
//            m_item->setRegisteredProperty(EllipseItem::P_POSX, fromSceneX(centerInScene.x()));
//            m_item->setRegisteredProperty(EllipseItem::P_POSY, fromSceneY(centerInScene.y()));

//            m_item->setRegisteredProperty(EllipseItem::P_WIDTH,
//                                          fromSceneX(centerInScene.x()+width/2.) - fromSceneX(centerInScene.x()-width/2.));
//            m_item->setRegisteredProperty(EllipseItem::P_HEIGHT,
//                                          fromSceneY(centerInScene.y()-height/2.) - fromSceneY(centerInScene.y()+height/2.));



//        } else if(m_activeHandleElement->getHandleType() == SizeHandleElement::RESIZE_HEIGHT) {
//            m_item->setRegisteredProperty(EllipseItem::P_POSY, fromSceneY(centerInScene.y()));
//            m_item->setRegisteredProperty(EllipseItem::P_HEIGHT,
//                                          fromSceneY(centerInScene.y()-height/2.) - fromSceneY(centerInScene.y()+height/2.));

//        } else if(m_activeHandleElement->getHandleType() == SizeHandleElement::RESIZE_WIDTH) {
//            m_item->setRegisteredProperty(EllipseItem::P_POSX, fromSceneX(centerInScene.x()));
//            m_item->setRegisteredProperty(EllipseItem::P_WIDTH,
//                                          fromSceneX(centerInScene.x()+width/2.) - fromSceneX(centerInScene.x()-width/2.));
//        }

//    } else {
//        IMaskView::mouseMoveEvent(event);
//    }
//}


void RectangleView::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "RectangleView::mouseReleaseEvent";
    onSizeHandleElementRequest(false);
    IMaskView::mouseReleaseEvent(event);
}

void RectangleView::update_view()
{
    qDebug() << ">>>> IMaskView::update_view() -> ";
    update_bounding_rect();
    update_position();
    update();
}

//! updates view's bounding rectangle using item properties
void RectangleView::update_bounding_rect()
{
    qDebug() << ">>>> IMaskView::update_bounding_rect() -> ";
    if(m_item) {
        m_mask_rect = QRectF(0.0, 0.0, width(), height());
        m_bounding_rect = m_mask_rect.marginsAdded(QMarginsF(bbox_margins, bbox_margins,
                                                      bbox_margins, bbox_margins));
    }
    for(QMap<SizeHandleElement::EHandleLocation, SizeHandleElement *>::iterator
            it = m_resize_handles.begin(); it!= m_resize_handles.end(); ++it) {
        it.value()->updateHandleElementPosition(m_mask_rect);
    }
}

//! updates position of view using item properties
void RectangleView::update_position()
{
    setX(toSceneX(RectangleItem::P_POSX));
    setY(toSceneY(RectangleItem::P_POSY));
    qDebug() << "RectangleView::update_position()" << pos();
}

//! returns the x-coordinate of the rectangle's left edge
qreal RectangleView::left() const
{
    qDebug() << "RectangleView::left()";
    return toSceneX(par(RectangleItem::P_POSX));
}

//! returns the x-coordinate of the rectangle's right edge
qreal RectangleView::right() const
{
    qDebug() << "RectangleView::right()";
    return toSceneX(par(RectangleItem::P_POSX)+par(RectangleItem::P_WIDTH));
}

//! returns width of the rectangle
qreal RectangleView::width() const
{
    return right() - left();
}


//! Returns the y-coordinate of the rectangle's top edge.
qreal RectangleView::top() const
{
    qDebug() << "RectangleView::top()";
    return toSceneY(par(RectangleItem::P_POSY));
}

//! Returns the y-coordinate of the rectangle's bottom edge.
qreal RectangleView::bottom() const
{
    qDebug() << "RectangleView::bottom()";
    return toSceneY(par(RectangleItem::P_POSY)-par(RectangleItem::P_HEIGHT));
}

qreal RectangleView::height() const
{
    return bottom() - top();
}

void RectangleView::create_size_handle_elements()
{
    qDebug() << "RectangleView::create_size_handle_elements()";
    QList<SizeHandleElement::EHandleLocation> points;
    points << SizeHandleElement::TOPLEFT << SizeHandleElement::TOPMIDDLE << SizeHandleElement::TOPRIGHT
           << SizeHandleElement::MIDDLERIGHT << SizeHandleElement::BOTTOMRIGHT
           << SizeHandleElement::BOTTOMMIDLE << SizeHandleElement::BOTTOMLEFT << SizeHandleElement::MIDDLELEFT;

    foreach(SizeHandleElement::EHandleLocation point_type, points) {
        SizeHandleElement *el = new SizeHandleElement(point_type, this);
        connect(el, SIGNAL(resize_request(bool)), this, SLOT(onSizeHandleElementRequest(bool)));
        el->setVisible(false);
        m_resize_handles[point_type] = el;
    }
}

