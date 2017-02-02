#include <QtTest>
#include "SampleModel.h"
#include "ParticleDistributionItem.h"
#include "ComboProperty.h"
#include "ParticleItem.h"

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
    QCOMPARE(prop.getValues(), QStringList() << QStringLiteral("None"));
    QCOMPARE(prop.getValue(), QStringLiteral("None"));
    QVERIFY(prop.getCachedValue().isEmpty());
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
    QCOMPARE(prop.getValue(), QStringLiteral("None"));

    // changing formfactor of the particle
    particle->getGroupItem(ParticleItem::P_FORM_FACTOR, Constants::BoxType);

    qDebug() << expectedBoxParams << prop.getValues();
    prop = dist->getItemValue(ParticleDistributionItem::P_DISTRIBUTED_PARAMETER)
                    .value<ComboProperty>();

    QCOMPARE(prop.getValues(), expectedAnisoParams);
    QCOMPARE(prop.getValue(), QStringLiteral("None"));
}
