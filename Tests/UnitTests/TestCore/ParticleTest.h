#ifndef PARTICLETEST_H
#define PARTICLETEST_H

#include "Particle.h"
#include "Units.h"
#include "HomogeneousMaterial.h"
#include "ParticleInfo.h"
#include "FormFactorFullSphere.h"
#include <iostream>

class ParticleTest : public ::testing::Test
{
protected:
    ParticleTest(){}
    virtual ~ParticleTest(){}
};


TEST_F(ParticleTest, ParticleInitialState)
{
    Particle particle;
    EXPECT_EQ(NULL, particle.getMaterial());
    EXPECT_EQ(complex_t(0,0), particle.getRefractiveIndex());
    EXPECT_EQ(NULL, particle.getSimpleFormFactor());
    EXPECT_FALSE(particle.hasDistributedFormFactor());
    EXPECT_EQ(NULL, particle.createFormFactor(1.0));
    ASSERT_THROW(particle.createDistributedParticles(0,0).size(), NullPointerException);
    EXPECT_EQ("Particle", particle.getName());

    Particle *particle2 = particle.clone();
    EXPECT_EQ(NULL, particle2->getMaterial());
    EXPECT_EQ(complex_t(0,0), particle2->getRefractiveIndex());
    EXPECT_EQ(NULL, particle2->getSimpleFormFactor());
    EXPECT_FALSE(particle2->hasDistributedFormFactor());
    EXPECT_EQ(NULL, particle2->createFormFactor(1.0));
    ASSERT_THROW(particle2->createDistributedParticles(0,0).size(), NullPointerException);
    EXPECT_EQ("Particle", particle2->getName());
    delete particle2;

    ASSERT_THROW(particle.cloneInvertB(), NullPointerException);
}


TEST_F(ParticleTest, ParticleConstructors)
{
    const IMaterial *mat = MaterialManager::getHomogeneousMaterial("Air",0,0);

    Particle *p1 = new Particle(mat);
    EXPECT_EQ("Air", p1->getMaterial()->getName());
    EXPECT_EQ(complex_t(1,0), p1->getRefractiveIndex());
    EXPECT_EQ(NULL, p1->getSimpleFormFactor());
    EXPECT_FALSE(p1->hasDistributedFormFactor());
    EXPECT_EQ(NULL, p1->createFormFactor(1.0));
    ASSERT_THROW(p1->createDistributedParticles(0,0).size(), NullPointerException);
    delete p1;

    FormFactorFullSphere sphere(1.0);
    Particle *p2 = new Particle(mat, sphere);
    EXPECT_EQ("FormFactorFullSphere", p2->getSimpleFormFactor()->getName());
    EXPECT_EQ(1, p2->getSimpleFormFactor()->getRadius());
    EXPECT_FALSE(p2->hasDistributedFormFactor());
    EXPECT_TRUE(dynamic_cast<FormFactorDecoratorMaterial *>(
            p2->createFormFactor(1.0)));
    EXPECT_EQ(complex_t(1,0),
              dynamic_cast<FormFactorDecoratorMaterial *>(
                      p2->createFormFactor(1.0))->getAmbientRefractiveIndex());
    delete p2;

    FormFactorFullSphere *sphere3 = new FormFactorFullSphere(1.0);
    sphere3->setName("sphere3");
    Particle *p3 = new Particle(mat, sphere3);
    EXPECT_EQ(sphere3, p3->getSimpleFormFactor());

    Particle *p4 = p3->clone();
    EXPECT_EQ("sphere3", p4->getSimpleFormFactor()->getName());

    delete p3;
    delete p4;
}


#endif // PARTICLETEST_H
