#ifndef PARTICLEINFOTEST_H
#define PARTICLEINFOTEST_H

#include "ParticleInfo.h"

class ParticleInfoTest : public ::testing::Test
{
 protected:
    ParticleInfoTest(){}
    virtual ~ParticleInfoTest(){}
};


TEST_F(ParticleInfoTest , ParticleInfoInitialState)
{

    //test with default parameter
    Particle particle;

    ParticleInfo particleInfo(particle);

    kvector_t position;
    EXPECT_EQ(position, particleInfo.getPosition());
    EXPECT_EQ(1.0, particleInfo.getAbundance());
    EXPECT_EQ("ParticleInfo", particleInfo.getName());

    //set new parameter
    position = kvector_t(1.0, 2.0, 3.0);
    particleInfo.setPosition(position);
    particleInfo.setAbundance(2.0);
    EXPECT_EQ(position, particleInfo.getPosition());
    EXPECT_EQ(2.0, particleInfo.getAbundance());
}


//test parameter pool
TEST_F(ParticleInfoTest , ParticleInfoTestPool)
{
    Particle particle;

    ParticleInfo particleInfo(particle);

    particleInfo.setParameterValue("/ParticleInfo/abundance",4.2);

    EXPECT_EQ(4.2, particleInfo.getAbundance());
    EXPECT_EQ("ParticleInfo", particleInfo.getName());
}


TEST_F(ParticleInfoTest , ParticleInfoInitialStateClonedParticle)
{

    //test with default parameter
    Particle particle;
    Particle *pClone = particle.clone();

    ParticleInfo particleInfo(*pClone,3.0);
    delete pClone;

    EXPECT_EQ(3.0, particleInfo.getAbundance());
    EXPECT_EQ("ParticleInfo", particleInfo.getName());
}


TEST_F(ParticleInfoTest , ParticleInfoClone)
{
    //test with default parameter
    Particle particle;

    ParticleInfo original(particle, 2.0);
    ParticleInfo *clone = original.clone();

    EXPECT_EQ(clone->getAbundance(), original.getAbundance());
    EXPECT_EQ(clone->getName(), original.getName());
    EXPECT_EQ(clone->getParticle()->getName(), original.getParticle()->getName());

    delete clone;
}


TEST_F(ParticleInfoTest , ParticleInfoCloneInvertB)
{
    HomogeneousMaterial mat("Air",0,0);
    Particle particle2(mat);
    ParticleInfo particle_info2(particle2, 2.0);
    ParticleInfo *clone = particle_info2.cloneInvertB();
    EXPECT_EQ(clone->getAbundance(), particle_info2.getAbundance());
    EXPECT_EQ(clone->getName(), particle_info2.getName());
    EXPECT_EQ(clone->getParticle()->getName(), particle2.getName()+"_inv");

    delete clone;
}


#endif // PARTICLEINFOTEST_H
