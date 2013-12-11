// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactorTest.h
//! @brief     Defines unit test for Form factors.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //
#ifndef FORMFACTORTEST_H
#define FORMFACTORTEST_H

#include "FormFactorAnisoPyramid.h"
#include "FormFactorBox.h"
#include "FormFactorCone.h"
#include "FormFactorCone6.h"
#include "FormFactorCylinder.h"
#include "FormFactorCuboctahedron.h"
#include "FormFactorEllipsoidalCylinder.h"
#include "FormFactorFullSphere.h"
#include "FormFactorFullSpheroid.h"
#include "FormFactorHemiEllipsoid.h"
#include "FormFactorParallelepiped.h"
#include "FormFactorPrism3.h"
#include "FormFactorPrism6.h"
#include "FormFactorPyramid.h"
#include "FormFactorSphere.h"
#include "FormFactorSpheroid.h"
#include "FormFactorTetrahedron.h"

#include "gtest/gtest.h"

class FormFactorTest : public ::testing::Test
{
 protected:
    FormFactorTest(){}
    virtual ~FormFactorTest(){}
};


//Test form factor of an anisotropic pyramid
TEST_F(FormFactorTest, AnisoPyramid)
{
    double length = 12.;
    double height = 5.;
    double width = 14.;
    double alpha = 0.8;
    double tga = std::tan(alpha);
    double volume = height*(length*width
                            - (length + width)*height/tga
                            + 4.0/3.0*height*height/(tga*tga));

    FormFactorAnisoPyramid anisopyramid(length, width, height, alpha);

    EXPECT_EQ("FormFactorAnisoPyramid",anisopyramid.getName());
    EXPECT_DOUBLE_EQ(volume, anisopyramid.getVolume());
    EXPECT_EQ(12., anisopyramid.getLength());
    EXPECT_EQ(14., anisopyramid.getWidth());
    EXPECT_EQ(5., anisopyramid.getHeight());
    EXPECT_EQ(0.8, anisopyramid.getAlpha());
    EXPECT_EQ((int)4, anisopyramid.getNumberOfStochasticParameters());

    FormFactorAnisoPyramid *anisopyramidclone = anisopyramid.clone();
    EXPECT_EQ("FormFactorAnisoPyramid",anisopyramidclone->getName());
    EXPECT_DOUBLE_EQ(volume, anisopyramidclone->getVolume());
    EXPECT_EQ(12., anisopyramidclone->getLength());
    EXPECT_EQ(14., anisopyramidclone->getWidth());
    EXPECT_EQ(5., anisopyramidclone->getHeight());
    EXPECT_EQ(0.8, anisopyramidclone->getAlpha());
    EXPECT_EQ((int)4, anisopyramidclone->getNumberOfStochasticParameters());
}

//Test form factor of an hemiellipsoid
TEST_F(FormFactorTest, HemiEllipsoid)
{
    double radius_a = 6.;
    double radius_b = 7.;
    double height = 5.;

    double volume = 2.*M_PI*radius_a*radius_b*height/3.;

    FormFactorHemiEllipsoid hemiellipsoid(radius_a, radius_b, height);

    EXPECT_EQ("FormFactorHemiEllipsoid",hemiellipsoid.getName());
    EXPECT_EQ(6., hemiellipsoid.getRadiusA());
    EXPECT_EQ(7., hemiellipsoid.getRadiusB());
    EXPECT_EQ(5., hemiellipsoid.getHeight());
    EXPECT_DOUBLE_EQ(volume, hemiellipsoid.getVolume());
    EXPECT_EQ((int)3, hemiellipsoid.getNumberOfStochasticParameters());

    FormFactorHemiEllipsoid *hemiellipsoidclone = hemiellipsoid.clone();
    EXPECT_EQ("FormFactorHemiEllipsoid",hemiellipsoidclone->getName());
    EXPECT_EQ(6., hemiellipsoidclone->getRadiusA());
    EXPECT_EQ(7., hemiellipsoidclone->getRadiusB());
    EXPECT_EQ(5., hemiellipsoidclone->getHeight());
    EXPECT_DOUBLE_EQ(volume, hemiellipsoidclone->getVolume());
    EXPECT_EQ((int)3, hemiellipsoidclone->getNumberOfStochasticParameters());
}

// Test form factor of a box
TEST_F(FormFactorTest, Box)
{
    double length = 6.;
    double height = 5.;
    double width = 7.;
    double volume = length*height*width;

    FormFactorBox box(length, width, height);

    EXPECT_EQ("FormFactorBox",box.getName());
    EXPECT_EQ(7., box.getWidth());
    EXPECT_EQ(5., box.getHeight());
    EXPECT_EQ(3., box.getRadius());
    EXPECT_DOUBLE_EQ(volume, box.getVolume());
    EXPECT_EQ(3, box.getNumberOfStochasticParameters());

    FormFactorBox *boxclone = box.clone();
    EXPECT_EQ("FormFactorBox",boxclone->getName());
    EXPECT_EQ(7., boxclone->getWidth());
    EXPECT_EQ(5., boxclone->getHeight());
    EXPECT_EQ(3., boxclone->getRadius());
    EXPECT_DOUBLE_EQ(volume, boxclone->getVolume());
    EXPECT_EQ(3, boxclone->getNumberOfStochasticParameters());
}

// Test form factor of a cone
TEST_F(FormFactorTest, Cone)
{
    double radius = 6.;
    double height = 5.;
    double alpha = 0.8;
    double tga = std::tan(alpha);
    double HdivRtga = height/tga/radius;
    double volume = M_PI/3.*tga*radius*radius*radius*
            (1. - (1.- HdivRtga)*(1.- HdivRtga)*(1.- HdivRtga));

    FormFactorCone cone(radius, height, alpha);

    EXPECT_EQ("FormFactorCone",cone.getName());
    EXPECT_EQ(6., cone.getRadius());
    EXPECT_EQ(5., cone.getHeight());
    EXPECT_EQ(0.8, cone.getAlpha());
    EXPECT_DOUBLE_EQ(volume, cone.getVolume());
    EXPECT_EQ((int)3, cone.getNumberOfStochasticParameters());

    FormFactorCone *coneclone = cone.clone();
    EXPECT_EQ("FormFactorCone",coneclone->getName());
    EXPECT_EQ(6., coneclone->getRadius());
    EXPECT_EQ(5., coneclone->getHeight());
    EXPECT_EQ(0.8, coneclone->getAlpha());
    EXPECT_DOUBLE_EQ(volume, coneclone->getVolume());
    EXPECT_EQ((int)3, coneclone->getNumberOfStochasticParameters());
}

// Test form factor of a cone6
TEST_F(FormFactorTest, Cone6)
{
    double radius = 6.;
    double height = 5.;
    double alpha = 0.8;
    double tga = std::tan(alpha);
    double HdivRtga = 2.*height/tga/radius/std::sqrt(3.);
    double volume = 3./4.*tga*radius*radius*radius*
            (1. - (1.- HdivRtga)*(1.- HdivRtga)*(1.- HdivRtga));

    FormFactorCone6 cone6(radius, height, alpha);

    EXPECT_EQ("FormFactorCone6",cone6.getName());
    EXPECT_EQ(6., cone6.getRadius());
    EXPECT_EQ(5., cone6.getHeight());
    EXPECT_EQ(0.8, cone6.getAlpha());
    EXPECT_DOUBLE_EQ(volume, cone6.getVolume());
    EXPECT_EQ((int)3, cone6.getNumberOfStochasticParameters());

    FormFactorCone6 *cone6clone = cone6.clone();
    EXPECT_EQ("FormFactorCone6",cone6clone->getName());
    EXPECT_EQ(6., cone6clone->getRadius());
    EXPECT_EQ(5., cone6clone->getHeight());
    EXPECT_EQ(0.8, cone6clone->getAlpha());
    EXPECT_DOUBLE_EQ(volume, cone6clone->getVolume());
    EXPECT_EQ((int)3, cone6clone->getNumberOfStochasticParameters());
}

// Test form factor of a cuboctahedron
TEST_F(FormFactorTest, Cuboctahedron)
{
    double half_side = 5.;
    double height = 4;
    double height_ratio = 1.;
    double alpha = 0.8;

    double tga = std::tan(alpha);
    double HdivRtga = height/half_side/tga;
    double ratioHdivRtga = height_ratio*height/half_side/tga;
    double volume = 4./3.*tga*half_side*half_side*half_side*( 2.
         - (1. - HdivRtga)*(1. - HdivRtga)*(1. - HdivRtga)
           - (1. - ratioHdivRtga)*(1. - ratioHdivRtga)*(1. - ratioHdivRtga));

    FormFactorCuboctahedron cuboctahedron(half_side, height,
                                          height_ratio, alpha);

    EXPECT_EQ("FormFactorCuboctahedron",cuboctahedron.getName());
    EXPECT_EQ(4., cuboctahedron.getHeight());
    EXPECT_EQ(5., cuboctahedron.getHalfSide());
    EXPECT_EQ(1., cuboctahedron.getHeightRatio());
    EXPECT_EQ(0.8, cuboctahedron.getAlpha());
    EXPECT_DOUBLE_EQ(volume, cuboctahedron.getVolume());
    EXPECT_EQ((int)4, cuboctahedron.getNumberOfStochasticParameters());

    FormFactorCuboctahedron *cuboctahedronclone = cuboctahedron.clone();
    EXPECT_EQ("FormFactorCuboctahedron",cuboctahedronclone->getName());
    EXPECT_EQ(4., cuboctahedronclone->getHeight());
    EXPECT_EQ(5., cuboctahedronclone->getHalfSide());
    EXPECT_EQ(1., cuboctahedronclone->getHeightRatio());
    EXPECT_EQ(0.8, cuboctahedronclone->getAlpha());
    EXPECT_DOUBLE_EQ(volume, cuboctahedron.getVolume());
    EXPECT_EQ((int)4, cuboctahedronclone->getNumberOfStochasticParameters());

}

// Test form factor of a cylinder
TEST_F(FormFactorTest, Cylinder)
{
    double radius = 3.;
    double height = 5.;
    double volume = M_PI*radius*radius*height;

    FormFactorCylinder cylinder(height,radius);
    EXPECT_EQ("FormFactorCylinder",cylinder.getName());
    EXPECT_EQ(5., cylinder.getHeight());
    EXPECT_EQ(3., cylinder.getRadius());
    EXPECT_DOUBLE_EQ(volume, cylinder.getVolume());
    EXPECT_EQ((int)2, cylinder.getNumberOfStochasticParameters());

    FormFactorCylinder *cylinderclone = cylinder.clone();
    EXPECT_EQ("FormFactorCylinder",cylinderclone->getName());
    EXPECT_EQ(5., cylinderclone->getHeight());
    EXPECT_EQ(3., cylinderclone-> getRadius());
    EXPECT_DOUBLE_EQ(volume, cylinderclone-> getVolume());
    EXPECT_EQ((int)2, cylinderclone-> getNumberOfStochasticParameters());
}

// Test form factor of an ellipsoidal cylinder
TEST_F(FormFactorTest, EllipsoidalCylinder)
{
    double radius = 3.;
    double width = 5.;
    double height = 4;
    double volume = M_PI*radius*width*height;

    FormFactorEllipsoidalCylinder ellipscyl(radius, width, height);

    EXPECT_EQ("FormFactorEllipsoidalCylinder",ellipscyl.getName());
    EXPECT_EQ(4., ellipscyl.getHeight());
    EXPECT_EQ(3., ellipscyl.getRadius());
    EXPECT_EQ(5., ellipscyl.getWidth());
    EXPECT_DOUBLE_EQ(volume, ellipscyl.getVolume());
    EXPECT_EQ((int)3, ellipscyl.getNumberOfStochasticParameters());

    FormFactorEllipsoidalCylinder *ellipscylclone = ellipscyl.clone();
    EXPECT_EQ("FormFactorEllipsoidalCylinder",ellipscylclone->getName());
    EXPECT_EQ(4., ellipscylclone->getHeight());
    EXPECT_EQ(3., ellipscylclone->getRadius());
    EXPECT_EQ(5., ellipscylclone->getWidth());
    EXPECT_DOUBLE_EQ(volume, ellipscylclone->getVolume());
    EXPECT_EQ((int)3, ellipscylclone->getNumberOfStochasticParameters());

}

// Test form factor of a full sphere
TEST_F(FormFactorTest, FullSphere)
{
    double radius = 5.;
    double volume = 4./3.*M_PI*radius*radius*radius;

    FormFactorFullSphere fullsphere(radius);

    EXPECT_EQ("FormFactorFullSphere",fullsphere.getName());
    EXPECT_EQ(5., fullsphere.getRadius());
    EXPECT_EQ(2.*5., fullsphere.getHeight());
    EXPECT_DOUBLE_EQ(volume, fullsphere.getVolume());
    EXPECT_EQ((int)1, fullsphere.getNumberOfStochasticParameters());

    FormFactorFullSphere *fullsphereclone = fullsphere.clone();
    EXPECT_EQ("FormFactorFullSphere",fullsphereclone->getName());
    EXPECT_EQ(5., fullsphereclone->getRadius());
    EXPECT_EQ(2.*5., fullsphereclone->getHeight());
    EXPECT_DOUBLE_EQ(volume, fullsphereclone->getVolume());
    EXPECT_EQ((int)1, fullsphereclone->getNumberOfStochasticParameters());
}

// Test form factor of a full spheroid
TEST_F(FormFactorTest, FullSpheroid)
{
    double radius = 3.;
    double height = 5.;
    double volume = 2./3.*M_PI*radius*radius*height;

    FormFactorFullSpheroid fullspheroid(radius,height);

    EXPECT_EQ("FormFactorFullSpheroid",fullspheroid.getName());
    EXPECT_EQ(3., fullspheroid.getRadius());
    EXPECT_EQ(5., fullspheroid.getHeight());
    EXPECT_DOUBLE_EQ(volume, fullspheroid.getVolume());
    EXPECT_EQ((int)2, fullspheroid.getNumberOfStochasticParameters());

    FormFactorFullSpheroid *fullspheroidclone = fullspheroid.clone();
    EXPECT_EQ("FormFactorFullSpheroid",fullspheroidclone->getName());
    EXPECT_EQ(3., fullspheroidclone->getRadius());
    EXPECT_EQ(5, fullspheroidclone->getHeight());
    EXPECT_DOUBLE_EQ(volume, fullspheroidclone->getVolume());
    EXPECT_EQ((int)2, fullspheroidclone->getNumberOfStochasticParameters());
}


// Test form factor of a parallelepiped
TEST_F(FormFactorTest, Parallelepiped)
{
   double radius = 11.;
   double height = 10.;
   double volume = 4.*radius*radius*height;

   FormFactorParallelepiped parallelepiped(height, radius);

   EXPECT_EQ("FormFactorParallelepiped",parallelepiped.getName());
   EXPECT_EQ(10., parallelepiped.getHeight());
   EXPECT_EQ(11., parallelepiped.getRadius());
   EXPECT_DOUBLE_EQ(volume, parallelepiped.getVolume());
   EXPECT_EQ((int)2, parallelepiped.getNumberOfStochasticParameters());

   FormFactorParallelepiped *parallelepipedclone = parallelepiped.clone();
   EXPECT_EQ("FormFactorParallelepiped",parallelepipedclone->getName());
   EXPECT_EQ(10., parallelepipedclone-> getHeight());
   EXPECT_EQ(11., parallelepipedclone-> getRadius());
   EXPECT_DOUBLE_EQ(volume, parallelepipedclone-> getVolume());
   EXPECT_EQ((int)2, parallelepipedclone-> getNumberOfStochasticParameters());
}

// Test form factor of a prism3
TEST_F(FormFactorTest, Prism3)
{
    double height = 4.;
    double half_side = 3.;
    double volume = sqrt(3.)*height*half_side*half_side;

    FormFactorPrism3 prism3(height, half_side);

    EXPECT_EQ("FormFactorPrism3",prism3.getName());
    EXPECT_EQ(4., prism3.getHeight());
    EXPECT_EQ(3., prism3.getHalfSide());
    EXPECT_DOUBLE_EQ(volume, prism3.getVolume());
    EXPECT_EQ((int)2, prism3.getNumberOfStochasticParameters());

    FormFactorPrism3 *prism3clone = prism3.clone();

    EXPECT_EQ("FormFactorPrism3",prism3clone->getName());
    EXPECT_EQ(4., prism3clone->getHeight());
    EXPECT_EQ(3., prism3clone->getHalfSide());
    EXPECT_DOUBLE_EQ(volume, prism3clone->getVolume());
    EXPECT_EQ((int)2, prism3clone->getNumberOfStochasticParameters());
}

// Test form factor of a prism6
TEST_F(FormFactorTest, Prism6)
{
    double height = 4.;
    double radius = 3.;
    double volume = 3.*sqrt(3.)/2.*height*radius*radius;

    FormFactorPrism6 prism6(radius, height);

    EXPECT_EQ("FormFactorPrism6",prism6.getName());
    EXPECT_EQ(4., prism6.getHeight());
    EXPECT_EQ(3., prism6.getRadius());
    EXPECT_DOUBLE_EQ(volume, prism6.getVolume());
    EXPECT_EQ((int)2, prism6.getNumberOfStochasticParameters());

    FormFactorPrism6 *prism6clone = prism6.clone();

    EXPECT_EQ("FormFactorPrism6",prism6clone->getName());
    EXPECT_EQ(4., prism6clone->getHeight());
    EXPECT_EQ(3., prism6clone->getRadius());
    EXPECT_DOUBLE_EQ(volume, prism6clone->getVolume());
    EXPECT_EQ((int)2, prism6clone->getNumberOfStochasticParameters());
}

// Test form factor of a pyramid
TEST_F(FormFactorTest, Pyramid)
{
    double height = 4.;
    double half_side = 5.;
    double alpha = 0.8;
    double tga = std::tan(alpha);
    double HdivRtga = height/half_side/tga;
    double volume = 4./3.*tga*half_side*half_side*half_side*( 1.
             - (1. - HdivRtga)*(1. - HdivRtga)*(1. - HdivRtga));

    FormFactorPyramid pyramid(height, half_side, alpha);

    EXPECT_EQ("FormFactorPyramid", pyramid.getName());
    EXPECT_EQ(4., pyramid.getHeight());
    EXPECT_EQ(5., pyramid.getHalfSide());
    EXPECT_EQ(0.8, pyramid.getAlpha());
    EXPECT_DOUBLE_EQ(volume, pyramid.getVolume());
    EXPECT_EQ((int)3, pyramid.getNumberOfStochasticParameters());

    FormFactorPyramid *pyramidclone = pyramid.clone();
    EXPECT_EQ("FormFactorPyramid", pyramidclone->getName());
    EXPECT_EQ(4., pyramidclone->getHeight());
    EXPECT_EQ(5., pyramidclone->getHalfSide());
    EXPECT_EQ(0.8, pyramidclone->getAlpha());
    EXPECT_DOUBLE_EQ(volume, pyramidclone->getVolume());
    EXPECT_EQ((int)3, pyramidclone->getNumberOfStochasticParameters());
}

// Test form factor of a sphere
TEST_F(FormFactorTest, Sphere)
{
    double radius = 5.;
    double height = 3.;
    double HdivR = height/radius;
    double volume = M_PI/3.*radius*radius*radius
            *(3.*HdivR -1. - (HdivR - 1.)*(HdivR - 1.)*(HdivR - 1.));

    FormFactorSphere sphere(radius, height);

    EXPECT_EQ("FormFactorSphere", sphere.getName());
    EXPECT_EQ(3., sphere.getHeight());
    EXPECT_DOUBLE_EQ(volume, sphere.getVolume());
    EXPECT_EQ((int)2, sphere.getNumberOfStochasticParameters());

    FormFactorSphere *sphereclone = sphere.clone();
    EXPECT_EQ("FormFactorSphere", sphereclone->getName());
    EXPECT_DOUBLE_EQ(3., sphereclone->getHeight());
    EXPECT_EQ((int)2, sphereclone->getNumberOfStochasticParameters());
}

// Test form factor of a spheroid
TEST_F(FormFactorTest, Spheroid)
{
    double height = 5.;
    double radius = 3.;
    double flattening = 1.5;
    double total_height =2.*flattening *radius;
    double volume = M_PI*radius*height/flattening*(1.-height/(3.*flattening*radius));

    FormFactorSpheroid spheroid(radius, height,flattening);

    EXPECT_EQ("FormFactorSpheroid", spheroid.getName());
    EXPECT_EQ(5., spheroid.getHeight());
    EXPECT_EQ(3., spheroid.getRadius());
    EXPECT_DOUBLE_EQ(total_height, spheroid.getHeightFullSpheroid());
    EXPECT_DOUBLE_EQ(volume, spheroid.getVolume());
    EXPECT_EQ((int)3, spheroid.getNumberOfStochasticParameters());

    FormFactorSpheroid *spheroidclone = spheroid.clone();
    EXPECT_EQ("FormFactorSpheroid", spheroidclone->getName());
    EXPECT_EQ(5., spheroidclone->getHeight());
    EXPECT_EQ(3., spheroidclone->getRadius());
    EXPECT_DOUBLE_EQ(total_height, spheroidclone->getHeightFullSpheroid());
    EXPECT_DOUBLE_EQ(volume, spheroidclone->getVolume());
    EXPECT_EQ((int)3, spheroidclone->getNumberOfStochasticParameters());
}

// Test form factor of a tetrahedron
TEST_F(FormFactorTest, Tetrahedron)
{
    double height = 4.;
    double half_side = 8.;
    double alpha = 0.8;
    double tga = std::tan(alpha);
    double sqrt3HdivRtga = std::sqrt(3.)*height/half_side/tga;
    double volume = tga/3.*half_side*half_side*half_side*(
     1.- (1. - sqrt3HdivRtga)*(1. - sqrt3HdivRtga)*(1. - sqrt3HdivRtga));

    FormFactorTetrahedron tetrahedron(half_side, height, alpha);

    EXPECT_EQ("FormFactorTetrahedron", tetrahedron.getName());
    EXPECT_EQ(4., tetrahedron.getHeight());
    EXPECT_EQ(8., tetrahedron.getHalfSide());
    EXPECT_EQ(0.8, tetrahedron.getAlpha());
    EXPECT_DOUBLE_EQ(volume, tetrahedron.getVolume());
    EXPECT_EQ((int)3, tetrahedron.getNumberOfStochasticParameters());

    FormFactorTetrahedron *tetrahedronclone = tetrahedron.clone();
    EXPECT_EQ("FormFactorTetrahedron", tetrahedronclone->getName());
    EXPECT_EQ(4., tetrahedronclone->getHeight());
    EXPECT_EQ(8., tetrahedronclone->getHalfSide());
    EXPECT_EQ(0.8, tetrahedronclone->getAlpha());
    EXPECT_DOUBLE_EQ(volume, tetrahedronclone->getVolume());
    EXPECT_EQ((int)3, tetrahedronclone->getNumberOfStochasticParameters());
}



#endif // FORMFACTORTEST_H

