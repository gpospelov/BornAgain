// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/RealSpaceWidgets/RealSpaceBuilderUtils.h
//! @brief     Defines RealSpaceBuilderUtils namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "RealSpaceMesoCrystalUtils.h"
#include "IParticle.h"
#include "Lattice2DItems.h"
#include "MesoCrystal.h"
#include "MesoCrystalItem.h"
#include "Particle.h"
#include "Particle3DContainer.h"
#include "ParticleCompositionItem.h"
#include "ParticleCoreShell.h"
#include "ParticleCoreShellItem.h"
#include "ParticleDistribution.h"
#include "ParticleDistributionItem.h"
#include "RealSpaceBuilderUtils.h"

RealSpaceMesoCrystal::RealSpaceMesoCrystal()
    : m_mesoCrystalItem(nullptr)
    , m_total_abundance(0.0)
{
}

RealSpaceMesoCrystal::~RealSpaceMesoCrystal()
{
}

RealSpaceMesoCrystal::RealSpaceMesoCrystal(const MesoCrystalItem* mesoCrystalItem,
                                                     double total_abundance)
{
    m_mesoCrystalItem = mesoCrystalItem;
    m_total_abundance = total_abundance;
}

Particle3DContainer RealSpaceMesoCrystal::populateMesoCrystal()
{
    auto lattice = m_mesoCrystalItem->getLattice();
    auto particleBasis = m_mesoCrystalItem->getBasis();
    auto particleOuterShape = m_mesoCrystalItem->getOuterShape();

    Particle3DContainer mesoCrystal3DContainer;

    if (dynamic_cast<const ParticleComposition*>(particleBasis.get())) {
        auto particleComposition = dynamic_cast<const ParticleComposition*>(particleBasis.get());
        mesoCrystal3DContainer
            = RealSpaceBuilderUtils::particleComposition3DContainer(*particleComposition);
    } else if (dynamic_cast<const ParticleCoreShell*>(particleBasis.get())) {
        auto particleCoreShell = dynamic_cast<const ParticleCoreShell*>(particleBasis.get());
        mesoCrystal3DContainer = RealSpaceBuilderUtils::particleCoreShell3DContainer(*particleCoreShell);
    } else {
        auto particle = dynamic_cast<const Particle*>(particleBasis.get());
        mesoCrystal3DContainer = RealSpaceBuilderUtils::singleParticle3DContainer(*particle);
    }

    // set the correct abundance for the MesoCrystal
    mesoCrystal3DContainer.setCumulativeAbundance(
                m_mesoCrystalItem->createMesoCrystal()->abundance() / m_total_abundance);
    mesoCrystal3DContainer.setParticleType(Constants::MesoCrystalType);

    return mesoCrystal3DContainer;
}
