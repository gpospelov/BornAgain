#include "ParticleView.h"



ParticleView::ParticleView(QGraphicsItem *parent)
    : ConnectableView(parent)
{
    setName("Particle");
    setColor(DesignerHelper::getDefaultParticleColor());
    setRectangle( QRect(0, 0, DesignerHelper::getDefaultParticleWidth(), DesignerHelper::getDefaultParticleHeight()) );
    addPort("out", NodeEditorPort::Output, NodeEditorPort::FormFactor);
    addPort("transformation", NodeEditorPort::Input, NodeEditorPort::GeometryTransformation);
    m_roundpar = 5;
}

