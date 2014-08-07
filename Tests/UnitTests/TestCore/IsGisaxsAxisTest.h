#ifndef ISGISAXSAXISTEST_H
#define ISGISAXSAXISTEST_H

#include "IsGisaxsAxis.h"
#include "OutputDataIOHelper.h"
#include "Units.h"
#include "gtest/gtest.h"
#include <vector>

class IsGisaxsAxisTest: public ::testing::Test
{
protected:
    IsGisaxsAxisTest()
        : m_axis("name", 100, -1.0, 1.0){}
    IsGisaxsAxis m_axis;
};


//TEST_F(IsGisaxsAxisTest, TypicalAxis)
//{
//    EXPECT_EQ(m_nbins, m_axis.getSize());
//    EXPECT_EQ(m_start, m_axis.getMin());
//    EXPECT_EQ(m_end, m_axis.getMax());

//    for(size_t i=0; i<m_axis.getSize(); ++i) {
//        EXPECT_DOUBLE_EQ( m_centers[i], m_axis[i]);
//    }

//    for(size_t i=0; i<m_axis.getSize(); ++i) {
//        EXPECT_DOUBLE_EQ( m_boundaries[i], m_axis.getBin(i).m_lower);
//        EXPECT_DOUBLE_EQ( m_boundaries[i+1], m_axis.getBin(i).m_upper);
//    }
//}


TEST_F(IsGisaxsAxisTest, CheckClone)
{
    IsGisaxsAxis *clone=m_axis.clone();
    EXPECT_TRUE(m_axis == *clone);
    delete clone;
}


TEST_F(IsGisaxsAxisTest, IOStream)
{

    std::ostringstream oss;
    oss << m_axis;

    IsGisaxsAxis *result = dynamic_cast<IsGisaxsAxis *>(OutputDataIOHelper::createFixedBinAxis(oss.str()));
    EXPECT_TRUE(m_axis == *result);
    delete result;
}


#endif
