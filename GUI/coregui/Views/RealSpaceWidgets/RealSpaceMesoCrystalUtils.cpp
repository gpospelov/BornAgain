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
#include "Exceptions.h"
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
    if (auto ff_Box = dynamic_cast<const FormFactorBox*>(outerShape)) {
        double L = ff_Box->getLength();
        double W = ff_Box->getWidth();
        double H = ff_Box->getHeight();

        if (std::abs(positionInside.x()) <= L/2 && std::abs(positionInside.y()) <= W/2 &&
                (positionInside.z() >= 0 && positionInside.z() <= H))
            check = true;
    }
    else if (auto ff_Cylinder = dynamic_cast<const FormFactorCylinder*>(outerShape)) {
        double R = ff_Cylinder->getRadius();
        double H = ff_Cylinder->getHeight();

        if (std::abs(positionInside.x()) > R || std::abs(positionInside.y()) > R ||
                positionInside.z() > H)
            return check;

        if (std::sqrt(std::pow(positionInside.x(),2) + std::pow(positionInside.y(),2)) <= R &&
                (positionInside.z() >=0 && positionInside.z() <= H))
            check = true;
    }
    else if (dynamic_cast<const FormFactorDot*>(outerShape)) {
        std::ostringstream ostr;
        ostr << "Cannot display particles inside the Mesocrystal!";
        ostr << "\n\nOuter shape is a Dot!";
        throw Exceptions::ClassInitializationException(ostr.str());
    }
    else if (auto ff_EllipsoidalCylinder
             = dynamic_cast<const FormFactorEllipsoidalCylinder*>(outerShape)) {
        double a = ff_EllipsoidalCylinder->getRadiusX();
        double b = ff_EllipsoidalCylinder->getRadiusY();
        double H = ff_EllipsoidalCylinder->getHeight();

        if (std::abs(positionInside.x()) > a || std::abs(positionInside.y()) > b ||
                positionInside.z() > H)
            return check;

        if ((std::pow(positionInside.x()/a, 2) + std::pow(positionInside.y()/b, 2)) <= 1
                && (positionInside.z() >= 0 && positionInside.z() <= H))
            check = true;
    }
    else if (auto ff_FullSphere = dynamic_cast<const FormFactorFullSphere*>(outerShape)) {
        double R = ff_FullSphere->getRadius();

        if (std::abs(positionInside.x()) > R || std::abs(positionInside.y()) > R ||
                positionInside.z() > 2*R)
            return check;

        double r_z = std::sqrt(std::pow(R,2)-std::pow(positionInside.z()-R,2));
        if (std::sqrt(std::pow(positionInside.x(),2) + std::pow(positionInside.y(),2)) <= r_z &&
                (positionInside.z() >= 0 && positionInside.z() <= 2*R))
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
                    *particleComposition);
    } else if (dynamic_cast<const ParticleCoreShell*>(particleBasis.get())) {
        auto particleCoreShell = dynamic_cast<const ParticleCoreShell*>(particleBasis.get());
        mesoCrystalBasis3DContainer = RealSpaceBuilderUtils::particleCoreShell3DContainer(
                    *particleCoreShell);
    } else {
        auto particle = dynamic_cast<const Particle*>(particleBasis.get());
        mesoCrystalBasis3DContainer = RealSpaceBuilderUtils::singleParticle3DContainer(
                    *particle);
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

                        particle3D->addExtrinsicRotation(
                                    RealSpaceBuilderUtils::implementParticleRotationfromIRotation(
                                        mesoCrystal_rotation));

                        particle3D->addTranslation(
                                    QVector3D(static_cast<float>(mesoCrystal_translation.x()),
                                              static_cast<float>(mesoCrystal_translation.y()),
                                              static_cast<float>(mesoCrystal_translation.z())));

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

    // assign grey (default) color to the outer shape
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
