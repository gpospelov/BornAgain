// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactorTest.h
//! @brief     Declares unit test for Form factors.
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORTEST_H
#define FORMFACTORTEST_H

#include "Units.h"
#include "BornAgainNamespace.h"
#include "IFormFactorBorn.h"
#include "ParticleShapes.h"
#include "gtest/gtest.h"

class FormFactorTest : public ::testing::Test
{
protected:
    FormFactorTest(){}
    void clone_test( const IFormFactorBorn* ff )
    {
        IFormFactorBorn* clone = ff->clone();
        EXPECT_EQ(clone->getName(), ff->getName());
        EXPECT_EQ(clone->getVolume(), ff->getVolume());
        cvector_t q(.1, .2, complex_t(.3, .004));
        EXPECT_EQ(clone->evaluate_for_q(q), ff->evaluate_for_q(q));
    }
};

TEST_F(FormFactorTest, AnisoPyramid)
{
    double length = 12.;
    double height = 5.;
    double width = 14.;
    double alpha = 0.8;
    double tga = std::tan(alpha);
    double volume = height*
        (length*width - (length + width)*height/tga + 4.0/3.0*height*height/(tga*tga));

    FormFactorAnisoPyramid anisopyramid(length, width, height, alpha);

    EXPECT_EQ(BornAgain::FFAnisoPyramidType, anisopyramid.getName());
    EXPECT_DOUBLE_EQ(volume, anisopyramid.getVolume());
    EXPECT_EQ(12., anisopyramid.getLength());
    EXPECT_EQ(14., anisopyramid.getWidth());
    EXPECT_EQ(5., anisopyramid.getHeight());
    EXPECT_EQ(0.8, anisopyramid.getAlpha());

    clone_test( &anisopyramid );
}

TEST_F(FormFactorTest, HemiEllipsoid)
{
    double radius_a = 6.;
    double radius_b = 7.;
    double height = 5.;

    double volume = 2.*Units::PI*radius_a*radius_b*height/3.;

    FormFactorHemiEllipsoid hemiellipsoid(radius_a, radius_b, height);

    EXPECT_EQ(BornAgain::FFHemiEllipsoidType, hemiellipsoid.getName());
    EXPECT_EQ(6., hemiellipsoid.getRadiusX());
    EXPECT_EQ(7., hemiellipsoid.getRadiusY());
    EXPECT_EQ(5., hemiellipsoid.getHeight());
    EXPECT_DOUBLE_EQ(volume, hemiellipsoid.getVolume());

    clone_test( &hemiellipsoid );
}

TEST_F(FormFactorTest, Box)
{
    double length = 6.;
    double height = 5.;
    double width = 7.;
    double volume = length*height*width;

    FormFactorBox box(length, width, height);

    EXPECT_EQ(BornAgain::FFBoxType, box.getName());
    EXPECT_EQ(7., box.getWidth());
    EXPECT_EQ(5., box.getHeight());
    EXPECT_EQ(3., box.getRadius());
    EXPECT_DOUBLE_EQ(volume, box.getVolume());

    clone_test( &box );
}

TEST_F(FormFactorTest, Cone)
{
    double radius = 6.;
    double height = 5.;
    double alpha = 0.8;
    double tga = std::tan(alpha);
    double HdivRtga = height/tga/radius;
    double volume = Units::PI/3.*tga*radius*radius*radius*
            (1. - (1.- HdivRtga)*(1.- HdivRtga)*(1.- HdivRtga));

    FormFactorCone cone(radius, height, alpha);

    EXPECT_EQ(BornAgain::FFConeType, cone.getName());
    EXPECT_EQ(6., cone.getRadius());
    EXPECT_EQ(5., cone.getHeight());
    EXPECT_EQ(0.8, cone.getAlpha());
    EXPECT_DOUBLE_EQ(volume, cone.getVolume());

    clone_test( &cone );
}

TEST_F(FormFactorTest, Cone6)
{
    double base_edge = 6.;
    double height = 5.;
    double alpha = 0.8;
    double tga = std::tan(alpha);
    double HdivRtga = 2.*height/tga/base_edge/std::sqrt(3.);
    double volume = 3./4.*tga*base_edge*base_edge*base_edge*
            (1. - (1.- HdivRtga)*(1.- HdivRtga)*(1.- HdivRtga));

    FormFactorCone6 cone6(base_edge, height, alpha);

    EXPECT_EQ(BornAgain::FFCone6Type, cone6.getName());
    EXPECT_EQ(6., cone6.getBaseEdge());
    EXPECT_EQ(5., cone6.getHeight());
    EXPECT_EQ(0.8, cone6.getAlpha());
    EXPECT_DOUBLE_EQ(volume, cone6.getVolume());

    clone_test( &cone6 );
}

TEST_F(FormFactorTest, Cuboctahedron)
{
    double length = 10.;
    double height = 4;
    double height_ratio = 1.;
    double alpha = 0.8;

    double tga = std::tan(alpha);
    double H2divLtga = height*2./length/tga;
    double ratioH2divLtga = height_ratio*height*2./length/tga;
    double volume = 1./6.*tga*length*length*length*( 2.
         - (1. - H2divLtga)*(1. - H2divLtga)*(1. - H2divLtga)
           - (1. - ratioH2divLtga)*(1. - ratioH2divLtga)*(1. - ratioH2divLtga));

    FormFactorCuboctahedron cuboctahedron(length, height, height_ratio, alpha);

    EXPECT_EQ(BornAgain::FFCuboctahedronType, cuboctahedron.getName());
    EXPECT_EQ(4., cuboctahedron.getHeight());
    EXPECT_EQ(10., cuboctahedron.getLength());
    EXPECT_EQ(1., cuboctahedron.getHeightRatio());
    EXPECT_EQ(0.8, cuboctahedron.getAlpha());
    EXPECT_DOUBLE_EQ(volume, cuboctahedron.getVolume());

    clone_test( &cuboctahedron );
}

TEST_F(FormFactorTest, Cylinder)
{
    double radius = 3.;
    double height = 5.;
    double volume = Units::PI*radius*radius*height;

    FormFactorCylinder cylinder(radius,height);

    EXPECT_EQ(BornAgain::FFCylinderType, cylinder.getName());
    EXPECT_EQ(5., cylinder.getHeight());
    EXPECT_EQ(3., cylinder.getRadius());
    EXPECT_DOUBLE_EQ(volume, cylinder.getVolume());

    clone_test( &cylinder );
}

TEST_F(FormFactorTest, Dodecahedron)
{
    double edge = 3.;
    double volume = (15+7*sqrt(5))/4*pow(edge,3);

    FormFactorDodecahedron dodecahedron(edge);
    EXPECT_EQ(BornAgain::FFDodecahedronType, dodecahedron.getName());
    EXPECT_EQ(edge, dodecahedron.getEdge());
    EXPECT_DOUBLE_EQ(volume, dodecahedron.getVolume());

    clone_test( &dodecahedron );
}

TEST_F(FormFactorTest, EllipsoidalCylinder)
{
    double radius_a = 3.;
    double radius_b = 5.;
    double height = 4;
    double volume = Units::PI*radius_a*radius_b*height;

    FormFactorEllipsoidalCylinder ellipscyl(radius_a, radius_b, height);

    EXPECT_EQ(BornAgain::FFEllipsoidalCylinderType, ellipscyl.getName());
    EXPECT_EQ(4., ellipscyl.getHeight());
    EXPECT_EQ(3., ellipscyl.getRadiusX());
    EXPECT_EQ(5., ellipscyl.getRadiusY());
    EXPECT_DOUBLE_EQ(volume, ellipscyl.getVolume());

    clone_test( &ellipscyl );
}

TEST_F(FormFactorTest, FullSphere)
{
    double radius = 5.;
    double volume = 4./3.*Units::PI*radius*radius*radius;

    FormFactorFullSphere fullsphere(radius);
    EXPECT_EQ(BornAgain::FFFullSphereType, fullsphere.getName());
    EXPECT_EQ(5., fullsphere.getRadius());
    EXPECT_DOUBLE_EQ(volume, fullsphere.getVolume());

    clone_test( &fullsphere );
}

TEST_F(FormFactorTest, FullSpheroid)
{
    double radius = 3.;
    double height = 5.;
    double volume = 2./3.*Units::PI*radius*radius*height;

    FormFactorFullSpheroid fullspheroid(radius,height);

    EXPECT_EQ(BornAgain::FFFullSpheroidType, fullspheroid.getName());
    EXPECT_EQ(3., fullspheroid.getRadius());
    EXPECT_EQ(5., fullspheroid.getHeight());
    EXPECT_DOUBLE_EQ(volume, fullspheroid.getVolume());

    clone_test( &fullspheroid );
}

TEST_F(FormFactorTest, Icosahedron)
{
    double edge = 7.;
    double volume = 5*(3+sqrt(5))/12*pow(edge,3);

    FormFactorIcosahedron icosahedron(edge);

    EXPECT_EQ(BornAgain::FFIcosahedronType, icosahedron.getName());
    EXPECT_EQ(edge, icosahedron.getEdge());
    EXPECT_DOUBLE_EQ(volume, icosahedron.getVolume());

    clone_test( &icosahedron );
}

TEST_F(FormFactorTest, Prism3)
{
    double height = 4.;
    double base_edge = 6.;
    double volume = sqrt(3.)/4.*height*base_edge*base_edge;

    FormFactorPrism3 prism3(base_edge, height);

    EXPECT_EQ(BornAgain::FFPrism3Type, prism3.getName());
    EXPECT_EQ(4., prism3.getHeight());
    EXPECT_EQ(6., prism3.getBaseEdge());
    EXPECT_DOUBLE_EQ(volume, prism3.getVolume());

    clone_test( &prism3 );
}

TEST_F(FormFactorTest, Prism6)
{
    double height = 4.;
    double base_edge = 3.;
    double volume = 3.*sqrt(3.)/2.*height*base_edge*base_edge;

    FormFactorPrism6 prism6(base_edge, height);

    EXPECT_EQ(BornAgain::FFPrism6Type, prism6.getName());
    EXPECT_EQ(4., prism6.getHeight());
    EXPECT_EQ(3., prism6.getBaseEdge());
    EXPECT_DOUBLE_EQ(volume, prism6.getVolume());

    clone_test( &prism6 );
}

TEST_F(FormFactorTest, Pyramid)
{
    double height = 4.;
    double length = 10.;
    double alpha = 0.8;
    double tga = std::tan(alpha);
    double H2divLtga = height*2./length/tga;
    double volume = 1./6.*tga*length* length*length*
        ( 1. - (1. - H2divLtga)*(1. - H2divLtga)*(1. - H2divLtga));

    FormFactorPyramid pyramid(length, height, alpha);

    EXPECT_EQ(BornAgain::FFPyramidType, pyramid.getName());
    EXPECT_EQ(4., pyramid.getHeight());
    EXPECT_EQ(10., pyramid.getBaseEdge());
    EXPECT_EQ(0.8, pyramid.getAlpha());
    EXPECT_DOUBLE_EQ(volume, pyramid.getVolume());

    clone_test( &pyramid );
}

TEST_F(FormFactorTest, TruncatedSphere)
{
    double radius = 5.;
    double height = 3.;
    double HdivR = height/radius;
    double volume = Units::PI/3.*radius*radius*radius*
            (3.*HdivR -1. - (HdivR - 1.)*(HdivR - 1.)*(HdivR - 1.));

    FormFactorTruncatedSphere trsphere(radius, height);

    EXPECT_EQ(BornAgain::FFTruncatedSphereType, trsphere.getName());
    EXPECT_EQ(3., trsphere.getHeight());
    EXPECT_DOUBLE_EQ(volume, trsphere.getVolume());

    clone_test( &trsphere );
}

TEST_F(FormFactorTest, TruncatedSpheroid)
{
    double height = 5.;
    double radius = 3.;
    double flattening = 1.5;
    double volume = Units::PI*radius*height*height/flattening*
            (1.-height/(3.*flattening*radius));

    FormFactorTruncatedSpheroid trspheroid(radius, height,flattening);

    EXPECT_EQ(BornAgain::FFTruncatedSpheroidType, trspheroid.getName());
    EXPECT_EQ(5., trspheroid.getHeight());
    EXPECT_EQ(3., trspheroid.getRadius());
    EXPECT_DOUBLE_EQ(volume, trspheroid.getVolume());

    clone_test( &trspheroid );
}

TEST_F(FormFactorTest, Tetrahedron)
{
    double height = 4.;
    double base_edge = 16.;
    double alpha = 0.8;
    double tga = std::tan(alpha);
    double sqrt3H2divLtga = std::sqrt(3.)*2.*height/base_edge/tga;
    double volume = tga/24.*base_edge*base_edge*base_edge*(
     1.- (1. - sqrt3H2divLtga)*(1. - sqrt3H2divLtga)*(1. - sqrt3H2divLtga));

    FormFactorTetrahedron tetrahedron(base_edge, height, alpha);

    EXPECT_EQ(BornAgain::FFTetrahedronType, tetrahedron.getName());
    EXPECT_EQ(4., tetrahedron.getHeight());
    EXPECT_EQ(16., tetrahedron.getBaseEdge());
    EXPECT_EQ(0.8, tetrahedron.getAlpha());
    EXPECT_DOUBLE_EQ(volume, tetrahedron.getVolume());

    clone_test( &tetrahedron );
}

TEST_F(FormFactorTest, Ripple1)
{
    double width = 20.;
    double height = 4.;
    double length = 100.0;
    double volume = 0.5*height*width*length;

    FormFactorRipple1 ripple1(length, width, height);

    EXPECT_EQ(BornAgain::FFRipple1Type, ripple1.getName());
    EXPECT_EQ(4., ripple1.getHeight());
    EXPECT_EQ(20., ripple1.getWidth());
    EXPECT_EQ(100., ripple1.getLength());
    EXPECT_DOUBLE_EQ(volume, ripple1.getVolume());

    clone_test( &ripple1 );
}

TEST_F(FormFactorTest, Ripple2)
{
    double width = 20.;
    double height = 4.;
    double length = 100.0;
    double d = 0.3; // asymetry
    double volume = 0.5*height*width*length;

    FormFactorRipple2 ripple2(length, width, height, d);

    EXPECT_EQ(BornAgain::FFRipple2Type, ripple2.getName());
    EXPECT_EQ(4., ripple2.getHeight());
    EXPECT_DOUBLE_EQ(volume, ripple2.getVolume());

    clone_test( &ripple2 );
}

TEST_F(FormFactorTest, TruncatedCube)
{
    double length = 15.;
    double t = 6.; // side length of removed trirectangular tetrahedron at each vertex
    double volume = length*length*length - 4./3.*t*t*t;

    FormFactorTruncatedCube trcube(length, t);

    EXPECT_EQ(BornAgain::FFTruncatedCubeType,trcube.getName());
    EXPECT_EQ(length, trcube.getLength());
    EXPECT_DOUBLE_EQ(t, trcube.getRemovedLength());
    EXPECT_DOUBLE_EQ(trcube.getVolume(), volume);

    clone_test( &trcube );
}

#endif // FORMFACTORTEST_H
