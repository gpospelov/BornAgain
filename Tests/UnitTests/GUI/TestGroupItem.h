#include <QtTest>
#include "test_utils.h"
#include "GroupInfo.h"
#include "GroupItem.h"
#include "ComboProperty.h"
#include "GroupPropertyRegistry.h"
#include "GUIHelpers.h"
#include "SessionModel.h"

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
    SessionModel model("TestModel");

    GroupInfo groupInfo = GroupPropertyRegistry::groupInfo(Constants::FormFactorGroup);
    QCOMPARE(groupInfo.defaultType(), Constants::CylinderType);

    auto groupItem = dynamic_cast<GroupItem*>(model.insertNewItem(Constants::GroupItemType));
    QCOMPARE(groupItem->children().size(), 0);
    QVERIFY(groupItem->currentItem() == nullptr);
    QVERIFY(groupItem->value().isValid() == false);

    // setting group property and checking currentItem
    groupItem->setGroupInfo(groupInfo);

    // setting group info twice
    QVERIFY_THROW(groupItem->setGroupInfo(groupInfo), GUIHelpers::Error);

    // checking current item
    QCOMPARE(groupItem->children().size(), 1);
    QCOMPARE(groupItem->children()[0], groupItem->currentItem());
    SessionItem *ffItem = groupItem->currentItem();
    QCOMPARE(ffItem->modelType(), Constants::CylinderType);

    // checking current variant
    QVariant value = groupItem->value();
    QVERIFY(value.canConvert<ComboProperty>() == true);
    ComboProperty combo = value.value<ComboProperty>();
    QCOMPARE(combo.getValues(), groupInfo.itemLabels());
    int index = groupInfo.itemTypes().indexOf(groupInfo.defaultType());
    QCOMPARE(combo.currentIndex(), index);
    QCOMPARE(combo.getValue(), groupInfo.itemLabels().at(index));

    // changing current item
    SessionItem *newItem = groupItem->setCurrentType(Constants::FullSphereType);
    QCOMPARE(newItem, groupItem->currentItem());
    QCOMPARE(newItem->modelType(), Constants::FullSphereType);
    QCOMPARE(groupItem->children().size(), 2);

    // checking current variant
    combo = groupItem->value().value<ComboProperty>();
    QCOMPARE(combo.getValues(), groupInfo.itemLabels());
    index = groupInfo.itemTypes().indexOf(Constants::FullSphereType);
    QCOMPARE(combo.currentIndex(), index);
    QCOMPARE(combo.getValue(), groupInfo.itemLabels().at(index));

    // returning back to previous item
    QCOMPARE(groupItem->setCurrentType(Constants::CylinderType), ffItem);
    QCOMPARE(groupItem->currentItem(), ffItem);
    QCOMPARE(groupItem->children().size(), 2);
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

