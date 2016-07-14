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

#include <QDebug>
#include "SessionItem.h"
#include "ParticleDistributionView.h"


ParticleDistributionView::ParticleDistributionView(QGraphicsItem *parent)
    : ConnectableView(parent)
{
    setName(Constants::ParticleDistributionType);
    setColor(DesignerHelper::getDefaultParticleColor());
    setRectangle(DesignerHelper::getDefaultBoundingRect(Constants::ParticleDistributionType));
    addPort("out", NodeEditorPort::OUTPUT, NodeEditorPort::FORM_FACTOR);
    addPort("particle", NodeEditorPort::INPUT, NodeEditorPort::FORM_FACTOR);
    m_roundpar = 5;
    m_label_vspace = 45;
}

void ParticleDistributionView::addView(IView *childView, int /* row */)
{
    // TODO restore logic
    int index = 0;//int(childView->getParameterizedItem()->port());
//                    ->getRegisteredProperty(ParameterizedItem::OBSOLETE_P_PORT)
//                    .toInt();
    qDebug() << "ParticleDistributionType::addView()" << index;
    connectInputPort(dynamic_cast<ConnectableView *>(childView), index);
}
