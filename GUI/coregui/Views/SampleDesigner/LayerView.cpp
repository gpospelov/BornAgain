// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/SampleDesigner/LayerView.cpp
//! @brief     Implements class LayerView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "LayerView.h"
#include "LayerItem.h"
#include "ParticleLayoutView.h"
#include "SessionItem.h"
#include "MaterialProperty.h"
#include "tooltipdatabase.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QDebug>



LayerView::LayerView(QGraphicsItem *parent)
    : ILayerView(parent)
{
    setColor(QColor(qrand() % 256, qrand() % 256, qrand() % 256) );
    setName(Constants::LayerType);
    setRectangle(DesignerHelper::getDefaultBoundingRect(Constants::LayerType));
    //setToolTip(QString("%1\n%2").arg("Layer").arg("A layer with thickness and material.\nCan be connected with ParticleLayout."));
    setToolTip(ToolTipDataBase::getSampleViewDesignerToolTip(Constants::LayerType));
    setAcceptDrops(false);
    addPort(QString(), NodeEditorPort::INPUT, NodeEditorPort::PARTICLE_LAYOUT);
}


void LayerView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    painter->setPen(Qt::black);
    if (option->state & (QStyle::State_Selected | QStyle::State_HasFocus)) {
        painter->setPen(Qt::DashLine);
    }
    painter->setBrush(DesignerHelper::getLayerGradient(m_color, getRectangle() ) );
    painter->drawRect(getRectangle());
}


void LayerView::addView(IView *childView, int /* row */)
{
    qDebug() << "LayerView::addView() " << m_item->itemName() << childView->getItem()->itemName();
    ParticleLayoutView *layout = dynamic_cast<ParticleLayoutView *>(childView);
    Q_ASSERT(layout);
    connectInputPort(layout, 0);
}

//QVariant LayerView::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
//{
//    return QGraphicsItem::itemChange(change, value);
//}
