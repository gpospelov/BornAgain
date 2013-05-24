#include "InterferenceFunction1DParacrystalView.h"
#include "DesignerHelper.h"

#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsDropShadowEffect>
#include <iostream>

InterferenceFunction1DParaCrystalView::InterferenceFunction1DParaCrystalView(QGraphicsItem *parent)
    : ISampleRectView(parent)
{
    setName("InterferenceFunction1DParaCrystal");
    setColor(QColor(240, 255, 255));
    setRectangle( QRect(0, 0, DesignerHelper::getDefaultInterferenceFunctionWidth(), DesignerHelper::getDefaultInterferenceFunctionHeight()) );

//    addPort("out", true);
    addPort("out", QNEPort::Output, QNEPort::Interference);
}


void InterferenceFunction1DParaCrystalView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    painter->setPen(Qt::gray);
    if (option->state & (QStyle::State_Selected | QStyle::State_HasFocus)) {
        painter->setPen(Qt::DashLine);
    }
    painter->setBrush(DesignerHelper::getDecorationGradient(m_color, getRectangle() ) );
    painter->drawRoundedRect(getRectangle(), 3, 3);
    // label
    painter->setPen(Qt::black);
    double width = getRectangle().width()*0.9;
    double height = getRectangle().height()*0.3;
    double yoffset = getRectangle().height()*0.05;
    QFont serifFont("Monospace", 12, QFont::Normal);
    painter->setFont(serifFont);
    QRect textRect( getRectangle().x() + (getRectangle().width()-width)/2., getRectangle().y() + yoffset, width, height );
    painter->drawText(textRect, Qt::AlignCenter, tr("Interference \n1D paracrystal"));
}


