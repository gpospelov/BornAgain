#include "ParticleItem.h"
#include "SampleModel.h"
#include "SessionItem.h"
#include "GroupItem.h"
#include "ParticleCompositionItem.h"
#include "ParticleDistributionItem.h"
#include <QtTest>

class TestParticleItem : public QObject
{
    Q_OBJECT

private slots:
    void test_InitialState();
    void test_compositionContext();
    void test_distributionContext();
};

inline void TestParticleItem::test_InitialState()
{
    SampleModel model;
    SessionItem* item = model.insertNewItem(Constants::ParticleType);

    QCOMPARE(item->displayName(), Constants::ParticleType);
    QCOMPARE(item->displayName(), item->itemName());
    // xpos, ypos, P_FORM_FACTOR, P_MATERIAL, P_ABUNDANCE, P_POSITION
    QCOMPARE(item->childItems().size(), 6);
    QCOMPARE(item->defaultTag(), ParticleItem::T_TRANSFORMATION);

    GroupItem* group = dynamic_cast<GroupItem*>(item->getItem(ParticleItem::P_FORM_FACTOR));
    QCOMPARE(group->displayName(), ParticleItem::P_FORM_FACTOR);
    QCOMPARE(group->childItems().size(), 1);
}

inline void TestParticleItem::test_compositionContext()
{
    SampleModel model;
    SessionItem* particle = model.insertNewItem(Constants::ParticleType);
    particle->setItemValue(ParticleItem::P_ABUNDANCE, 0.2);
    QVERIFY(particle->getItem(ParticleItem::P_ABUNDANCE)->isEnabled() == true);
    QCOMPARE(particle->getItemValue(ParticleItem::P_ABUNDANCE).toDouble(), 0.2);

    // adding particle to composition, checking that abundance is default
    SessionItem* composition = model.insertNewItem(Constants::ParticleCompositionType);
    model.moveParameterizedItem(particle, composition, -1, ParticleCompositionItem::T_PARTICLES);
    QVERIFY(particle->getItem(ParticleItem::P_ABUNDANCE)->isEnabled() == false);
    QCOMPARE(particle->getItemValue(ParticleItem::P_ABUNDANCE).toDouble(), 1.0);

    // removing particle, checking that abundance is enabled again
    composition->takeRow(particle->parentRow());
    QVERIFY(particle->getItem(ParticleItem::P_ABUNDANCE)->isEnabled() == true);
    delete particle;
}

inline void TestParticleItem::test_distributionContext()
{
    SampleModel model;
    SessionItem* particle = model.insertNewItem(Constants::ParticleType);
    particle->setItemValue(ParticleItem::P_ABUNDANCE, 0.2);
    QVERIFY(particle->getItem(ParticleItem::P_ABUNDANCE)->isEnabled() == true);
    QCOMPARE(particle->getItemValue(ParticleItem::P_ABUNDANCE).toDouble(), 0.2);

    // adding particle to distribution, checking that abundance is default
    SessionItem* distribution = model.insertNewItem(Constants::ParticleDistributionType);
    model.moveParameterizedItem(particle, distribution, -1, ParticleDistributionItem::T_PARTICLES);
    QVERIFY(particle->getItem(ParticleItem::P_ABUNDANCE)->isEnabled() == false);
    QCOMPARE(particle->getItemValue(ParticleItem::P_ABUNDANCE).toDouble(), 1.0);

    // removing particle, checking that abundance is enabled again
    distribution->takeRow(particle->parentRow());
    QVERIFY(particle->getItem(ParticleItem::P_ABUNDANCE)->isEnabled() == true);
    delete particle;
}

