#ifndef PARTICLECOMPOSITIONTEST_H
#define PARTICLECOMPOSITIONTEST_H

#include "ParticleComposition.h"
#include "Particle.h"
#include "Materials.h"
#include "Units.h"
#include "HomogeneousMaterial.h"
#include "ParticleInfo.h"
#include "FormFactorFullSphere.h"
#include <iostream>


class ParticleCompositionTest : public ::testing::Test
{
protected:
    ParticleCompositionTest(){}
    virtual ~ParticleCompositionTest(){}
};

TEST_F(ParticleCompositionTest, ParticleCompositionDefaultConstructor)
{
    ParticleComposition *lb = new ParticleComposition();
    Particle particle;
    std::vector<kvector_t > positions;
    positions.push_back(kvector_t(0.0,0.0,0.0));
    EXPECT_EQ("ParticleComposition",lb->getName());
    EXPECT_EQ(0, lb->getAmbientMaterial());
    EXPECT_EQ(0, lb->getNbrParticles());

    delete lb;

}

TEST_F(ParticleCompositionTest, ParticleCompositionConstructorWithOneParameter)
{
    Particle particle;
    ParticleComposition *lb = new ParticleComposition(particle);
    std::vector<kvector_t > positions;
    positions.push_back(kvector_t(0.0,0.0,0.0));
    EXPECT_EQ("ParticleComposition",lb->getName());
    lb->addParticle(particle, positions);
    EXPECT_EQ(particle.getMaterial(),lb->getParticle(0)->getAmbientMaterial());
    EXPECT_EQ(particle.getName(),lb->getParticle(0)->getName());
    EXPECT_EQ(particle.getTransform3D(),lb->getParticle(0)->getTransform3D());
    EXPECT_EQ(particle.getMaterial(),lb->getParticle(1)->getAmbientMaterial());
    EXPECT_EQ(particle.getName(),lb->getParticle(1)->getName());
    EXPECT_EQ(particle.getTransform3D(),lb->getParticle(1)->getTransform3D());
    EXPECT_EQ(positions, lb->getParticlePositions(0));
    EXPECT_EQ(positions, lb->getParticlePositions(1));

    HomogeneousMaterial material("Air",0.0,0.0);
    lb->setAmbientMaterial(material);
    EXPECT_EQ("Air", lb->getAmbientMaterial()->getName());
    EXPECT_EQ(1.0, lb->getAmbientMaterial()->getRefractiveIndex());

    delete lb;
}


TEST_F(ParticleCompositionTest, ParticleCompositionConstructorWithTwoParameter)
{
    Particle particle;
    std::vector<kvector_t > positions;
    positions.push_back(kvector_t(1.0,1.0,1.0));
    ParticleComposition *lb = new ParticleComposition(particle, positions);

    EXPECT_EQ("ParticleComposition",lb->getName());
    lb->addParticle(particle, positions);
    EXPECT_EQ(particle.getMaterial(),lb->getParticle(0)->getAmbientMaterial());
    EXPECT_EQ(particle.getName(),lb->getParticle(0)->getName());
    EXPECT_EQ(particle.getTransform3D(),lb->getParticle(0)->getTransform3D());
    EXPECT_EQ(particle.getMaterial(),lb->getParticle(1)->getAmbientMaterial());
    EXPECT_EQ(particle.getName(),lb->getParticle(1)->getName());
    EXPECT_EQ(particle.getTransform3D(),lb->getParticle(1)->getTransform3D());
    EXPECT_EQ(positions, lb->getParticlePositions(0));
    EXPECT_EQ(positions, lb->getParticlePositions(1));

    HomogeneousMaterial material("Air",0.0,0.0);
    lb->setAmbientMaterial(material);
    EXPECT_EQ("Air", lb->getAmbientMaterial()->getName());
    EXPECT_EQ(1.0, lb->getAmbientMaterial()->getRefractiveIndex());

    delete lb;
}

TEST_F(ParticleCompositionTest, ParticleCompositionClone)
{
    ParticleComposition *lb = new ParticleComposition();
    Particle particle;
    std::vector<kvector_t > positions;
    positions.push_back(kvector_t(1.0,1.0,1.0));
    HomogeneousMaterial material("Air",0.0,0.0);
    lb->addParticle(particle, positions);
    lb->setAmbientMaterial(material);
    ParticleComposition *lbClone = lb->clone();

    EXPECT_EQ(lbClone->getName(),lb->getName());

    EXPECT_EQ(lbClone->getParticle(0)->getAmbientMaterial()->getRefractiveIndex(),lb->getParticle(0)->getAmbientMaterial()->getRefractiveIndex());
    EXPECT_EQ(lbClone->getParticle(0)->getName(), lb->getParticle(0)->getName());
    EXPECT_EQ(lbClone->getParticle(0)->getTransform3D(),lb->getParticle(0)->getTransform3D());
    EXPECT_EQ(positions, lb->getParticlePositions(0));


    EXPECT_EQ("Air", lb->getAmbientMaterial()->getName());
    EXPECT_EQ(1.0, lb->getAmbientMaterial()->getRefractiveIndex());

    delete lb;
    delete lbClone;
}


#endif
