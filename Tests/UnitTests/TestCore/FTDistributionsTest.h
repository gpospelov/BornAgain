#ifndef FTDISTRIBUTIONSTEST_H
#define FTDISTRIBUTIONSTEST_H

#include "FTDistributions.h"
#include "BornAgainNamespace.h"

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
    EXPECT_EQ(BornAgain::FTDistribution1DCauchyType, iftd1D->getName());
    EXPECT_NEAR(0.961538, iftd1D->evaluate(0.2),0.000001);

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
    EXPECT_EQ(BornAgain::FTDistribution1DCauchyType, iftd1DClone->getName());
    EXPECT_NEAR(0.5, iftd1DClone->evaluate(0.2),0.000001);

    delete iftd1D;
    delete iftd1DClone;
}

TEST_F(FTDistributionsTest, FTDistribution1DGaussConstructor)
{
    IFTDistribution1D * iftd1D = new FTDistribution1DGauss(1.0);
    EXPECT_EQ(1.0, iftd1D->getOmega());
    EXPECT_EQ(BornAgain::FTDistribution1DGaussType, iftd1D->getName());
    EXPECT_NEAR(0.9801987, iftd1D->evaluate(0.2),0.000001);

    iftd1D->setOmega(3.0);
    EXPECT_EQ(3.0, iftd1D->getOmega());

    delete iftd1D;
}

TEST_F(FTDistributionsTest, FTDistribution1DGaussClone)
{
    IFTDistribution1D * iftd1D = new FTDistribution1DGauss(-5.0);
    IFTDistribution1D * iftd1DClone = iftd1D->clone();

    EXPECT_EQ(-5.0, iftd1DClone->getOmega());
    EXPECT_EQ(BornAgain::FTDistribution1DGaussType, iftd1DClone->getName());
    EXPECT_NEAR(0.6065307, iftd1DClone->evaluate(0.2),0.000001);

    delete iftd1D;
    delete iftd1DClone;
}

TEST_F(FTDistributionsTest, FTDistribution1DGateConstructor)
{
    IFTDistribution1D * iftd1D = new FTDistribution1DGate(1.0);
    EXPECT_EQ(1.0, iftd1D->getOmega());
    EXPECT_EQ(BornAgain::FTDistribution1DGateType, iftd1D->getName());
    EXPECT_NEAR(0.993347, iftd1D->evaluate(0.2),0.000001);

    iftd1D->setOmega(3.0);
    EXPECT_EQ(3.0, iftd1D->getOmega());

    delete iftd1D;
}

TEST_F(FTDistributionsTest, FTDistribution1DGateClone)
{
    IFTDistribution1D * iftd1D = new FTDistribution1DGate(-5.0);
    IFTDistribution1D * iftd1DClone = iftd1D->clone();

    EXPECT_EQ(-5.0, iftd1DClone->getOmega());
    EXPECT_EQ(BornAgain::FTDistribution1DGateType, iftd1DClone->getName());
    EXPECT_NEAR(0.841471, iftd1DClone->evaluate(0.2),0.000001);

    delete iftd1D;
    delete iftd1DClone;
}

TEST_F(FTDistributionsTest, FTDistribution1DTriangleConstructor)
{
    IFTDistribution1D * iftd1D = new FTDistribution1DTriangle(1.0);
    EXPECT_EQ(1.0, iftd1D->getOmega());
    EXPECT_EQ(BornAgain::FTDistribution1DTriangleType, iftd1D->getName());
    EXPECT_NEAR(0.996671, iftd1D->evaluate(0.2),0.000001);

    iftd1D->setOmega(3.0);
    EXPECT_EQ(3.0, iftd1D->getOmega());

    delete iftd1D;
}

TEST_F(FTDistributionsTest, FTDistribution1DTriangleClone)
{
    IFTDistribution1D * iftd1D = new FTDistribution1DTriangle(-5.0);
    IFTDistribution1D * iftd1DClone = iftd1D->clone();

    EXPECT_EQ(-5.0, iftd1DClone->getOmega());
    EXPECT_EQ(BornAgain::FTDistribution1DTriangleType, iftd1DClone->getName());
    EXPECT_NEAR(0.919395, iftd1DClone->evaluate(0.2),0.000001);

    delete iftd1D;
    delete iftd1DClone;
}

TEST_F(FTDistributionsTest, FTDistribution1DCosineConstructor)
{
    IFTDistribution1D * iftd1D = new FTDistribution1DCosine(1.0);
    EXPECT_EQ(1.0, iftd1D->getOmega());
    EXPECT_EQ(BornAgain::FTDistribution1DCosineType, iftd1D->getName());
    EXPECT_NEAR(0.997389, iftd1D->evaluate(0.2),0.000001);

    iftd1D->setOmega(3.0);
    EXPECT_EQ(3.0, iftd1D->getOmega());

    delete iftd1D;
}

TEST_F(FTDistributionsTest, FTDistribution1DCosineClone)
{
    IFTDistribution1D * iftd1D = new FTDistribution1DCosine(-5.0);
    IFTDistribution1D * iftd1DClone = iftd1D->clone();

    EXPECT_EQ(-5.0, iftd1DClone->getOmega());
    EXPECT_EQ(BornAgain::FTDistribution1DCosineType, iftd1DClone->getName());
    EXPECT_NEAR(0.936342, iftd1DClone->evaluate(0.2),0.000001);

    delete iftd1D;
    delete iftd1DClone;
}

TEST_F(FTDistributionsTest, FTDistribution1DVoigtConstructor)
{
    IFTDistribution1D * iftd1D = new FTDistribution1DVoigt(1.0,1.7);
    EXPECT_EQ(1.0, iftd1D->getOmega());
    EXPECT_EQ(BornAgain::FTDistribution1DVoigtType, iftd1D->getName());
    EXPECT_NEAR(0.993261, iftd1D->evaluate(0.2),0.000001);

    iftd1D->setOmega(3.0);
    EXPECT_EQ(3.0, iftd1D->getOmega());

    delete iftd1D;
}

TEST_F(FTDistributionsTest, FTDistribution1DVoigtClone)
{
    IFTDistribution1D * iftd1D = new FTDistribution1DVoigt(-5.0,-5.6);
    IFTDistribution1D * iftd1DClone = iftd1D->clone();

    EXPECT_EQ(-5.0, iftd1DClone->getOmega());
    EXPECT_EQ(BornAgain::FTDistribution1DVoigtType, iftd1DClone->getName());
    EXPECT_NEAR(-0.096572, iftd1DClone->evaluate(0.2),0.000001);

    delete iftd1D;
    delete iftd1DClone;
}


// test 2D

TEST_F(FTDistributionsTest, FTDistribution2DCauchyConstructor)
{
    IFTDistribution2D * iftd2D = new FTDistribution2DCauchy(1.0,-2.0);
    EXPECT_EQ(1.0, iftd2D->getCoherenceLengthX());
    EXPECT_EQ(-2.0, iftd2D->getCoherenceLengthY());
    EXPECT_EQ(Units::PI/2.0, iftd2D->getDelta());
    EXPECT_EQ(0.0, iftd2D->getGamma());
    EXPECT_EQ(BornAgain::FTDistribution2DCauchyType, iftd2D->getName());
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
    EXPECT_EQ(Units::PI/2.0, iftd2DClone->getDelta());
    EXPECT_EQ(0.0, iftd2DClone->getGamma());
    EXPECT_EQ(BornAgain::FTDistribution2DCauchyType, iftd2DClone->getName());
    EXPECT_NEAR(0.165121078, iftd2DClone->evaluate(0.2, 0.5),0.000001);

    delete iftd2D;
    delete iftd2DClone;
}



TEST_F(FTDistributionsTest, FTDistribution2DGaussConstructor)
{
    IFTDistribution2D * iftd2D = new FTDistribution2DGauss(1.0,-2.0);
    EXPECT_EQ(1.0, iftd2D->getCoherenceLengthX());
    EXPECT_EQ(-2.0, iftd2D->getCoherenceLengthY());
    EXPECT_EQ(Units::PI/2.0, iftd2D->getDelta());
    EXPECT_EQ(0.0, iftd2D->getGamma());
    EXPECT_EQ(BornAgain::FTDistribution2DGaussType, iftd2D->getName());
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
    EXPECT_EQ(Units::PI/2.0, iftd2DClone->getDelta());
    EXPECT_EQ(0.0, iftd2DClone->getGamma());
    EXPECT_EQ(BornAgain::FTDistribution2DGaussType, iftd2DClone->getName());
    EXPECT_NEAR(0.3130945, iftd2DClone->evaluate(0.2, 0.5),0.000001);

    delete iftd2D;
    delete iftd2DClone;
}

TEST_F(FTDistributionsTest, FTDistribution2DGateConstructor)
{
    IFTDistribution2D * iftd2D = new FTDistribution2DGate(1.0,-2.0);
    EXPECT_EQ(1.0, iftd2D->getCoherenceLengthX());
    EXPECT_EQ(-2.0, iftd2D->getCoherenceLengthY());
    EXPECT_EQ(Units::PI/2.0, iftd2D->getDelta());
    EXPECT_EQ(0.0, iftd2D->getGamma());
    EXPECT_EQ(BornAgain::FTDistribution2DGateType, iftd2D->getName());
    EXPECT_NEAR(0.875513, iftd2D->evaluate(0.2, 0.5),0.000001);

    iftd2D->setGamma(3.0);
    EXPECT_EQ(3.0, iftd2D->getGamma());

    delete iftd2D;
}

TEST_F(FTDistributionsTest, FTDistribution2DGateClone)
{
    IFTDistribution2D * iftd2D = new FTDistribution2DGate(-5.0,2.3);
    IFTDistribution2D * iftd2DClone = iftd2D->clone();

    EXPECT_EQ(-5.0, iftd2DClone->getCoherenceLengthX());
    EXPECT_EQ(2.3, iftd2DClone->getCoherenceLengthY());
    EXPECT_EQ(Units::PI/2.0, iftd2DClone->getDelta());
    EXPECT_EQ(0.0, iftd2DClone->getGamma());
    EXPECT_EQ(BornAgain::FTDistribution2DGateType, iftd2DClone->getName());
    EXPECT_NEAR(0.736461, iftd2DClone->evaluate(0.2, 0.5),0.000001);

    delete iftd2D;
    delete iftd2DClone;
}

TEST_F(FTDistributionsTest, FTDistribution2DConeConstructor)
{
    IFTDistribution2D * iftd2D = new FTDistribution2DCone(1.0,-2.0);
    EXPECT_EQ(1.0, iftd2D->getCoherenceLengthX());
    EXPECT_EQ(-2.0, iftd2D->getCoherenceLengthY());
    EXPECT_EQ(Units::PI/2.0, iftd2D->getDelta());
    EXPECT_EQ(0.0, iftd2D->getGamma());
    EXPECT_EQ(BornAgain::FTDistribution2DConeType, iftd2D->getName());
    EXPECT_NEAR(0.924374, iftd2D->evaluate(0.2, 0.5),0.000001);

    iftd2D->setGamma(3.0);
    EXPECT_EQ(3.0, iftd2D->getGamma());

    delete iftd2D;
}

TEST_F(FTDistributionsTest, FTDistribution2DConeClone)
{
    IFTDistribution2D * iftd2D = new FTDistribution2DCone(-5.0,2.3);
    IFTDistribution2D * iftd2DClone = iftd2D->clone();

    EXPECT_EQ(-5.0, iftd2DClone->getCoherenceLengthX());
    EXPECT_EQ(2.3, iftd2DClone->getCoherenceLengthY());
    EXPECT_EQ(Units::PI/2.0, iftd2DClone->getDelta());
    EXPECT_EQ(0.0, iftd2DClone->getGamma());
    EXPECT_EQ(BornAgain::FTDistribution2DConeType, iftd2DClone->getName());
    EXPECT_NEAR(0.837410, iftd2DClone->evaluate(0.2, 0.5),0.000001);

    delete iftd2D;
    delete iftd2DClone;
}

TEST_F(FTDistributionsTest, FTDistribution2DVoigtConstructor)
{
    IFTDistribution2D * iftd2D = new FTDistribution2DVoigt(1.0,-2.0,3.5);
    EXPECT_EQ(1.0, iftd2D->getCoherenceLengthX());
    EXPECT_EQ(-2.0, iftd2D->getCoherenceLengthY());
    EXPECT_EQ(Units::PI/2.0, iftd2D->getDelta());
    EXPECT_EQ(0.0, iftd2D->getGamma());
    EXPECT_EQ(BornAgain::FTDistribution2DVoigtType, iftd2D->getName());
    EXPECT_NEAR(1.2228072, iftd2D->evaluate(0.2, 0.5),0.000001);

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
    EXPECT_EQ(Units::PI/2.0, iftd2DClone->getDelta());
    EXPECT_EQ(0.0, iftd2DClone->getGamma());
    EXPECT_EQ(BornAgain::FTDistribution2DVoigtType, iftd2DClone->getName());
    EXPECT_NEAR(-0.6635305, iftd2DClone->evaluate(0.2, 0.5),0.000001);

    delete iftd2D;
    delete iftd2DClone;
}


#endif //FTDISTRIBUTIONSTEST_H
