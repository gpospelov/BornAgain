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
//    EXPECT_EQ(NULL, mp_coreshell->createFormFactor(1.0));
    EXPECT_EQ("ParticleCoreShell", mp_coreshell->getName());
}

#endif // PARTICLECORESHELLTEST_H
