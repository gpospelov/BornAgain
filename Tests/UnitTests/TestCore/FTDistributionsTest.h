#ifndef FTDISTRIBUTIONSTEST_H
#define FTDISTRIBUTIONSTEST_H

#include "FTDistributions.h"

class FTDistributionsTest : public ::testing::Test
{
protected:
    FTDistributionsTest(){}
    virtual ~FTDistributionsTest(){}
};


// test 1D
TEST_F(FTDistributionsTest, FTDistribution1DCauchyConstructor)
{
    IFTDistribution1D * iftd1D = new FTDistribution1DCauchy(1.0);
    EXPECT_EQ(1.0, iftd1D->getOmega());
    EXPECT_EQ("1DDistributionCauchy", iftd1D->getName());
    EXPECT_NEAR(0.942866, iftd1D->evaluate(0.2),0.000001);

    iftd1D->setOmega(3.0);
    EXPECT_EQ(3.0, iftd1D->getOmega());

    iftd1D->setParameterValue("omega", -7.0);
    EXPECT_EQ(-7.0, iftd1D->getOmega());

    delete iftd1D;
}

TEST_F(FTDistributionsTest, FTDistribution1DCauchyClone)
{
    IFTDistribution1D * iftd1D = new FTDistribution1DCauchy(-5.0);
    IFTDistribution1D * iftd1DClone = iftd1D->clone();

    EXPECT_EQ(-5.0, iftd1DClone->getOmega());
    EXPECT_EQ("1DDistributionCauchy", iftd1DClone->getName());
    EXPECT_NEAR(0.353553, iftd1DClone->evaluate(0.2),0.000001);

    delete iftd1D;
    delete iftd1DClone;
}

TEST_F(FTDistributionsTest, FTDistribution1DGaussConstructor)
{
    IFTDistribution1D * iftd1D = new FTDistribution1DGauss(1.0);
    EXPECT_EQ(1.0, iftd1D->getOmega());
    EXPECT_EQ("1DDistributionGauss", iftd1D->getName());
    EXPECT_NEAR(0.4950249, iftd1D->evaluate(0.2),0.000001);

    iftd1D->setOmega(3.0);
    EXPECT_EQ(3.0, iftd1D->getOmega());

    delete iftd1D;
}

TEST_F(FTDistributionsTest, FTDistribution1DGaussClone)
{
    IFTDistribution1D * iftd1D = new FTDistribution1DGauss(-5.0);
    IFTDistribution1D * iftd1DClone = iftd1D->clone();

    EXPECT_EQ(-5.0, iftd1DClone->getOmega());
    EXPECT_EQ("1DDistributionGauss", iftd1DClone->getName());
    EXPECT_NEAR(0.389400, iftd1DClone->evaluate(0.2),0.000001);

    delete iftd1D;
    delete iftd1DClone;
}

TEST_F(FTDistributionsTest, FTDistribution1DVoigtConstructor)
{
    IFTDistribution1D * iftd1D = new FTDistribution1DVoigt(1.0,1.7);
    EXPECT_EQ(1.0, iftd1D->getOmega());
    EXPECT_EQ("1DDistributionVoigt", iftd1D->getName());
    EXPECT_NEAR(0.181536, iftd1D->evaluate(0.2),0.000001);

    iftd1D->setOmega(3.0);
    EXPECT_EQ(3.0, iftd1D->getOmega());

    delete iftd1D;
}

TEST_F(FTDistributionsTest, FTDistribution1DVoigtClone)
{
    IFTDistribution1D * iftd1D = new FTDistribution1DVoigt(-5.0,-5.6);
    IFTDistribution1D * iftd1DClone = iftd1D->clone();

    EXPECT_EQ(-5.0, iftd1DClone->getOmega());
    EXPECT_EQ("1DDistributionVoigt", iftd1DClone->getName());
    EXPECT_NEAR(0.152810, iftd1DClone->evaluate(0.2),0.000001);

    delete iftd1D;
    delete iftd1DClone;
}


// test 2D

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
    EXPECT_NEAR(0.5945205, iftd2D->evaluate(0.2, 0.5),0.000001);

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
    EXPECT_NEAR(0.3130945, iftd2DClone->evaluate(0.2, 0.5),0.000001);

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
