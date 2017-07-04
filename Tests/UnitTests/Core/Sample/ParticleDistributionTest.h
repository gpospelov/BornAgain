#include "Particle.h"
#include "ParticleDistribution.h"
#include "HomogeneousMaterial.h"
#include "Distributions.h"
#include "BornAgainNamespace.h"
#include "ParameterUtils.h"
#include "Units.h"

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

TEST_F(ParticleDistributionTest, mainParameterUnits)
{
    HomogeneousMaterial mat("Air",0.0, 0.0);
    DistributionGate gate(1.0, 2.0);

    ParameterDistribution par("/Particle/FullSphere/Radius", gate, 5);
    ParticleDistribution distr(Particle(mat, FormFactorFullSphere(1.0)), par);
    EXPECT_EQ(ParameterUtils::mainParUnits(distr), BornAgain::UnitsNm);

    par = ParameterDistribution("/Particle/Cone/Alpha", gate, 5);
    ParticleDistribution distr2(Particle(mat, FormFactorCone(10.0, 20.0, 70.0*Units::deg)), par);
    EXPECT_EQ(ParameterUtils::mainParUnits(distr2), BornAgain::UnitsRad);

}
