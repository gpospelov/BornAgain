#include "Particle.h"
#include "ParticleDistribution.h"
#include "HomogeneousMaterial.h"
#include "Distributions.h"
#include "BornAgainNamespace.h"

class ParticleDistributionTest : public ::testing::Test
{
protected:
    ParticleDistributionTest(){}
};

TEST_F(ParticleDistributionTest, getChildren)
{
    Particle particle(HomogeneousMaterial("Air",0.0, 0.0), FormFactorFullSphere(1.0));
    ParameterDistribution parameter("name", DistributionGate(1.0, 2.0), 5, 0.0, 1.0);
    ParticleDistribution distr(particle, parameter);

    std::vector<const INode*> children = distr.getChildren();

    EXPECT_EQ(children.size(), 2u);
    EXPECT_EQ(children.at(0)->getName(), BornAgain::ParticleType);
}

