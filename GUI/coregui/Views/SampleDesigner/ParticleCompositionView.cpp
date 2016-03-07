// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/SampleDesigner/ParticleCompositionView.cpp
//! @brief     Implements class ParticleCompositionView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ParticleCompositionView.h"
#include "ParameterizedItem.h"
#include <QDebug>

ParticleCompositionView::ParticleCompositionView(QGraphicsItem *parent) : ConnectableView(parent)
{
    setName(Constants::ParticleCompositionType);
    setColor(DesignerHelper::getDefaultParticleColor());
    setRectangle(DesignerHelper::getDefaultBoundingRect(Constants::ParticleCoreShellType));
    addPort("out", NodeEditorPort::OUTPUT, NodeEditorPort::FORM_FACTOR);
    addPort("particles", NodeEditorPort::INPUT, NodeEditorPort::FORM_FACTOR);
    addPort("transformation", NodeEditorPort::INPUT, NodeEditorPort::TRANSFORMATION);
    m_roundpar = 5;
    m_label_vspace = 45;
}

void ParticleCompositionView::addView(IView *childView, int /* row */)
{
    // TODO restore logic
    int index = 0;//int(childView->getParameterizedItem()->port());
//                    ->getRegisteredProperty(ParameterizedItem::OBSOLETE_P_PORT)
//                    .toInt();
    qDebug() << "ParticleCompositionView::addView()" << index;
    connectInputPort(dynamic_cast<ConnectableView *>(childView), index);
}
