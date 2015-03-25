#ifndef PARTICLELAYOUTTEST_H
#define PARTICLELAYOUTTEST_H

#include "ParticleLayout.h"
#include "InterferenceFunctionNone.h"

class ParticleLayoutTest : public :: testing :: Test {

protected:
    ParticleLayoutTest(){}
    virtual ~ParticleLayoutTest(){}

};


TEST_F(ParticleLayoutTest, ParticleLayoutInitial)
{
    ParticleLayout particleDecoration;

    EXPECT_EQ("ParticleLayout", particleDecoration.getName());
    EXPECT_EQ(size_t(0), particleDecoration.getNumberOfParticles());
    EXPECT_EQ(size_t(0), particleDecoration.getNumberOfInterferenceFunctions());
}


TEST_F(ParticleLayoutTest, ParticleLayoutInitByValue)
{
    Particle particle;

    ParticleLayout particleDecoration(particle, 1.0, 2.0);

    EXPECT_EQ("ParticleLayout", particleDecoration.getName());
    EXPECT_EQ(size_t(1), particleDecoration.getNumberOfParticles());
    EXPECT_EQ(size_t(0), particleDecoration.getNumberOfInterferenceFunctions());


    const ParticleInfo * pInfo = particleDecoration.getParticleInfo(size_t(0));
    EXPECT_TRUE(NULL!=pInfo);
    EXPECT_EQ(1.0, pInfo->getDepth());
    EXPECT_EQ(2.0, pInfo->getAbundance());

    EXPECT_EQ(size_t(0), particleDecoration.getNumberOfInterferenceFunctions());

}


TEST_F(ParticleLayoutTest, ParticleLayoutInitByRef)
{
    Particle particle;

    ParticleLayout particleDecoration(particle, 3.0, -2.0);

    EXPECT_EQ("ParticleLayout", particleDecoration.getName());
    EXPECT_EQ(size_t(1), particleDecoration.getNumberOfParticles());
    EXPECT_EQ(size_t(0), particleDecoration.getNumberOfInterferenceFunctions());


    const ParticleInfo * pInfo = particleDecoration.getParticleInfo(size_t(0));
    EXPECT_TRUE(NULL!=pInfo);
    EXPECT_EQ(3.0, pInfo->getDepth());
    EXPECT_EQ(-2.0, pInfo->getAbundance());
}


TEST_F(ParticleLayoutTest, ParticleLayoutAddParticleInfo)
{
    ParticleLayout particleDecoration;

    Particle particle;
    ParticleInfo particleInfo(particle, 0.1,-2.0);
    particleDecoration.addParticleInfo(particleInfo);

    EXPECT_EQ(size_t(1), particleDecoration.getNumberOfParticles());

    Particle particle2;
    ParticleInfo particleInfo2(particle2, 5.0,0.1);
    particleDecoration.addParticleInfo(particleInfo2);

    EXPECT_EQ(size_t(2), particleDecoration.getNumberOfParticles());

    const ParticleInfo * pInfo = particleDecoration.getParticleInfo(size_t(0));
    EXPECT_TRUE(NULL!=pInfo);
    EXPECT_EQ(0.1, pInfo->getDepth());
    EXPECT_EQ(-2.0, pInfo->getAbundance());

    const ParticleInfo * pInfo2 = particleDecoration.getParticleInfo(size_t(1));
    EXPECT_TRUE(NULL!=pInfo2);
    EXPECT_EQ(5.0, pInfo2->getDepth());
    EXPECT_EQ(0.1, pInfo2->getAbundance());
}


TEST_F(ParticleLayoutTest, ParticleLayoutAddParticle)
{
    ParticleLayout particleDecoration;

    Particle particle1;
    Particle particle2;
    Particle particle3;
    Particle particle4;

    Geometry::Transform3D transform3 =
            Geometry::Transform3D::createRotateY(45.*Units::degree);
    Geometry::Transform3D transform4 =
            Geometry::Transform3D::createRotateZ(45.*Units::degree);

    particleDecoration.addParticle(particle1);
    particleDecoration.addParticle(particle2, 2.1, 2.2);
    particleDecoration.addParticle(particle3, transform3);
    particleDecoration.addParticle(particle4, transform4, 4.1, -4.2);

    EXPECT_EQ(size_t(4), particleDecoration.getNumberOfParticles());

    const ParticleInfo * pInfo1 = particleDecoration.getParticleInfo(size_t(0));
    EXPECT_TRUE(NULL!=pInfo1);
    EXPECT_EQ(0.0, pInfo1->getDepth());
    EXPECT_EQ(1.0, pInfo1->getAbundance());
    EXPECT_TRUE(NULL == pInfo1->getParticle()->getRotation());

    const ParticleInfo * pInfo2 = particleDecoration.getParticleInfo(size_t(1));
    EXPECT_TRUE(NULL!=pInfo2);
    EXPECT_EQ(2.1, pInfo2->getDepth());
    EXPECT_EQ(2.2, pInfo2->getAbundance());
    EXPECT_TRUE(NULL == pInfo2->getParticle()->getRotation());

    const ParticleInfo * pInfo3 = particleDecoration.getParticleInfo(size_t(2));
    EXPECT_TRUE(NULL!=pInfo3);
    EXPECT_EQ(0.0, pInfo3->getDepth());
    EXPECT_EQ(1.0, pInfo3->getAbundance());
    EXPECT_TRUE(NULL != pInfo3->getParticle()->getRotation());

    const ParticleInfo * pInfo4 = particleDecoration.getParticleInfo(size_t(3));
    EXPECT_TRUE(NULL!=pInfo4);
    EXPECT_EQ(4.1, pInfo4->getDepth());
    EXPECT_EQ(-4.2, pInfo4->getAbundance());
    EXPECT_TRUE(NULL != pInfo4->getParticle()->getRotation());
}


TEST_F(ParticleLayoutTest, ParticleLayoutAbundanceFraction)
{
    ParticleLayout particleDecoration;

    Particle particle1;
    Particle particle2;
    Particle particle3;
    Particle particle4;

    Geometry::Transform3D transform3 =
            Geometry::Transform3D::createRotateY(45.*Units::degree);

    Geometry::Transform3D transform4 =
            Geometry::Transform3D::createRotateZ(45.*Units::degree);

    particleDecoration.addParticle(particle1);
    EXPECT_EQ(1.0, particleDecoration.getAbundanceOfParticle(size_t(0)));

    particleDecoration.addParticle(particle2, 2.1, 2.0);
    EXPECT_EQ(2.0, particleDecoration.getAbundanceOfParticle(size_t(1)));

    particleDecoration.addParticle(particle3, transform3);
    EXPECT_EQ(1.0, particleDecoration.getAbundanceOfParticle(size_t(2)));

    particleDecoration.addParticle(particle4, transform4, 4.1, 4.0);
    EXPECT_EQ(4.0, particleDecoration.getAbundanceOfParticle(size_t(3)));
}


TEST_F(ParticleLayoutTest, ParticleLayoutClone)
{
    ParticleLayout particleDecoration;

    Particle particle1;
    Particle particle2;
    Particle particle3;
    Particle particle4;

    Geometry::Transform3D transform3 =
            Geometry::Transform3D::createRotateY(45.*Units::degree);
    Geometry::Transform3D transform4 =
            Geometry::Transform3D::createRotateZ(45.*Units::degree);

    particleDecoration.addParticle(particle1);
    particleDecoration.addParticle(particle2, 2.1, 2.0);
    particleDecoration.addParticle(particle3, transform3);
    particleDecoration.addParticle(particle4, transform4, 4.1, 4.0);

    HomogeneousMaterial mat5("core", 0, 0);
    Particle particle5(mat5);
    ParticleInfo particleInfo5(particle5, 0.0, 0.0);
    particleDecoration.addParticleInfo(particleInfo5);

    particleDecoration.addInterferenceFunction(new InterferenceFunctionNone());
    particleDecoration.addInterferenceFunction(new InterferenceFunctionNone());
    particleDecoration.addInterferenceFunction(new InterferenceFunctionNone());

    ParticleLayout * clone = particleDecoration.clone();

    EXPECT_EQ("ParticleLayout", clone->getName());

    const ParticleInfo * pInfo1 = clone->getParticleInfo(size_t(0));
    EXPECT_TRUE(NULL!=pInfo1);
    EXPECT_EQ(0.0, pInfo1->getDepth());
    EXPECT_EQ(1.0, pInfo1->getAbundance());
    EXPECT_TRUE(NULL == pInfo1->getParticle()->getRotation());

    const ParticleInfo * pInfo2 = clone->getParticleInfo(size_t(1));
    EXPECT_TRUE(NULL!=pInfo2);
    EXPECT_EQ(2.1, pInfo2->getDepth());
    EXPECT_EQ(2.0, pInfo2->getAbundance());
    EXPECT_TRUE(NULL == pInfo2->getParticle()->getRotation());

    const ParticleInfo * pInfo3 = clone->getParticleInfo(size_t(2));
    EXPECT_TRUE(NULL!=pInfo3);
    EXPECT_EQ(0.0, pInfo3->getDepth());
    EXPECT_EQ(1.0, pInfo3->getAbundance());
    EXPECT_TRUE(NULL != pInfo3->getParticle()->getRotation());

    const ParticleInfo * pInfo4 = clone->getParticleInfo(size_t(3));
    EXPECT_TRUE(NULL!=pInfo4);
    EXPECT_EQ(4.1, pInfo4->getDepth());
    EXPECT_EQ(4.0, pInfo4->getAbundance());
    EXPECT_TRUE(NULL != pInfo4->getParticle()->getRotation());

    const ParticleInfo * pInfo5 = clone->getParticleInfo(size_t(4));
    EXPECT_TRUE(NULL!=pInfo5);
    EXPECT_EQ(0.0, pInfo5->getDepth());
    EXPECT_EQ(0.0, pInfo5->getAbundance());
    EXPECT_TRUE(NULL == pInfo2->getParticle()->getRotation());

    EXPECT_EQ(1.0, clone->getAbundanceOfParticle(size_t(0)));
    EXPECT_EQ(2.0, clone->getAbundanceOfParticle(size_t(1)));
    EXPECT_EQ(1.0, clone->getAbundanceOfParticle(size_t(2)));
    EXPECT_EQ(4.0, clone->getAbundanceOfParticle(size_t(3)));
    EXPECT_EQ(0.0, clone->getAbundanceOfParticle(size_t(4)));

    EXPECT_EQ(size_t(3), clone->getNumberOfInterferenceFunctions());
    EXPECT_EQ(size_t(3), clone->getInterferenceFunctions().size());
    EXPECT_TRUE(NULL!=clone->getInterferenceFunction(size_t(0)));
    EXPECT_TRUE(NULL!=clone->getInterferenceFunction(size_t(1)));
    EXPECT_TRUE(NULL!=clone->getInterferenceFunction(size_t(2)));
}


TEST_F(ParticleLayoutTest, ParticleLayoutCloneInvertB)
{
    ParticleLayout particleDecoration;

    HomogeneousMaterial mat1("Air",0,0);
    Particle particle1(mat1);

    HomogeneousMaterial mat2("Stone",0,0);
    Particle particle2(mat2);

    HomogeneousMaterial mat3("wood",0,0);
    Particle particle3(mat3);

    HomogeneousMaterial mat4("silica",0,0);
    Particle particle4(mat4);

    Geometry::Transform3D transform3 =
            Geometry::Transform3D::createRotateY(45.*Units::degree);
    Geometry::Transform3D transform4 =
            Geometry::Transform3D::createRotateZ(45.*Units::degree);

    particleDecoration.addParticle(particle1);
    particleDecoration.addParticle(particle2, 2.1, 2.0);
    particleDecoration.addParticle(particle3, transform3);
    particleDecoration.addParticle(particle4, transform4, 4.1, 4.0);

    HomogeneousMaterial mat5("core",0,0);
    Particle particle5(mat5);
    ParticleInfo particleInfo5(particle5, 0.0,0.0);
    particleDecoration.addParticleInfo(particleInfo5);

    particleDecoration.addInterferenceFunction(new InterferenceFunctionNone());
    particleDecoration.addInterferenceFunction(new InterferenceFunctionNone());
    particleDecoration.addInterferenceFunction(new InterferenceFunctionNone());

    ParticleLayout * clone = particleDecoration.cloneInvertB();

    EXPECT_EQ("ParticleLayout_inv", clone->getName());

    const ParticleInfo * pInfo1 = clone->getParticleInfo(size_t(0));
    EXPECT_TRUE(NULL!=pInfo1);
    EXPECT_EQ(0.0, pInfo1->getDepth());
    EXPECT_EQ(1.0, pInfo1->getAbundance());
    EXPECT_TRUE(NULL == pInfo1->getParticle()->getRotation());

    const ParticleInfo * pInfo2 = clone->getParticleInfo(size_t(1));
    EXPECT_TRUE(NULL!=pInfo2);
    EXPECT_EQ(2.1, pInfo2->getDepth());
    EXPECT_EQ(2.0, pInfo2->getAbundance());
    EXPECT_TRUE(NULL == pInfo2->getParticle()->getRotation());

    const ParticleInfo * pInfo3 = clone->getParticleInfo(size_t(2));
    EXPECT_TRUE(NULL!=pInfo3);
    EXPECT_EQ(0.0, pInfo3->getDepth());
    EXPECT_EQ(1.0, pInfo3->getAbundance());
    EXPECT_TRUE(NULL != pInfo3->getParticle()->getRotation());

    const ParticleInfo * pInfo4 = clone->getParticleInfo(size_t(3));
    EXPECT_TRUE(NULL!=pInfo4);
    EXPECT_EQ(4.1, pInfo4->getDepth());
    EXPECT_EQ(4.0, pInfo4->getAbundance());
    EXPECT_TRUE(NULL != pInfo4->getParticle()->getRotation());


    const ParticleInfo * pInfo5 = clone->getParticleInfo(size_t(4));
    EXPECT_TRUE(NULL!=pInfo5);
    EXPECT_EQ(0.0, pInfo5->getDepth());
    EXPECT_EQ(0.0, pInfo5->getAbundance());
    EXPECT_TRUE(NULL == pInfo2->getParticle()->getRotation());

    EXPECT_EQ(1.0, clone->getAbundanceOfParticle(size_t(0)));
    EXPECT_EQ(2.0, clone->getAbundanceOfParticle(size_t(1)));
    EXPECT_EQ(1.0, clone->getAbundanceOfParticle(size_t(2)));
    EXPECT_EQ(4.0, clone->getAbundanceOfParticle(size_t(3)));
    EXPECT_EQ(0.0, clone->getAbundanceOfParticle(size_t(4)));

    EXPECT_EQ(size_t(3), clone->getNumberOfInterferenceFunctions());
    EXPECT_EQ(size_t(3), clone->getInterferenceFunctions().size());
    EXPECT_TRUE(NULL!=clone->getInterferenceFunction(size_t(0)));
    EXPECT_TRUE(NULL!=clone->getInterferenceFunction(size_t(1)));
    EXPECT_TRUE(NULL!=clone->getInterferenceFunction(size_t(2)));
}


TEST_F(ParticleLayoutTest, ParticleLayoutInterferenceFunction)
{
    ParticleLayout particleDecoration;

    particleDecoration.addInterferenceFunction(new InterferenceFunctionNone());
    particleDecoration.addInterferenceFunction(new InterferenceFunctionNone());
    particleDecoration.addInterferenceFunction(new InterferenceFunctionNone());

    EXPECT_EQ(size_t(3), particleDecoration.getNumberOfInterferenceFunctions());
    EXPECT_EQ(size_t(3), particleDecoration.getInterferenceFunctions().size());
    EXPECT_TRUE(NULL!=particleDecoration.getInterferenceFunction(size_t(0)));
    EXPECT_TRUE(NULL!=particleDecoration.getInterferenceFunction(size_t(1)));
    EXPECT_TRUE(NULL!=particleDecoration.getInterferenceFunction(size_t(2)));
}


#endif // PARTICLELAYOUTTEST_H
