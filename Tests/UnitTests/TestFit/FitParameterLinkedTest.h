#ifndef FITPARAMETERLINKEDTEST_H
#define FITPARAMETERLINKEDTEST_H

#include "ParameterPool.h"
#include "FitParameterLinked.h"

#include "gtest/gtest.h"


class FitParameterLinkedTest : public ::testing::Test
{
 protected:
    FitParameterLinkedTest(){}
    virtual ~FitParameterLinkedTest(){}
};


TEST_F(FitParameterLinkedTest, FitParameterLinkedInitial)
{
    FitParameterLinked fitParameterLinked;

    EXPECT_EQ("", fitParameterLinked.getName());
    EXPECT_EQ(0.0, fitParameterLinked.getValue());
    EXPECT_EQ(0.0, fitParameterLinked.getStep());
    EXPECT_EQ(0.0, fitParameterLinked.getError());

    EXPECT_FALSE(fitParameterLinked.hasLowerLimit());
    EXPECT_FALSE(fitParameterLinked.hasUpperLimit());
    EXPECT_FALSE(fitParameterLinked.hasLowerAndUpperLimits());
    EXPECT_FALSE(fitParameterLinked.isFixed());
}

TEST_F(FitParameterLinkedTest, FitParameterLinkedWithValue)
{
    AttLimits attLimits = AttLimits::limited(-10.0, 2.0);

    FitParameterLinked fitParameter("FitPL", 2.0, 0.2, attLimits, 0.01);

    EXPECT_EQ("FitPL", fitParameter.getName());
    EXPECT_EQ(2.0, fitParameter.getValue());
    EXPECT_EQ(0.2, fitParameter.getStep());
    EXPECT_EQ(0.01, fitParameter.getError());

    EXPECT_EQ(-10.0, fitParameter.getLowerLimit());
    EXPECT_EQ(2.0, fitParameter.getUpperLimit());

}

TEST_F(FitParameterLinkedTest, FitParameterLinkedParamPool)
{
    FitParameterLinked fitParameterLinked;

    double pValue1 = 1.0;
    double pValue2 = 2.0;
    double pValue3 = 3.0;
    double pValue4 = 4.0;
    double pValue5 = 5.0;
    double pValue6 = 6.0;

    /* TODO restore
    RealParameterWrapper poolpar1(&pValue1);
    RealParameterWrapper poolpar2(&pValue2);
    RealParameterWrapper poolpar3(&pValue3);
    RealParameterWrapper poolpar4(&pValue4);
    RealParameterWrapper poolpar5(&pValue5);
    RealParameterWrapper poolpar6(&pValue6);

    fitParameterLinked.addParameter(poolpar1);
    fitParameterLinked.addParameter(poolpar2);
    fitParameterLinked.addParameter(poolpar3);

    fitParameterLinked.setValue(11.2);
    EXPECT_EQ(11.2, fitParameterLinked.getValue());
    EXPECT_EQ(11.2, pValue1);
    EXPECT_EQ(11.2, pValue2);
    EXPECT_EQ(11.2, pValue3);

    ParameterPool m_pool;
    m_pool.addParameter("par4",poolpar4);
    m_pool.addParameter("par5",poolpar5);
    m_pool.addParameter("par6",poolpar6);

    fitParameterLinked.addMatchedParametersFromPool(&m_pool,"par4");
    fitParameterLinked.setValue(2.3);

    EXPECT_EQ(2.3, fitParameterLinked.getValue());
    EXPECT_EQ(2.3, pValue1);
    EXPECT_EQ(2.3, pValue2);
    EXPECT_EQ(2.3, pValue3);
    EXPECT_EQ(2.3, pValue4);
    */
}

#endif //FITPARAMETERLINKEDTEST_H
