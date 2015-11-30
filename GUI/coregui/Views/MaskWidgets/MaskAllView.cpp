// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaskWidgets/MaskAllView.cpp
//! @brief     Implements MaskAllView class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MaskAllView.h"
#include "ColorMapSceneAdaptor.h"
#include "MaskItems.h"
#include "MaskEditorHelper.h"
#include <QPainter>
#include <QBrush>
#include <QStyleOptionGraphicsItem>
#include <QDebug>

MaskAllView::MaskAllView()
{
    setFlag(QGraphicsItem::ItemIsSelectable);

}

void MaskAllView::update_view()
{
    prepareGeometryChange();
    m_bounding_rect = m_adaptor->getViewportRectangle();
    update();
}

void MaskAllView::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
//    painter->setRenderHints(QPainter::Antialiasing);
    QColor color(250, 250, 240, 150);
    painter->setBrush(color);
    painter->drawRect(m_bounding_rect);

    if(isSelected()) {
        QPen pen;
        pen.setStyle(Qt::DashLine);
        painter->setPen(pen);
        painter->setBrush(Qt::NoBrush);
        painter->drawRect(m_bounding_rect);
    }
}
