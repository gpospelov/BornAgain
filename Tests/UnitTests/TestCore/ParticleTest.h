#ifndef PARTICLETEST_H
#define PARTICLETEST_H

#include "Particle.h"
#include "Units.h"

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



}


#endif // PARTICLETEST_H
