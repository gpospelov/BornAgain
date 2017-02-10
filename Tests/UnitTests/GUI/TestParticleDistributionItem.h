#include <QtTest>
#include "SampleModel.h"
#include "ParticleDistributionItem.h"
#include "ComboProperty.h"
#include "ParticleItem.h"
#include "Distributions.h"
#include "ParticleDistribution.h"
#include "TransformFromDomain.h"
#include "Particle.h"
#include "HomogeneousMaterial.h"
#include "MaterialModel.h"
#include "DistributionItems.h"
#include "MaterialEditor.h"
#include "RealLimitsItems.h"

namespace {
    const QStringList expectedAnisoParams = {
        "None", "Particle/AnisoPyramid/Length", "Particle/AnisoPyramid/Width",
        "Particle/AnisoPyramid/Height", "Particle/AnisoPyramid/Alpha",
        "Particle/Position Offset/X", "Particle/Position Offset/Y", "Particle/Position Offset/Z"};

    const QStringList expectedBoxParams = {
        "None", "Particle/Box/Length", "Particle/Box/Width",
        "Particle/Box/Height", "Particle/Position Offset/X",
        "Particle/Position Offset/Y", "Particle/Position Offset/Z"};
}


class TestParticleDistributionItem : public QObject {
    Q_OBJECT

private slots:
    void test_InitialState();
    void test_AddParticle();
    void test_FromDomain();
    void test_FromDomainWithLimits();
};

inline void TestParticleDistributionItem::test_InitialState()
{
    SampleModel model;
    SessionItem *distItem = model.insertNewItem(Constants::ParticleDistributionType);

    QCOMPARE(distItem->displayName(), Constants::ParticleDistributionType);
    QCOMPARE(distItem->displayName(), distItem->itemName());

    // xpos, ypos, P_ABUNDANCE, P_DISTRIBUTION, P_DISTRIBUTED_PARAMETER
    QCOMPARE(distItem->childItems().size(), 5);

    QCOMPARE(distItem->defaultTag(), ParticleDistributionItem::T_PARTICLES);

    QCOMPARE(distItem->acceptableDefaultItemTypes(),
             QVector<QString>() << Constants::ParticleType
             << Constants::ParticleCoreShellType << Constants::ParticleCompositionType);

    ComboProperty prop = distItem->getItemValue(ParticleDistributionItem::P_DISTRIBUTED_PARAMETER)
                    .value<ComboProperty>();
    QCOMPARE(prop.getValues(), QStringList() << ParticleDistributionItem::NO_SELECTION);
    QCOMPARE(prop.getValue(), ParticleDistributionItem::NO_SELECTION);
}

inline void TestParticleDistributionItem::test_AddParticle()
{
    SampleModel model;
    SessionItem *dist = model.insertNewItem(Constants::ParticleDistributionType);

    // adding default particle and checking list of available parameters
    SessionItem *particle = model.insertNewItem(Constants::ParticleType, dist->index());

    QCOMPARE(dist->getItems().size(), 1);

    ComboProperty prop = dist->getItemValue(ParticleDistributionItem::P_DISTRIBUTED_PARAMETER)
                    .value<ComboProperty>();

    QCOMPARE(prop.getValues(), expectedAnisoParams);
    QCOMPARE(prop.getValue(), ParticleDistributionItem::NO_SELECTION);

    // changing formfactor of the particle
    particle->setGroupProperty(ParticleItem::P_FORM_FACTOR, Constants::BoxType);

    prop = dist->getItemValue(ParticleDistributionItem::P_DISTRIBUTED_PARAMETER)
                    .value<ComboProperty>();

    QCOMPARE(prop.getValues(), expectedBoxParams);
    QCOMPARE(prop.getValue(), ParticleDistributionItem::NO_SELECTION);
}

inline void TestParticleDistributionItem::test_FromDomain()
{
    const std::string pattern("Particle/Cylinder/Radius");

    // creating domain distribution
    FormFactorCylinder cylinder(1.0, 2.0);
    Particle particle(HomogeneousMaterial("Particle", 6e-4, 2e-8), cylinder);
    DistributionGaussian gauss(1.0, 0.1);
    ParameterDistribution par_distr(pattern, gauss, 100, 3.0);

    ParticleDistribution particle_collection(particle, par_distr);

    // creating GUI distribution
    SampleModel model;
    SessionItem *distItem = model.insertNewItem(Constants::ParticleDistributionType);
    SessionItem *particleItem = model.insertNewItem(Constants::ParticleType, distItem->index());

    // Sets it from domain
    TransformFromDomain::setItemFromSample(distItem, &particle_collection);

    ComboProperty prop = distItem->getItemValue(ParticleDistributionItem::P_DISTRIBUTED_PARAMETER)
                    .value<ComboProperty>();

    QCOMPARE(prop.getValue(), ParticleDistributionItem::NO_SELECTION);

    // changing particle type and check that distribution picked up domain name
    particleItem->setGroupProperty(ParticleItem::P_FORM_FACTOR, Constants::CylinderType);
    prop = distItem->getItemValue(ParticleDistributionItem::P_DISTRIBUTED_PARAMETER)
                    .value<ComboProperty>();

    QCOMPARE(prop.getValue(), QString::fromStdString(pattern));
}

inline void TestParticleDistributionItem::test_FromDomainWithLimits()
{
    const std::string pattern("Particle/Cylinder/Radius");

    // creating domain distribution
    FormFactorCylinder cylinder(1.0, 2.0);
    Particle particle(HomogeneousMaterial("Particle", 6e-4, 2e-8), cylinder);
    DistributionGaussian gauss(1.0, 0.1);

    RealLimits domainLimits = RealLimits::limited(1.0, 2.0);
    ParameterDistribution par_distr(pattern, gauss, 100, 3.0, domainLimits);

    ParticleDistribution particle_collection(particle, par_distr);

    // creating GUI distribution
    SampleModel model;
    SessionItem *partDistItem = model.insertNewItem(Constants::ParticleDistributionType);
    model.insertNewItem(Constants::ParticleType, partDistItem->index());

//    // Sets it from domain
    TransformFromDomain::setItemFromSample(partDistItem, &particle_collection);

    SessionItem *distItem = partDistItem->getGroupItem(ParticleDistributionItem::P_DISTRIBUTION);
    Q_ASSERT(distItem);
    RealLimitsItem* limitsItem = dynamic_cast<RealLimitsItem*>(
            distItem->getGroupItem(DistributionItem::P_LIMITS));
    Q_ASSERT(limitsItem);

    QCOMPARE(limitsItem->createRealLimits(), domainLimits);
}

