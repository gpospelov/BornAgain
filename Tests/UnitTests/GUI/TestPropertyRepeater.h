#include <QtTest>
#include "SessionModel.h"
#include "PropertyRepeater.h"
#include "item_constants.h"
#include "IntensityDataItem.h"
#include "AxesItems.h"

namespace {

IntensityDataItem* createItem(SessionModel& model)
{
    return dynamic_cast<IntensityDataItem*>(model.insertNewItem(Constants::IntensityDataType));
}

}

class TestPropertyRepeater : public QObject {
    Q_OBJECT

private:

private slots:
    void test_twoItems();
    void test_threeItems();
    void test_repeaterFilteredBroadcast();
    void test_repeaterFilteredReceive();
};

//! Repeater handles two items.

inline void TestPropertyRepeater::test_twoItems()
{
    SessionModel model("test");

    IntensityDataItem* item1 = createItem(model);
    IntensityDataItem* item2 = createItem(model);

    item1->xAxisItem()->setItemValue(BasicAxisItem::P_MAX, 2.0);
    item2->xAxisItem()->setItemValue(BasicAxisItem::P_MAX, 3.0);

    PropertyRepeater repeater;
    repeater.addItem(item1);
    repeater.addItem(item2);

    // adding items to the repeater do not change values
    QCOMPARE(item1->getItemValue(IntensityDataItem::P_IS_INTERPOLATED).toBool(), true);
    QCOMPARE(item2->getItemValue(IntensityDataItem::P_IS_INTERPOLATED).toBool(), true);
    QCOMPARE(item1->getUpperX(), 2.0);
    QCOMPARE(item2->getUpperX(), 3.0);

    // change of the value of one item leads to the change in another
    item1->xAxisItem()->setItemValue(BasicAxisItem::P_MAX, 4.0);
    QCOMPARE(item1->getUpperX(), 4.0);
    QCOMPARE(item2->getUpperX(), 4.0);

    item1->setItemValue(IntensityDataItem::P_IS_INTERPOLATED, false);
    QCOMPARE(item1->getItemValue(IntensityDataItem::P_IS_INTERPOLATED).toBool(), false);
    QCOMPARE(item2->getItemValue(IntensityDataItem::P_IS_INTERPOLATED).toBool(), false);

    // clearing repeater will stop update
    repeater.clear();
    item1->xAxisItem()->setItemValue(BasicAxisItem::P_MAX, 5.0);
    QCOMPARE(item1->getUpperX(), 5.0);
    QCOMPARE(item2->getUpperX(), 4.0);
}

//! Repeater handles three items.

inline void TestPropertyRepeater::test_threeItems()
{
    SessionModel model("test");

    IntensityDataItem* item1 = createItem(model);
    IntensityDataItem* item2 = createItem(model);
    IntensityDataItem* item3 = createItem(model);

    item1->xAxisItem()->setItemValue(BasicAxisItem::P_MAX, 1.0);
    item2->xAxisItem()->setItemValue(BasicAxisItem::P_MAX, 2.0);
    item3->xAxisItem()->setItemValue(BasicAxisItem::P_MAX, 3.0);

    PropertyRepeater repeater;
    repeater.addItem(item1);
    repeater.addItem(item2);
    repeater.addItem(item3);

    // change of the value of one item leads to the change in two another
    item1->xAxisItem()->setItemValue(BasicAxisItem::P_MAX, 4.0);
    QCOMPARE(item1->getUpperX(), 4.0);
    QCOMPARE(item2->getUpperX(), 4.0);
    QCOMPARE(item3->getUpperX(), 4.0);
}

//! Checks if item with active properties specified receives updates only for these properties.

inline void TestPropertyRepeater::test_repeaterFilteredBroadcast()
{
    SessionModel model("test");

    IntensityDataItem* item1 = createItem(model);
    IntensityDataItem* item2 = createItem(model);
    IntensityDataItem* item3 = createItem(model);

    item1->xAxisItem()->setItemValue(BasicAxisItem::P_MIN, 0.0);
    item2->xAxisItem()->setItemValue(BasicAxisItem::P_MIN, 0.0);
    item3->xAxisItem()->setItemValue(BasicAxisItem::P_MIN, 0.0);
    item1->xAxisItem()->setItemValue(BasicAxisItem::P_MAX, 1.0);
    item2->xAxisItem()->setItemValue(BasicAxisItem::P_MAX, 1.0);
    item3->xAxisItem()->setItemValue(BasicAxisItem::P_MAX, 1.0);

    QStringList activeProperties = QStringList() << BasicAxisItem::P_MAX;
    PropertyRepeater repeater;
    repeater.addItem(item1);
    repeater.addItem(item2, activeProperties);
    repeater.addItem(item3);

    // changing two properties in item2 and checkig that only P_MAX changed in item1 and item3
    item2->xAxisItem()->setItemValue(BasicAxisItem::P_MIN, 2.0);
    item2->xAxisItem()->setItemValue(BasicAxisItem::P_MAX, 3.0);
    QCOMPARE(item1->getLowerX(), 0.0);
    QCOMPARE(item3->getLowerX(), 0.0);
    QCOMPARE(item1->getUpperX(), 3.0);
    QCOMPARE(item3->getUpperX(), 3.0);
}

inline void TestPropertyRepeater::test_repeaterFilteredReceive()
{
    SessionModel model("test");

    IntensityDataItem* item1 = createItem(model);
    IntensityDataItem* item2 = createItem(model);
    IntensityDataItem* item3 = createItem(model);

    item1->xAxisItem()->setItemValue(BasicAxisItem::P_MIN, 0.0);
    item2->xAxisItem()->setItemValue(BasicAxisItem::P_MIN, 0.0);
    item3->xAxisItem()->setItemValue(BasicAxisItem::P_MIN, 0.0);
    item1->xAxisItem()->setItemValue(BasicAxisItem::P_MAX, 1.0);
    item2->xAxisItem()->setItemValue(BasicAxisItem::P_MAX, 1.0);
    item3->xAxisItem()->setItemValue(BasicAxisItem::P_MAX, 1.0);

    QStringList activeProperties = QStringList() << BasicAxisItem::P_MAX;
    PropertyRepeater repeater;
    repeater.addItem(item1);
    repeater.addItem(item2, activeProperties);
    repeater.addItem(item3);

    // changing two properties in item1 and checking that P_MIN of item2 remain intact
    item1->xAxisItem()->setItemValue(BasicAxisItem::P_MIN, 2.0);
    item1->xAxisItem()->setItemValue(BasicAxisItem::P_MAX, 3.0);
    QCOMPARE(item2->getLowerX(), 0.0); // remain intact
    QCOMPARE(item2->getUpperX(), 3.0);
    QCOMPARE(item3->getLowerX(), 2.0);
    QCOMPARE(item3->getUpperX(), 3.0);

}
