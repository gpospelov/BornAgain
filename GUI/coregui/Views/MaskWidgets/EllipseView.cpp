// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaskWidgets/EllipseView.cpp
//! @brief     Implements EllipseView class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ISceneAdaptor.h"
#include "MaskEditorHelper.h"
#include "MaskItems.h"
#include "SizeHandleElement.h"
#include "EllipseView.h"
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QMarginsF>
#include <QPainter>
#include <QRegion>

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

void EllipseView::onChangedX()
{
    m_block_on_property_change = true;
    m_item->setItemValue(EllipseItem::P_XCENTER, fromSceneX(this->x()));
    m_block_on_property_change = false;
}

void EllipseView::onChangedY()
{
    m_block_on_property_change = true;
    m_item->setItemValue(EllipseItem::P_YCENTER, fromSceneY(this->y()));
    m_block_on_property_change = false;
}

void EllipseView::onPropertyChange(const QString &propertyName)
{
    qDebug() << "EllipseView::onPropertyChange()" << propertyName;
    if(m_block_on_property_change) return;

    m_block_on_property_change = true;

    if(propertyName == EllipseItem::P_XRADIUS || propertyName == EllipseItem::P_YRADIUS) {
        //update_bounding_rect();
        update_view();
    }
    else if(propertyName == EllipseItem::P_XCENTER) {
        setX(toSceneX(EllipseItem::P_XCENTER));
    }
    else if(propertyName == EllipseItem::P_YCENTER) {
        setY(toSceneY(EllipseItem::P_YCENTER));
    }
    else if(propertyName == EllipseItem::P_ANGLE) {
        setTransform(QTransform().rotate(-1.0*par(EllipseItem::P_ANGLE)));
    }
    else if(propertyName == MaskItem::P_MASK_VALUE) {
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
    } else {
        setFlag(QGraphicsItem::ItemIsMovable, true);
        m_activeHandleElement = 0;
    }
}

void EllipseView::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setRenderHints(QPainter::Antialiasing);
    bool mask_value = m_item->getItemValue(MaskItem::P_MASK_VALUE).toBool();
    painter->setBrush(MaskEditorHelper::getMaskBrush(mask_value));
    painter->setPen(MaskEditorHelper::getMaskPen(mask_value));
    painter->drawEllipse(m_mask_rect);
}

//! Track if item selected/deselected and show/hide size handles
QVariant EllipseView::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if(change == QGraphicsItem::ItemSelectedChange) {
        for(QMap<SizeHandleElement::EHandleLocation, SizeHandleElement *>::iterator
            it = m_resize_handles.begin(); it!= m_resize_handles.end(); ++it) {
            it.value()->setVisible(!this->isSelected());
        }
    }
    return value;
}

void EllipseView::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(m_activeHandleElement) {
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

        if(m_activeHandleElement->getHandleType() == SizeHandleElement::RESIZE) {
            m_item->setItemValue(EllipseItem::P_XCENTER, fromSceneX(centerInScene.x()));
            m_item->setItemValue(EllipseItem::P_YCENTER, fromSceneY(centerInScene.y()));

            m_item->setItemValue(EllipseItem::P_XRADIUS,
                                          (fromSceneX(centerInScene.x()+width/2.) -
                                          fromSceneX(centerInScene.x()-width/2.))/2.);
            m_item->setItemValue(EllipseItem::P_YRADIUS,
                                          (fromSceneY(centerInScene.y()-height/2.) -
                                          fromSceneY(centerInScene.y()+height/2.))/2.);



        } else if(m_activeHandleElement->getHandleType() == SizeHandleElement::RESIZE_HEIGHT) {
            m_item->setItemValue(EllipseItem::P_YCENTER, fromSceneY(centerInScene.y()));
            m_item->setItemValue(EllipseItem::P_YRADIUS,
                                          (fromSceneY(centerInScene.y()-height/2.) -
                                          fromSceneY(centerInScene.y()+height/2.))/2.);

        } else if(m_activeHandleElement->getHandleType() == SizeHandleElement::RESIZE_WIDTH) {
            m_item->setItemValue(EllipseItem::P_XCENTER, fromSceneX(centerInScene.x()));
            m_item->setItemValue(EllipseItem::P_XRADIUS,
                                          (fromSceneX(centerInScene.x()+width/2.) -
                                          fromSceneX(centerInScene.x()-width/2.))/2.);
        }

    } else {
        IMaskView::mouseMoveEvent(event);
    }
}

void EllipseView::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    onSizeHandleElementRequest(false);
    IMaskView::mouseReleaseEvent(event);
}

void EllipseView::update_view()
{
//    prepareGeometryChange();
    update_bounding_rect();
    update_position();
    update();
}

//! updates view's bounding rectangle using item properties
void EllipseView::update_bounding_rect()
{
    if(m_item) {
        m_mask_rect = QRectF(-width()/2., -height()/2., width(), height());
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
    setX(toSceneX(EllipseItem::P_XCENTER));
    setY(toSceneY(EllipseItem::P_YCENTER));
    if(par(EllipseItem::P_ANGLE) != 0.0)
        setTransform(QTransform().rotate(-1.0*par(EllipseItem::P_ANGLE)));

}

//! returns the x-coordinate of the rectangle's left edge
qreal EllipseView::left() const
{
    return toSceneX(par(EllipseItem::P_XCENTER) - par(EllipseItem::P_XRADIUS));
}

//! returns the x-coordinate of the rectangle's right edge
qreal EllipseView::right() const
{
    return toSceneX(par(EllipseItem::P_XCENTER)+par(EllipseItem::P_XRADIUS));
}

//! returns width of the rectangle
qreal EllipseView::width() const
{
    return right() - left();
}


//! Returns the y-coordinate of the rectangle's top edge.
qreal EllipseView::top() const
{
    return toSceneY(par(EllipseItem::P_YCENTER)+par(EllipseItem::P_YRADIUS));
}

//! Returns the y-coordinate of the rectangle's bottom edge.
qreal EllipseView::bottom() const
{
    return toSceneY(par(EllipseItem::P_YCENTER)-par(EllipseItem::P_YRADIUS));
}

qreal EllipseView::height() const
{
    return bottom() - top();
}

void EllipseView::create_size_handle_elements()
{
    QList<SizeHandleElement::EHandleLocation> points;
    points << SizeHandleElement::TOPLEFT << SizeHandleElement::TOPMIDDLE
           << SizeHandleElement::TOPRIGHT
           << SizeHandleElement::MIDDLERIGHT << SizeHandleElement::BOTTOMRIGHT
           << SizeHandleElement::BOTTOMMIDLE << SizeHandleElement::BOTTOMLEFT
           << SizeHandleElement::MIDDLELEFT;

    foreach(SizeHandleElement::EHandleLocation point_type, points) {
        SizeHandleElement *el = new SizeHandleElement(point_type, this);
        connect(el, SIGNAL(resize_request(bool)), this,
                SLOT(onSizeHandleElementRequest(bool)), Qt::UniqueConnection);
        el->setVisible(false);
        m_resize_handles[point_type] = el;
    }
}

