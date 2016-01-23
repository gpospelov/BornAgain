#ifndef MATRIXFUNCTIONSTEST_H
#define MATRIXFUNCTIONSTEST_H

#include "MathFunctions.h"
#include "gtest/gtest.h"

class MatrixFunctionsTest : public::testing::Test
{
protected:
    MatrixFunctionsTest();
    virtual ~MatrixFunctionsTest(){}

    Eigen::Matrix2cd matrix_2cd;
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
};

MatrixFunctionsTest::MatrixFunctionsTest(){
    matrix_2cd(0,0) = complex_t(2.0, 1.0);
    matrix_2cd(0,1) = complex_t(3.0, 1.0);
    matrix_2cd(1,0) = complex_t(4.0, 1.0);
    matrix_2cd(1,1) = complex_t(5.0, 1.0);
}

TEST_F(MatrixFunctionsTest, Norm)
{

    Eigen::Matrix2d matrix_norm = MathFunctions::Norm(matrix_2cd);
    EXPECT_EQ(std::norm((complex_t)matrix_2cd(0,0)), matrix_norm(0,0));
    EXPECT_EQ(std::norm((complex_t)matrix_2cd(0,1)), matrix_norm(0,1));
    EXPECT_EQ(std::norm((complex_t)matrix_2cd(1,0)), matrix_norm(1,0));
    EXPECT_EQ(std::norm((complex_t)matrix_2cd(1,1)), matrix_norm(1,1));
}

TEST_F(MatrixFunctionsTest, Abs)
{
   Eigen::Matrix2d matrix_abs = MathFunctions::Abs(matrix_2cd);
   EXPECT_EQ(std::abs((complex_t)matrix_2cd(0,0)), matrix_abs(0,0));
   EXPECT_EQ(std::abs((complex_t)matrix_2cd(0,1)), matrix_abs(0,1));
   EXPECT_EQ(std::abs((complex_t)matrix_2cd(1,0)), matrix_abs(1,0));
   EXPECT_EQ(std::abs((complex_t)matrix_2cd(1,1)), matrix_abs(1,1));
}

TEST_F(MatrixFunctionsTest, ProductByElement)
{
    Eigen::Matrix2cd matrix_2cd2;
    matrix_2cd2(0,0) = complex_t(2.0, 1.0);
    matrix_2cd2(0,1) = complex_t(3.0, 1.0);
    matrix_2cd2(1,0) = complex_t(4.0, 1.0);
    matrix_2cd2(1,1) = complex_t(5.0, 1.0);

   Eigen::Matrix2cd matrix_prod = MathFunctions::ProductByElement(matrix_2cd, matrix_2cd2);
   EXPECT_EQ(complex_t(3.0, 4.0), matrix_prod(0,0));
   EXPECT_EQ(complex_t(8.0, 6.0), matrix_prod(0,1));
   EXPECT_EQ(complex_t(15.0, 8.0), matrix_prod(1,0));
   EXPECT_EQ(complex_t(24.0, 10.0), matrix_prod(1,1));
}

TEST_F(MatrixFunctionsTest, Conj)
{
   Eigen::Matrix2cd matrix_conj = MathFunctions::Conj(matrix_2cd);
   EXPECT_EQ(std::conj((complex_t)matrix_2cd(0,0)), matrix_conj(0,0));
   EXPECT_EQ(std::conj((complex_t)matrix_2cd(0,1)), matrix_conj(0,1));
   EXPECT_EQ(std::conj((complex_t)matrix_2cd(1,0)), matrix_conj(1,0));
   EXPECT_EQ(std::conj((complex_t)matrix_2cd(1,1)), matrix_conj(1,1));
}

TEST_F(MatrixFunctionsTest, Real)
{
   Eigen::Matrix2d matrix_conj = MathFunctions::Real(matrix_2cd);
   EXPECT_EQ(((complex_t)matrix_2cd(0,0)).real(), matrix_conj(0,0));
   EXPECT_EQ(((complex_t)matrix_2cd(0,1)).real(), matrix_conj(0,1));
   EXPECT_EQ(((complex_t)matrix_2cd(1,0)).real(), matrix_conj(1,0));
   EXPECT_EQ(((complex_t)matrix_2cd(1,1)).real(), matrix_conj(1,1));
}

#endif //MATRIXFUNCTIONSTEST_H
