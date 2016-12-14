#include "FormFactorFullSphere.h"
#include "HomogeneousMaterial.h"
#include "MathConstants.h"
#include "Particle.h"
#include "ParticleComposition.h"
#include "BornAgainNamespace.h"
#include <iostream>

class ParticleCompositionTest : public ::testing::Test
{
protected:
    ParticleCompositionTest(){}
    virtual ~ParticleCompositionTest(){}
};

TEST_F(ParticleCompositionTest, ParticleCompositionDefaultConstructor)
{
    std::unique_ptr<ParticleComposition> composition(new ParticleComposition());
    std::vector<kvector_t> positions;
    positions.push_back(kvector_t(0.0, 0.0, 0.0));
    EXPECT_EQ(BornAgain::ParticleCompositionType, composition->getName());
    EXPECT_EQ(nullptr, composition->getAmbientMaterial());
    EXPECT_EQ(0u, composition->getNbrParticles());
}

TEST_F(ParticleCompositionTest, ParticleCompositionConstructorWithOneParameter)
{
    kvector_t position0(0.0, 0.0, 0.0);
    kvector_t position1(4.0, 5.0, 6.0);

    Particle particle;
    std::unique_ptr<ParticleComposition> composition(new ParticleComposition(particle));

    EXPECT_EQ(BornAgain::ParticleCompositionType, composition->getName());
    composition->addParticle(particle, position1);

    EXPECT_EQ(particle.getMaterial(), composition->getParticle(0)->getAmbientMaterial());
    EXPECT_EQ(particle.getName(), composition->getParticle(0)->getName());
    EXPECT_EQ(particle.getRotation(), composition->getParticle(0)->getRotation());
    EXPECT_EQ(particle.getMaterial(), composition->getParticle(1)->getAmbientMaterial());
    EXPECT_EQ(particle.getName(), composition->getParticle(1)->getName());
    EXPECT_EQ(particle.getRotation(), composition->getParticle(1)->getRotation());
    EXPECT_EQ(position0, composition->getParticlePosition(0));
    EXPECT_EQ(position1, composition->getParticlePosition(1));

    HomogeneousMaterial material("Air", 0.0, 0.0);
    composition->setAmbientMaterial(material);
    EXPECT_EQ("Air", composition->getAmbientMaterial()->getName());
    EXPECT_EQ(1.0, composition->getAmbientMaterial()->getRefractiveIndex());
}

TEST_F(ParticleCompositionTest, ParticleCompositionConstructorWithTwoParameter)
{
    Particle particle;
    kvector_t position = kvector_t(1.0, 1.0, 1.0);
    std::unique_ptr<ParticleComposition> composition(new ParticleComposition(particle, position));

    EXPECT_EQ(BornAgain::ParticleCompositionType, composition->getName());
    composition->addParticle(particle, position);
    EXPECT_EQ(particle.getMaterial(), composition->getParticle(0)->getAmbientMaterial());
    EXPECT_EQ(particle.getName(), composition->getParticle(0)->getName());
    EXPECT_EQ(particle.getRotation(), composition->getParticle(0)->getRotation());
    EXPECT_EQ(particle.getMaterial(), composition->getParticle(1)->getAmbientMaterial());
    EXPECT_EQ(particle.getName(), composition->getParticle(1)->getName());
    EXPECT_EQ(particle.getRotation(), composition->getParticle(1)->getRotation());
    EXPECT_EQ(position, composition->getParticlePosition(0));
    EXPECT_EQ(position, composition->getParticlePosition(1));

    HomogeneousMaterial material("Air", 0.0, 0.0);
    composition->setAmbientMaterial(material);
    EXPECT_EQ("Air", composition->getAmbientMaterial()->getName());
    EXPECT_EQ(1.0, composition->getAmbientMaterial()->getRefractiveIndex());
}

TEST_F(ParticleCompositionTest, ParticleCompositionClone)
{
    ParticleComposition composition;
    Particle particle;
    kvector_t position = kvector_t(1.0, 1.0, 1.0);
    HomogeneousMaterial material("Air", 0.0, 0.0);
    composition.addParticle(particle, position);
    composition.setAmbientMaterial(material);

    std::unique_ptr<ParticleComposition> clone(composition.clone());

    EXPECT_EQ(clone->getName(), composition.getName());

    EXPECT_EQ(clone->getParticle(0)->getAmbientMaterial()->getRefractiveIndex(),
              composition.getParticle(0)->getAmbientMaterial()->getRefractiveIndex());
    EXPECT_EQ(clone->getParticle(0)->getName(), composition.getParticle(0)->getName());
    EXPECT_EQ(clone->getParticle(0)->getRotation(), nullptr);
    EXPECT_EQ(position, clone->getParticlePosition(0));

    EXPECT_EQ("Air", clone->getAmbientMaterial()->getName());
    EXPECT_EQ(1.0, clone->getAmbientMaterial()->getRefractiveIndex());
}

TEST_F(ParticleCompositionTest, getChildren)
{
    HomogeneousMaterial material("Air", 0.0, 0.0);

    ParticleComposition composition;
    composition.addParticle(Particle(material, FormFactorFullSphere(1.0)));
    composition.addParticle(Particle(material, FormFactorFullSphere(1.0)));
    composition.setRotation(RotationY(45.));

    std::vector<const INode*> children = composition.getChildren();
    EXPECT_EQ(children.size(), 3u);
    EXPECT_EQ(children.at(0)->getName(), BornAgain::YRotationType);
    EXPECT_EQ(children.at(1)->getName(), BornAgain::ParticleType);
    EXPECT_EQ(children.at(2)->getName(), BornAgain::ParticleType);
}
