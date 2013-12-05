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
    Particle *particleClone = particleInfo.getParticle()->clone();

    EXPECT_EQ(0.0, particleInfo.getDepth());
    EXPECT_EQ(0.0, particleInfo.getAbundance());
    EXPECT_EQ("ParticleInfo", particleInfo.getName());
    EXPECT_EQ(particleClone->getName(), particle.getName());

    //set new parameter
    particleInfo.setDepth(1.0);
    particleInfo.setAbundance(2.0);
    EXPECT_EQ(1.0, particleInfo.getDepth());
    EXPECT_EQ(2.0, particleInfo.getAbundance());


    ParticleInfo particleInfo2(particle,2,3);
    particleClone = particleInfo2.getParticle()->clone();

    EXPECT_EQ(2, particleInfo2.getDepth());
    EXPECT_EQ(3, particleInfo2.getAbundance());
    EXPECT_EQ("ParticleInfo", particleInfo2.getName());
    EXPECT_EQ(particleClone->getName(), particle.getName());


    delete particleClone;
}


//test parameter pool
TEST_F(ParticleInfoTest , ParticleInfoTestPool)
{
    Particle particle;

    ParticleInfo particleInfo(particle);
    Particle *particleClone = particleInfo.getParticle()->clone();

    EXPECT_EQ(0.0, particleInfo.getDepth());
    EXPECT_EQ(0.0, particleInfo.getAbundance());
    EXPECT_EQ("ParticleInfo", particleInfo.getName());
    EXPECT_EQ(particleClone->getName(), particle.getName());

    particleInfo.setParameterValue("/ParticleInfo/depth",4.1);
    particleInfo.setParameterValue("/ParticleInfo/abundance",4.2);


    EXPECT_EQ(4.1, particleInfo.getDepth());
    EXPECT_EQ(4.2, particleInfo.getAbundance());
    EXPECT_EQ("ParticleInfo", particleInfo.getName());

    delete particleClone;
}


TEST_F(ParticleInfoTest , ParticleInfoInitialStateClonedParticle)
{

    //test with default parameter
    Particle particle;
    Particle *pClone = particle.clone();

    ParticleInfo particleInfo(pClone);


    EXPECT_EQ(0, particleInfo.getDepth());
    EXPECT_EQ(0, particleInfo.getAbundance());
    EXPECT_EQ("ParticleInfo", particleInfo.getName());
    EXPECT_EQ(pClone->getName(), particleInfo.getParticle()->getName());


    //test with given parameter
    pClone = Particle().clone();
    ParticleInfo particleInfo2(pClone,2,3);

    EXPECT_EQ(2, particleInfo2.getDepth());
    EXPECT_EQ(3, particleInfo2.getAbundance());
    EXPECT_EQ("ParticleInfo", particleInfo2.getName());
    EXPECT_EQ(pClone->getName(), particleInfo2.getParticle()->getName());

}



TEST_F(ParticleInfoTest , ParticleInfoClone)
{
    //test with default parameter
    Particle particle;

    ParticleInfo original(particle, 1,2);
    ParticleInfo *clone = original.clone();

    EXPECT_EQ(clone->getDepth(), original.getDepth());
    EXPECT_EQ(clone->getAbundance(), original.getAbundance());
    EXPECT_EQ(clone->getName(), original.getName());
    EXPECT_EQ(clone->getParticle()->getName(), original.getParticle()->getName());

    delete clone;

}



TEST_F(ParticleInfoTest , ParticleInfoInvertClone)
{
    //[ERROR: if the material is not set]
    Particle particle;
    ParticleInfo particle_info(particle, 1,2);
    ASSERT_THROW(particle_info.cloneInvertB(), NullPointerException);

    const IMaterial *mat = MaterialManager::getHomogeneousMaterial("Air",0,0);
    Particle particle2(mat);
    ParticleInfo particle_info2(particle2, 1,2);
    ParticleInfo *clone = particle_info2.cloneInvertB();
    EXPECT_EQ(clone->getDepth(), particle_info2.getDepth());
    EXPECT_EQ(clone->getAbundance(), particle_info2.getAbundance());
    EXPECT_EQ(clone->getName(), particle_info2.getName());
    EXPECT_EQ(clone->getParticle()->getName(), particle2.getName()+"_inv");

    delete clone;

}



#endif // PARTICLEINFOTEST_H

