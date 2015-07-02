// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/TestComponentsRegistry.cpp
//! @brief     Defines different registries for functional test component service.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "TestComponentsRegistry.h"
#include "BornAgainNamespace.h"
#include "FormFactors.h"
#include "FTDistributions.h"

TestFTDistribution2DRegistry::TestFTDistribution2DRegistry()
{
    add(BornAgain::FTDistribution2DCauchyType, new FTDistribution2DCauchy(0.5, 1.0));
    add(BornAgain::FTDistribution2DGaussType, new FTDistribution2DGauss(0.5, 1.0));
    add(BornAgain::FTDistribution2DGateType, new FTDistribution2DGate(0.5, 1.0));
    add(BornAgain::FTDistribution2DConeType, new FTDistribution2DCone(0.5, 1.0));
    add(BornAgain::FTDistribution2DVoigtType, new FTDistribution2DVoigt(0.5, 1.0, 0.2));
}

// ----------------------------------------------------------------------------

TestFormFactorsRegistry::TestFormFactorsRegistry()
{
    add(BornAgain::AnisoPyramidType,
        new FormFactorAnisoPyramid(10.0, 20.0, 5.0, Units::deg2rad(54.73 )));

    add(BornAgain::BoxType,
        new FormFactorBox(10.0, 20.0, 5.0));

    add(BornAgain::ConeType,
        new FormFactorCone(5.0, 6.0, Units::deg2rad(54.73 )));

    add(BornAgain::Cone6Type,
        new FormFactorCone6(2./sqrt(3.)*5.0, 5.0, Units::deg2rad(54.73)));

    add(BornAgain::CuboctahedronType,
        new FormFactorCuboctahedron(10.0, 5.0, 1.0, Units::deg2rad(54.73 )));

    add(BornAgain::CylinderType,
        new FormFactorCylinder(5.0, 10.0));

    add(BornAgain::EllipsoidalCylinderType,
        new FormFactorEllipsoidalCylinder(5.0, 10.0, 15.0));

    add(BornAgain::FullSphereType,
        new FormFactorFullSphere(5.0));

    add(BornAgain::FullSpheroidType,
        new FormFactorFullSpheroid(5.0, 10.0));

    add(BornAgain::HemiEllipsoidType,
        new FormFactorHemiEllipsoid(5.0, 10.0, 15.0));

    add(BornAgain::Prism3Type,
        new FormFactorPrism3(10.0, 5.0));

    add(BornAgain::Prism6Type,
        new FormFactorPrism6(2./sqrt(3.)*5.0, 5.0));

    add(BornAgain::PyramidType,
        new FormFactorPyramid(10.0, 5.0, Units::deg2rad(54.73 )));

    add(BornAgain::Ripple1Type,
        new FormFactorRipple1(100.0, 20.0, 4.0));

    add(BornAgain::Ripple2Type,
        new FormFactorRipple2(100.0, 20.0, 4.0, 0.0));

    add(BornAgain::TetrahedronType,
        new FormFactorTetrahedron(10.0, 4.0, Units::deg2rad(54.73 )));

    add(BornAgain::TruncatedCubeType,
        new FormFactorTruncatedCube(15.0, 6.0));

    add(BornAgain::TruncatedSphereType,
        new FormFactorTruncatedSphere(5.0, 7.0));

    add(BornAgain::TruncatedSpheroidType,
        new FormFactorTruncatedSpheroid(5.0, 7.0, 1.0));
}
