#include <QtTest>
#include "GroupInfo.h"
#include "GroupItem.h"
#include "GroupPropertyRegistry.h"
#include "GUIHelpers.h"
#include "verify_throw_macro.h"

class TestGroupItem : public QObject {
    Q_OBJECT

private slots:
    void test_groupInfo();
    void test_CreateGroup();
    void test_groupPropertyWithDisplayNames();
};

inline void TestGroupItem::test_groupInfo()
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

inline void TestGroupItem::test_CreateGroup()
{
    GroupInfo groupInfo = GroupPropertyRegistry::groupInfo(Constants::DistributionGroup);
    QCOMPARE(groupInfo.defaultType(), Constants::DistributionGaussianType);

    GroupItem groupItem;
    QCOMPARE(groupItem.children().size(), 0);
    QVERIFY(groupItem.currentItem() == nullptr);

    // setting group property and checking currentItem
    groupItem.setGroupInfo(groupInfo);
    QCOMPARE(groupItem.children().size(), 1);
    QCOMPARE(groupItem.children()[0], groupItem.currentItem());
    SessionItem *cosineItem = groupItem.currentItem();
    QCOMPARE(cosineItem->modelType(), Constants::DistributionGaussianType);

    // setting group info twice
    QVERIFY_THROW(groupItem.setGroupInfo(groupInfo), GUIHelpers::Error);

    // changing current item
    SessionItem *newItem = groupItem.setCurrentType(Constants::DistributionNoneType);
    QCOMPARE(newItem, groupItem.currentItem());
    QCOMPARE(newItem->modelType(), Constants::DistributionNoneType);
    QCOMPARE(groupItem.children().size(), 2);

    // returning back to previous item
    QCOMPARE(groupItem.setCurrentType(Constants::DistributionGaussianType), cosineItem);
    QCOMPARE(groupItem.currentItem(), cosineItem);
    QCOMPARE(groupItem.children().size(), 2);
}

//! Checking that GroupProperty stays functional if displayName of currentItem is changed.

inline void TestGroupItem::test_groupPropertyWithDisplayNames()
{
    GroupInfo groupInfo = GroupPropertyRegistry::groupInfo(Constants::DistributionGroup);

    GroupItem groupItem;
    groupItem.setGroupInfo(groupInfo);

    SessionItem *cosineItem = groupItem.currentItem();
    cosineItem->setDisplayName(Constants::DistributionCosineType+QString::number(0));

    QCOMPARE(groupItem.currentItem(), cosineItem);
}

