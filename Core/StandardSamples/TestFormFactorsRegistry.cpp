#include "TestFormFactorsRegistry.h"
#include "Constants.h"
#include "FormFactors.h"

TestFormFactorsRegistry::TestFormFactorsRegistry()
{
    add(Constants::AnisoPyramidType) = new FormFactorAnisoPyramid(10.0, 20.0, 5.0, Units::deg2rad(54.73 ));
    add(Constants::BoxType) = new FormFactorBox(10.0, 20.0, 5.0);
    add(Constants::ConeType) = new FormFactorCone(5.0, 5.0, Units::deg2rad(54.73 ));
    add(Constants::Cone6Type) = new FormFactorCone6(2./sqrt(3.)*5.0, 5.0, Units::deg2rad(54.73));
    add(Constants::CuboctahedronType) = new FormFactorCuboctahedron(10.0, 5.0, 1.0, Units::deg2rad(54.73 ));
    add(Constants::CylinderType) = new FormFactorCylinder(5.0, 5.0);
    add(Constants::EllipsoidalCylinderType) = new FormFactorEllipsoidalCylinder(5.0, 10.0, 5.0);
    add(Constants::FullSphereType) = new FormFactorFullSphere(5.0);
    add(Constants::FullSpheroidType) = new FormFactorFullSpheroid(5.0, 5.0);
    add(Constants::HemiEllipsoidType) = new FormFactorHemiEllipsoid(5.0, 10.0, 5.0);
    add(Constants::Prism3Type) = new FormFactorPrism3(10.0, 5.0);
    add(Constants::Prism6Type) = new FormFactorPrism6(2./sqrt(3.)*5.0, 5.0);
    add(Constants::PyramidType) = new FormFactorPyramid(10.0, 5.0, Units::deg2rad(54.73 ));
    add(Constants::Ripple1Type) = new FormFactorRipple1(100.0, 20.0, 4.0);
    add(Constants::Ripple2Type) = new FormFactorRipple2(100.0, 20.0, 4.0, 0.0);
    add(Constants::TetrahedronType) = new FormFactorTetrahedron(10.0, 4.0, Units::deg2rad(54.73 ));
    add(Constants::TruncatedCubeType) = new FormFactorTruncatedCube(15.0, 6.0);
    add(Constants::TruncatedSphereType) = new FormFactorTruncatedSphere(5.0, 5.0);
    add(Constants::TruncatedSpheroidType) = new FormFactorTruncatedSpheroid(5.0, 5.0, 1.0);
}
