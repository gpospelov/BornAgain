#ifndef CUSTOMBINAXISTEST_H
#define CUSTOMBINAXISTEST_H

#include "CustomBinAxis.h"
#include "OutputDataIOHelper.h"
#include "Units.h"
#include "gtest/gtest.h"
#include <vector>

class CusomBinAxisTest: public ::testing::Test
{
protected:
    CusomBinAxisTest()
        : m_axis("name", 100, -1.0, 1.0){}
    CustomBinAxis m_axis;
};


TEST_F(CusomBinAxisTest, CheckClone)
{
    CustomBinAxis *clone=m_axis.clone();
    EXPECT_TRUE(m_axis == *clone);
    delete clone;
}

TEST_F(CusomBinAxisTest, IOStream)
{

    std::ostringstream oss;
    oss << m_axis;

    CustomBinAxis *result = dynamic_cast<CustomBinAxis *>(OutputDataIOHelper::createFixedBinAxis(oss.str()));
    EXPECT_TRUE(m_axis == *result);
    delete result;
}


#endif
