#include "ParticleDecorationView.h"
#include "DesignerHelper.h"
#include "qneport.h"

#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsDropShadowEffect>
#include <iostream>

ParticleDecorationView::ParticleDecorationView(QGraphicsItem *parent)
    : ISampleView(parent)
    , m_name("ParticleDecoration")
    , m_color(QColor(135,206, 50))
    , m_rect(0, 0, DesignerHelper::getDefaultDecorationWidth(), DesignerHelper::getDefaultDecorationHeight())
{
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
    effect->setBlurRadius(8);
    effect->setOffset(2,2);
    setGraphicsEffect(effect);

    addPort("out", true);
    addPort("interference", false);
    addPort("form factors", false);
}


QRectF ParticleDecorationView::boundingRect() const
{
    return rect();
}

void ParticleDecorationView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    painter->setPen(Qt::gray);
    if (option->state & (QStyle::State_Selected | QStyle::State_HasFocus)) {
        painter->setPen(Qt::DashLine);
    }
    painter->setBrush(DesignerHelper::getDecorationGradient(m_color, rect() ) );
    painter->drawRoundedRect(rect(), 3, 3);
    // label
    painter->setPen(Qt::black);
    double width = rect().width()*0.9;
    double height = rect().height()*0.2;
    double yoffset = rect().height()*0.05;
    QFont serifFont("Monospace", 12, QFont::Normal);
    painter->setFont(serifFont);
    QRect textRect( rect().x() + (rect().width()-width)/2., rect().y() + yoffset, width, height );
    painter->drawText(textRect, Qt::AlignCenter, tr("Particle \ndecoration"));
}



QNEPort* ParticleDecorationView::addPort(const QString &name, bool isOutput, int flags, int ptr)
{
    QNEPort *port = new QNEPort(this, name, isOutput);
    port->setNEBlock(this);

    Q_ASSERT(childItems().size());
    int hspace =rect().height()*0.7;
    int dy = hspace / (childItems().size() + 2);
    int ypos = rect().height() - hspace + dy;

    int nOutPorts = getNumberOfOutputPorts();
    int nport(0);
    foreach(QGraphicsItem *port_, childItems()) {
        QNEPort *port = (QNEPort*) port_;
        if (port->isOutput()) {
            port->setPos(rect().width(), ypos);
        }else{
            if(nport == nOutPorts) ypos +=dy; // additional margin between output and input ports
            port->setPos(0.0, ypos);
        }
        ypos += dy;
        nport++;
    }

    return port;
}


int ParticleDecorationView::getNumberOfOutputPorts()
{
    int result(0);
    foreach(QGraphicsItem *port_, childItems()) {
        QNEPort *port = (QNEPort*) port_;
        if (port->isOutput()) result++;
    }
    return result;
}

int ParticleDecorationView::getNumberOfInputPorts()
{
    return childItems().size() - getNumberOfOutputPorts();
}

