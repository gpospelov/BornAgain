#include "Particle.h"
#include "BornAgainNamespace.h"
#include "MathConstants.h"
#include "HomogeneousMaterial.h"
#include "FormFactorFullSphere.h"

#include <iostream>

class ParticleTest : public ::testing::Test
{
protected:
    ParticleTest(){}
};

TEST_F(ParticleTest, InitialState)
{
    Particle particle;
    HomogeneousMaterial vacuum;
    EXPECT_EQ(vacuum, *particle.material());
    EXPECT_EQ(complex_t(1,0), particle.refractiveIndex());
    EXPECT_EQ(nullptr, particle.formFactor());
    EXPECT_EQ(nullptr, particle.createFormFactor());
    EXPECT_EQ(nullptr, particle.rotation());
    EXPECT_EQ(BornAgain::ParticleType, particle.getName());
}

TEST_F(ParticleTest, Clone)
{
    Particle particle;
    HomogeneousMaterial vacuum;
    std::unique_ptr<Particle> clone(particle.clone());
    EXPECT_EQ(vacuum, *clone->material());
    EXPECT_EQ(complex_t(1,0), clone->refractiveIndex());
    EXPECT_EQ(nullptr, clone->formFactor());
    EXPECT_EQ(nullptr, clone->createFormFactor());
    EXPECT_EQ(nullptr, clone->rotation());
    EXPECT_EQ(BornAgain::ParticleType, clone->getName());
}

TEST_F(ParticleTest, CloneInvertB)
{
    Particle particle;
    HomogeneousMaterial vacuum;
    std::unique_ptr<Particle> clone(particle.cloneInvertB());
    EXPECT_EQ(vacuum, *clone->material());
    EXPECT_EQ(complex_t(1,0), clone->refractiveIndex());
    EXPECT_EQ(nullptr, clone->formFactor());
    EXPECT_EQ(nullptr, clone->createFormFactor());
    EXPECT_EQ(nullptr, clone->rotation());
    EXPECT_EQ(BornAgain::ParticleType, clone->getName());
}

TEST_F(ParticleTest, Constructors)
{
    HomogeneousMaterial mat("Air",0,0);
    FormFactorFullSphere sphere(1.0);
    RotationZ transform(45.*Units::degree);

    // construction with material
    std::unique_ptr<Particle> p1(new Particle(mat));
    EXPECT_EQ("Air", p1->material()->getName());
    EXPECT_EQ(complex_t(1,0), p1->refractiveIndex());
    EXPECT_EQ(nullptr, p1->formFactor());
    EXPECT_EQ(nullptr, p1->createFormFactor());
    EXPECT_EQ( nullptr, p1->rotation());

    // construction with formfactor
    std::unique_ptr<Particle> p2(new Particle(mat, sphere));
    EXPECT_EQ("Air", p2->material()->getName());
    EXPECT_EQ(complex_t(1,0), p2->refractiveIndex());
    EXPECT_EQ(BornAgain::FFFullSphereType, p2->formFactor()->getName());
    EXPECT_EQ(1, p2->formFactor()->getRadialExtension());
    EXPECT_TRUE(dynamic_cast<FormFactorDecoratorMaterial *>(p2->createFormFactor()));
    EXPECT_EQ(complex_t(1,0), dynamic_cast<FormFactorDecoratorMaterial *>(
                      p2->createFormFactor())->getAmbientRefractiveIndex());
    EXPECT_EQ( nullptr, p2->rotation());

    // construction with transformation
    std::unique_ptr<Particle> p3(new Particle(mat, sphere, transform));
    EXPECT_EQ("Air", p3->material()->getName());
    EXPECT_EQ(complex_t(1,0), p3->refractiveIndex());
    EXPECT_EQ(BornAgain::FFFullSphereType, p3->formFactor()->getName());
    EXPECT_EQ(1, p3->formFactor()->getRadialExtension());
    EXPECT_TRUE(dynamic_cast<FormFactorDecoratorMaterial *>(p3->createFormFactor()));
    EXPECT_EQ(complex_t(1,0), dynamic_cast<FormFactorDecoratorMaterial *>(
                      p3->createFormFactor())->getAmbientRefractiveIndex());
    EXPECT_EQ(BornAgain::ZRotationType, p3->rotation()->getName());
}

TEST_F(ParticleTest, setters)
{
    HomogeneousMaterial mat("Air",0,0);
    FormFactorFullSphere sphere(2.1);
    RotationY transform(45.*Units::degree);

    Particle particle;
    HomogeneousMaterial vacuum;
    EXPECT_EQ(vacuum, *particle.material());
    EXPECT_EQ(nullptr, particle.formFactor());
    EXPECT_EQ(nullptr, particle.rotation());

    particle.setFormFactor(sphere);
    EXPECT_EQ(BornAgain::FFFullSphereType, particle.formFactor()->getName());
    EXPECT_EQ(2.1, particle.formFactor()->getRadialExtension());

    particle.setRotation(transform);
    EXPECT_TRUE(nullptr != particle.rotation());

    std::unique_ptr<Particle> particle2(particle.clone());
    EXPECT_EQ(BornAgain::ParticleType, particle2->getName());
    EXPECT_EQ(vacuum.getName(), particle2->material()->getName());
    EXPECT_EQ(complex_t(1.0), particle2->refractiveIndex());
    EXPECT_TRUE(nullptr != particle2->formFactor());
    EXPECT_EQ(2.1, particle2->formFactor()->getRadialExtension());
    EXPECT_TRUE(nullptr != particle2->rotation());
}

TEST_F(ParticleTest, getChildren)
{
    HomogeneousMaterial mat("Air",0,0);
    FormFactorFullSphere sphere(2.1);

    // Checking children of particle (no rotation)
    std::unique_ptr<Particle> particle(new Particle(mat, sphere));
    std::vector<const INode*> children = particle->getChildren();
    EXPECT_EQ(children.size(), 1u);
    EXPECT_EQ(children.at(0)->getName(), BornAgain::FFFullSphereType);

    // Checking children of particle (with rotation)
    particle.reset(new Particle(mat, sphere, RotationY(45.)));
    children = particle->getChildren();
    EXPECT_EQ(children.size(), 2u);
    EXPECT_EQ(children.at(0)->getName(), BornAgain::YRotationType);
    EXPECT_EQ(children.at(1)->getName(), BornAgain::FFFullSphereType);
}
