#ifndef FTDISTRIBUTIONSTEST_H
#define FTDISTRIBUTIONSTEST_H

#include "FTDistributions.h"

class FTDistributionsTest : public ::testing::Test
{
protected:
    FTDistributionsTest(){}
    virtual ~FTDistributionsTest(){}
};




TEST_F(FTDistributionsTest, FTDistribution2DCauchyConstructor)
{
    IFTDistribution2D * iftd2D = new FTDistribution2DCauchy(1.0,-2.0);
    EXPECT_EQ(1.0, iftd2D->getCoherenceLengthX());
    EXPECT_EQ(-2.0, iftd2D->getCoherenceLengthY());
    EXPECT_EQ(M_PI/2.0, iftd2D->getDelta());
    EXPECT_EQ(0.0, iftd2D->getGamma());
    EXPECT_EQ("2DDistributionCauchy", iftd2D->getName());
    EXPECT_NEAR(0.343206, iftd2D->evaluate(0.2, 0.5),0.000001);

    iftd2D->setGamma(3.0);
    EXPECT_EQ(3.0, iftd2D->getGamma());

    iftd2D->setParameterValue("coherence_length_x", -7.0);
    iftd2D->setParameterValue("coherence_length_y", 5.3);
    EXPECT_EQ(-7.0, iftd2D->getCoherenceLengthX());
    EXPECT_EQ(5.3, iftd2D->getCoherenceLengthY());


    delete iftd2D;
}

TEST_F(FTDistributionsTest, FTDistribution2DCauchyClone)
{
    IFTDistribution2D * iftd2D = new FTDistribution2DCauchy(-5.0,2.3);
    IFTDistribution2D * iftd2DClone = iftd2D->clone();

    EXPECT_EQ(-5.0, iftd2DClone->getCoherenceLengthX());
    EXPECT_EQ(2.3, iftd2DClone->getCoherenceLengthY());
    EXPECT_EQ(M_PI/2.0, iftd2DClone->getDelta());
    EXPECT_EQ(0.0, iftd2DClone->getGamma());
    EXPECT_EQ("2DDistributionCauchy", iftd2DClone->getName());
    EXPECT_NEAR(0.165121078, iftd2DClone->evaluate(0.2, 0.5),0.000001);



    delete iftd2D;
    delete iftd2DClone;
}



TEST_F(FTDistributionsTest, FTDistribution2DGaussConstructor)
{
    IFTDistribution2D * iftd2D = new FTDistribution2DGauss(1.0,-2.0);
    EXPECT_EQ(1.0, iftd2D->getCoherenceLengthX());
    EXPECT_EQ(-2.0, iftd2D->getCoherenceLengthY());
    EXPECT_EQ(M_PI/2.0, iftd2D->getDelta());
    EXPECT_EQ(0.0, iftd2D->getGamma());
    EXPECT_EQ("2DDistributionGauss", iftd2D->getName());
    EXPECT_NEAR(0.3855258, iftd2D->evaluate(0.2, 0.5),0.000001);

    iftd2D->setGamma(3.0);
    EXPECT_EQ(3.0, iftd2D->getGamma());


    delete iftd2D;
}

TEST_F(FTDistributionsTest, FTDistribution2DGaussClone)
{
    IFTDistribution2D * iftd2D = new FTDistribution2DGauss(-5.0,2.3);
    IFTDistribution2D * iftd2DClone = iftd2D->clone();

    EXPECT_EQ(-5.0, iftd2DClone->getCoherenceLengthX());
    EXPECT_EQ(2.3, iftd2DClone->getCoherenceLengthY());
    EXPECT_EQ(M_PI/2.0, iftd2DClone->getDelta());
    EXPECT_EQ(0.0, iftd2DClone->getGamma());
    EXPECT_EQ("2DDistributionGauss", iftd2DClone->getName());
    EXPECT_NEAR(0.279774, iftd2DClone->evaluate(0.2, 0.5),0.000001);

    delete iftd2D;
    delete iftd2DClone;
}

TEST_F(FTDistributionsTest, FTDistribution2DVoigtConstructor)
{
    IFTDistribution2D * iftd2D = new FTDistribution2DVoigt(1.0,-2.0,3.5);
    EXPECT_EQ(1.0, iftd2D->getCoherenceLengthX());
    EXPECT_EQ(-2.0, iftd2D->getCoherenceLengthY());
    EXPECT_EQ(M_PI/2.0, iftd2D->getDelta());
    EXPECT_EQ(0.0, iftd2D->getGamma());
    EXPECT_EQ("2DDistributionVoigt", iftd2D->getName());
    EXPECT_NEAR(0.4913253, iftd2D->evaluate(0.2, 0.5),0.000001);

    iftd2D->setGamma(3.0);
    EXPECT_EQ(3.0, iftd2D->getGamma());


    delete iftd2D;
}

TEST_F(FTDistributionsTest, FTDistribution2DVoigtClone)
{
    IFTDistribution2D * iftd2D = new FTDistribution2DVoigt(-5.0,2.3, -5.6);
    IFTDistribution2D * iftd2DClone = iftd2D->clone();

    EXPECT_EQ(-5.0, iftd2DClone->getCoherenceLengthX());
    EXPECT_EQ(2.3, iftd2DClone->getCoherenceLengthY());
    EXPECT_EQ(M_PI/2.0, iftd2DClone->getDelta());
    EXPECT_EQ(0.0, iftd2DClone->getGamma());
    EXPECT_EQ("2DDistributionVoigt", iftd2DClone->getName());
    EXPECT_NEAR(-0.476936, iftd2DClone->evaluate(0.2, 0.5),0.000001);

    delete iftd2D;
    delete iftd2DClone;
}


#endif //FTDISTRIBUTIONSTEST_H
