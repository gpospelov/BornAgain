#ifndef CVECTORTEST_H
#define CVECTORTEST_H



#include "Types.h"
#include <cmath>

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
    cvector_t a(complex_t(1.,-2.), complex_t(3.,-4), complex_t(5,-6));
    cvector_t b(complex_t(-0.1,0.2), complex_t(-0.3,0.4), complex_t(-0.5,0.6));
    cvector_t c(complex_t(10.,20.), complex_t(30.,40.), complex_t(50,60));
    cvector_t result = a.cross(b.cross(c)) - a.dot(c)*b + a.dot(b)*c;
    EXPECT_TRUE(result.x() == complex_t(0,0));
    EXPECT_TRUE(result.y() == complex_t(0,0));
    EXPECT_TRUE(result.z() == complex_t(0,0));

    // f = f_re + j*f_im
    cvector_t e(1,2,3);
    cvector_t f(5,6,7);
    EXPECT_TRUE( (e+complex_t(0,1)*f) == cvector_t(complex_t(1.,5.), complex_t(2.,6), complex_t(3,7)) );

    std::cout << e*f << std::endl;
}



#endif // CVECTORTEST_H
