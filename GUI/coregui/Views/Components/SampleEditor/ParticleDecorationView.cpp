#include "ParticleDecorationView.h"
#include "DesignerHelper.h"

#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsDropShadowEffect>
#include <iostream>

ParticleDecorationView::ParticleDecorationView(QGraphicsItem *parent)
    : ISampleRectView(parent)
{
    setName("ParticleDecoration");
    setLabel("Particle \ndecoration");
    setColor(QColor(135, 206, 50));
    setRectangle( QRect(0, 0, DesignerHelper::getDefaultDecorationWidth(), DesignerHelper::getDefaultDecorationHeight()) );
    addPort("out", QNEPort::Output, QNEPort::ParticleFactory);
    addPort("interference", QNEPort::Input, QNEPort::Interference);
    addPort("form factors", QNEPort::Input, QNEPort::FormFactor);
}


void ParticleDecorationView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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
    //double height = getRectangle().height()*0.2;
    //double yoffset = getRectangle().height()*0.05;
    double yoffset = 4;
    double height = m_label_vspace - yoffset;
    QFont serifFont("Monospace", 12, QFont::Normal);
    painter->setFont(serifFont);
    QRect textRect( getRectangle().x() + (getRectangle().width()-width)/2., getRectangle().y() + yoffset, width, height );
    painter->drawText(textRect, Qt::AlignCenter, tr("Particle \ndecoration"));
}


