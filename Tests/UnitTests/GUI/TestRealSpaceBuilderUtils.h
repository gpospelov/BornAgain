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
#include "RealSpaceModel.h"
#include "Particle3DContainer.h"

class TestRealSpaceBuilderUtils : public ::testing::Test
{
public:
    ~TestRealSpaceBuilderUtils();
};

TestRealSpaceBuilderUtils::~TestRealSpaceBuilderUtils() = default;

TEST_F(TestRealSpaceBuilderUtils, test_RealSpaceModelandParticle)
{
    RealSpaceModel realSpaceModel;

    auto cylinder3D = std::make_unique<RealSpace::Particles::Cylinder>(5, 10);
    QVector3D lattice_position1(0,0,0);
    cylinder3D->addTranslation(lattice_position1);
    realSpaceModel.add(cylinder3D.release());

// Causes a failure as one cannot add an already added particle to the model
//    QVector3D lattice_position2(10,10,10);
//    cylinder3D->addTranslation(lattice_position2);
//    realSpaceModel.add(cylinder3D.release());
}

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

TEST_F(TestRealSpaceBuilderUtils, test_Particle3DContainer)
{
    Particle3DContainer p1;

    EXPECT_EQ(p1.containerSize(), static_cast<size_t>(0));
    EXPECT_EQ(p1.cumulativeAbundance(), 0);
    EXPECT_EQ(p1.particleType(), "");

    // Create 3D cylinder using corresponding constructor RealSpace::Particles::Cylinder()
    auto cylinder3D = std::make_unique<RealSpace::Particles::Cylinder>(5, 10);

    // Associate it to a Particle3DContainer object
    p1.addParticle(cylinder3D.release());
    p1.setCumulativeAbundance(1);
    p1.setParticleType(Constants::ParticleType);

    EXPECT_EQ(p1.containerSize(), static_cast<size_t>(1));
    EXPECT_EQ(p1.cumulativeAbundance(), 1);
    EXPECT_EQ(p1.particleType(), Constants::ParticleType);

    RealSpaceModel realSpaceModel;


    // Test copy constructor
    // If copy constructor (DEEP copy) is not implemented then p2/p3 is basically
    // the same as p1 and cannot be added to the RealSpaceModel once p1 is added
    Particle3DContainer p2(p1);

    EXPECT_EQ(p2.containerSize(), static_cast<size_t>(1));
    EXPECT_EQ(p2.cumulativeAbundance(), 1);
    EXPECT_EQ(p2.particleType(), Constants::ParticleType);

    Particle3DContainer p3 = Particle3DContainer(p1);

    EXPECT_EQ(p3.containerSize(), static_cast<size_t>(1));
    EXPECT_EQ(p3.cumulativeAbundance(), 1);
    EXPECT_EQ(p3.particleType(), Constants::ParticleType);

    // Test copy assignment operator
    // If assignment operator (DEEP) is not implemented then p4 is basically
    // the same as p1 and cannot be added to the RealSpaceModel once p1 is added
    Particle3DContainer p4;
    p4 = p1;

    EXPECT_EQ(p4.containerSize(), static_cast<size_t>(1));
    EXPECT_EQ(p4.cumulativeAbundance(), 1);
    EXPECT_EQ(p4.particleType(), Constants::ParticleType);

    // Add particle to RealSpaceModel by first creating a unique instance of it and then
    // releasing (transfer ownership) to the model which deletes the new particle instance later on
    auto p1_unique = p1.createParticle(0);
    auto p2_unique = p2.createParticle(0);
    auto p3_unique = p3.createParticle(0);
    auto p4_unique = p4.createParticle(0);

    realSpaceModel.add(p1_unique.release());
    realSpaceModel.add(p2_unique.release());
    realSpaceModel.add(p3_unique.release());
    realSpaceModel.add(p4_unique.release());


    // Test move constructor
    Particle3DContainer p5(std::move(p4));

    // Test the contents of the Particle3DContainer being moved-from
    EXPECT_EQ(p4.containerSize(), static_cast<size_t>(0)); // move empties the std::vector container
    EXPECT_EQ(p4.cumulativeAbundance(), 1); // move doesn't affect int data member
    EXPECT_EQ(p4.particleType(), ""); // move empties the QString

    // Test the contents of the Particle3DContainer being moved-to
    EXPECT_EQ(p5.containerSize(), static_cast<size_t>(1));
    EXPECT_EQ(p5.cumulativeAbundance(), 1);
    EXPECT_EQ(p5.particleType(), Constants::ParticleType);

    auto p5_unique = p5.createParticle(0);
    realSpaceModel.add(p5_unique.release());

    Particle3DContainer p6 = Particle3DContainer(std::move(p5));

    EXPECT_EQ(p5.containerSize(), static_cast<size_t>(0));
    EXPECT_EQ(p5.cumulativeAbundance(), 1);
    EXPECT_EQ(p5.particleType(), "");

    EXPECT_EQ(p6.containerSize(), static_cast<size_t>(1));
    EXPECT_EQ(p6.cumulativeAbundance(), 1);
    EXPECT_EQ(p6.particleType(), Constants::ParticleType);

    auto p6_unique = p6.createParticle(0);
    realSpaceModel.add(p6_unique.release());

    //Test move assignment operator
    Particle3DContainer p7;
    p7 = std::move(p6);

    EXPECT_EQ(p6.containerSize(), static_cast<size_t>(0));
    EXPECT_EQ(p6.cumulativeAbundance(), 1);
    EXPECT_EQ(p6.particleType(), "");

    EXPECT_EQ(p7.containerSize(), static_cast<size_t>(1));
    EXPECT_EQ(p7.cumulativeAbundance(), 1);
    EXPECT_EQ(p7.particleType(), Constants::ParticleType);

    auto p7_unique = p7.createParticle(0);
    realSpaceModel.add(p7_unique.release());

    // The normal raw instances p1, p2 etc. get deleted by the destructor of Particle3DContainer
}

TEST_F(TestRealSpaceBuilderUtils, test_getSingleParticle3DContainer)
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

    // Create a 3D particle from particleItem and associate it to a Particle3DContainer object
    auto singleParticle3DContainer = RealSpaceBuilderUtils::getSingleParticle3DContainer(particle, 8);

    EXPECT_EQ(singleParticle3DContainer.containerSize(), static_cast<size_t>(1));
    //EXPECT_TRUE(singleParticle3DContainer.m_3Dparticles.at(0) != nullptr);
    EXPECT_EQ(singleParticle3DContainer.cumulativeAbundance(), 1);
    EXPECT_EQ(singleParticle3DContainer.particleType(), Constants::ParticleType);
}

TEST_F(TestRealSpaceBuilderUtils, test_getParticle3DContainerVector)
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

    auto particle3DContainer_vector = RealSpaceBuilderUtils::getParticle3DContainerVector(*layout);

    EXPECT_EQ(particle3DContainer_vector.size(), static_cast<size_t>(3));

    EXPECT_EQ(particle3DContainer_vector.at(0).containerSize(), static_cast<size_t>(1));
    EXPECT_EQ(particle3DContainer_vector.at(0).cumulativeAbundance(), 0.5);
    EXPECT_EQ(particle3DContainer_vector.at(0).particleType(), Constants::ParticleType);

    EXPECT_EQ(particle3DContainer_vector.at(1).containerSize(), static_cast<size_t>(1));
    EXPECT_EQ(particle3DContainer_vector.at(1).cumulativeAbundance(), 0.8);
    EXPECT_EQ(particle3DContainer_vector.at(1).particleType(), Constants::ParticleType);

    EXPECT_EQ(particle3DContainer_vector.at(2).containerSize(), static_cast<size_t>(1));
    EXPECT_EQ(particle3DContainer_vector.at(2).cumulativeAbundance(), 1.0);
    EXPECT_EQ(particle3DContainer_vector.at(2).particleType(), Constants::ParticleType);
}


#endif // TESTREALSPACEBUILDERUTILS_H
