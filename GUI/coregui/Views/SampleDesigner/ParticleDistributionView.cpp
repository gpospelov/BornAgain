// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/SampleDesigner/ParticleDistributionView.cpp
//! @brief     Implements class ParticleDistributionView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ParticleDistributionView.h"
#include "ParameterizedItem.h"
#include <QDebug>


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
    int index = int(childView->getParameterizedItem()->port());
//                    ->getRegisteredProperty(ParameterizedItem::OBSOLETE_P_PORT)
//                    .toInt();
    qDebug() << "ParticleDistributionType::addView()" << index;
    connectInputPort(dynamic_cast<ConnectableView *>(childView), index);
}
