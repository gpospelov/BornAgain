#ifndef DISTRIBUTIONHANDLERTEST_H
#define DISTRIBUTIONHANDLERTEST_H

#include "DistributionHandler.h"
#include "Distributions.h"
#include <cmath>

class DistributionHandlerTest : public ::testing::Test
{

protected:
   DistributionHandlderTest(){}
    virtual ~DistributionHandlerTest(){}
};

TEST_F(DistributionHandlerTest, DistributionHandlerConstructor)
{
    DistributionHandler handler();
    DistributionGate distribution(1.0, 2.0);
    std::string paraName = 'DistributionGate';
    EXPECT_EQ(0, handler.getTotalNumberOfSamples());
    handler().addParameterDistribution(paraName, distribution, 1.0, 1.0);
    EXPECT_EQ(1, handler.getTotalNumberOfSamples());
    EXPECT_EQ("",handler.getName());

}


#endif
