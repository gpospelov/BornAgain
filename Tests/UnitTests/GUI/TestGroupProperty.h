#include <QtTest>
#include <QDebug>
#include "GroupItem.h"
#include "GroupPropertyRegistry.h"
#include "GUIHelpers.h"
#include "verify_throw_macro.h"

class TestGroupProperty : public QObject {
    Q_OBJECT

private slots:
    void test_CreateGroup();
};

inline void TestGroupProperty::test_CreateGroup()
{
    GroupProperty_t property = GroupPropertyRegistry::createGroupProperty(
        "MyGroupProperty", Constants::DistributionGroup);

    QCOMPARE(property->getCurrentType(), Constants::DistributionCosineType);

    GroupItem groupItem;
    QCOMPARE(groupItem.childItems().size(), 0);
    QVERIFY(groupItem.currentItem() == nullptr);

    // setting group property
    groupItem.setGroup(property);
    QCOMPARE(groupItem.childItems().size(), 1);
    QCOMPARE(groupItem.childItems()[0], groupItem.currentItem());
    QCOMPARE(groupItem.currentItem()->modelType(), Constants::DistributionCosineType);

    // setting group property twice
    QVERIFY_THROW(groupItem.setGroup(property), GUIHelpers::Error);

    // changing current item
    SessionItem *newItem = groupItem.setCurrentType(Constants::DistributionNoneType);
    QCOMPARE(newItem, groupItem.currentItem());
    QCOMPARE(newItem->modelType(), Constants::DistributionNoneType);
    QCOMPARE(groupItem.childItems().size(), 2);

}

//GroupProperty_t group_property = item->group();
//group_property->setCurrentType(value);
//return group_property->getCurrentItem();
