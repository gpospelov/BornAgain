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
#include "DesignerHelper.h"
#include <QPainter>
#include <QDebug>

RectangleView::RectangleView()
    : m_block_on_property_change(false)
{
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable);
    setAcceptHoverEvents(true);

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

//void RectangleView::setParameterizedItem(ParameterizedItem *item)
//{
//    IMaskView::setParameterizedItem(item);
//    setX(toSceneX(RectangleItem::P_POSX));
//    setY(toSceneY(RectangleItem::P_POSY));
//    update_view();
//}

void RectangleView::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{

    painter->setRenderHints(QPainter::Antialiasing);
    prepareGeometryChange();

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(DesignerHelper::getDefaultColor("Transparant red"));
    painter->setPen(brush.color().darker());
    painter->setBrush(brush);
    painter->drawRect(boundingRect());
}

void RectangleView::update_view()
{
    qDebug() << ">>>> IMaskView::update_view() -> ";
    update_bounding_rect();
    update_position();
    update();
}

void RectangleView::update_bounding_rect()
{
    if(m_item) {
        qreal item_ytop = par(RectangleItem::P_POSY);
        qreal item_yheight = par(RectangleItem::P_HEIGHT);
        qreal scene_ytop = toSceneY(item_ytop);
        qreal scene_ybot = toSceneY(item_ytop-item_yheight);

        qreal item_xleft = par(RectangleItem::P_POSX);
        qreal item_xwidth = par(RectangleItem::P_WIDTH);
        qreal scene_xleft = toSceneX(item_xleft);
        qreal scene_xright = toSceneX(item_xleft+item_xwidth);

        m_bounding_rect = QRectF(0.0, 0.0, scene_xright - scene_xleft,
                              scene_ybot-scene_ytop);
    }
    qDebug() << "RectangleView::calculate_bounding_rect()" << m_bounding_rect
             << "orig_width:" << par(RectangleItem::P_WIDTH)
             << "toSceneX(RectangleItem::P_WIDTH):" << toSceneX(RectangleItem::P_WIDTH)
             << "toSceneY(RectangleItem::P_HEIGHT):" << toSceneY(RectangleItem::P_HEIGHT);
}

void RectangleView::update_position()
{
    setX(toSceneX(RectangleItem::P_POSX));
    setY(toSceneY(RectangleItem::P_POSY));
    qDebug() << "RectangleView::update_position()" << pos();
}

