// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/SampleDesigner/ParticleLayoutView.cpp
//! @brief     Implements class ParticleLayoutView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

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
    setColor(QColor(135, 206, 50));
    setRectangle( DesignerHelper::getDefaultBoundingRect(Constants::ParticleLayoutType));
    addPort("out", NodeEditorPort::OUTPUT, NodeEditorPort::PARTICLE_LAYOUT);
    addPort("particle", NodeEditorPort::INPUT, NodeEditorPort::FORM_FACTOR);
    addPort("interference", NodeEditorPort::INPUT, NodeEditorPort::INTERFERENCE);
    m_roundpar = 3;
}

void ParticleLayoutView::addView(IView *childView, int /* row */)
{
    qDebug() << "ParticleLayoutView::addView() xxx " << m_item->name()
             << childView->getParameterizedItem()->name() << childView->type()
             << DesignerHelper::PARTICLE;
    if(childView->type() == DesignerHelper::PARTICLE) {
        connectInputPort(dynamic_cast<ConnectableView *>(childView), 0);
    }
    else if(childView->type() == DesignerHelper::INTERFERENCE_FUNCTION_RADIAL_PARA
         || childView->type() == DesignerHelper::INTERFERENCE_FUNCTION_2D_PARA
         || childView->type() == DesignerHelper::INTERFERENCE_FUNCTION_1D_LATTICE
         || childView->type() == DesignerHelper::INTERFERENCE_FUNCTION_2D_LATTICE) {
        connectInputPort(dynamic_cast<ConnectableView *>(childView), 1);
    }
    else {
        throw GUIHelpers::Error("ParticleLayoutView::addView() -> Error. Unknown view");
    }
}
