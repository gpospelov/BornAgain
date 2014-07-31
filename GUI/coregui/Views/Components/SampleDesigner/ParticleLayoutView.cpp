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
    addPort("out", NodeEditorPort::Output, NodeEditorPort::ParticleLayout);
    addPort("particle", NodeEditorPort::Input, NodeEditorPort::FormFactor);
    addPort("interference", NodeEditorPort::Input, NodeEditorPort::Interference);
    m_roundpar = 3;
}


void ParticleLayoutView::addView(IView *childView, int /* row */)
{
    qDebug() << "ParticleLayoutView::addView() xxx " << m_item->itemName() << childView->getParameterizedItem()->itemName() << childView->type() << DesignerHelper::ParticleType;
    if(childView->type() == DesignerHelper::ParticleType) {
        connectInputPort(dynamic_cast<ConnectableView *>(childView), 0);
    }
    else if(childView->type() == DesignerHelper::InterferenceFunction1DParaType
            || childView->type() == DesignerHelper::InterferenceFunction2DParaType) {
        connectInputPort(dynamic_cast<ConnectableView *>(childView), 1);
    }
    else {
        throw GUIHelpers::Error("ParticleLayoutView::addView() -> Error. Unknown view");
    }
}
