#ifndef PARAMETERDISTRIBUTIONTEST_H
#define PARAMETERDISTRIBUTIONTEST_H

#include "ParameterDistribution.h"
#include "Distributions.h"
#include "ParameterSample.h"
#include "IParameterized.h"
#include <cmath>

class ParameterDistributionTest : public ::testing::Test
{

protected:
   ParameterDistributionTest(){}
    virtual ~ParameterDistributionTest(){}
};

TEST_F(ParameterDistributionTest, DistributionGateConstructor)
{
    std::string name = "ParameterDistribution";
    DistributionGate distribution(1.0,2.0);
    EXPECT_THROW(ParameterDistribution(name,distribution,1.0, -1.0), RuntimeErrorException);
    ParameterDistribution pd1D(name,distribution,1,0.0);
    EXPECT_EQ(1.5, pd1D.getDistribution()->getMean());
    EXPECT_EQ("DistributionGate", pd1D.getDistribution()->getName());
    EXPECT_EQ(1.0, pd1D.getDistribution()->probabilityDensity(1));
    EXPECT_EQ("ParameterDistribution",pd1D.getMainParameterName());
    EXPECT_EQ(1,pd1D.getNbrSamples());
    EXPECT_EQ(0.0, pd1D.getSigmaFactor());

    ParameterDistribution pd1D1(name, distribution, 0, 1.0);
    EXPECT_THROW(pd1D1.generateSamples(),OutOfBoundsException);
    std::vector<ParameterSample> list = pd1D.generateSamples();
    ParameterSample parameterSample = list[0];
    EXPECT_EQ(pd1D.getDistribution()->getMean(), parameterSample.value);
    EXPECT_EQ(pd1D.getDistribution()->probabilityDensity(pd1D.getDistribution()->getMean()), parameterSample.weight);
    pd1D.linkParameter("parameter");

    std::vector<std::string> linked_par_names = pd1D.getLinkedParameterNames();
    EXPECT_EQ("parameter", linked_par_names[0]);


    std::string nameOther = "ParameterDistribution2";
    DistributionGate distributionOther(1.0,2.0);
    ParameterDistribution pd1DOther(nameOther,distributionOther,1,0.0);
    pd1D.operator =(pd1DOther);
    EXPECT_EQ(pd1DOther.getDistribution()->getName(), pd1D.getDistribution()->getName());
    EXPECT_EQ(pd1DOther.getLinkedParameterNames(), pd1D.getLinkedParameterNames());
    EXPECT_EQ(pd1DOther.getNbrSamples(), pd1D.getNbrSamples());
    EXPECT_EQ(pd1DOther.getName(), pd1D.getName());
    EXPECT_EQ(pd1DOther.getMainParameterName(), pd1D.getMainParameterName());
    EXPECT_EQ(pd1DOther.getSigmaFactor(), pd1D.getSigmaFactor());

}

#endif
