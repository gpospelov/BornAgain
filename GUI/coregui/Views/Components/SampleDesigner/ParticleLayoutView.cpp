#include "ParticleLayoutView.h"
#include "ParticleView.h"
#include "DesignerHelper.h"
#include "ParameterizedItem.h"
#include "GUIHelpers.h"
#include <QDebug>


ParticleLayoutView::ParticleLayoutView(QGraphicsItem *parent)
    : ConnectableView(parent)
{
    setName(Constants::ParticleLayoutType);
    setLabel("Particle \nlayout");
    setColor(QColor(135, 206, 50));
    setRectangle( DesignerHelper::getDefaultBoundingRect(Constants::ParticleLayoutType));
    addPort("out", NodeEditorPort::OUTPUT, NodeEditorPort::PARTICLE_LAYOUT);
    addPort("particle", NodeEditorPort::INPUT, NodeEditorPort::FORM_FACTOR);
    addPort("interference", NodeEditorPort::INPUT, NodeEditorPort::INTERFERENCE);
    m_roundpar = 3;
}


void ParticleLayoutView::addView(IView *childView, int /* row */)
{
    qDebug() << "ParticleLayoutView::addView() xxx " << m_item->itemName() << childView->getParameterizedItem()->itemName() << childView->type() << DesignerHelper::PARTICLE;
    if(childView->type() == DesignerHelper::PARTICLE) {
        connectInputPort(dynamic_cast<ConnectableView *>(childView), 0);
    }
    else if(childView->type() == DesignerHelper::INTERFERENCE_FUNCTION_1D_PARA
         || childView->type() == DesignerHelper::INTERFERENCE_FUNCTION_2D_PARA
         || childView->type() == DesignerHelper::INTERFERENCE_FUNCTION_2D_LATTICE) {
        connectInputPort(dynamic_cast<ConnectableView *>(childView), 1);
    }
    else {
        throw GUIHelpers::Error("ParticleLayoutView::addView() -> Error. Unknown view");
    }
}
