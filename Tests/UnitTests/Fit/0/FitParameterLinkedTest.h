#ifndef FITPARAMETERLINKEDTEST_H
#define FITPARAMETERLINKEDTEST_H

#include "IParameterized.h"
#include "RealParameter.h"
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

    EXPECT_EQ("", fitParameterLinked.name());
    EXPECT_EQ(0.0, fitParameterLinked.value());
    EXPECT_EQ(0.0, fitParameterLinked.step());
    EXPECT_EQ(0.0, fitParameterLinked.error());

    EXPECT_FALSE(fitParameterLinked.limits().isLowerLimited());
    EXPECT_FALSE(fitParameterLinked.limits().isUpperLimited());
    EXPECT_FALSE(fitParameterLinked.limits().isLimited());
    EXPECT_FALSE(fitParameterLinked.limits().isFixed());
}

TEST_F(FitParameterLinkedTest, FitParameterLinkedWithValue)
{
    AttLimits limits = AttLimits::limited(-10.0, 2.0);

    FitParameterLinked fitParameter("FitPL", 2.0, limits, 0.2);

    EXPECT_EQ("FitPL", fitParameter.name());
    EXPECT_EQ(2.0, fitParameter.value());
    EXPECT_EQ(0.2, fitParameter.step());

    EXPECT_EQ(-10.0, fitParameter.limits().lowerLimit());
    EXPECT_EQ(2.0, fitParameter.limits().upperLimit());
}

TEST_F(FitParameterLinkedTest, FitParameterLinkedParamPool)
{
    class ParametrizedObject : public IParameterized
    {
    public:
        ParametrizedObject(double p1, double p2) : m1(p1), m2(p2)
        {
            registerParameter("1", &m1);
            registerParameter("2", &m2);
        }
        virtual void onChange() final {}
        double m1, m2;
    };
    ParametrizedObject obj1(1., 2.);
    ParametrizedObject obj2(3., 4.);
    ParametrizedObject obj3(5., 6.);

    RealParameter* par11(obj1.getParameter("1"));
    RealParameter* par21(obj2.getParameter("1"));
    RealParameter* par32(obj3.getParameter("2"));

    FitParameterLinked linked;
    linked.addParameter(par11);
    linked.addParameter(par21);
    linked.addParameter(par32);

    linked.setValue(11.2);
    EXPECT_EQ(linked.value(), 11.2);
    EXPECT_EQ(obj1.getParameter("1")->getValue(), 11.2);
    EXPECT_EQ(obj1.getParameter("2")->getValue(), 2);
    EXPECT_EQ(obj2.getParameter("1")->getValue(), 11.2);
    EXPECT_EQ(obj2.getParameter("2")->getValue(), 4);
    EXPECT_EQ(obj3.getParameter("1")->getValue(), 5);
    EXPECT_EQ(obj3.getParameter("2")->getValue(), 11.2);

    /* I need to understand a use case before I can restore this test - JWu apr16
    ParameterPool* pool( obj3.getParameterPool() );
    double par7 = 7.7;
    double par8 = 8.8;
    double par9 = 9.9;

    pool->addParameter("par7",par7);
    pool->addParameter("par8",par8);
    pool->addParameter("par9",par9);

    linked.addMatchedParametersFromPool(pool,"par7");
    linked.setValue(2.3);

    EXPECT_EQ(linked.getValue(), 2.3);
    EXPECT_EQ(par7, 2.3);
    EXPECT_EQ(pool.getParameter("par7"), 2.3);
    EXPECT_EQ(obj1.getParameter("1"), 2.3);
    EXPECT_EQ(obj1.getParameter("2"), 2);
    EXPECT_EQ(obj2.getParameter("1"), 2.3);
    EXPECT_EQ(obj2.getParameter("2"), 4);
    EXPECT_EQ(obj2.getParameter("1"), 5);
    EXPECT_EQ(obj3.getParameter("2"), 2.3);
    */
}

#endif // FITPARAMETERLINKEDTEST_H
