#include "ParticleDistributionView.h"
#include "ParameterizedItem.h"
#include <QDebug>


ParticleDistributionView::ParticleDistributionView(QGraphicsItem *parent)
    : ConnectableView(parent)
{
    setName(Constants::ParticleDistributionType);
    setLabel("Distributed\nparticle");
    setColor(DesignerHelper::getDefaultParticleColor());
    setRectangle(DesignerHelper::getDefaultBoundingRect(Constants::ParticleDistributionType));
    addPort("out", NodeEditorPort::Output, NodeEditorPort::FormFactor);
    addPort("particle", NodeEditorPort::Input, NodeEditorPort::FormFactor);
    m_roundpar = 5;
    m_label_vspace = 45;
}


void ParticleDistributionView::addView(IView *childView, int /* row */)
{
    int index = childView->getParameterizedItem()->getRegisteredProperty(ParameterizedItem::P_PORT).toInt();
    qDebug() << "ParticleDistributionType::addView()" << index;
    connectInputPort(dynamic_cast<ConnectableView *>(childView), index);
}
