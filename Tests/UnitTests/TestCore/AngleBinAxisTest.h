#ifndef ANGLEBINAXISTEST_H
#define ANGLEBINAXISTEST_H

#include "AngleBinAxis.h"
#include "Units.h"
#include "gtest/gtest.h"
#include <iostream>

class AngleBinAxisTest: public ::testing::Test
{
protected:
    AngleBinAxisTest() {}

};

TEST_F(AngleBinAxisTest, UnitAxis)
{
    AngleBinAxis axis("angle", 1, -1.0*Units::degree, 1.0*Units::degree);
    EXPECT_EQ(1, axis.getSize());
//    EXPECT_DOUBLE_EQ(-1.0*Units::degree, axis.getMin());
//    EXPECT_DOUBLE_EQ(1.0*Units::degree, axis.getMax());
//    EXPECT_DOUBLE_EQ(0.0, axis[0]);
//    EXPECT_DOUBLE_EQ(-1.0*Units::degree, axis.getBin(0).m_lower);
//    EXPECT_DOUBLE_EQ(0.0, axis.getBin(0).getMidPoint());
//    EXPECT_DOUBLE_EQ(1.0*Units::degree, axis.getBin(0).m_upper);
//    EXPECT_DOUBLE_EQ(2.0*Units::degree, axis.getBin(0).getBinSize());

//    std::cout << Units::rad2deg(axis.getMin()) << " " << Units::rad2deg(axis.getMax()) << std::endl;
//    std::cout << Units::rad2deg(axis[0]) << std::endl;
}

TEST_F(AngleBinAxisTest, TwoBinsAxis)
{
    AngleBinAxis axis("angle", 2, 0.0*Units::degree, 1.0*Units::degree);
    EXPECT_EQ(2, axis.getSize());
//    EXPECT_DOUBLE_EQ(0.0*Units::degree, axis.getMin());
//    EXPECT_DOUBLE_EQ(1.0*Units::degree, axis.getMax());

//    double start_sin = std::sin(0.0*Units::degree);
//    double end_sin = std::sin(1.0*Units::degree);
//    double step_sin = (end_sin - start_sin)/2.;
//    EXPECT_DOUBLE_EQ(std::asin(start_sin + step_sin/2.), axis[0]);
//    EXPECT_DOUBLE_EQ(std::asin(start_sin + step_sin/2.), axis[1]);

//    EXPECT_DOUBLE_EQ( std::asin(start_sin + step_sin/2.), axis.getBin(0).getMidPoint());

//    std::cout << Units::rad2deg(axis[0]) << " " << Units::rad2deg(axis[1]) << std::endl;
}


TEST_F(AngleBinAxisTest, IsGISAXSAxis)
{
//    double start(-1.0);
//    double end(1.0);
//    int nbins(100);

//    AngleBinAxis *axis = AngleBinAxis::createIsGISAXSAxis("name", nbins, start, end);

//    double start_sin = std::sin(start);
//    double end_sin = std::sin(end);
//    double step = (end_sin-start_sin)/(nbins-1);
//    std::vector<double> values;
//    for(int i=0; i<nbins; ++i) {
//        values.push_back(std::asin(start_sin + step*i));
//    }
//    for(size_t i=0; i<100; ++i) {
//        EXPECT_DOUBLE_EQ(values[i], (*axis)[i]);
//    }


}


#endif
