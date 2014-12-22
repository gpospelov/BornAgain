// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Models/ParticleDistributionItem.cpp
//! @brief     Implements class ParticleDistributionItem.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ParticleDistributionItem.h"
#include "ComboProperty.h"

const QString ParticleDistributionItem::P_DISTRIBUTED_PARAMETER =
        "Distributed parameter";
const QString ParticleDistributionItem::P_DISTRIBUTION = "Distribution";
const QString ParticleDistributionItem::P_SAMPLE_NUMBER = "Number of samples";
const QString ParticleDistributionItem::P_SIGMA_FACTOR = "Sigma factor";


ParticleDistributionItem::ParticleDistributionItem(ParameterizedItem *parent)
    : ParameterizedGraphicsItem(Constants::ParticleDistributionType, parent)
{
    setItemName(Constants::ParticleDistributionType);
    setItemPort(ParameterizedItem::PortInfo::Port0);

    ComboProperty par_name;
    par_name << "*/radius" << "*/height";
    registerProperty(P_DISTRIBUTED_PARAMETER, par_name.getVariant());
    registerGroupProperty(P_DISTRIBUTION, Constants::DistributionGroup);
    registerProperty(P_SAMPLE_NUMBER, 5);
    registerProperty(P_SIGMA_FACTOR, 2.0);

    addToValidChildren(Constants::ParticleType, PortInfo::Port0);
    addToValidChildren(Constants::ParticleCoreShellType, PortInfo::Port0);
}

ParticleDistributionItem::~ParticleDistributionItem()
{
}

QStringList ParticleDistributionItem::getChildParameterNames() const
{
    QStringList result;
    if (hasChildItems()) {
        for (QList::iterator it = m_children.begin();
             it != m_children.end(); ++it) {
            //TODO: add parameters to result
        }
    }
}

