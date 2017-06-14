// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ParticleLayoutItem.cpp
//! @brief     Implements class ParticleLayoutItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ParticleLayoutItem.h"
#include "ComboProperty.h"
#include "BornAgainNamespace.h"

const QString ParticleLayoutItem::P_APPROX = "Approximation";
const QString ParticleLayoutItem::P_TOTAL_DENSITY
    = QString::fromStdString(BornAgain::TotalParticleDensity);
const QString ParticleLayoutItem::T_PARTICLES = "Particle Tag";
const QString ParticleLayoutItem::T_INTERFERENCE = "Interference Tag";

ParticleLayoutItem::ParticleLayoutItem()
    : SessionGraphicsItem(Constants::ParticleLayoutType)
{
    ComboProperty approx = ComboProperty() << Constants::LAYOUT_DA << Constants::LAYOUT_SSCA;
    addProperty(P_APPROX, approx.getVariant());
    addProperty(P_TOTAL_DENSITY, 1.0);
    getItem(P_TOTAL_DENSITY)->setDecimals(10);

    registerTag(T_PARTICLES, 0, -1, QStringList() << Constants::ParticleType << Constants::ParticleCoreShellType
                << Constants::ParticleCompositionType << Constants::ParticleDistributionType);
    setDefaultTag(T_PARTICLES);
    registerTag(T_INTERFERENCE, 0, 1, QStringList() << Constants::InterferenceFunctionRadialParaCrystalType
                << Constants::InterferenceFunction2DParaCrystalType << Constants::InterferenceFunction1DLatticeType
                << Constants::InterferenceFunction2DLatticeType);

    mapper()->setOnChildrenChange(
                [this](SessionItem* item)
    {
        int count = 0;
        for (auto child_item : childItems()) {
            if (child_item->modelType() == Constants::InterferenceFunction2DParaCrystalType
                || child_item->modelType() == Constants::InterferenceFunction2DLatticeType) {
                count++;
            }
        }
        if ((item && count > 0) || (!item && count > 1))
            getItem(P_TOTAL_DENSITY)->setEnabled(false);
        else
            getItem(P_TOTAL_DENSITY)->setEnabled(true);
    });
}

ParticleLayoutItem::~ParticleLayoutItem()
{
}
