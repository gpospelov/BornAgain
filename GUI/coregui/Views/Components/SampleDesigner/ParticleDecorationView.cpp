#include "ParticleDecorationView.h"
#include "DesignerHelper.h"


ParticleDecorationView::ParticleDecorationView(QGraphicsItem *parent)
    : ISampleRectView(parent)
{
    setName("ParticleDecoration");
    setLabel("Particle \ndecoration");
    setColor(QColor(135, 206, 50));
    setRectangle( QRect(0, 0, DesignerHelper::getDefaultDecorationWidth(), DesignerHelper::getDefaultDecorationHeight()) );
    addPort("out", NodeEditorPort::Output, NodeEditorPort::ParticleFactory);
    addPort("interference", NodeEditorPort::Input, NodeEditorPort::Interference);
    addPort("form factors", NodeEditorPort::Input, NodeEditorPort::FormFactor);
    m_roundpar = 3;
}
