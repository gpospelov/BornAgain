#include <QtTest>
#include "ComponentUtils.h"
#include "SessionItem.h"
#include "SessionModel.h"
#include "item_constants.h"
#include "ParticleItem.h"
#include "FormFactorItems.h"
#include <QDebug>

class TestComponentUtils : public QObject
{
    Q_OBJECT
public:

private slots:
    void test_componentItems();
    void test_componentItemsFFChange();
};

//! Testing component items of particle item.

inline void TestComponentUtils::test_componentItems()
{
    SessionModel model("TestModel");

    SessionItem* particle = model.insertNewItem(Constants::ParticleType);
    SessionItem* group = particle->getItem(ParticleItem::P_FORM_FACTOR);
    SessionItem* ffItem = particle->getGroupItem(ParticleItem::P_FORM_FACTOR);

    QList<const SessionItem*> expectedList = QList<const SessionItem*> ()
            << group
            << ffItem->getItem(CylinderItem::P_RADIUS)
            << ffItem->getItem(CylinderItem::P_HEIGHT)
            << particle->getItem(ParticleItem::P_MATERIAL)
            << particle->getItem(ParticleItem::P_ABUNDANCE)
            << particle->getItem(ParticleItem::P_POSITION);

    auto itemList = ComponentUtils::componentItems(*particle);
    QCOMPARE(itemList.size(), 6);
    QCOMPARE(itemList, expectedList);
}

inline void TestComponentUtils::test_componentItemsFFChange()
{
    SessionModel model("TestModel");

    SessionItem* particle = model.insertNewItem(Constants::ParticleType);
    SessionItem* group = particle->getItem(ParticleItem::P_FORM_FACTOR);

    particle->setGroupProperty(ParticleItem::P_FORM_FACTOR, Constants::FullSphereType);
    SessionItem* sphereItem = particle->getGroupItem(ParticleItem::P_FORM_FACTOR);

    QList<const SessionItem*> expectedList = QList<const SessionItem*> ()
            << group
            << sphereItem->getItem(FullSphereItem::P_RADIUS)
            << particle->getItem(ParticleItem::P_MATERIAL)
            << particle->getItem(ParticleItem::P_ABUNDANCE)
            << particle->getItem(ParticleItem::P_POSITION);

    auto itemList = ComponentUtils::componentItems(*particle);
    QCOMPARE(itemList.size(), 5);
    QCOMPARE(itemList, expectedList);
}
