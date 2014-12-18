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

const QString ParticleDistributionItem::P_PARAMETER_NAME =
        "Distributed parameter name";

ParticleDistributionItem::ParticleDistributionItem(ParameterizedItem *parent)
    : ParameterizedGraphicsItem(Constants::ParticleDistributionType, parent)
{
    setItemName(Constants::ParticleDistributionType);
    setItemPort(ParameterizedItem::PortInfo::Port0);

    ComboProperty par_name;
    par_name << "Radius" << "Height";
    registerProperty(P_PARAMETER_NAME, par_name.getVariant());

    addToValidChildren(Constants::ParticleType, PortInfo::Port0);
    addToValidChildren(Constants::ParticleCoreShellType, PortInfo::Port0);
}

ParticleDistributionItem::~ParticleDistributionItem()
{
}

