// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ParticleLayoutItem.cpp
//! @brief     Implements class ParticleLayoutItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "ParticleLayoutItem.h"
#include "ComboProperty.h"
#include "BornAgainNamespace.h"

namespace {

//! Returns true if name is related to 2D interference functions.
bool isInterference2D(const QString& name)
{
    if(name == Constants::InterferenceFunction2DLatticeType ||
       name == Constants::InterferenceFunction2DParaCrystalType)
        return true;
    return false;
}

const QString density_tooltip =
    "Number of particles per square nanometer (particle surface density).\n "
    "Should be defined for disordered and 1d-ordered particle collections.";
}

const QString ParticleLayoutItem::P_APPROX = "Approximation";
const QString ParticleLayoutItem::P_TOTAL_DENSITY
    = QString::fromStdString(BornAgain::TotalParticleDensity);
const QString ParticleLayoutItem::T_PARTICLES = "Particle Tag";
const QString ParticleLayoutItem::T_INTERFERENCE = "Interference Tag";

ParticleLayoutItem::ParticleLayoutItem() : SessionGraphicsItem(Constants::ParticleLayoutType)
{
    setToolTip(QStringLiteral("A layout of particles"));

    ComboProperty approx = ComboProperty() << Constants::LAYOUT_DA << Constants::LAYOUT_SSCA;
    addProperty(P_APPROX, approx.variant())->setToolTip(
        QStringLiteral("Approximation used to distribute the particles"));
    addProperty(P_TOTAL_DENSITY, 1.0)->setToolTip(density_tooltip);
    getItem(P_TOTAL_DENSITY)->setDecimals(10);

    registerTag(T_PARTICLES, 0, -1, QStringList() << Constants::ParticleType
                                                  << Constants::ParticleCoreShellType
                                                  << Constants::ParticleCompositionType
                                                  << Constants::MesoCrystalType
                                                  << Constants::ParticleDistributionType);
    setDefaultTag(T_PARTICLES);
    registerTag(T_INTERFERENCE, 0, 1, QStringList()
                                          << Constants::InterferenceFunctionRadialParaCrystalType
                                          << Constants::InterferenceFunction2DParaCrystalType
                                          << Constants::InterferenceFunction1DLatticeType
                                          << Constants::InterferenceFunction2DLatticeType);

    mapper()->setOnChildrenChange([this](SessionItem*) {
        updateDensityAppearance();
    });
}

//! Disables/enables total density property, depending on type of interference function.
//! Two dimensional interference calculates density automatically, so property should
//! be disabled.

void ParticleLayoutItem::updateDensityAppearance()
{
    getItem(P_TOTAL_DENSITY)->setEnabled(true);
    if(auto interferenceItem = getItem(T_INTERFERENCE))
        if (isInterference2D(interferenceItem->modelType()))
            getItem(P_TOTAL_DENSITY)->setEnabled(false);
}
