#ifndef PARTICLECORESHELLTEST_H
#define PARTICLECORESHELLTEST_H

#include "ParticleCoreShell.h"
#include "Units.h"
#include "HomogeneousMaterial.h"
#include "FormFactorFullSphere.h"
#include <iostream>

class ParticleCoreShellTest : public ::testing::Test
{
protected:
    ParticleCoreShellTest();
    virtual ~ParticleCoreShellTest();

    ParticleCoreShell *mp_coreshell;
};

ParticleCoreShellTest::ParticleCoreShellTest()
    : mp_coreshell(0)
{
    Particle core;
    Particle shell;
    kvector_t position;
    mp_coreshell = new ParticleCoreShell(shell, core, position);
}

ParticleCoreShellTest::~ParticleCoreShellTest()
{
    delete mp_coreshell;
}


TEST_F(ParticleCoreShellTest, InitialState)
{
    EXPECT_EQ(NULL, mp_coreshell->getAmbientMaterial());
    EXPECT_EQ(NULL, mp_coreshell->createFormFactor(1.0));
    EXPECT_EQ(NULL, mp_coreshell->getRotation());
    EXPECT_EQ("ParticleCoreShell", mp_coreshell->getName());
    EXPECT_EQ("Particle", mp_coreshell->getCoreParticle()->getName());
    EXPECT_EQ("Particle", mp_coreshell->getShellParticle()->getName());
}

TEST_F(ParticleCoreShellTest, Clone)
{
    ParticleCoreShell *p_clone = mp_coreshell->clone();
    EXPECT_EQ(NULL, p_clone->getAmbientMaterial());
    EXPECT_EQ(NULL, p_clone->createFormFactor(1.0));
    EXPECT_EQ(NULL, p_clone->getRotation());
    EXPECT_EQ("ParticleCoreShell", p_clone->getName());
    EXPECT_EQ("Particle", p_clone->getCoreParticle()->getName());
    EXPECT_EQ("Particle", p_clone->getShellParticle()->getName());
    delete p_clone;
}

TEST_F(ParticleCoreShellTest, CloneInvertB)
{
    ParticleCoreShell *p_clone = mp_coreshell->cloneInvertB();
    EXPECT_EQ(NULL, p_clone->getAmbientMaterial());
    EXPECT_EQ(NULL, p_clone->createFormFactor(1.0));
    EXPECT_EQ(NULL, p_clone->getRotation());
    EXPECT_EQ("ParticleCoreShell_inv", p_clone->getName());
    EXPECT_EQ("Particle_inv", p_clone->getCoreParticle()->getName());
    EXPECT_EQ("Particle_inv", p_clone->getShellParticle()->getName());
    delete p_clone;
}

TEST_F(ParticleCoreShellTest, AmbientMaterial)
{
    HomogeneousMaterial mat("Air", 0.0, 0.0);
    EXPECT_EQ(NULL, mp_coreshell->getAmbientMaterial());
    mp_coreshell->setAmbientMaterial(mat);
    const IMaterial *p_material = mp_coreshell->getAmbientMaterial();
    EXPECT_EQ("Air", p_material->getName());
    EXPECT_EQ(complex_t(1.0, 0.0), p_material->getRefractiveIndex());
    p_material = mp_coreshell->getCoreParticle()->getAmbientMaterial();
    EXPECT_EQ(NULL, p_material);
    p_material = mp_coreshell->getShellParticle()->getAmbientMaterial();
    EXPECT_EQ("Air", p_material->getName());
    EXPECT_EQ(complex_t(1.0, 0.0), p_material->getRefractiveIndex());
    EXPECT_EQ(NULL, mp_coreshell->createFormFactor(1.0));
    EXPECT_EQ("ParticleCoreShell", mp_coreshell->getName());
    EXPECT_EQ("Particle", mp_coreshell->getCoreParticle()->getName());
    EXPECT_EQ("Particle", mp_coreshell->getShellParticle()->getName());
}

#endif // PARTICLECORESHELLTEST_H
