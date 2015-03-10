#ifndef LATTICEBASISTEST_H
#define LATTICEBASISTEST_H

#include "LatticeBasis.h"
#include "Particle.h"
#include "Materials.h"
#include "Units.h"
#include "HomogeneousMaterial.h"
#include "ParticleInfo.h"
#include "FormFactorFullSphere.h"
#include <iostream>


class LatticeBasisTest : public ::testing::Test
{
protected:
    LatticeBasisTest(){}
    virtual ~LatticeBasisTest(){}
};

TEST_F(LatticeBasisTest, LatticeBasisDefaultConstructor)
{
    LatticeBasis *lb = new LatticeBasis();
    Particle particle;
    std::vector<kvector_t > positions;
    positions.push_back(kvector_t(0.0,0.0,0.0));
    EXPECT_EQ("LatticeBasis",lb->getName());
    EXPECT_EQ(0, lb->getAmbientMaterial());
    EXPECT_EQ(0, lb->getNbrParticles());

    delete lb;

}

TEST_F(LatticeBasisTest, LatticeBasisConstructorWithOneParameter)
{
    Particle particle;
    LatticeBasis *lb = new LatticeBasis(particle);
    std::vector<kvector_t > positions;
    positions.push_back(kvector_t(0.0,0.0,0.0));
    EXPECT_EQ("LatticeBasis",lb->getName());
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


TEST_F(LatticeBasisTest, LatticeBasisConstructorWithTwoParameter)
{
    Particle particle;
    std::vector<kvector_t > positions;
    positions.push_back(kvector_t(1.0,1.0,1.0));
    LatticeBasis *lb = new LatticeBasis(particle, positions);

    EXPECT_EQ("LatticeBasis",lb->getName());
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

TEST_F(LatticeBasisTest, LatticeBasisClone)
{
    LatticeBasis *lb = new LatticeBasis();
    Particle particle;
    std::vector<kvector_t > positions;
    positions.push_back(kvector_t(1.0,1.0,1.0));
    HomogeneousMaterial material("Air",0.0,0.0);
    lb->addParticle(particle, positions);
    lb->setAmbientMaterial(material);
    LatticeBasis *lbClone = lb->clone();

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
