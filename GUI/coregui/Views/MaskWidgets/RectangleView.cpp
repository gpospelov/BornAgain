// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaskWidgets/IMaskView.h
//! @brief     Implements interface class IMaskView for all masks on graphics scene
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
#include "PointElement.h"
#include <QPainter>
#include <QMarginsF>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

namespace {
const double bbox_margins = 5; // additional margins around rectangle to form bounding box

QMap<PointElement::EPointType, PointElement::EPointType> getMapOfOppositeCorners()
{
    QMap<PointElement::EPointType, PointElement::EPointType> result;
    result[PointElement::TOPLEFT] = PointElement::BOTTOMRIGHT;
    result[PointElement::TOPMIDDLE] = PointElement::BOTTOMMIDLE;
    result[PointElement::TOPRIGHT] = PointElement::BOTTOMLEFT;
    result[PointElement::MIDDLERIGHT] = PointElement::MIDDLELEFT;
    result[PointElement::BOTTOMRIGHT] = PointElement::TOPLEFT;
    result[PointElement::BOTTOMMIDLE] = PointElement::TOPMIDDLE;
    result[PointElement::BOTTOMLEFT] = PointElement::TOPRIGHT;
    result[PointElement::MIDDLELEFT] = PointElement::MIDDLERIGHT;
    return result;
}


}

QMap<PointElement::EPointType, PointElement::EPointType> RectangleView::m_opposite_corners = getMapOfOppositeCorners();

RectangleView::RectangleView()
    : m_block_on_property_change(false)
    , m_view_state(NONE)
{
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable );
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    setAcceptHoverEvents(true);
    create_points();
}

void RectangleView::onChangedX()
{
    m_block_on_property_change = true;
    m_item->setRegisteredProperty(RectangleItem::P_POSX, fromSceneX(this->x()));
    m_block_on_property_change = false;
}

void RectangleView::onChangedY()
{
    m_block_on_property_change = true;
    m_item->setRegisteredProperty(RectangleItem::P_POSY, fromSceneY(this->y()));
    m_block_on_property_change = false;
}

void RectangleView::onPropertyChange(const QString &propertyName)
{
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

}

void RectangleView::onGripResizeRequest()
{
    m_view_state = RESIZE;
    setFlag(QGraphicsItem::ItemIsMovable, false);
    PointElement *element = qobject_cast<PointElement *>(sender());
    Q_ASSERT(element);

    PointElement::EPointType oposite_corner = m_opposite_corners[element->getPointType()];
    m_resize_opposite_origin = m_point_elements[oposite_corner]->scenePos();
    qDebug() << "RectangleView::onGripResizeRequest()"
             << "element->getPointType()" << element->getPointType()
             << "oposite_corner" << oposite_corner
             << "m_resize_opposite_origin:" << m_resize_opposite_origin;


}

void RectangleView::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{

    painter->setRenderHints(QPainter::Antialiasing);
    prepareGeometryChange();

    bool mask_value = m_item->getRegisteredProperty(MaskItem::P_MASK_VALUE).toBool();
    painter->setBrush(MaskEditorHelper::getMaskBrush(mask_value));
    painter->setPen(MaskEditorHelper::getMaskPen(mask_value));
    painter->drawRect(QRectF(0.0, 0.0, width(), height()));

    if (this->isSelected()) {
//        paint_rectangle_marker(painter, QPointF(0,0));
//        QVector<QPointF> corners;
//        corners.push_back(m_mask_rect.topLeft(), m_mask_rect.topRight(), m_mask_rect.bottomRight(), m_mask_rect.bottomLeft());
    }

}

QVariant RectangleView::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if(change == QGraphicsItem::ItemSelectedChange) {
        for(QMap<PointElement::EPointType, PointElement *>::iterator it = m_point_elements.begin(); it!= m_point_elements.end(); ++it) {
            it.value()->setVisible(!this->isSelected());
        }
    }
    return QGraphicsItem::itemChange(change, value);
}

void RectangleView::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "RectangleView::mousePressEvent";
    IMaskView::mousePressEvent(event);
}

void RectangleView::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "RectangleView::mouseMoveEvent" << event->scenePos();

    if(m_view_state == RESIZE) {
        qDebug() << "   opposite_origin:" << m_resize_opposite_origin;
        qreal xmin = std::min(event->scenePos().x(),m_resize_opposite_origin.x());
        qreal xmax = std::max(event->scenePos().x(),m_resize_opposite_origin.x());
        qreal ymin = std::min(event->scenePos().y(),m_resize_opposite_origin.y());
        qreal ymax = std::max(event->scenePos().y(),m_resize_opposite_origin.y());

        qDebug() << "RESIZE "
                 << "xmin:" << xmin << "ymin:" << ymin << "xmax:" << xmax << "ymax:" << ymax;

        qDebug() << "   converted "
                 << "fromSceneX(xmin):" << fromSceneX(xmin) << "fromSceneY(ymin):" << fromSceneY(ymin)
                 << "width:" << (fromSceneX(xmax) - fromSceneX(xmin)) << "height:" << (fromSceneY(ymin) - fromSceneY(ymax));


        m_item->setRegisteredProperty(RectangleItem::P_POSX, fromSceneX(xmin));
        m_item->setRegisteredProperty(RectangleItem::P_POSY, fromSceneY(ymin));
        m_item->setRegisteredProperty(RectangleItem::P_WIDTH, fromSceneX(xmax) - fromSceneX(xmin));
        m_item->setRegisteredProperty(RectangleItem::P_HEIGHT, fromSceneY(ymin) - fromSceneY(ymax));
    } else {
        IMaskView::mouseMoveEvent(event);
    }
}

void RectangleView::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "RectangleView::mouseReleaseEvent";
    setFlag(QGraphicsItem::ItemIsMovable, true);
    m_view_state = NONE;
    IMaskView::mouseReleaseEvent(event);
}

void RectangleView::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    qDebug() << "RectangleView::hoverMoveEvent";
    IMaskView::hoverMoveEvent(event);
}

//void RectangleView::paint_rectangle_marker(QPainter *painter, const QPointF &pos)
//{
//    painter->setBrush(MaskEditorHelper::getSelectionMarkerBrush());
//    painter->setPen(MaskEditorHelper::getSelectionMarkerPen());
//    painter->drawRect(MaskEditorHelper::getMarkerRectangle(pos));
//}

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
    if(m_item) {
        m_mask_rect = QRectF(0.0, 0.0, width(), height());
        m_bounding_rect = m_mask_rect.marginsAdded(QMarginsF(bbox_margins, bbox_margins,
                                                      bbox_margins, bbox_margins));
//        m_bounding_rect = m_mask_rect;
    }
    qDebug() << "RectangleView::calculate_bounding_rect()" << m_bounding_rect
             << "orig_width:" << par(RectangleItem::P_WIDTH)
             << "toSceneX(RectangleItem::P_WIDTH):" << toSceneX(RectangleItem::P_WIDTH)
             << "toSceneY(RectangleItem::P_HEIGHT):" << toSceneY(RectangleItem::P_HEIGHT);

    for(QMap<PointElement::EPointType, PointElement *>::iterator it = m_point_elements.begin(); it!= m_point_elements.end(); ++it) {
        it.value()->set_position(m_mask_rect);
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
    return toSceneX(par(RectangleItem::P_POSX));
}

//! returns the x-coordinate of the rectangle's right edge
qreal RectangleView::right() const
{
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
    return toSceneY(par(RectangleItem::P_POSY));
}

//! Returns the y-coordinate of the rectangle's bottom edge.
qreal RectangleView::bottom() const
{
    return toSceneY(par(RectangleItem::P_POSY)-par(RectangleItem::P_HEIGHT));
}

qreal RectangleView::height() const
{
    return bottom() - top();
}

void RectangleView::create_points()
{
    QList<PointElement::EPointType> points;
    points << PointElement::TOPLEFT << PointElement::TOPMIDDLE << PointElement::TOPRIGHT
           << PointElement::MIDDLERIGHT << PointElement::BOTTOMRIGHT
           << PointElement::BOTTOMMIDLE << PointElement::BOTTOMLEFT << PointElement::MIDDLELEFT;

    foreach(PointElement::EPointType point_type, points) {
        PointElement *el = new PointElement(point_type, this);
        connect(el, SIGNAL(resize_request()), this, SLOT(onGripResizeRequest()));
        el->setVisible(false);
        m_point_elements[point_type] = el;

//        Q_UNUSED(el);
    }
}

