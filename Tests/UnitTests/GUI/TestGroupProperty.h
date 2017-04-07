#include <QtTest>
#include "GroupInfo.h"
#include "GroupItem.h"
#include "GroupPropertyRegistry.h"
#include "GUIHelpers.h"
#include "verify_throw_macro.h"

class TestGroupProperty : public QObject {
    Q_OBJECT

private slots:
    void test_groupInfo();
    void test_groupProperty();
    void test_CreateGroup();
    void test_groupPropertyWithDisplayNames();
};

inline void TestGroupProperty::test_groupInfo()
{
    GroupInfo info("Group");
    info.add("BBB", "b_label");
    info.add("AAA", "a_label");
    info.add("CCC", "c_label");
    info.setDefaultType("AAA");

    // sorted group (default behavior)
    QCOMPARE(info.groupType(), QString("Group"));
    QCOMPARE(info.defaultType(), QString("AAA"));
    QCOMPARE(info.itemTypes(), QStringList() << "AAA" << "BBB" << "CCC");
    QCOMPARE(info.itemLabels(), QStringList() << "a_label" << "b_label" << "c_label");

    // unsorted group
    info = GroupInfo("Group2", false);
    info.add("BBB2", "b_label2");
    info.add("AAA2", "a_label2");
    info.add("CCC2", "c_label2");
    info.setDefaultType("AAA2");
    QCOMPARE(info.defaultType(), QString("AAA2"));
    QCOMPARE(info.itemTypes(), QStringList() << "BBB2" << "AAA2" << "CCC2");
    QCOMPARE(info.itemLabels(), QStringList() << "b_label2" << "a_label2" << "c_label2");

    // attempt to set non-existing default type
    QVERIFY_THROW(info.setDefaultType("XXX"), GUIHelpers::Error);

    // attempt to add same info twice
    QVERIFY_THROW(info.add("CCC2", "c_label2"), GUIHelpers::Error);
}

inline void TestGroupProperty::test_groupProperty()
{
    GroupProperty_t property = GroupPropertyRegistry::createGroupProperty(
        Constants::DistributionGroup);

    QCOMPARE(property->currentType(), Constants::DistributionGaussianType);
    QVERIFY(property->currentItem() == nullptr);

}


inline void TestGroupProperty::test_CreateGroup()
{
    GroupProperty_t property = GroupPropertyRegistry::createGroupProperty(
        Constants::DistributionGroup);

    QCOMPARE(property->currentType(), Constants::DistributionGaussianType);

    GroupItem groupItem;
    QCOMPARE(groupItem.childItems().size(), 0);
    QVERIFY(groupItem.currentItem() == nullptr);

    // setting group property and checking currentItem
    groupItem.setGroup(property);
    QCOMPARE(groupItem.childItems().size(), 1);
    QCOMPARE(groupItem.childItems()[0], groupItem.currentItem());
    SessionItem *cosineItem = groupItem.currentItem();
    QCOMPARE(cosineItem->modelType(), Constants::DistributionGaussianType);
    QCOMPARE(property->currentItem(), cosineItem);

    // setting group property twice
    QVERIFY_THROW(groupItem.setGroup(property), GUIHelpers::Error);

    // changing current item
    SessionItem *newItem = groupItem.setCurrentType(Constants::DistributionNoneType);
    QCOMPARE(newItem, groupItem.currentItem());
    QCOMPARE(newItem->modelType(), Constants::DistributionNoneType);
    QCOMPARE(groupItem.childItems().size(), 2);

    // returning back to previous item
    QCOMPARE(groupItem.setCurrentType(Constants::DistributionGaussianType), cosineItem);
    QCOMPARE(groupItem.currentItem(), cosineItem);
    QCOMPARE(groupItem.childItems().size(), 2);
}

//! Checking that GroupProperty stays functional if displayName of currentItem is changed.

inline void TestGroupProperty::test_groupPropertyWithDisplayNames()
{
    GroupProperty_t property = GroupPropertyRegistry::createGroupProperty(
        Constants::DistributionGroup);

    GroupItem groupItem;
    groupItem.setGroup(property);

    SessionItem *cosineItem = groupItem.currentItem();
    cosineItem->setDisplayName(Constants::DistributionCosineType+QString::number(0));

    QCOMPARE(groupItem.currentItem(), cosineItem);
}

