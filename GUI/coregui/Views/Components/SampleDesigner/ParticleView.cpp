#include "ParticleView.h"



ParticleView::ParticleView(QGraphicsItem *parent)
    : ConnectableView(parent)
{
    setName("Particle");
    setColor(DesignerHelper::getDefaultFormFactorColor());
    setRectangle( QRect(0, 0, DesignerHelper::getDefaultFormFactorWidth(), DesignerHelper::getDefaultFormFactorHeight()) );
    addPort("out", NodeEditorPort::Output, NodeEditorPort::FormFactor);
    addPort("transformation", NodeEditorPort::Input, NodeEditorPort::GeometryTransformation);
    m_roundpar = 5;
}

