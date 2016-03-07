// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/ParticleLayoutItem.cpp
//! @brief     Implements class ParticleLayoutItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ParticleLayoutItem.h"
#include "ParticleCoreShellItem.h"
#include "ParticleDistributionItem.h"
#include "ComboProperty.h"

const QString ParticleLayoutItem::P_APPROX = "Approximation";
const QString ParticleLayoutItem::P_TOTAL_DENSITY = "Total particle density";
const QString ParticleLayoutItem::T_PARTICLES = "Particle Tag";
const QString ParticleLayoutItem::T_INTERFERENCE = "Interference Tag";

ParticleLayoutItem::ParticleLayoutItem()
    : ParameterizedGraphicsItem(Constants::ParticleLayoutType)
{
    ComboProperty approx;
    approx << "Decoupling Approximation" << "Size Space Coupling Approximation";
    registerProperty(P_APPROX, approx.getVariant());
    registerProperty(P_TOTAL_DENSITY, 1.0);

    registerTag(T_PARTICLES, 0, -1, QStringList() << Constants::ParticleType << Constants::ParticleCoreShellType
                << Constants::ParticleCompositionType << Constants::ParticleDistributionType);
    setDefaultTag(T_PARTICLES);
    registerTag(T_INTERFERENCE, 0, 1, QStringList() << Constants::InterferenceFunctionRadialParaCrystalType
                << Constants::InterferenceFunction2DParaCrystalType << Constants::InterferenceFunction1DLatticeType
                << Constants::InterferenceFunction2DLatticeType);

    // FIXME: not updated when child get removed
    mapper()->setOnChildPropertyChange(
                [this](ParameterizedItem *, const QString &)
    {
        for (auto child_item : childItems()) {
            if (child_item->modelType() == Constants::InterferenceFunction2DParaCrystalType
                || child_item->modelType() == Constants::InterferenceFunction2DLatticeType) {
                getItem(P_TOTAL_DENSITY)->setEnabled(false);
                return;
            }
        }
        getItem(P_TOTAL_DENSITY)->setEnabled(true);
    });
}

ParticleLayoutItem::~ParticleLayoutItem()
{
}
