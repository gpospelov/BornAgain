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
#include "HardParticles.h"
#include "IFormFactor.h"
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
#include "TransformTo3D.h"
#include <ba3d/model/particles.h>

namespace
{
const int n = 10;

bool isPositionInsideMesoCrystal(const IFormFactor* outerShape, kvector_t positionInside)
{
    bool check(false);
    if (auto ff_Cylinder = dynamic_cast<const FormFactorCylinder*>(outerShape)) {
        double radius = ff_Cylinder->getRadius();
        double height = ff_Cylinder->getHeight();
        if (std::sqrt(std::pow(positionInside.x(),2) + std::pow(positionInside.y(),2)) <= radius &&
                (positionInside.z() >=0 && positionInside.z() <= height))
            check = true;
    }
    return check;
}

}

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

Particle3DContainer RealSpaceMesoCrystal::populateMesoCrystal(
        const IRotation* extra_rotation, kvector_t extra_translation)
{
    auto mesoCrystal = m_mesoCrystalItem->createMesoCrystal();

    std::unique_ptr<MesoCrystal> M_clone(mesoCrystal->clone()); // clone of the mesoCrystal
    M_clone->rotate(*extra_rotation);
    M_clone->translate(extra_translation);

    // These methods DO NOT add rotation/tranlation of the mesoCrystal to its children
    // and hence they need to be added manually
    auto lattice = m_mesoCrystalItem->getLattice();
    auto particleBasis = m_mesoCrystalItem->getBasis();
    auto outerShapeff = m_mesoCrystalItem->getOuterShape();

    auto mesoCrystal_rotation = M_clone->rotation();
    auto mesoCrystal_translation = M_clone->position();
    if(!mesoCrystal_rotation)
        mesoCrystal_rotation = IRotation::createIdentity();

    Particle3DContainer mesoCrystalBasis3DContainer;

    if (dynamic_cast<const ParticleComposition*>(particleBasis.get())) {
        auto particleComposition = dynamic_cast<const ParticleComposition*>(particleBasis.get());
        mesoCrystalBasis3DContainer
            = RealSpaceBuilderUtils::particleComposition3DContainer(
                    *particleComposition, 1.0, mesoCrystal_rotation, mesoCrystal_translation);
    } else if (dynamic_cast<const ParticleCoreShell*>(particleBasis.get())) {
        auto particleCoreShell = dynamic_cast<const ParticleCoreShell*>(particleBasis.get());
        mesoCrystalBasis3DContainer = RealSpaceBuilderUtils::particleCoreShell3DContainer(
                    *particleCoreShell, 1.0, mesoCrystal_rotation, mesoCrystal_translation);
    } else {
        auto particle = dynamic_cast<const Particle*>(particleBasis.get());
        mesoCrystalBasis3DContainer = RealSpaceBuilderUtils::singleParticle3DContainer(
                    *particle, 1.0, mesoCrystal_rotation, mesoCrystal_translation);
    }

    Particle3DContainer mesoCrystal3DContainer;

    for (int k = -n; k <= n; k++) {
        for (int j = -n; j <= n; j++) {
            for (int i = -n; i <= n; i++) {
                auto positionInside = i*lattice.getBasisVectorA() +
                        j*lattice.getBasisVectorB() + k*lattice.getBasisVectorC();

                if (isPositionInsideMesoCrystal(outerShapeff.get(), positionInside)) {
                    for (size_t it = 0; it < mesoCrystalBasis3DContainer.containerSize(); ++it) {
                        auto particle3D = mesoCrystalBasis3DContainer.createParticle(it);
                        particle3D->addTranslation(
                                    QVector3D(static_cast<float>(positionInside.x()),
                                              static_cast<float>(positionInside.y()),
                                              static_cast<float>(positionInside.z())));

                        mesoCrystal3DContainer.addParticle(particle3D.release(),
                            mesoCrystalBasis3DContainer.particle3DBlend(it));

                    }
                }
            }
        }
    }

    // Add outer shape for visualisation
    auto outerShape3D = TransformTo3D::createParticlefromIFormFactor(outerShapeff.get());
    outerShape3D->addTransform(
                RealSpaceBuilderUtils::implementParticleRotationfromIRotation(mesoCrystal_rotation),
                QVector3D(static_cast<float>(mesoCrystal_translation.x()),
                          static_cast<float>(mesoCrystal_translation.y()),
                          static_cast<float>(mesoCrystal_translation.z())));

    // assign grey correct color to the outer shape
    QColor color = QColor();
    color.setAlphaF(0.3);
    outerShape3D->color = color;
    mesoCrystal3DContainer.addParticle(outerShape3D.release(), true);


    // set the correct abundance for the MesoCrystal
    mesoCrystal3DContainer.setCumulativeAbundance(
                M_clone->abundance() / m_total_abundance);
    mesoCrystal3DContainer.setParticleType(Constants::MesoCrystalType);

    return mesoCrystal3DContainer;
}
