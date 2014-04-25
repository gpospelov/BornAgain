#include "ParticleLayoutView.h"
#include "ParticleView.h"
#include "DesignerHelper.h"
#include "ParameterizedItem.h"
#include <QDebug>


ParticleLayoutView::ParticleLayoutView(QGraphicsItem *parent)
    : ConnectableView(parent)
{
    setName("ParticleLayout");
    setLabel("Particle \nlayout");
    setColor(QColor(135, 206, 50));
    setRectangle( DesignerHelper::getDefaultBoundingRect("ParticleLayout"));
    addPort("out", NodeEditorPort::Output, NodeEditorPort::ParticleFactory);
    addPort("interference", NodeEditorPort::Input, NodeEditorPort::Interference);
    addPort("particle", NodeEditorPort::Input, NodeEditorPort::FormFactor);
    m_roundpar = 3;
}


void ParticleLayoutView::addView(IView *childView, int /* row */)
{
    qDebug() << "ParticleLayoutView::addView() " << m_item->itemName() << childView->getParameterizedItem()->itemName();
    ParticleView *particle = dynamic_cast<ParticleView *>(childView);
    Q_ASSERT(particle);
    connectInputPort(particle);

}
