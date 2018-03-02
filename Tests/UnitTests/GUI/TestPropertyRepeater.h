#include "AxesItems.h"
#include "IntensityDataItem.h"
#include "PropertyRepeater.h"
#include "SessionModel.h"
#include "google_test.h"
#include "item_constants.h"

namespace
{

IntensityDataItem* createData(SessionModel& model)
{
    return dynamic_cast<IntensityDataItem*>(model.insertNewItem(Constants::IntensityDataType));
}

BasicAxisItem* createAxis(SessionModel& model)
{
    return dynamic_cast<BasicAxisItem*>(model.insertNewItem(Constants::BasicAxisType));
}
}

class TestPropertyRepeater : public ::testing::Test
{
public:
    ~TestPropertyRepeater();
};

TestPropertyRepeater::~TestPropertyRepeater() = default;

//! Repeater handles two items.

TEST_F(TestPropertyRepeater, test_twoItems)
{
    SessionModel model("test");

    auto item1 = createAxis(model);
    auto item2 = createAxis(model);

    item1->setItemValue(BasicAxisItem::P_MAX, 2.0);
    item2->setItemValue(BasicAxisItem::P_MAX, 3.0);

    PropertyRepeater repeater;
    repeater.addItem(item1);
    repeater.addItem(item2);

    // adding items to the repeater do not change values
    EXPECT_EQ(item1->getItemValue(BasicAxisItem::P_MAX).toDouble(), 2.0);
    EXPECT_EQ(item2->getItemValue(BasicAxisItem::P_MAX).toDouble(), 3.0);

    // change of the value of one item leads to the change in another
    item1->setItemValue(BasicAxisItem::P_MAX, 4.0);
    EXPECT_EQ(item1->getItemValue(BasicAxisItem::P_MAX).toDouble(), 4.0);
    EXPECT_EQ(item2->getItemValue(BasicAxisItem::P_MAX).toDouble(), 4.0);

    // clearing repeater will stop update
    repeater.clear();
    item1->setItemValue(BasicAxisItem::P_MAX, 5.0);
    EXPECT_EQ(item1->getItemValue(BasicAxisItem::P_MAX).toDouble(), 5.0);
    EXPECT_EQ(item2->getItemValue(BasicAxisItem::P_MAX).toDouble(), 4.0);
}

//! Repeater handles three items.

TEST_F(TestPropertyRepeater, test_threeItems)
{
    SessionModel model("test");

    auto item1 = createAxis(model);
    auto item2 = createAxis(model);
    auto item3 = createAxis(model);

    item1->setItemValue(BasicAxisItem::P_MAX, 1.0);
    item2->setItemValue(BasicAxisItem::P_MAX, 2.0);
    item3->setItemValue(BasicAxisItem::P_MAX, 3.0);

    PropertyRepeater repeater;
    repeater.addItem(item1);
    repeater.addItem(item2);
    repeater.addItem(item3);

    // change of the value of one item leads to the change in two another
    item1->setItemValue(BasicAxisItem::P_MAX, 4.0);
    EXPECT_EQ(item1->getItemValue(BasicAxisItem::P_MAX).toDouble(), 4.0);
    EXPECT_EQ(item2->getItemValue(BasicAxisItem::P_MAX).toDouble(), 4.0);
    EXPECT_EQ(item3->getItemValue(BasicAxisItem::P_MAX).toDouble(), 4.0);
}

//! Checks if item with active properties specified receives updates only for these properties.

TEST_F(TestPropertyRepeater, test_filteredBroadcast)
{
    SessionModel model("test");

    auto item1 = createAxis(model);
    auto item2 = createAxis(model);
    auto item3 = createAxis(model);

    item1->setItemValue(BasicAxisItem::P_MIN, 0.0);
    item2->setItemValue(BasicAxisItem::P_MIN, 0.0);
    item3->setItemValue(BasicAxisItem::P_MIN, 0.0);
    item1->setItemValue(BasicAxisItem::P_MAX, 1.0);
    item2->setItemValue(BasicAxisItem::P_MAX, 1.0);
    item3->setItemValue(BasicAxisItem::P_MAX, 1.0);

    QStringList activeProperties = QStringList() << BasicAxisItem::P_MAX;
    PropertyRepeater repeater;
    repeater.addItem(item1);
    repeater.addItem(item2, activeProperties);
    repeater.addItem(item3);

    // changing two properties in item2 and checkig that only P_MAX changed in item1 and item3
    item2->setItemValue(BasicAxisItem::P_MIN, 2.0);
    item2->setItemValue(BasicAxisItem::P_MAX, 3.0);

    EXPECT_EQ(item1->getItemValue(BasicAxisItem::P_MIN).toDouble(), 0.0);
    EXPECT_EQ(item3->getItemValue(BasicAxisItem::P_MIN).toDouble(), 0.0);
    EXPECT_EQ(item1->getItemValue(BasicAxisItem::P_MAX).toDouble(), 3.0);
    EXPECT_EQ(item3->getItemValue(BasicAxisItem::P_MAX).toDouble(), 3.0);
}

TEST_F(TestPropertyRepeater, test_filteredReceive)
{
    SessionModel model("test");

    auto item1 = createAxis(model);
    auto item2 = createAxis(model);
    auto item3 = createAxis(model);

    item1->setItemValue(BasicAxisItem::P_MIN, 0.0);
    item2->setItemValue(BasicAxisItem::P_MIN, 0.0);
    item3->setItemValue(BasicAxisItem::P_MIN, 0.0);
    item1->setItemValue(BasicAxisItem::P_MAX, 1.0);
    item2->setItemValue(BasicAxisItem::P_MAX, 1.0);
    item3->setItemValue(BasicAxisItem::P_MAX, 1.0);

    QStringList activeProperties = QStringList() << BasicAxisItem::P_MAX;
    PropertyRepeater repeater;
    repeater.addItem(item1);
    repeater.addItem(item2, activeProperties);
    repeater.addItem(item3);

    // changing two properties in item1 and checking that P_MIN of item2 remain intact
    item1->setItemValue(BasicAxisItem::P_MIN, 2.0);
    item1->setItemValue(BasicAxisItem::P_MAX, 3.0);

    EXPECT_EQ(item2->getItemValue(BasicAxisItem::P_MIN).toDouble(), 0.0);
    EXPECT_EQ(item2->getItemValue(BasicAxisItem::P_MAX).toDouble(), 3.0); // remain intact
    EXPECT_EQ(item3->getItemValue(BasicAxisItem::P_MIN).toDouble(), 2.0);
    EXPECT_EQ(item3->getItemValue(BasicAxisItem::P_MAX).toDouble(), 3.0);
}

//! Checking repeater in "repeat childs properties" mode

TEST_F(TestPropertyRepeater, test_repeatAll)
{
    SessionModel model("test");

    auto item1 = createData(model);
    auto item2 = createData(model);

    item1->xAxisItem()->setItemValue(BasicAxisItem::P_MAX, 2.0);
    item2->xAxisItem()->setItemValue(BasicAxisItem::P_MAX, 3.0);

    const bool repeat_child_properties = true;
    PropertyRepeater repeater(nullptr, repeat_child_properties);
    repeater.addItem(item1);
    repeater.addItem(item2);

    // adding items to the repeater do not change values
    EXPECT_EQ(item1->getItemValue(IntensityDataItem::P_IS_INTERPOLATED).toBool(), true);
    EXPECT_EQ(item2->getItemValue(IntensityDataItem::P_IS_INTERPOLATED).toBool(), true);
    EXPECT_EQ(item1->getUpperX(), 2.0);
    EXPECT_EQ(item2->getUpperX(), 3.0);

    // change of the value of one item leads to the change in another
    item1->xAxisItem()->setItemValue(BasicAxisItem::P_MAX, 4.0);
    EXPECT_EQ(item1->getUpperX(), 4.0);
    EXPECT_EQ(item2->getUpperX(), 4.0);

    item1->setItemValue(IntensityDataItem::P_IS_INTERPOLATED, false);
    EXPECT_EQ(item1->getItemValue(IntensityDataItem::P_IS_INTERPOLATED).toBool(), false);
    EXPECT_EQ(item2->getItemValue(IntensityDataItem::P_IS_INTERPOLATED).toBool(), false);

    // clearing repeater will stop update
    repeater.clear();
    item1->xAxisItem()->setItemValue(BasicAxisItem::P_MAX, 5.0);
    EXPECT_EQ(item1->getUpperX(), 5.0);
    EXPECT_EQ(item2->getUpperX(), 4.0);
}
