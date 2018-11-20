#include "google_test.h"
#include "ComboProperty.h"
#include "DistributionItems.h"
#include "Distributions.h"
#include "MaterialEditor.h"
#include "MaterialFactoryFuncs.h"
#include "MaterialModel.h"
#include "Particle.h"
#include "ParticleDistribution.h"
#include "ParticleDistributionItem.h"
#include "ParticleItem.h"
#include "RealLimitsItems.h"
#include "SampleModel.h"
#include "TransformFromDomain.h"
#include "FormFactors.h"
#include <QXmlStreamWriter>

namespace
{
const QStringList expectedCylinderParams = {"None",
                                            "Particle/Cylinder/Radius",
                                            "Particle/Cylinder/Height",
                                            "Particle/Position Offset/X",
                                            "Particle/Position Offset/Y",
                                            "Particle/Position Offset/Z"};

const QStringList expectedBoxParams = {"None",
                                       "Particle/Box/Length",
                                       "Particle/Box/Width",
                                       "Particle/Box/Height",
                                       "Particle/Position Offset/X",
                                       "Particle/Position Offset/Y",
                                       "Particle/Position Offset/Z"};
}

class TestParticleDistributionItem : public ::testing::Test
{
public:
    ~TestParticleDistributionItem();
};

TestParticleDistributionItem::~TestParticleDistributionItem() = default;

TEST_F(TestParticleDistributionItem, test_InitialState)
{
    SampleModel model;
    SessionItem* distItem = model.insertNewItem(Constants::ParticleDistributionType);

    EXPECT_EQ(distItem->displayName(), Constants::ParticleDistributionType);
    EXPECT_EQ(distItem->displayName(), distItem->itemName());

    // xpos, ypos, P_ABUNDANCE, P_DISTRIBUTION, P_DISTRIBUTED_PARAMETER
    EXPECT_EQ(distItem->children().size(), 6);

    EXPECT_EQ(distItem->defaultTag(), ParticleDistributionItem::T_PARTICLES);

    EXPECT_EQ(distItem->acceptableDefaultItemTypes(),
              QVector<QString>() << Constants::ParticleType << Constants::ParticleCoreShellType
                                 << Constants::ParticleCompositionType
                                 << Constants::MesoCrystalType);

    // main parameter
    ComboProperty prop = distItem->getItemValue(ParticleDistributionItem::P_DISTRIBUTED_PARAMETER)
                             .value<ComboProperty>();
    EXPECT_EQ(prop.getValues(), QStringList() << ParticleDistributionItem::NO_SELECTION);
    EXPECT_EQ(prop.getValue(), ParticleDistributionItem::NO_SELECTION);

    // linked parameter
    prop = distItem->getItemValue(ParticleDistributionItem::P_LINKED_PARAMETER)
                             .value<ComboProperty>();
    EXPECT_EQ(prop.getValues(), QStringList() << ParticleDistributionItem::NO_SELECTION);
    EXPECT_EQ(prop.getValue(), ParticleDistributionItem::NO_SELECTION);
}

TEST_F(TestParticleDistributionItem, test_AddParticle)
{
    SampleModel model;
    SessionItem* dist = model.insertNewItem(Constants::ParticleDistributionType);

    // adding default particle and checking list of available parameters
    SessionItem* particle = model.insertNewItem(Constants::ParticleType, dist->index());

    EXPECT_EQ(dist->getItems().size(), 1);

    ComboProperty prop = dist->getItemValue(ParticleDistributionItem::P_DISTRIBUTED_PARAMETER)
                             .value<ComboProperty>();

    EXPECT_EQ(prop.getValues(), expectedCylinderParams);
    EXPECT_EQ(prop.getValue(), ParticleDistributionItem::NO_SELECTION);

    // linked parameter
    prop = dist->getItemValue(ParticleDistributionItem::P_LINKED_PARAMETER)
                             .value<ComboProperty>();

    EXPECT_EQ(prop.getValues(), expectedCylinderParams);
    EXPECT_EQ(prop.getValue(), ParticleDistributionItem::NO_SELECTION);

    // changing formfactor of the particle
    particle->setGroupProperty(ParticleItem::P_FORM_FACTOR, Constants::BoxType);

    prop = dist->getItemValue(ParticleDistributionItem::P_DISTRIBUTED_PARAMETER)
               .value<ComboProperty>();

    EXPECT_EQ(prop.getValues(), expectedBoxParams);
    EXPECT_EQ(prop.getValue(), ParticleDistributionItem::NO_SELECTION);
}

TEST_F(TestParticleDistributionItem, test_FromDomain)
{
    const std::string pattern("/Particle/Cylinder/Radius");

    // creating domain distribution
    FormFactorCylinder cylinder(1.0, 2.0);
    Particle particle(HomogeneousMaterial("Particle", 6e-4, 2e-8), cylinder);
    DistributionGaussian gauss(1.0, 0.1);
    ParameterDistribution par_distr(pattern, gauss, 100, 3.0);

    ParticleDistribution particle_collection(particle, par_distr);

    // creating GUI distribution
    SampleModel model;
    SessionItem* distItem = model.insertNewItem(Constants::ParticleDistributionType);
    SessionItem* particleItem = model.insertNewItem(Constants::ParticleType, distItem->index());

    particleItem->setGroupProperty(ParticleItem::P_FORM_FACTOR, Constants::AnisoPyramidType);

    // Sets it from domain
    TransformFromDomain::setParticleDistributionItem(distItem, particle_collection);

    ComboProperty prop = distItem->getItemValue(ParticleDistributionItem::P_DISTRIBUTED_PARAMETER)
                             .value<ComboProperty>();

    EXPECT_EQ(prop.getValue(), ParticleDistributionItem::NO_SELECTION);

    // changing particle type and check that distribution picked up domain name
    particleItem->setGroupProperty(ParticleItem::P_FORM_FACTOR, Constants::CylinderType);
    prop = distItem->getItemValue(ParticleDistributionItem::P_DISTRIBUTED_PARAMETER)
               .value<ComboProperty>();

    EXPECT_EQ(prop.getValue(), QString("Particle/Cylinder/Radius"));
}

TEST_F(TestParticleDistributionItem, test_FromDomainWithLimits)
{
    const std::string pattern("/Particle/Cylinder/Radius");

    // creating domain distribution
    FormFactorCylinder cylinder(1.0, 2.0);
    Particle particle(HomogeneousMaterial("Particle", 6e-4, 2e-8), cylinder);
    DistributionGaussian gauss(1.0, 0.1);

    RealLimits domainLimits = RealLimits::limited(1.0, 2.0);
    ParameterDistribution par_distr(pattern, gauss, 100, 3.0, domainLimits);

    ParticleDistribution particle_collection(particle, par_distr);

    // creating GUI distribution
    SampleModel model;
    SessionItem* partDistItem = model.insertNewItem(Constants::ParticleDistributionType);
    model.insertNewItem(Constants::ParticleType, partDistItem->index());

    //    // Sets it from domain
    TransformFromDomain::setParticleDistributionItem(partDistItem, particle_collection);

    SessionItem* distItem = partDistItem->getGroupItem(ParticleDistributionItem::P_DISTRIBUTION);
    Q_ASSERT(distItem);
    RealLimitsItem* limitsItem
        = dynamic_cast<RealLimitsItem*>(distItem->getGroupItem(DistributionItem::P_LIMITS));
    Q_ASSERT(limitsItem);

    EXPECT_EQ(limitsItem->createRealLimits(), domainLimits);
}

TEST_F(TestParticleDistributionItem, test_Clone)
{
    std::unique_ptr<MaterialModel> P_materialModel(new MaterialModel());

    SampleModel model1;
    SessionItem* dist = model1.insertNewItem(Constants::ParticleDistributionType);
    model1.insertNewItem(Constants::ParticleType, dist->index());

    QString buffer1;
    QXmlStreamWriter writer1(&buffer1);
    model1.writeTo(&writer1);

    std::unique_ptr<SampleModel> model2(model1.createCopy());
    QString buffer2;
    QXmlStreamWriter writer2(&buffer2);
    model2->writeTo(&writer2);

    EXPECT_EQ(buffer1, buffer2);
}
