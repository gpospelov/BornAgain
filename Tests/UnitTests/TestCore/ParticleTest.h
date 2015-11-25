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


TEST_F(ParticleTest, InitialState)
{
    Particle particle;
    EXPECT_EQ(NULL, particle.getMaterial());
    EXPECT_EQ(complex_t(0,0), particle.getRefractiveIndex());
    EXPECT_EQ(NULL, particle.getFormFactor());
    EXPECT_EQ(NULL, particle.createFormFactor(1.0));
    EXPECT_EQ("Particle", particle.getName());
}

TEST_F(ParticleTest, Clone)
{
    Particle particle;
    Particle *particle2 = particle.clone();
    EXPECT_EQ(NULL, particle2->getMaterial());
    EXPECT_EQ(complex_t(0,0), particle2->getRefractiveIndex());
    EXPECT_EQ(NULL, particle2->getFormFactor());
    EXPECT_EQ(NULL, particle2->createFormFactor(1.0));
    EXPECT_EQ("Particle", particle2->getName());
    delete particle2;
}

TEST_F(ParticleTest, CloneInvertB)
{
    Particle particle;
    Particle *particle2 = particle.cloneInvertB();
    EXPECT_EQ(NULL, particle2->getMaterial());
    EXPECT_EQ(complex_t(0,0), particle2->getRefractiveIndex());
    EXPECT_EQ(NULL, particle2->getFormFactor());
    EXPECT_EQ(NULL, particle2->createFormFactor(1.0));
    EXPECT_EQ("Particle_inv", particle2->getName());
    delete particle2;
}

TEST_F(ParticleTest, Constructors)
{
    HomogeneousMaterial mat("Air",0,0);

    Particle *p1 = new Particle(mat);
    EXPECT_EQ("Air", p1->getMaterial()->getName());
    EXPECT_EQ(complex_t(1,0), p1->getRefractiveIndex());
    EXPECT_EQ(NULL, p1->getFormFactor());
    EXPECT_EQ(NULL, p1->createFormFactor(1.0));
    EXPECT_EQ( NULL, p1->getRotation());

    delete p1;

    FormFactorFullSphere sphere(1.0);
    Particle *p2 = new Particle(mat, sphere);
    EXPECT_EQ("FormFactorFullSphere", p2->getFormFactor()->getName());
    EXPECT_EQ(1, p2->getFormFactor()->getRadius());
    EXPECT_TRUE(dynamic_cast<FormFactorDecoratorMaterial *>(
            p2->createFormFactor(1.0)));
    EXPECT_EQ(complex_t(1,0),
              dynamic_cast<FormFactorDecoratorMaterial *>(
                      p2->createFormFactor(1.0))->getAmbientRefractiveIndex());
    delete p2;

    FormFactorFullSphere sphere3(1.0);
    Particle *p3 = new Particle(mat, sphere3);
    EXPECT_EQ(sphere3.getName(), p3->getFormFactor()->getName());
    EXPECT_EQ(sphere3.getRadius(), p3->getFormFactor()->getRadius());

    Particle *p4 = p3->clone();
    EXPECT_EQ("FormFactorFullSphere", p4->getFormFactor()->getName());

    delete p3;
    delete p4;
}

TEST_F(ParticleTest, Transform)
{
    HomogeneousMaterial mat("Air",0,0);
    FormFactorFullSphere sphere(1.0);
    RotationZ transform(45.*Units::degree);
    Particle *particle = new Particle(mat, sphere, transform);

    EXPECT_EQ("Air", particle->getMaterial()->getName());

    EXPECT_TRUE(NULL != particle->getRotation());

    delete particle;
}

TEST_F(ParticleTest, SetParam)
{
    HomogeneousMaterial mat("Air",0,0);
    FormFactorFullSphere sphere(2.1);
    RotationY transform(45.*Units::degree);

    Particle particle;
    EXPECT_EQ(NULL, particle.getMaterial());
    EXPECT_EQ(NULL, particle.getFormFactor());
    EXPECT_EQ(NULL, particle.getRotation());

    particle.setMaterial(mat);
    EXPECT_EQ("Air", particle.getMaterial()->getName());
    EXPECT_EQ(complex_t(1.0), particle.getRefractiveIndex());

    particle.setFormFactor(sphere);
    EXPECT_EQ("FormFactorFullSphere", particle.getFormFactor()->getName());
    EXPECT_EQ(2.1, particle.getFormFactor()->getRadius());

    particle.setRotation(transform);
    EXPECT_TRUE(NULL != particle.getRotation());
    Particle *particle2 = particle.clone();
    EXPECT_EQ("Particle", particle2->getName());
    EXPECT_EQ("Air", particle2->getMaterial()->getName());
    EXPECT_EQ(complex_t(1.0), particle2->getRefractiveIndex());
    EXPECT_TRUE(NULL != particle2->getFormFactor());
    EXPECT_EQ(2.1, particle2->getFormFactor()->getRadius());
    EXPECT_TRUE(NULL != particle2->getRotation());

    delete particle2;
}

#endif // PARTICLETEST_H
