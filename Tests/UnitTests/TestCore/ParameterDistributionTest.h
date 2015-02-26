#ifndef PARAMETERDISTRIBUTIONTEST_H
#define PARAMETERDISTRIBUTIONTEST_H

#include "ParameterDistribution.h"
#include "Distributions.h"

class ParameterDistributionTest : public ::testing::Test
{
protected:
    ParameterDistributionTest(){}
    virtual ~ParameterDistributionTest(){}
};


TEST_F(ParameterDistributionTest, InitialState)
{
    DistributionGate gate(1.0, 2.0);
    std::string par_name("name");
    int nbr_samples(5);
    double sigma_factor(2.0);
    ParameterDistribution par(par_name, gate, nbr_samples, sigma_factor);

    EXPECT_EQ(par.getMainParameterName(), par_name);
    EXPECT_EQ(par.getNbrSamples(), nbr_samples);
    EXPECT_EQ(par.getSigmaFactor(), sigma_factor);

    const DistributionGate *gate2 = dynamic_cast<const DistributionGate *>(par.getDistribution());
    EXPECT_FALSE(gate2 == 0);
    EXPECT_EQ(gate2->getMin(), gate.getMin());
    EXPECT_EQ(gate2->getMax(), gate.getMax());
    EXPECT_EQ(size_t(0), par.getLinkedParameterNames().size());

    par.linkParameter("aaa").linkParameter("bbb");
    std::vector<std::string> linked = par.getLinkedParameterNames();
    EXPECT_EQ(linked[0], std::string("aaa"));
    EXPECT_EQ(linked[1], std::string("bbb"));
}

TEST_F(ParameterDistributionTest, AssignmentOperator)
{
    DistributionLogNormal lognormal(1.0, 2.0);
    std::string par_name("name");
    int nbr_samples(2);
    double sigma_factor(5.0);
    ParameterDistribution par(par_name, lognormal, nbr_samples, sigma_factor);
    par.linkParameter("aaa").linkParameter("bbb");

    ParameterDistribution par2 = par;

    EXPECT_EQ(par2.getMainParameterName(), par.getMainParameterName());
    EXPECT_EQ(par2.getNbrSamples(), par.getNbrSamples());
    EXPECT_EQ(par2.getSigmaFactor(), par.getSigmaFactor());
    EXPECT_EQ(dynamic_cast<const DistributionLogNormal *>(par2.getDistribution())->getMean(), lognormal.getMean());
    EXPECT_EQ(dynamic_cast<const DistributionLogNormal *>(par2.getDistribution())->getMedian(), lognormal.getMedian());
    EXPECT_EQ(par2.getLinkedParameterNames()[0], par.getLinkedParameterNames()[0]);
    EXPECT_EQ(par2.getLinkedParameterNames()[1], par.getLinkedParameterNames()[1]);
}

TEST_F(ParameterDistributionTest, CopyConstructor)
{
    DistributionLorentz lorents(1.0, 2.0);
    std::string par_name("name");
    int nbr_samples(2);
    double sigma_factor(5.0);
    ParameterDistribution par(par_name, lorents, nbr_samples, sigma_factor);
    par.linkParameter("aaa").linkParameter("bbb");

    ParameterDistribution par2(par);

    EXPECT_EQ(par2.getMainParameterName(), par.getMainParameterName());
    EXPECT_EQ(par2.getNbrSamples(), par.getNbrSamples());
    EXPECT_EQ(par2.getSigmaFactor(), par.getSigmaFactor());
    EXPECT_EQ(dynamic_cast<const DistributionLorentz *>(par2.getDistribution())->getMean(), lorents.getMean());
    EXPECT_EQ(dynamic_cast<const DistributionLorentz *>(par2.getDistribution())->getHWHM(), lorents.getHWHM());
    EXPECT_EQ(par2.getLinkedParameterNames()[0], par.getLinkedParameterNames()[0]);
    EXPECT_EQ(par2.getLinkedParameterNames()[1], par.getLinkedParameterNames()[1]);
}


#endif
