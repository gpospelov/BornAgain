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

    EXPECT_EQ(0.0, particleInfo.getDepth());
    EXPECT_EQ(0.0, particleInfo.getAbundance());
    EXPECT_EQ("ParticleInfo", particleInfo.getName());

    //set new parameter
    particleInfo.setDepth(1.0);
    particleInfo.setAbundance(2.0);
    EXPECT_EQ(1.0, particleInfo.getDepth());
    EXPECT_EQ(2.0, particleInfo.getAbundance());


    ParticleInfo particleInfo2(particle,2.0,3.0);

    EXPECT_EQ(2.0, particleInfo2.getDepth());
    EXPECT_EQ(3.0, particleInfo2.getAbundance());
    EXPECT_EQ("ParticleInfo", particleInfo2.getName());
}


//test parameter pool
TEST_F(ParticleInfoTest , ParticleInfoTestPool)
{
    Particle particle;

    ParticleInfo particleInfo(particle);

    particleInfo.setParameterValue("/ParticleInfo/depth",4.1);
    particleInfo.setParameterValue("/ParticleInfo/abundance",4.2);

    EXPECT_EQ(4.1, particleInfo.getDepth());
    EXPECT_EQ(4.2, particleInfo.getAbundance());
    EXPECT_EQ("ParticleInfo", particleInfo.getName());
}


TEST_F(ParticleInfoTest , ParticleInfoInitialStateClonedParticle)
{

    //test with default parameter
    Particle particle;
    Particle *pClone = particle.clone();

    ParticleInfo particleInfo(*pClone,2.0,3.0);
    delete pClone;

    EXPECT_EQ(2.0, particleInfo.getDepth());
    EXPECT_EQ(3.0, particleInfo.getAbundance());
    EXPECT_EQ("ParticleInfo", particleInfo.getName());
}



TEST_F(ParticleInfoTest , ParticleInfoClone)
{
    //test with default parameter
    Particle particle;

    ParticleInfo original(particle, 1.0,2.0);
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
    ParticleInfo particle_info(particle, 1.0,2.0);
    ASSERT_THROW(particle_info.cloneInvertB(), NullPointerException);

    HomogeneousMaterial mat("Air",0,0);
    Particle particle2(mat);
    ParticleInfo particle_info2(particle2, 1.0,2.0);
    ParticleInfo *clone = particle_info2.cloneInvertB();
    EXPECT_EQ(clone->getDepth(), particle_info2.getDepth());
    EXPECT_EQ(clone->getAbundance(), particle_info2.getAbundance());
    EXPECT_EQ(clone->getName(), particle_info2.getName());
    EXPECT_EQ(clone->getParticle()->getName(), particle2.getName()+"_inv");

    delete clone;

}



#endif // PARTICLEINFOTEST_H

