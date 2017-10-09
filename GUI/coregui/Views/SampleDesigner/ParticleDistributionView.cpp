// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/ParticleDistributionView.cpp
//! @brief     Implements class ParticleDistributionView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ParticleDistributionView.h"
#include "SessionItem.h"

ParticleDistributionView::ParticleDistributionView(QGraphicsItem *parent)
    : ConnectableView(parent)
{
    setName(Constants::ParticleDistributionType);
    setColor(DesignerHelper::getDefaultParticleColor());
    setRectangle(DesignerHelper::getDefaultBoundingRect(Constants::ParticleDistributionType));
    addPort("out", NodeEditorPort::OUTPUT, NodeEditorPort::FORM_FACTOR)
        ->setToolTip(QStringLiteral("Connect to the ParticleLayout"));
    addPort("particle", NodeEditorPort::INPUT, NodeEditorPort::FORM_FACTOR)
    ->setToolTip(QStringLiteral("Connect particle to this port. It will be a prototype \n"
                                "for parametric distribution."));
    m_roundpar = 5;
    m_label_vspace = 45;
}

void ParticleDistributionView::addView(IView *childView, int /* row */)
{
    connectInputPort(dynamic_cast<ConnectableView *>(childView), 0);
}
