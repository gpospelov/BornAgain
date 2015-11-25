// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaskWidgets/EllipseView.cpp
//! @brief     Implements EllipseView class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "EllipseView.h"
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


EllipseView::EllipseView()
    : m_block_on_property_change(false)
    , m_activeHandleElement(0)
{
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable );
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    setAcceptHoverEvents(true);
    create_size_handle_elements();
}

void EllipseView::setSceneAdaptor(const ISceneAdaptor *adaptor)
{
    IMaskView::setSceneAdaptor(adaptor);
    for(QMap<SizeHandleElement::EHandleLocation, SizeHandleElement *>::iterator
        it = m_resize_handles.begin(); it!= m_resize_handles.end(); ++it) {
        it.value()->setSceneAdaptor(m_adaptor);
    }
}

void EllipseView::onChangedX()
{
    qDebug() << "EllipseView::onChangedX()";
//    if(m_block_on_property_change) return;

    m_block_on_property_change = true;
    m_item->setRegisteredProperty(EllipseItem::P_POSX, fromSceneX(this->x()));
    m_block_on_property_change = false;
}

void EllipseView::onChangedY()
{
    qDebug() << "EllipseView::onChangedY()";
//    if(m_block_on_property_change) return;

    m_block_on_property_change = true;
    m_item->setRegisteredProperty(EllipseItem::P_POSY, fromSceneY(this->y()));
    m_block_on_property_change = false;
}

void EllipseView::onPropertyChange(const QString &propertyName)
{
    qDebug() << "EllipseView::onPropertyChange()";
    if(m_block_on_property_change) return;

    m_block_on_property_change = true;

    if(propertyName == EllipseItem::P_WIDTH || propertyName == EllipseItem::P_HEIGHT) {
        update_bounding_rect();
    }
    else if(propertyName == EllipseItem::P_POSX) {
        setX(toSceneX(EllipseItem::P_POSX));
//        setX(left());
    }
    else if(propertyName == EllipseItem::P_POSY) {
        setY(toSceneY(EllipseItem::P_POSY));
//        setY(top());
    }
    else if(propertyName == EllipseItem::P_ANGLE) {
        qDebug() << "   ";
        qDebug() << "   ";

        QTransform transform;
        QPointF center = m_bounding_rect.center();
        qDebug() << "translating" << center << par(EllipseItem::P_ANGLE);
//        transform.translate(center.x(), center.y());
        transform.rotate(par(EllipseItem::P_ANGLE));
//        transform.translate(-center.x(), -center.y());
        setTransform(transform);
        update();
    }

    m_block_on_property_change = false;

}

//! triggered by SizeHandleElement
void EllipseView::onSizeHandleElementRequest(bool going_to_resize)
{
    qDebug() << "EllipseView::onSizeHandleElementRequest()";
    if(going_to_resize) {
        setFlag(QGraphicsItem::ItemIsMovable, false);
        m_activeHandleElement = qobject_cast<SizeHandleElement *>(sender());
        Q_ASSERT(m_activeHandleElement);
        SizeHandleElement::EHandleLocation oposite_corner
                = m_activeHandleElement->getOppositeHandleLocation();
        m_resize_opposite_origin = m_resize_handles[oposite_corner]->scenePos();
//        m_resize_opposite_origin = m_resize_handles[oposite_corner]->pos();
        qDebug() << "       m_resize_opposite_origin:" << m_resize_opposite_origin;
    } else {
        setFlag(QGraphicsItem::ItemIsMovable, true);
        m_activeHandleElement = 0;
    }
}

void EllipseView::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
//    qDebug() << "EllipseView::paint" << getParameterizedItem() << m_adaptor->getViewportRectangle();

//    QPolygonF clip_polygon = mapFromScene(m_adaptor->getViewportRectangle());
//    painter->setClipRegion(QRegion(clip_polygon.toPolygon()));

    painter->setRenderHints(QPainter::Antialiasing);
    prepareGeometryChange();

//    clipPainter(painter);

    bool mask_value = m_item->getRegisteredProperty(MaskItem::P_MASK_VALUE).toBool();
    painter->setBrush(MaskEditorHelper::getMaskBrush(mask_value));
    painter->setPen(MaskEditorHelper::getMaskPen(mask_value));
//    painter->drawRect(QRectF(0.0, 0.0, width(), height()));
    painter->drawEllipse(m_mask_rect);


}

//! Track if item selected/deselected and show/hide size handles
QVariant EllipseView::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    qDebug() << "EllipseView::itemChange" << change << value;
    if(change == QGraphicsItem::ItemSelectedChange) {
        for(QMap<SizeHandleElement::EHandleLocation, SizeHandleElement *>::iterator
            it = m_resize_handles.begin(); it!= m_resize_handles.end(); ++it) {
            it.value()->setVisible(!this->isSelected());
        }
    }
//    return QGraphicsItem::itemChange(change, value);
    return value;
}

void EllipseView::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "EllipseView::mousePressEvent";
    IMaskView::mousePressEvent(event);
}

void EllipseView::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "EllipseView::mouseMoveEvent" << event->scenePos();

    if(m_activeHandleElement) {
        qDebug() << "   opposite_origin:" << m_resize_opposite_origin << event->pos();
        QPointF opposPos = mapFromScene(m_resize_opposite_origin);
        qreal xmin = std::min(event->pos().x(),opposPos.x());
        qreal xmax = std::max(event->pos().x(),opposPos.x());
        qreal ymin = std::min(event->pos().y(),opposPos.y());
        qreal ymax = std::max(event->pos().y(),opposPos.y());
        qreal width = xmax-xmin;
        qreal height = ymax-ymin;

        qreal xcenter = xmin + (xmax-xmin)/2.;
        qreal ycenter = ymin + (ymax-ymin)/2.;

        QPointF center(xcenter, ycenter);
        QPointF centerInScene = mapToScene(center);

        qDebug() << "   opposite_origin:" << width << height << "center:" << center << " centerInScene" << centerInScene;


        if(m_activeHandleElement->getHandleType() == SizeHandleElement::RESIZE) {
            m_item->setRegisteredProperty(EllipseItem::P_POSX, fromSceneX(centerInScene.x()));
            m_item->setRegisteredProperty(EllipseItem::P_POSY, fromSceneY(centerInScene.y()));

            m_item->setRegisteredProperty(EllipseItem::P_WIDTH,
                                          fromSceneX(centerInScene.x()+width/2.) - fromSceneX(centerInScene.x()-width/2.));
            m_item->setRegisteredProperty(EllipseItem::P_HEIGHT,
                                          fromSceneY(centerInScene.y()-height/2.) - fromSceneY(centerInScene.y()+height/2.));



        } else if(m_activeHandleElement->getHandleType() == SizeHandleElement::RESIZE_HEIGHT) {
            m_item->setRegisteredProperty(EllipseItem::P_POSY, fromSceneY(centerInScene.y()));
            m_item->setRegisteredProperty(EllipseItem::P_HEIGHT,
                                          fromSceneY(centerInScene.y()-height/2.) - fromSceneY(centerInScene.y()+height/2.));

        } else if(m_activeHandleElement->getHandleType() == SizeHandleElement::RESIZE_WIDTH) {
            m_item->setRegisteredProperty(EllipseItem::P_POSX, fromSceneX(centerInScene.x()));
            m_item->setRegisteredProperty(EllipseItem::P_WIDTH,
                                          fromSceneX(centerInScene.x()+width/2.) - fromSceneX(centerInScene.x()-width/2.));
        }

    } else {
        IMaskView::mouseMoveEvent(event);
    }
}

void EllipseView::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "EllipseView::mouseReleaseEvent";
    onSizeHandleElementRequest(false);
    IMaskView::mouseReleaseEvent(event);
}

void EllipseView::update_view()
{
    qDebug() << ">>>> EllipseView::update_view() -> ";
    update_bounding_rect();
    update_position();
    update();
}

//! updates view's bounding rectangle using item properties
void EllipseView::update_bounding_rect()
{
    qDebug() << ">>>> EllipseView::update_bounding_rect() -> ";
    if(m_item) {
        m_mask_rect = QRectF(-width()/2., -height()/2., width(), height());
//        m_mask_rect = QRectF(0.0, 0.0, width(), height());
        qDebug() << ">>>> EllipseView::update_bounding_rect() -> " << m_mask_rect;
        m_bounding_rect = m_mask_rect.marginsAdded(QMarginsF(bbox_margins, bbox_margins,
                                                      bbox_margins, bbox_margins));
    }
    for(QMap<SizeHandleElement::EHandleLocation, SizeHandleElement *>::iterator
            it = m_resize_handles.begin(); it!= m_resize_handles.end(); ++it) {
        it.value()->updateHandleElementPosition(m_mask_rect);
    }
}

//! updates position of view using item properties
void EllipseView::update_position()
{
    setX(toSceneX(EllipseItem::P_POSX));
    setY(toSceneY(EllipseItem::P_POSY));
//    m_block_on_property_change = true;
//    setX(left());
//    setY(top());
//    m_block_on_property_change = false;
    qDebug() << "EllipseView::update_position()" << pos();
}

//! returns the x-coordinate of the rectangle's left edge
qreal EllipseView::left() const
{
    qDebug() << "EllipseView::left()";
    return toSceneX(par(EllipseItem::P_POSX) - par(EllipseItem::P_WIDTH)/2.);
}

//! returns the x-coordinate of the rectangle's right edge
qreal EllipseView::right() const
{
    qDebug() << "EllipseView::right()";
    return toSceneX(par(EllipseItem::P_POSX)+par(EllipseItem::P_WIDTH)/2.);
}

//! returns width of the rectangle
qreal EllipseView::width() const
{
    return right() - left();
}


//! Returns the y-coordinate of the rectangle's top edge.
qreal EllipseView::top() const
{
    qDebug() << "EllipseView::top()";
    return toSceneY(par(EllipseItem::P_POSY)+par(EllipseItem::P_HEIGHT)/2.);
}

//! Returns the y-coordinate of the rectangle's bottom edge.
qreal EllipseView::bottom() const
{
    qDebug() << "EllipseView::bottom()";
    return toSceneY(par(EllipseItem::P_POSY)-par(EllipseItem::P_HEIGHT)/2.);
}

qreal EllipseView::height() const
{
    return bottom() - top();
}




void EllipseView::create_size_handle_elements()
{
    qDebug() << "EllipseView::create_size_handle_elements()";
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

