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

}

TEST_F(ParticleTest, ParticleClone)
{
    Particle particle;
    Particle *particle2 = particle.clone();
    EXPECT_EQ(NULL, particle2->getMaterial());
    EXPECT_EQ(complex_t(0,0), particle2->getRefractiveIndex());
    EXPECT_EQ(NULL, particle2->getSimpleFormFactor());
    EXPECT_FALSE(particle2->hasDistributedFormFactor());
    EXPECT_EQ(NULL, particle2->createFormFactor(1.0));
    ASSERT_THROW(particle2->createDistributedParticles(0,0).size(), NullPointerException);
    EXPECT_EQ("Particle", particle2->getName());
    delete particle2;
}
TEST_F(ParticleTest, ParticleCloneInvertB)
{
    Particle particle;
    ASSERT_THROW(particle.cloneInvertB(), NullPointerException);
}


TEST_F(ParticleTest, ParticleConstructors)
{
    HomogeneousMaterial mat("Air",0,0);

    Particle *p1 = new Particle(mat);
    EXPECT_EQ("Air", p1->getMaterial()->getName());
    EXPECT_EQ(complex_t(1,0), p1->getRefractiveIndex());
    EXPECT_EQ(NULL, p1->getSimpleFormFactor());
    EXPECT_FALSE(p1->hasDistributedFormFactor());
    EXPECT_EQ(NULL, p1->createFormFactor(1.0));
    ASSERT_THROW(p1->createDistributedParticles(0,0).size(), NullPointerException);
    EXPECT_EQ( NULL, p1->getPTransform3D());

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

    FormFactorFullSphere sphere3(1.0);
    sphere3.setName("sphere3");
    Particle *p3 = new Particle(mat, sphere3);
    EXPECT_EQ(sphere3.getName(), p3->getSimpleFormFactor()->getName());
    EXPECT_EQ(sphere3.getRadius(), p3->getSimpleFormFactor()->getRadius());

    Particle *p4 = p3->clone();
    EXPECT_EQ("sphere3", p4->getSimpleFormFactor()->getName());

    delete p3;
    delete p4;
}

TEST_F(ParticleTest, ParticleTransform)
{
    HomogeneousMaterial mat("Air",0,0);
    FormFactorFullSphere sphere(1.0);
    Geometry::Transform3D transform =
            Geometry::Transform3D::createRotateZ(45.*Units::degree);
    Particle *particle = new Particle(mat, sphere, transform);

    EXPECT_EQ("Air", particle->getMaterial()->getName());

    EXPECT_TRUE(NULL != particle->getPTransform3D());

    const Geometry::Transform3D * rZ3D  = particle->getPTransform3D();
    EXPECT_TRUE( NULL != rZ3D);

    const Geometry::Transform3D * rZ3D2 = rZ3D->createInverse();
    EXPECT_TRUE(NULL!=rZ3D2);


    delete particle;

}

TEST_F(ParticleTest, SetParam)
{
    HomogeneousMaterial mat("Air",0,0);
    FormFactorFullSphere *sphere = new FormFactorFullSphere(2.1);
    Geometry::Transform3D transform =
            Geometry::Transform3D::createRotateY(45.*Units::degree);

    Particle particle;
    EXPECT_EQ(NULL, particle.getMaterial());
    EXPECT_EQ(NULL, particle.getSimpleFormFactor());
    EXPECT_EQ(NULL, particle.getPTransform3D());

    particle.setMaterial(&mat);
    EXPECT_EQ("Air", particle.getMaterial()->getName());
    EXPECT_EQ(complex_t(1.0), particle.getRefractiveIndex());

    particle.setSimpleFormFactor(sphere);
    EXPECT_EQ("FormFactorFullSphere", particle.getSimpleFormFactor()->getName());
    EXPECT_EQ(2.1, particle.getSimpleFormFactor()->getRadius());
    EXPECT_FALSE(particle.hasDistributedFormFactor());

    particle.setTransformation(transform);
    EXPECT_TRUE(NULL != particle.getPTransform3D());
    const Geometry::Transform3D * rY3D  = particle.getPTransform3D();
    EXPECT_TRUE( NULL != rY3D);
    const Geometry::Transform3D * rY3D2 = rY3D->createInverse();
    EXPECT_TRUE(NULL!=rY3D2);



    Particle *particle2 = particle.clone();
    EXPECT_EQ("Particle", particle2->getName());
    EXPECT_EQ("Air", particle2->getMaterial()->getName());
    EXPECT_EQ(complex_t(1.0), particle2->getRefractiveIndex());
    EXPECT_TRUE(NULL != particle2->getSimpleFormFactor());
    EXPECT_EQ(2.1, particle2->getSimpleFormFactor()->getRadius());
    EXPECT_FALSE(particle2->hasDistributedFormFactor());
    EXPECT_TRUE(NULL != particle2->getPTransform3D());

    delete particle2;


}


#endif // PARTICLETEST_H
