#include "ParticleLayout.h"
#include "InterferenceFunctionNone.h"
#include "InterferenceFunction1DLattice.h"
#include "BornAgainNamespace.h"

class ParticleLayoutTest : public :: testing :: Test {

protected:
    ParticleLayoutTest(){}
};

TEST_F(ParticleLayoutTest, ParticleLayoutInitial)
{
    ParticleLayout particleDecoration;

    EXPECT_EQ(BornAgain::ParticleLayoutType, particleDecoration.getName());
    EXPECT_EQ(size_t(0), particleDecoration.numberOfParticles());
    EXPECT_EQ(nullptr, particleDecoration.interferenceFunction());
}

TEST_F(ParticleLayoutTest, ParticleLayoutInitByValue)
{
    Particle particle;

    ParticleLayout particleDecoration(particle, 2.0);

    EXPECT_EQ(BornAgain::ParticleLayoutType, particleDecoration.getName());
    EXPECT_EQ(size_t(1), particleDecoration.numberOfParticles());
    EXPECT_EQ(nullptr, particleDecoration.interferenceFunction());


    const IAbstractParticle * p_particle = particleDecoration.particle(size_t(0));
    EXPECT_TRUE(nullptr!=p_particle);
    EXPECT_EQ(2.0, particleDecoration.abundanceOfParticle(size_t(0)));

    EXPECT_EQ(nullptr, particleDecoration.interferenceFunction());
}

TEST_F(ParticleLayoutTest, ParticleLayoutInitByRef)
{
    Particle particle;

    ParticleLayout particleDecoration(particle, -2.0);

    EXPECT_EQ(BornAgain::ParticleLayoutType, particleDecoration.getName());
    EXPECT_EQ(size_t(1), particleDecoration.numberOfParticles());
    EXPECT_EQ(nullptr, particleDecoration.interferenceFunction());


    const IAbstractParticle * p_particle = particleDecoration.particle(size_t(0));
    EXPECT_TRUE(nullptr!=p_particle);
    EXPECT_EQ(-2.0, particleDecoration.abundanceOfParticle(size_t(0)));
}

TEST_F(ParticleLayoutTest, ParticleLayoutAddParticle)
{
    ParticleLayout particleDecoration;

    Particle particle1;
    Particle particle2;
    Particle particle3;
    Particle particle4;

    RotationZ transform3(45.*Units::degree);
    RotationZ transform4(45.*Units::degree);

    particleDecoration.addParticle(particle1);
    particleDecoration.addParticle(particle2, 2.2);
    particleDecoration.addParticle(particle3, 1.0, kvector_t(0,0,0), transform3);
    particleDecoration.addParticle(particle4, -4.2, kvector_t(0,0,0), transform4);

    EXPECT_EQ(size_t(4), particleDecoration.numberOfParticles());

    const IAbstractParticle * p_particle1 = particleDecoration.particle(size_t(0));
    EXPECT_TRUE(nullptr!=p_particle1);
    EXPECT_EQ(1.0, particleDecoration.abundanceOfParticle(size_t(0)));

    const IAbstractParticle * p_particle2 = particleDecoration.particle(size_t(1));
    EXPECT_TRUE(nullptr!=p_particle2);
    EXPECT_EQ(2.2, particleDecoration.abundanceOfParticle(size_t(1)));

    const IAbstractParticle * p_particle3 = particleDecoration.particle(size_t(2));
    EXPECT_TRUE(nullptr!=p_particle3);
    EXPECT_EQ(1.0, particleDecoration.abundanceOfParticle(size_t(2)));

    const IAbstractParticle * p_particle4 = particleDecoration.particle(size_t(3));
    EXPECT_TRUE(nullptr!=p_particle4);
    EXPECT_EQ(-4.2, particleDecoration.abundanceOfParticle(size_t(3)));
}

TEST_F(ParticleLayoutTest, ParticleLayoutAbundanceFraction)
{
    ParticleLayout particleDecoration;

    Particle particle1;
    Particle particle2;
    Particle particle3;
    Particle particle4;

    RotationY transform3(45.*Units::degree);
    RotationZ transform4(45.*Units::degree);

    particleDecoration.addParticle(particle1);
    EXPECT_EQ(1.0, particleDecoration.abundanceOfParticle(size_t(0)));

    particleDecoration.addParticle(particle2, 2.0);
    EXPECT_EQ(2.0, particleDecoration.abundanceOfParticle(size_t(1)));

    particleDecoration.addParticle(particle3, 1.0, kvector_t(0,0,0), transform3);
    EXPECT_EQ(1.0, particleDecoration.abundanceOfParticle(size_t(2)));

    particleDecoration.addParticle(particle4, 4.0, kvector_t(0,0,0), transform4);
    EXPECT_EQ(4.0, particleDecoration.abundanceOfParticle(size_t(3)));
}

TEST_F(ParticleLayoutTest, ParticleLayoutClone)
{
    ParticleLayout particleDecoration;

    Particle particle1;
    Particle particle2;
    Particle particle3;
    Particle particle4;

    RotationY transform3(45.*Units::degree);
    RotationZ transform4(45.*Units::degree);

    particleDecoration.addParticle(particle1);
    particleDecoration.addParticle(particle2, 2.0);
    particleDecoration.addParticle(particle3, 1.0, kvector_t(0,0,0), transform3);
    particleDecoration.addParticle(particle4, 4.0, kvector_t(0,0,0), transform4);

    HomogeneousMaterial mat5("core", 0, 0);
    Particle particle5(mat5);
    particleDecoration.addParticle(particle5, 0.0);

    InterferenceFunctionNone iff_none;
    particleDecoration.setInterferenceFunction(iff_none);
    particleDecoration.setInterferenceFunction(iff_none);
    particleDecoration.setInterferenceFunction(iff_none);

    ParticleLayout * clone = particleDecoration.clone();

    EXPECT_EQ(BornAgain::ParticleLayoutType, clone->getName());

    const IAbstractParticle * p_particle1 = clone->particle(size_t(0));
    EXPECT_TRUE(nullptr!=p_particle1);
    EXPECT_EQ(1.0, particleDecoration.abundanceOfParticle(size_t(0)));

    const IAbstractParticle * p_particle2 = clone->particle(size_t(1));
    EXPECT_TRUE(nullptr!=p_particle2);
    EXPECT_EQ(2.0, particleDecoration.abundanceOfParticle(size_t(1)));

    const IAbstractParticle * p_particle3 = clone->particle(size_t(2));
    EXPECT_TRUE(nullptr!=p_particle3);
    EXPECT_EQ(1.0, particleDecoration.abundanceOfParticle(size_t(2)));

    const IAbstractParticle * p_particle4 = clone->particle(size_t(3));
    EXPECT_TRUE(nullptr!=p_particle4);
    EXPECT_EQ(4.0, particleDecoration.abundanceOfParticle(size_t(3)));

    const IAbstractParticle * p_particle5 = clone->particle(size_t(4));
    EXPECT_TRUE(nullptr!=p_particle5);
    EXPECT_EQ(0.0, particleDecoration.abundanceOfParticle(size_t(4)));

    EXPECT_TRUE(nullptr!=clone->interferenceFunction());
}

TEST_F(ParticleLayoutTest, ParticleLayoutInterferenceFunction)
{
    ParticleLayout particleDecoration;

    InterferenceFunctionNone iff_none;
    particleDecoration.setInterferenceFunction(iff_none);

    EXPECT_TRUE(nullptr!=particleDecoration.interferenceFunction());
}

TEST_F(ParticleLayoutTest, getChildren)
{
    ParticleLayout layout;
    std::vector<const INode*> children = layout.getChildren();
    EXPECT_EQ(children.size(), 0u);

    layout.addParticle(Particle());
    layout.setInterferenceFunction(InterferenceFunction1DLattice(1.0, 2.0));
    children = layout.getChildren();
    EXPECT_EQ(children.size(), 2u);
    EXPECT_EQ(children.at(0)->getName(), BornAgain::ParticleType);
    EXPECT_EQ(children.at(1)->getName(), BornAgain::InterferenceFunction1DLatticeType);


}
