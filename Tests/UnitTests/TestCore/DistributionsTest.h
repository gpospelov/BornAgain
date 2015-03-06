#ifndef DISTRIBUTIONSTEST_H
#define DISTRIBUTIONSTEST_H

#include "Distributions.h"
#include <cmath>

class DistributionsTest : public ::testing::Test
{

protected:
   DistributionsTest(){}
    virtual ~DistributionsTest(){}
};

// -------------------------------------------------------------------------- //

TEST_F(DistributionsTest, DistributionGateDefaultConstructor)
{
    DistributionGate * id1D = new DistributionGate();
    EXPECT_EQ(0.5, id1D->getMean());
    EXPECT_EQ(0.0, id1D->getMin());
    EXPECT_EQ(1.0, id1D->getMax());
    EXPECT_EQ(1.0, id1D->probabilityDensity(1));
    EXPECT_EQ(0, id1D->probabilityDensity(3));
    EXPECT_EQ("DistributionGate", id1D->getName());

    std::vector<double> list1 = id1D->generateValueList(1, 0.0);
    EXPECT_EQ(list1.size(), size_t(1));
    EXPECT_EQ(id1D->getMean(), list1[0]);

    std::vector<double> list2 = id1D->generateValueList(2, 0.0);
    EXPECT_EQ(list2.size(), size_t(2));
    EXPECT_EQ(0, list2[0]);
    EXPECT_EQ(1, list2[1]);

    delete id1D;
}

TEST_F(DistributionsTest, DistributionGateConstructor)
{
    EXPECT_THROW(DistributionGate(1.0, 1.0), ClassInitializationException);
    DistributionGate * id1D = new DistributionGate(1.0, 2.0);
    EXPECT_EQ(1.5, id1D->getMean());
    EXPECT_EQ(1.0, id1D->getMin());
    EXPECT_EQ(2.0, id1D->getMax());
    EXPECT_EQ(1.0, id1D->probabilityDensity(1));
    EXPECT_EQ(0, id1D->probabilityDensity(3));
    EXPECT_EQ("DistributionGate", id1D->getName());

    std::vector<double> list1 = id1D->generateValueList(1, 0.0);
    EXPECT_EQ(id1D->getMean(), list1[0]);

    std::vector<double> list2 = id1D->generateValueList(2, 0.0);
    EXPECT_EQ(1, list2[0]);
    EXPECT_EQ(2, list2[1]);

    delete id1D;
}

TEST_F(DistributionsTest, DistributionGateParameters)
{
    DistributionGate gate(2.0, 3.0);
    EXPECT_EQ(gate.getMin(), gate.getParameterPool()->getParameter("min").getValue());
    EXPECT_EQ(gate.getMax(), gate.getParameterPool()->getParameter("max").getValue());
}

TEST_F(DistributionsTest, DistributionGateClone)
{
    DistributionGate gate(2.0, 3.0);
    DistributionGate *clone = gate.clone();
    EXPECT_EQ(gate.getName(), clone->getName());
    EXPECT_EQ(gate.getMean(), clone->getMean());
    EXPECT_EQ(gate.getMin(), clone->getMin());
    EXPECT_EQ(gate.getMax(), clone->getMax());
    delete clone;
}

// -------------------------------------------------------------------------- //

TEST_F(DistributionsTest, DistributionLorentzDefaultConstructer)
{
    DistributionLorentz * id1D = new DistributionLorentz();
    EXPECT_EQ(0.0, id1D->getMean());
    EXPECT_EQ(1.0, id1D->getHWHM());
    EXPECT_EQ("DistributionLorentz", id1D->getName());
    EXPECT_EQ(1/(2*M_PI), id1D->probabilityDensity(1.0));

    std::vector<double> list1 = id1D->generateValueList(1, 0.0);
    EXPECT_EQ(id1D->getMean(), list1[0]);

    std::vector<double> list2 = id1D->generateValueList(2, 0.0);
    EXPECT_EQ(-2, list2[0]);
    EXPECT_EQ(2, list2[1]);
    delete id1D;
}

TEST_F(DistributionsTest, DistributionLorentzConstructer)
{
    DistributionLorentz * id1D = new DistributionLorentz(1.0, 1.0);
    EXPECT_EQ(1.0, id1D->getMean());
    EXPECT_EQ(1.0, id1D->getHWHM());
    EXPECT_EQ("DistributionLorentz", id1D->getName());
    EXPECT_EQ(1.0/M_PI, id1D->probabilityDensity(1.0));

    std::vector<double> list1 = id1D->generateValueList(1, 0.0);
    EXPECT_EQ(id1D->getMean(), list1[0]);

    std::vector<double> list2 = id1D->generateValueList(2, 0.0);
    EXPECT_EQ(-1, list2[0]);
    EXPECT_EQ(3, list2[1]);

    delete id1D;
}

TEST_F(DistributionsTest, DistributionLorentzClone)
{
    DistributionLorentz * id1D = new DistributionLorentz(1.0, 2.0);
    DistributionLorentz* id1DClone = id1D->clone();
    EXPECT_EQ(1.0, id1DClone->getMean());
    EXPECT_EQ(2.0, id1DClone->getHWHM());
    EXPECT_EQ(2/(5*M_PI), id1DClone->probabilityDensity(2.0));
    EXPECT_EQ("DistributionLorentz", id1DClone->getName());

    std::vector<double> list1 = id1DClone->generateValueList(1, 0.0);
    EXPECT_EQ(id1D->getMean(), list1[0]);

    std::vector<double> list2 = id1DClone->generateValueList(2, 0.0);
    EXPECT_EQ(-3, list2[0]);
    EXPECT_EQ(5, list2[1]);

    delete id1D;
    delete id1DClone;
}

// -------------------------------------------------------------------------- //

TEST_F(DistributionsTest, DistributionGaussianDefaultConstructor)
{
    DistributionGaussian* id1D = new DistributionGaussian();
    EXPECT_EQ(0.0, id1D->getMean());
    EXPECT_EQ(1.0, id1D->getStdDev());
    EXPECT_EQ(std::exp(-1.0/2.0)/std::sqrt(2.0*M_PI), id1D->probabilityDensity(1.0));
    EXPECT_EQ("DistributionGaussian", id1D->getName());

    std::vector<double> list1 = id1D->generateValueList(1, 0.0);
    EXPECT_EQ(id1D->getMean(), list1[0]);

    std::vector<double> list2 = id1D->generateValueList(2, 0.0);
    EXPECT_EQ(-2, list2[0]);
    EXPECT_EQ(2, list2[1]);

    delete id1D;
}

TEST_F(DistributionsTest, DistributionGaussianConstructor)
{
    DistributionGaussian* id1D = new DistributionGaussian(1.0, 1.0);
    EXPECT_EQ(1.0, id1D->getMean());
    EXPECT_EQ(1.0, id1D->getStdDev());
    EXPECT_EQ(1/std::sqrt(2.0*M_PI), id1D->probabilityDensity(1.0));
    EXPECT_EQ("DistributionGaussian", id1D->getName());

    std::vector<double> list1 = id1D->generateValueList(1, 0.0);
    EXPECT_EQ(id1D->getMean(), list1[0]);

    std::vector<double> list2 = id1D->generateValueList(2, 0.0);
    EXPECT_EQ(-1, list2[0]);
    EXPECT_EQ(3, list2[1]);

    delete id1D;
}

TEST_F(DistributionsTest, DistributionGaussianClone)
{
    DistributionGaussian* id1D = new DistributionGaussian(1.0, 1.0);
    DistributionGaussian* id1DClone = id1D->clone();
    EXPECT_EQ(1.0, id1DClone->getMean());
    EXPECT_EQ(1.0, id1DClone->getStdDev());
    EXPECT_EQ(1/std::sqrt(2.0*M_PI), id1DClone->probabilityDensity(1.0));
    EXPECT_EQ("DistributionGaussian", id1DClone->getName());

    std::vector<double> list1 = id1DClone->generateValueList(1, 0.0);
    EXPECT_EQ(id1D->getMean(), list1[0]);

    std::vector<double> list2 = id1DClone->generateValueList(2, 0.0);
    EXPECT_EQ(-1, list2[0]);
    EXPECT_EQ(3, list2[1]);

    delete id1D;
    delete id1DClone;

}

// -------------------------------------------------------------------------- //

TEST_F(DistributionsTest, DistributionLogNormalConstructorWithOneParameter)
{
    DistributionLogNormal* id1D = new DistributionLogNormal(1.0);
    EXPECT_EQ(1.0, id1D->getMedian());
    EXPECT_EQ(1.0, id1D->getScalePar());
    EXPECT_EQ(std::exp(0.5), id1D->getMean());
    EXPECT_EQ(1.0/std::sqrt(2.0*M_PI), id1D->probabilityDensity(1.0));
    EXPECT_EQ("DistributionLogNormal", id1D->getName());

    std::vector<double> list1 = id1D->generateValueList(1, 0.0);
    EXPECT_EQ(id1D->getMedian(), list1[0]);

    std::vector<double> list2 = id1D->generateValueList(2, 0.0);
    EXPECT_EQ(std::exp(-2), list2[0]);
    EXPECT_EQ(std::exp(-2) + std::exp(2) - std::exp(-2), list2[1]);

    delete id1D;
}

TEST_F(DistributionsTest, DistributionLogNormalConstructorWithTwoParameter)
{
    DistributionLogNormal* id1D = new DistributionLogNormal(1.0,1.0);
    EXPECT_EQ(1.0, id1D->getMedian());
    EXPECT_EQ(1.0, id1D->getScalePar());
    EXPECT_EQ(std::exp(0.5), id1D->getMean());
    EXPECT_EQ(1.0/std::sqrt(2.0*M_PI), id1D->probabilityDensity(1.0));
    EXPECT_EQ("DistributionLogNormal", id1D->getName());

    std::vector<double> list1 = id1D->generateValueList(1, 0.0);
    EXPECT_EQ(id1D->getMedian(), list1[0]);

    std::vector<double> list2 = id1D->generateValueList(2, 0.0);
    EXPECT_EQ(std::exp(-2), list2[0]);
    EXPECT_EQ(std::exp(-2) + std::exp(2) - std::exp(-2), list2[1]);

    delete id1D;
}

TEST_F(DistributionsTest, DistributionLogNormalClone)
{
    DistributionLogNormal* id1D = new DistributionLogNormal(1.0, 1.0);
    DistributionLogNormal* id1DClone = id1D->clone();
    EXPECT_EQ(1.0, id1D->getMedian());
    EXPECT_EQ(1.0, id1D->getScalePar());
    EXPECT_EQ(std::exp(0.5), id1D->getMean());
    EXPECT_EQ(1/std::sqrt(2.0*M_PI), id1D->probabilityDensity(1.0));
    EXPECT_EQ("DistributionLogNormal", id1D->getName());

    std::vector<double> list1 = id1D->generateValueList(1.0, 0.0);
    EXPECT_EQ(id1D->getMedian(), list1[0]);

    std::vector<double> list2 = id1D->generateValueList(2.0,0.0);
    EXPECT_EQ(std::exp(-2), list2[0]);
    EXPECT_EQ(std::exp(-2) + std::exp(2) - std::exp(-2), list2[1]);

    delete id1D;
    delete id1DClone;
}

// -------------------------------------------------------------------------- //

TEST_F(DistributionsTest, DistributionCosineDefaultConstructor)
{
    DistributionCosine* id1D = new DistributionCosine();
    EXPECT_EQ(0.0, id1D->getMean());
    EXPECT_EQ(1.0, id1D->getSigma());
    EXPECT_EQ((1.0+std::cos(1))/(2.0*M_PI), id1D->probabilityDensity(1.0));
    EXPECT_EQ(0, id1D->probabilityDensity(100.0));
    EXPECT_EQ("DistributionCosine", id1D->getName());

    std::vector<double> list1 = id1D->generateValueList(1, 0.0);
    EXPECT_EQ(id1D->getMean(), list1[0]);

    std::vector<double> list2 = id1D->generateValueList(2, 0.0);
    EXPECT_EQ(-M_PI, list2[0]);
    EXPECT_EQ(M_PI, list2[1]);

    delete id1D;
}

TEST_F(DistributionsTest, DistributionCosineConstructor)
{
    DistributionCosine* id1D = new DistributionCosine(1.0,1.0);
    EXPECT_EQ(1.0, id1D->getMean());
    EXPECT_EQ(1.0, id1D->getSigma());
    EXPECT_EQ(2.0/(2.0*M_PI), id1D->probabilityDensity(1.0));
    EXPECT_EQ(0, id1D->probabilityDensity(100.0));
    EXPECT_EQ("DistributionCosine", id1D->getName());

    std::vector<double> list1 = id1D->generateValueList(1, 0.0);
    EXPECT_EQ(id1D->getMean(), list1[0]);

    std::vector<double> list2 = id1D->generateValueList(2, 0.0);
    EXPECT_EQ(1-M_PI, list2[0]);
    EXPECT_EQ(1+M_PI, list2[1]);

    delete id1D;
}

TEST_F(DistributionsTest, DistributionCosineClone)
{
    DistributionCosine* id1D = new DistributionCosine(1.0,1.0);
    DistributionCosine* id1DClone = id1D->clone();
    EXPECT_EQ(1.0, id1DClone->getMean());
    EXPECT_EQ(1.0, id1DClone->getSigma());
    EXPECT_EQ(2.0/(2.0*M_PI), id1DClone->probabilityDensity(1.0));
    EXPECT_EQ(0, id1D->probabilityDensity(100.0));
    EXPECT_EQ("DistributionCosine", id1DClone->getName());

    std::vector<double> list1 = id1DClone->generateValueList(1, 0.0);
    EXPECT_EQ(id1DClone->getMean(), list1[0]);

    std::vector<double> list2 = id1DClone->generateValueList(2, 0.0);
    EXPECT_EQ(1-M_PI, list2[0]);
    EXPECT_EQ(1+M_PI, list2[1]);

    delete id1D;
    delete id1DClone;
}

#endif
