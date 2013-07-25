#ifndef CVECTORTEST_H
#define CVECTORTEST_H



#include "Types.h"
#include <cmath>

#include "Eigen/Core"


class CVectorTest : public ::testing::Test
{
 protected:
    CVectorTest();
    virtual ~CVectorTest();
};


CVectorTest::CVectorTest()
{
}

CVectorTest::~CVectorTest()
{
}

TEST_F(CVectorTest, BasicArithmetics)
{
    // ax(bxc) - (a*c)*b + (a*b)*c = 0
    //cvector_t a(complex_t(1.,-2.), complex_t(3.,-4), complex_t(5,-6));
    //cvector_t b(complex_t(-0.1,0.2),
    //            complex_t(-0.3,0.4),
    //            complex_t(-0.5,0.6));
    //cvector_t c(complex_t(10.,20.), complex_t(30.,40.), complex_t(50,60));
    //cvector_t result = a.cross(b.cross(c)) - a.dot(c)*b + a.dot(b)*c;
    //EXPECT_TRUE(result.x() == complex_t(0,0));
    //EXPECT_TRUE(result.y() == complex_t(0,0));
    //EXPECT_TRUE(result.z() == complex_t(0,0));

    // Cross product with "Eigen" library
    //Eigen::Vector3cd vac(complex_t(1.,-2.), complex_t(3.,-4), complex_t(5,-6));
    //Eigen::Vector3cd vbc(complex_t(-0.1,0.2),
    //                     complex_t(-0.3,0.4),
    //                     complex_t(-0.5,0.6));
    //Eigen::Vector3cd vcc(complex_t(10.,20.),
    //                     complex_t(30.,40.),
    //                     complex_t(50,60));
    //Eigen::Vector3cd result = vac.cross(vbc.cross(vcc))
    //                        - vac.dot(vcc)*vbc
    //                        + vac.dot(vbc)*vcc;

    //EXPECT_TRUE(result.x() == complex_t(0,0));
    //EXPECT_TRUE(result.y() == complex_t(0,0));
    //EXPECT_TRUE(result.z() == complex_t(0,0));

    // Dot product with "Eigen" library
    Eigen::Vector3cd va(complex_t(1.,0.), complex_t(2.,0.), complex_t(3.,0.));
    //Eigen::Vector3cd vb(complex_t(2.,0.), complex_t(3.,0.), complex_t(4.,0.));
    Eigen::Vector3cd vc(complex_t(1.,1.), complex_t(2.,-5.), complex_t(3.,4.));


    EXPECT_TRUE(va.dot(vc) == complex_t(14.,3.));

    // Dot product defined in BasicVector3D
    cvector_t a(complex_t(1.,0.), complex_t(2.,0.), complex_t(3.,0.));
    cvector_t b(complex_t(2.,0.), complex_t(3.,0.), complex_t(4.,0.));
    cvector_t c(complex_t(1.,1.), complex_t(2.,-5.), complex_t(3.,4.));
    EXPECT_TRUE(a.dot(b) == complex_t(20.,0));
    EXPECT_TRUE(a.dot(c) == complex_t(14.,3.));
    EXPECT_TRUE(c.dot(b) == complex_t(20.,-3.));
    EXPECT_TRUE(a.dot(a) == complex_t(14.,0));
    EXPECT_TRUE(c.dot(c) == complex_t(56.,0));

    // f = f_re + j*f_im
    cvector_t e(1,2,3);
    cvector_t f(5,6,7);
    EXPECT_TRUE( (e+complex_t(0,1)*f) == cvector_t(complex_t(1.,5.),
                                                   complex_t(2.,6),
                                                   complex_t(3,7)) );
}



#endif // CVECTORTEST_H
