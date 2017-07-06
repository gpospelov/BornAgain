#include "TestGUICoreObjectCorrespondence.h"
#include "GUICoreObjectCorrespondence.h"
#include "FormFactors.h"
#include "InterferenceFunctions.h"
#include "FormFactorItems.h"
#include "InterferenceFunctionItems.h"
#include "Units.h"

void TestGUICoreObjectCorrespondence::test_AnisoPyramid()
{
    AnisoPyramidItem gui_anisopyramid;
    FormFactorAnisoPyramid core_anisopyramid(1.0, 2.0, 0.1, 45.0*Units::degree);
    GUICoreObjectCorrespondence(gui_anisopyramid, core_anisopyramid);
}

void TestGUICoreObjectCorrespondence::test_Box()
{
    BoxItem gui_box;
    FormFactorBox core_box(1.0, 1.5, 3.0);
    GUICoreObjectCorrespondence(gui_box, core_box);
}

void TestGUICoreObjectCorrespondence::test_Cone()
{
    ConeItem gui_cone;
    FormFactorCone core_cone(1.0, 0.2, 45.0*Units::degree);
    GUICoreObjectCorrespondence(gui_cone, core_cone);
}

void TestGUICoreObjectCorrespondence::test_Cone6()
{
    Cone6Item gui_cone6;
    FormFactorCone6 core_cone6(1.0, 0.2, 45.0*Units::degree);
    GUICoreObjectCorrespondence(gui_cone6, core_cone6);
}

void TestGUICoreObjectCorrespondence::test_Cuboctahedron()
{
    CuboctahedronItem gui_cuboctahedron;
    FormFactorCuboctahedron core_cuboctahedron(1.0, 0.4, 1.0, 45.0*Units::degree);
    GUICoreObjectCorrespondence(gui_cuboctahedron, core_cuboctahedron);
}

void TestGUICoreObjectCorrespondence::test_Dodecahedron()
{
    DodecahedronItem gui_dodecahedron;
    FormFactorDodecahedron core_dodecahedron(3.0);
    GUICoreObjectCorrespondence(gui_dodecahedron, core_dodecahedron);
}

void TestGUICoreObjectCorrespondence::test_Dot()
{
    DotItem gui_dot;
    FormFactorTrivial core_dot;
    GUICoreObjectCorrespondence(gui_dot, core_dot);
}

void TestGUICoreObjectCorrespondence::test_Cylinder()
{
    CylinderItem gui_cylinder;
    FormFactorCylinder core_cylinder(1.0, 3.0);
    GUICoreObjectCorrespondence(gui_cylinder, core_cylinder);
}

void TestGUICoreObjectCorrespondence::test_EllipsoidalCylinder()
{
    EllipsoidalCylinderItem gui_ellcylinder;
    FormFactorEllipsoidalCylinder core_ellcylinder(2.0, 1.0, 1.0);
    GUICoreObjectCorrespondence(gui_ellcylinder, core_ellcylinder);
}

void TestGUICoreObjectCorrespondence::test_FullSphere()
{
    FullSphereItem gui_sphere;
    FormFactorFullSphere core_sphere(1.0);
    GUICoreObjectCorrespondence(gui_sphere, core_sphere);
}

void TestGUICoreObjectCorrespondence::test_FullSpheroid()
{
    FullSpheroidItem gui_spheroid;
    FormFactorFullSpheroid core_spheroid(1.0, 2.0);
    GUICoreObjectCorrespondence(gui_spheroid, core_spheroid);
}

void TestGUICoreObjectCorrespondence::test_HemiEllipsoid()
{
    HemiEllipsoidItem gui_hemiellipsoid;
    FormFactorHemiEllipsoid core_hemiellipsoid(2.0, 1.0, 0.5);
    GUICoreObjectCorrespondence(gui_hemiellipsoid, core_hemiellipsoid);
}

void TestGUICoreObjectCorrespondence::test_Icosahedron()
{
    IcosahedronItem gui_icosahedron;
    FormFactorIcosahedron core_icosahedron(8.0);
    GUICoreObjectCorrespondence(gui_icosahedron, core_icosahedron);
}

void TestGUICoreObjectCorrespondence::test_Prism3()
{
    Prism3Item gui_prism3;
    FormFactorPrism3 core_prism3(1.0, 2.0);
    GUICoreObjectCorrespondence(gui_prism3, core_prism3);
}

void TestGUICoreObjectCorrespondence::test_Prism6()
{
    Prism6Item gui_prism6;
    FormFactorPrism6 core_prism6(1.0, 2.0);
    GUICoreObjectCorrespondence(gui_prism6, core_prism6);
}

void TestGUICoreObjectCorrespondence::test_Pyramid()
{
    PyramidItem gui_pyramid;
    FormFactorPyramid core_pyramid(1.0, 0.2, 45.0*Units::degree);
    GUICoreObjectCorrespondence(gui_pyramid, core_pyramid);
}

void TestGUICoreObjectCorrespondence::test_Ripple1()
{
    Ripple1Item gui_ripple1;
    FormFactorRipple1 core_ripple1(10.0, 2.0, 1.0);
    GUICoreObjectCorrespondence(gui_ripple1, core_ripple1);
}

void TestGUICoreObjectCorrespondence::test_Ripple2()
{
    Ripple2Item gui_ripple2;
    FormFactorRipple2 core_ripple2(10.0, 2.0, 1.0, 0.1);
    GUICoreObjectCorrespondence(gui_ripple2, core_ripple2);
}

void TestGUICoreObjectCorrespondence::test_Tetrahedron()
{
    TetrahedronItem gui_tetrahedron;
    FormFactorTetrahedron core_tetrahedron(1.0, 0.1, 45.0*Units::degree);
    GUICoreObjectCorrespondence(gui_tetrahedron, core_tetrahedron);
}

void TestGUICoreObjectCorrespondence::test_TruncatedCube()
{
    TruncatedCubeItem gui_trunccube;
    FormFactorTruncatedCube core_trunccube(2.0, 0.2);
    GUICoreObjectCorrespondence(gui_trunccube, core_trunccube);
}

void TestGUICoreObjectCorrespondence::test_TruncatedSphere()
{
    TruncatedSphereItem gui_truncsphere;
    FormFactorTruncatedSphere core_truncsphere(1.0, 0.5);
    GUICoreObjectCorrespondence(gui_truncsphere, core_truncsphere);
}

void TestGUICoreObjectCorrespondence::test_TruncatedSpheroid()
{
    TruncatedSpheroidItem gui_truncspheroid;
    FormFactorTruncatedSpheroid core_truncspheroid(1.0, 1.5, 1.5);
    GUICoreObjectCorrespondence(gui_truncspheroid, core_truncspheroid);
}

void TestGUICoreObjectCorrespondence::test_RadialParacrystal()
{
    InterferenceFunctionRadialParaCrystalItem gui_radialparacrystal;
    InterferenceFunctionRadialParaCrystal core_radialparacrystal(10.0, 1e-6);
    GUICoreObjectCorrespondence(gui_radialparacrystal, core_radialparacrystal);
}

void TestGUICoreObjectCorrespondence::test_1DLattice()
{
    InterferenceFunction1DLatticeItem gui_1d_lattice;
    InterferenceFunction1DLattice core_1d_lattice(20.0, 0.0);
    GUICoreObjectCorrespondence(gui_1d_lattice, core_1d_lattice);
}

//void TestGUICoreObjectCorrespondence::test_2DParacrystal()
//{
//    InterferenceFunction2DParaCrystalItem gui_2d_paracrystal;
//    InterferenceFunction2DParaCrystal core_2d_paracrystal(10.0, 10.0, 90.0*Units::degree);
//    GUICoreObjectCorrespondence(gui_2d_paracrystal, core_2d_paracrystal);
//}

//void TestGUICoreObjectCorrespondence::test_2DLattice()
//{
//    InterferenceFunction2DLatticeItem gui_2d_lattice;
//    InterferenceFunction2DLattice core_2d_lattice(10.0, 10.0, 90.0*Units::degree);
//    GUICoreObjectCorrespondence(gui_2d_lattice, core_2d_lattice);
//}
