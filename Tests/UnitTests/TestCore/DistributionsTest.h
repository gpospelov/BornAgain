#ifndef DISTRIBUTIONSTEST_H
#define DISTRIBUTIONSTEST_H

#include "Units.h"
#include "Distributions.h"
#include "ParameterSample.h"
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
    EXPECT_EQ(1.0, id1D->probabilityDensity(1.0));
    EXPECT_EQ(0, id1D->probabilityDensity(3.0));
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
    // Throw error when m_min > m_max:
    EXPECT_THROW(DistributionGate(1.1, 1.0), ClassInitializationException);

    // When m_min == m_max, only one sample is generated (the mean):
    DistributionGate distr1(1.0, 1.0);
    std::vector<double> list1 = distr1.generateValueList(5, 0.0);
    EXPECT_EQ(size_t(1), list1.size());
    EXPECT_EQ(1.0, list1[0]);

    // Test distribution with m_min < m_max:
    DistributionGate distr2(1.0, 2.0);
    EXPECT_EQ(1.5, distr2.getMean());
    EXPECT_EQ(1.0, distr2.getMin());
    EXPECT_EQ(2.0, distr2.getMax());
    EXPECT_EQ(1.0, distr2.probabilityDensity(1));
    EXPECT_EQ(0, distr2.probabilityDensity(3));
    EXPECT_EQ("DistributionGate", distr2.getName());

    std::vector<double> list2 = distr2.generateValueList(1, 0.0);
    EXPECT_EQ(list2.size(), size_t(1));
    EXPECT_EQ(distr2.getMean(), list2[0]);

    list2 = distr2.generateValueList(2, 0.0);
    EXPECT_EQ(list2.size(), size_t(2));
    EXPECT_EQ(1.0, list2[0]);
    EXPECT_EQ(2.0, list2[1]);

    std::vector<ParameterSample> samples = distr2.generateSamples(3);
    EXPECT_EQ(samples.size(), size_t(3));
    EXPECT_EQ(samples[0].value, 1.0);
    EXPECT_EQ(samples[0].weight, 1./3.);
    EXPECT_EQ(samples[1].value, 1.5);
    EXPECT_EQ(samples[1].weight, 1./3.);
    EXPECT_EQ(samples[2].value, 2.0);
    EXPECT_EQ(samples[2].weight, 1./3.);
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

TEST_F(DistributionsTest, DistributionLorentzDefaultConstructor)
{
    DistributionLorentz * distr = new DistributionLorentz();
    EXPECT_EQ(0.0, distr->getMean());
    EXPECT_EQ(1.0, distr->getHWHM());
    EXPECT_EQ("DistributionLorentz", distr->getName());
    EXPECT_EQ(1/(2*Units::PI), distr->probabilityDensity(1.0));

    std::vector<double> list1 = distr->generateValueList(1, 0.0);
    EXPECT_EQ(distr->getMean(), list1[0]);

    std::vector<double> list2 = distr->generateValueList(2, 0.0);
    EXPECT_EQ(-2, list2[0]);
    EXPECT_EQ(2, list2[1]);
    delete distr;
}

TEST_F(DistributionsTest, DistributionLorentzConstructor)
{
    // When HWHM == 0.0, only one sample is generated (the mean):
    DistributionLorentz distr1(1.0, 0.0);
    std::vector<double> list1 = distr1.generateValueList(5, 0.0);
    EXPECT_EQ(size_t(1), list1.size());
    EXPECT_EQ(1.0, list1[0]);

    // Test distribution with HWHM > 0.0:
    DistributionLorentz distr2(1.0, 1.0);
    EXPECT_EQ(1.0, distr2.getMean());
    EXPECT_EQ(1.0, distr2.getHWHM());
    EXPECT_EQ("DistributionLorentz", distr2.getName());
    EXPECT_EQ(1.0/Units::PI, distr2.probabilityDensity(1.0));

    std::vector<double> list2 = distr2.generateValueList(1, 0.0);
    EXPECT_EQ(distr2.getMean(), list2[0]);

    std::vector<double> list3 = distr2.generateValueList(2, 0.0);
    EXPECT_EQ(-1, list3[0]);
    EXPECT_EQ(3, list3[1]);
}

TEST_F(DistributionsTest, DistributionLorentzParameters)
{
    DistributionLorentz lorentz(2.0, 3.0);
    EXPECT_EQ(lorentz.getMean(), lorentz.getParameterPool()->getParameter("mean").getValue());
    EXPECT_EQ(lorentz.getHWHM(), lorentz.getParameterPool()->getParameter("hwhm").getValue());
}


TEST_F(DistributionsTest, DistributionLorentzClone)
{
    DistributionLorentz * id1D = new DistributionLorentz(1.0, 2.0);
    DistributionLorentz* id1DClone = id1D->clone();
    EXPECT_EQ(1.0, id1DClone->getMean());
    EXPECT_EQ(2.0, id1DClone->getHWHM());
    EXPECT_EQ("DistributionLorentz", id1DClone->getName());

    delete id1D;
    delete id1DClone;
}

TEST_F(DistributionsTest, DistributionLorentzSamples)
{
    DistributionLorentz distr(1.0, 0.1);

    const int nbr_samples(3);

    // with sigma factor
    const double sigma_factor(2.0);
    std::vector<ParameterSample> samples = distr.generateSamples(nbr_samples, sigma_factor);

    EXPECT_EQ(samples.size(), size_t(nbr_samples));
    EXPECT_EQ(samples[0].value, 1.0 - sigma_factor*0.1);
    EXPECT_EQ(samples[1].value, 1.0);
    EXPECT_EQ(samples[2].value, 1.0 + sigma_factor*0.1);
    double d1 = distr.probabilityDensity(samples[0].value);
    double d2 = distr.probabilityDensity(samples[1].value);
    double d3 = distr.probabilityDensity(samples[2].value);
    EXPECT_EQ(samples[0].weight, d1/(d1+d2+d3));
    EXPECT_EQ(samples[1].weight, d2/(d1+d2+d3));
    EXPECT_EQ(samples[2].weight, d3/(d1+d2+d3));

    // with AttLimits
    samples = distr.generateSamples(nbr_samples, sigma_factor, AttLimits::lowerLimited(0.99));
    EXPECT_EQ(samples[0].value, 0.99);
    EXPECT_EQ(samples[1].value, samples[0].value + (samples[2].value - samples[0].value)/2.0);
    EXPECT_EQ(samples[2].value, 1.0 + sigma_factor*0.1);

    // with xmin, xmax
    samples = distr.generateSamples(nbr_samples, 0.8, 1.2);
    EXPECT_EQ(samples[0].value, 0.8);
    EXPECT_EQ(samples[1].value, 1.0);
    EXPECT_EQ(samples[2].value, 1.2);

}

// -------------------------------------------------------------------------- //

TEST_F(DistributionsTest, DistributionGaussianDefaultConstructor)
{
    DistributionGaussian* id1D = new DistributionGaussian();
    EXPECT_EQ(0.0, id1D->getMean());
    EXPECT_EQ(1.0, id1D->getStdDev());
    EXPECT_EQ(std::exp(-1.0/2.0)/std::sqrt(2.0*Units::PI), id1D->probabilityDensity(1.0));
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
    // When std_dev == 0.0, only one sample is generated (the mean):
    DistributionGaussian distr1(1.0, 0.0);
    std::vector<double> list1 = distr1.generateValueList(5, 0.0);
    EXPECT_EQ(size_t(1), list1.size());
    EXPECT_EQ(1.0, list1[0]);

    // Test distribution with std_dev > 0.0:
    DistributionGaussian distr2(1.0, 1.0);
    EXPECT_EQ(1.0, distr2.getMean());
    EXPECT_EQ(1.0, distr2.getStdDev());
    EXPECT_EQ(1/std::sqrt(2.0*Units::PI), distr2.probabilityDensity(1.0));
    EXPECT_EQ("DistributionGaussian", distr2.getName());

    std::vector<double> list2 = distr2.generateValueList(1, 0.0);
    EXPECT_EQ(distr2.getMean(), list2[0]);

    std::vector<double> list3 = distr2.generateValueList(2, 0.0);
    EXPECT_EQ(-1, list3[0]);
    EXPECT_EQ(3, list3[1]);
}

TEST_F(DistributionsTest, DistributionGaussianParameters)
{
    DistributionGaussian gaussian(2.0, 3.0);
    EXPECT_EQ(gaussian.getMean(), gaussian.getParameterPool()->getParameter("mean").getValue());
    EXPECT_EQ(gaussian.getStdDev(), gaussian.getParameterPool()->getParameter("std_dev").getValue());
}

TEST_F(DistributionsTest, DistributionGaussianClone)
{
    DistributionGaussian* id1D = new DistributionGaussian(1.0, 1.0);
    DistributionGaussian* id1DClone = id1D->clone();
    EXPECT_EQ(1.0, id1DClone->getMean());
    EXPECT_EQ(1.0, id1DClone->getStdDev());
    EXPECT_EQ(1/std::sqrt(2.0*Units::PI), id1DClone->probabilityDensity(1.0));
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
    // When scale_par == 0.0, only one sample is generated (the mean):
    DistributionLogNormal distr1(1.0, 0.0);
    std::vector<double> list1 = distr1.generateValueList(5, 0.0);
    EXPECT_EQ(size_t(1), list1.size());
    EXPECT_EQ(1.0, list1[0]);

    // Test distribution with scale_par > 0.0:
    DistributionLogNormal distr2(1.0);
    EXPECT_EQ(1.0, distr2.getMedian());
    EXPECT_EQ(1.0, distr2.getScalePar());
    EXPECT_EQ(std::exp(0.5), distr2.getMean());
    EXPECT_EQ(1.0/std::sqrt(2.0*Units::PI), distr2.probabilityDensity(1.0));
    EXPECT_EQ("DistributionLogNormal", distr2.getName());

    std::vector<double> list2 = distr2.generateValueList(1, 0.0);
    EXPECT_EQ(distr2.getMedian(), list2[0]);

    std::vector<double> list3 = distr2.generateValueList(2, 0.0);
    EXPECT_EQ(std::exp(-2), list3[0]);
    EXPECT_EQ(std::exp(-2) + std::exp(2) - std::exp(-2), list3[1]);
}

TEST_F(DistributionsTest, DistributionLogNormalConstructorWithTwoParameter)
{
    DistributionLogNormal* id1D = new DistributionLogNormal(1.0,1.0);
    EXPECT_EQ(1.0, id1D->getMedian());
    EXPECT_EQ(1.0, id1D->getScalePar());
    EXPECT_EQ(std::exp(0.5), id1D->getMean());
    EXPECT_EQ(1.0/std::sqrt(2.0*Units::PI), id1D->probabilityDensity(1.0));
    EXPECT_EQ("DistributionLogNormal", id1D->getName());

    std::vector<double> list1 = id1D->generateValueList(1, 0.0);
    EXPECT_EQ(id1D->getMedian(), list1[0]);

    std::vector<double> list2 = id1D->generateValueList(2, 0.0);
    EXPECT_EQ(std::exp(-2), list2[0]);
    EXPECT_EQ(std::exp(-2) + std::exp(2) - std::exp(-2), list2[1]);

    delete id1D;
}

TEST_F(DistributionsTest, DistributionLogNormalParameters)
{
    DistributionLogNormal logNormal(2.0, 3.0);
    EXPECT_EQ(logNormal.getMedian(), logNormal.getParameterPool()->getParameter("median").getValue());
    EXPECT_EQ(logNormal.getScalePar(), logNormal.getParameterPool()->getParameter("scale_parameter").getValue());
}

TEST_F(DistributionsTest, DistributionLogNormalClone)
{
    DistributionLogNormal* id1D = new DistributionLogNormal(1.0, 1.0);
    DistributionLogNormal* id1DClone = id1D->clone();
    EXPECT_EQ(1.0, id1D->getMedian());
    EXPECT_EQ(1.0, id1D->getScalePar());
    EXPECT_EQ(std::exp(0.5), id1D->getMean());
    EXPECT_EQ(1/std::sqrt(2.0*Units::PI), id1D->probabilityDensity(1.0));
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
    EXPECT_DOUBLE_EQ((1.0+std::cos(1.0))/(2.0*Units::PI), id1D->probabilityDensity(1.0));
    EXPECT_EQ(0, id1D->probabilityDensity(100.0));
    EXPECT_EQ("DistributionCosine", id1D->getName());

    std::vector<double> list1 = id1D->generateValueList(1, 0.0);
    EXPECT_EQ(id1D->getMean(), list1[0]);

    std::vector<double> list2 = id1D->generateValueList(2, 0.0);
    EXPECT_EQ(-Units::PI, list2[0]);
    EXPECT_EQ(Units::PI, list2[1]);

    delete id1D;
}

TEST_F(DistributionsTest, DistributionCosineConstructor)
{
    // When sigma == 0.0, only one sample is generated (the mean):
    DistributionCosine distr1(1.0, 0.0);
    std::vector<double> list1 = distr1.generateValueList(5, 0.0);
    EXPECT_EQ(size_t(1), list1.size());
    EXPECT_EQ(1.0, list1[0]);

    // Test distribution with sigma > 0.0:
    DistributionCosine distr2(1.0,1.0);
    EXPECT_EQ(1.0, distr2.getMean());
    EXPECT_EQ(1.0, distr2.getSigma());
    EXPECT_EQ(2.0/(2.0*Units::PI), distr2.probabilityDensity(1.0));
    EXPECT_EQ(0, distr2.probabilityDensity(100.0));
    EXPECT_EQ("DistributionCosine", distr2.getName());

    std::vector<double> list2 = distr2.generateValueList(1, 0.0);
    EXPECT_EQ(distr2.getMean(), list2[0]);

    std::vector<double> list3 = distr2.generateValueList(2, 0.0);
    EXPECT_EQ(1-Units::PI, list3[0]);
    EXPECT_EQ(1+Units::PI, list3[1]);
}

TEST_F(DistributionsTest, DistributionCosineParameters)
{
    DistributionCosine cosine(2.0, 3.0);
    EXPECT_EQ(cosine.getMean(), cosine.getParameterPool()->getParameter("mean").getValue());
    EXPECT_EQ(cosine.getSigma(), cosine.getParameterPool()->getParameter("sigma").getValue());
}

TEST_F(DistributionsTest, DistributionCosineClone)
{
    DistributionCosine* id1D = new DistributionCosine(1.0,1.0);
    DistributionCosine* id1DClone = id1D->clone();
    EXPECT_EQ(1.0, id1DClone->getMean());
    EXPECT_EQ(1.0, id1DClone->getSigma());
    EXPECT_EQ(2.0/(2.0*Units::PI), id1DClone->probabilityDensity(1.0));
    EXPECT_EQ(0, id1D->probabilityDensity(100.0));
    EXPECT_EQ("DistributionCosine", id1DClone->getName());

    std::vector<double> list1 = id1DClone->generateValueList(1, 0.0);
    EXPECT_EQ(id1DClone->getMean(), list1[0]);

    std::vector<double> list2 = id1DClone->generateValueList(2, 0.0);
    EXPECT_EQ(1-Units::PI, list2[0]);
    EXPECT_EQ(1+Units::PI, list2[1]);

    delete id1D;
    delete id1DClone;
}

#endif
