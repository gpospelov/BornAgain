#ifndef TESTREALSPACEBUILDERUTILS_H
#define TESTREALSPACEBUILDERUTILS_H

#include "google_test.h"
#include <QObject>
#include "RealSpaceBuilderUtils.h"
#include "RealSpaceBuilder.h"
#include "SampleModel.h"
#include "ParticleLayoutItem.h"
#include "ParticleItem.h"
#include "IFormFactor.h"
#include "IFormFactorDecorator.h"
#include "Particle.h"
#include "ApplicationModels.h"
#include "TransformTo3D.h"

class TestRealSpaceBuilderUtils : public ::testing::Test
{
public:
    ~TestRealSpaceBuilderUtils();
};

TestRealSpaceBuilderUtils::~TestRealSpaceBuilderUtils() = default;

TEST_F(TestRealSpaceBuilderUtils, test_cumulativeAbundance)
{
    SampleModel sampleModel;
    auto layout
        = dynamic_cast<ParticleLayoutItem*>(sampleModel.insertNewItem(Constants::ParticleLayoutType));

    auto particle1 = sampleModel.insertNewItem(Constants::ParticleType, sampleModel.indexOfItem(layout),
                                         -1, ParticleLayoutItem::T_PARTICLES);
    EXPECT_EQ(particle1->parent(), layout);

    SessionItem* particle2 = sampleModel.insertNewItem(Constants::ParticleType);
    EXPECT_EQ(particle2->parent(), sampleModel.rootItem());

    sampleModel.moveItem(particle2, layout, -1, ParticleLayoutItem::T_PARTICLES);
    EXPECT_EQ(particle2->parent(), layout);

    particle1->setItemValue(ParticleItem::P_ABUNDANCE, 8.0);
    particle2->setItemValue(ParticleItem::P_ABUNDANCE, 2.0);

    EXPECT_EQ(RealSpaceBuilderUtils::computeCumulativeAbundances(*layout).last(), 10.0);

}

TEST_F(TestRealSpaceBuilderUtils, test_Particle3DType)
{
    Particle3DType particle3DType;

    EXPECT_EQ((particle3DType.m_3Dparticles).size(), 0);
    EXPECT_EQ(particle3DType.m_cumulative_abundance, 0);
    EXPECT_EQ(particle3DType.m_type, "");

    // Create a 3D particle directly using constructor
    auto cylinder3D = RealSpace::Particles::Cylinder(5, 10);

    // Associate it to a Particle3DType object
    particle3DType.m_3Dparticles.append(&cylinder3D);

    particle3DType.m_cumulative_abundance = 1;
    particle3DType.m_type = Constants::ParticleType;

    EXPECT_EQ(particle3DType.m_3Dparticles.size(), 1);
    //EXPECT_TRUE(particle3DType.m_3Dparticles.at(0) != nullptr);
    EXPECT_EQ(particle3DType.m_cumulative_abundance, 1);
    EXPECT_EQ(particle3DType.m_type, Constants::ParticleType);
}

TEST_F(TestRealSpaceBuilderUtils, test_getSingleParticle3DType)
{
    ApplicationModels models;
    SampleModel* sampleModel = models.sampleModel();

    auto particle = sampleModel->insertNewItem(Constants::ParticleType);
    EXPECT_EQ(particle->getItemValue(ParticleItem::P_ABUNDANCE).toDouble(), 1.0);
    EXPECT_EQ(particle->getGroupItem(ParticleItem::P_FORM_FACTOR)->modelType(), Constants::CylinderType);

    particle->setItemValue(ParticleItem::P_ABUNDANCE, 8.0);
    EXPECT_EQ(particle->getItemValue(ParticleItem::P_ABUNDANCE).toDouble(), 8.0);
    particle->setGroupProperty(ParticleItem::P_FORM_FACTOR, Constants::BoxType);
    EXPECT_EQ(particle->getGroupItem(ParticleItem::P_FORM_FACTOR)->modelType(), Constants::BoxType);

    // Create a 3D particle from particleItem and associate it to a Particle3DType object
    auto singleParticle3DType = RealSpaceBuilderUtils::getSingleParticle3DType(particle, 8);

    EXPECT_EQ(singleParticle3DType.m_3Dparticles.size(), 1);
    //EXPECT_TRUE(singleParticle3DType.m_3Dparticles.at(0) != nullptr);
    EXPECT_EQ(singleParticle3DType.m_cumulative_abundance, 1);
    EXPECT_EQ(singleParticle3DType.m_type, Constants::ParticleType);
}

TEST_F(TestRealSpaceBuilderUtils, test_getParticle3DTypeVector)
{
    ApplicationModels models;
    SampleModel* sampleModel = models.sampleModel();

    auto layout
        = dynamic_cast<ParticleLayoutItem*>(sampleModel->insertNewItem(Constants::ParticleLayoutType));

    auto particle1 = sampleModel->insertNewItem(Constants::ParticleType);
    auto particle2 = sampleModel->insertNewItem(Constants::ParticleType);
    auto particle3 = sampleModel->insertNewItem(Constants::ParticleType);

    sampleModel->moveItem(particle1, layout, -1, ParticleLayoutItem::T_PARTICLES);
    sampleModel->moveItem(particle2, layout, -1, ParticleLayoutItem::T_PARTICLES);
    sampleModel->moveItem(particle3, layout, -1, ParticleLayoutItem::T_PARTICLES);

    particle1->setItemValue(ParticleItem::P_ABUNDANCE, 5.0);
    particle2->setItemValue(ParticleItem::P_ABUNDANCE, 3.0);
    particle3->setItemValue(ParticleItem::P_ABUNDANCE, 2.0);

    double total_abundance = RealSpaceBuilderUtils::computeCumulativeAbundances(*layout).last();
    EXPECT_EQ(total_abundance, 10.0);

    particle1->setGroupProperty(ParticleItem::P_FORM_FACTOR, Constants::BoxType);
    particle2->setGroupProperty(ParticleItem::P_FORM_FACTOR, Constants::ConeType);
    particle3->setGroupProperty(ParticleItem::P_FORM_FACTOR, Constants::PyramidType);

    auto particle3DType_vector = RealSpaceBuilderUtils::getParticle3DTypeVector(*layout);

    EXPECT_EQ(particle3DType_vector.size(), 3);

    EXPECT_EQ(particle3DType_vector.at(0).m_3Dparticles.size(), 1);
    EXPECT_EQ(particle3DType_vector.at(0).m_cumulative_abundance, 0.5);
    EXPECT_EQ(particle3DType_vector.at(0).m_type, Constants::ParticleType);

    EXPECT_EQ((particle3DType_vector.at(1)).m_3Dparticles.size(), 1);
    EXPECT_EQ(particle3DType_vector.at(1).m_cumulative_abundance, 0.8);
    EXPECT_EQ(particle3DType_vector.at(1).m_type, Constants::ParticleType);

    EXPECT_EQ((particle3DType_vector.at(2)).m_3Dparticles.size(), 1);
    EXPECT_EQ(particle3DType_vector.at(2).m_cumulative_abundance, 1.0);
    EXPECT_EQ(particle3DType_vector.at(2).m_type, Constants::ParticleType);
}


#endif // TESTREALSPACEBUILDERUTILS_H
