#include "ParticleDecorationView.h"
#include "DesignerHelper.h"


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
    m_roundpar = 3;
}
