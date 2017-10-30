#include "SessionItemController.h"
#include "SessionModel.h"
#include "AxesItems.h"
#include <QtTest>
#include <QDebug>

//! Helper class to test object behaviour after their death.

class TestListener
{
public:
    TestListener() : m_onItemDestroyedCount(0), m_onPropertyChangeCount(0)
      , m_onWidgetDestroyed(0) {}
    void clear() {
        m_onItemDestroyedCount = 0;
        m_onPropertyChangeCount = 0;
        m_onWidgetDestroyed = 0;
    }
    int m_onItemDestroyedCount;
    int m_onPropertyChangeCount;
    int m_onWidgetDestroyed;
};

//! Helper class to test SessionItemController usage in widget context.

class TestObject : public QObject
{
    Q_OBJECT
public:
    TestObject(TestListener* listener)
        : m_listener(listener)
        , m_controller(new SessionItemController(this))
        , m_is_subscribed(false)
    {
        m_controller->setSubscribeCallback([this](){onSubscribe();});
        m_controller->setUnsubscribeCallback([this](){onUnsubscribe();});
    }
    ~TestObject() { m_listener->m_onWidgetDestroyed++;}

    void setItem(SessionItem* item) {m_controller->setItem(item);}
    void onSubscribe() {
        m_is_subscribed = true;
        currentItem()->mapper()->setOnPropertyChange([this](const QString&) {
            m_listener->m_onPropertyChangeCount++;}, this);

        currentItem()->mapper()->setOnItemDestroy([this](SessionItem*) {
            m_listener->m_onItemDestroyedCount++; }, this);

    }

    SessionItem* currentItem() { return m_controller->currentItem();}

    void onUnsubscribe() {
        m_is_subscribed = false;
    }

    void setVisible(bool isVisible) {
        if (isVisible)
            m_controller->subscribe();
        else
            m_controller->unsubscribe();
    }

    TestListener* m_listener;
    SessionItemController* m_controller;
    bool m_is_subscribed;
};

class TestSessionItemController : public QObject
{
    Q_OBJECT
public:

private slots:
    void test_InitialState();
    void test_setItem();
    void test_setItemAndSubscribeItem();
    void test_onPropertyChange();
    void test_onItemDestroyWidgetVisible();
    void test_onItemDestroyWidgetHidden();
    void test_onTwoItems();
    void test_onTwoItemsWhenHidden();
    void test_deleteWidget();
};

//! Testing helper classes which will be used for controller testing.

inline void TestSessionItemController::test_InitialState()
{
    TestListener listener;
    QCOMPARE(listener.m_onItemDestroyedCount, 0);
    QCOMPARE(listener.m_onPropertyChangeCount, 0);

    TestObject object(&listener);
    QCOMPARE(object.currentItem(), nullptr);
    QCOMPARE(object.m_is_subscribed, false);

    // setting null item
    object.setItem(nullptr);
    QCOMPARE(listener.m_onItemDestroyedCount, 0);
    QCOMPARE(listener.m_onPropertyChangeCount, 0);
    QCOMPARE(object.currentItem(), nullptr);
    QCOMPARE(object.m_is_subscribed, false);

    object.setVisible(true);
    QCOMPARE(object.currentItem(), nullptr);
    QCOMPARE(object.m_is_subscribed, false);
}

//! Setting item and doing nothing.

inline void TestSessionItemController::test_setItem()
{
    TestListener listener;
    TestObject object(&listener);
    SessionModel model("TestModel");
    SessionItem* item = model.insertNewItem(Constants::BasicAxisType);

    object.setItem(item);
    QCOMPARE(object.currentItem(), item);
    QCOMPARE(object.m_is_subscribed, false);
    QCOMPARE(listener.m_onItemDestroyedCount, 0);
    QCOMPARE(listener.m_onPropertyChangeCount, 0);
}

//! Setting item and subscribing to it.

inline void TestSessionItemController::test_setItemAndSubscribeItem()
{
    TestListener listener;
    TestObject object(&listener);
    SessionModel model("TestModel");
    SessionItem* item = model.insertNewItem(Constants::BasicAxisType);

    object.setItem(item);
    object.setVisible(true);
    QCOMPARE(object.currentItem(), item);
    QCOMPARE(object.m_is_subscribed, true);
    QCOMPARE(listener.m_onItemDestroyedCount, 0);
    QCOMPARE(listener.m_onPropertyChangeCount, 0);
}

//! Setting item properties when widget is in hidden/shown state.

inline void TestSessionItemController::test_onPropertyChange()
{
    TestListener listener;
    TestObject object(&listener);
    SessionModel model("TestModel");
    SessionItem* item = model.insertNewItem(Constants::BasicAxisType);

    object.setItem(item);
    QCOMPARE(object.currentItem(), item);
    QCOMPARE(object.m_is_subscribed, false);

    // changing item, should be no reaction
    item->setItemValue(BasicAxisItem::P_MAX, 3.0);
    QCOMPARE(listener.m_onItemDestroyedCount, 0);
    QCOMPARE(listener.m_onPropertyChangeCount, 0);

    // setting visible and changing item
    object.setVisible(true);
    QCOMPARE(object.m_is_subscribed, true);
    item->setItemValue(BasicAxisItem::P_MAX, 4.0);
    QCOMPARE(listener.m_onItemDestroyedCount, 0);
    QCOMPARE(listener.m_onPropertyChangeCount, 1);

    // same value, no change expected
    item->setItemValue(BasicAxisItem::P_MAX, 4.0);
    QCOMPARE(listener.m_onPropertyChangeCount, 1);

    // new value
    item->setItemValue(BasicAxisItem::P_MAX, 4.1);
    QCOMPARE(listener.m_onPropertyChangeCount, 2);

    // setting invisible and changing item, no reaction on item value change expected
    object.setVisible(false);
    QCOMPARE(object.m_is_subscribed, false);
    item->setItemValue(BasicAxisItem::P_MAX, 5.0);
    QCOMPARE(listener.m_onItemDestroyedCount, 0);
    QCOMPARE(listener.m_onPropertyChangeCount, 2);
}

//! Deleting item when widget is visible.

inline void TestSessionItemController::test_onItemDestroyWidgetVisible()
{
    TestListener listener;
    TestObject object(&listener);
    SessionModel model("TestModel");
    SessionItem* item = model.insertNewItem(Constants::BasicAxisType);

    object.setItem(item);
    object.setVisible(true);

    item->setItemValue(BasicAxisItem::P_MAX, 4.0);
    QCOMPARE(listener.m_onItemDestroyedCount, 0);
    QCOMPARE(listener.m_onPropertyChangeCount, 1);

    // item deletion should lead to automatic unsubscription
    delete item->parent()->takeRow(0);
    QCOMPARE(listener.m_onItemDestroyedCount, 1);
    QCOMPARE(object.m_is_subscribed, false);
    QCOMPARE(object.currentItem(), nullptr);

    object.setVisible(false);
    QCOMPARE(listener.m_onItemDestroyedCount, 1);
    QCOMPARE(object.m_is_subscribed, false);
    QCOMPARE(object.currentItem(), nullptr);
}

inline void TestSessionItemController::test_onItemDestroyWidgetHidden()
{
    TestListener listener;
    TestObject object(&listener);
    SessionModel model("TestModel");
    SessionItem* item = model.insertNewItem(Constants::BasicAxisType);

    object.setItem(item);
    object.setVisible(true);

    item->setItemValue(BasicAxisItem::P_MAX, 4.0);
    QCOMPARE(listener.m_onItemDestroyedCount, 0);
    QCOMPARE(listener.m_onPropertyChangeCount, 1);

    object.setVisible(false);

    // Deleting item when widget is hidden.
    // Widget itself shouldn't notice onItemDestroy because of hidden state.
    // But the controller should notice, and unsubscribe the widget.

    delete item->parent()->takeRow(0);
    QCOMPARE(listener.m_onItemDestroyedCount, 0);
    QCOMPARE(object.m_is_subscribed, false);
    QCOMPARE(object.currentItem(), nullptr);

    object.setVisible(true);
    QCOMPARE(listener.m_onItemDestroyedCount, 0);
    QCOMPARE(object.m_is_subscribed, false);
    QCOMPARE(object.currentItem(), nullptr);
}

//! Typical scenario when one item follows the other.

inline void TestSessionItemController::test_onTwoItems()
{
    TestListener listener;
    TestObject object(&listener);
    SessionModel model("TestModel");
    SessionItem* item1 = model.insertNewItem(Constants::BasicAxisType);
    SessionItem* item2 = model.insertNewItem(Constants::BasicAxisType);

    object.setItem(item1);
    QCOMPARE(object.currentItem(), item1);
    object.setVisible(true);

    item1->setItemValue(BasicAxisItem::P_MAX, 4.0);
    QCOMPARE(listener.m_onItemDestroyedCount, 0);
    QCOMPARE(listener.m_onPropertyChangeCount, 1);

    // changing the item
    object.setItem(item2);
    QCOMPARE(object.currentItem(), item2);
    // since by design setting the item doesn't lead to automatic subscription, we have to subscribe
    object.setVisible(true);

    // changing the value of previous item, widget shouldn't react
    item1->setItemValue(BasicAxisItem::P_MAX, 5.0);
    QCOMPARE(listener.m_onItemDestroyedCount, 0);
    QCOMPARE(listener.m_onPropertyChangeCount, 1);

    // changing the value of new item, widget should react
    item2->setItemValue(BasicAxisItem::P_MAX, 6.0);
    QCOMPARE(listener.m_onPropertyChangeCount, 2);
}

//! Settings two items one after another, when widget stays hidden

inline void TestSessionItemController::test_onTwoItemsWhenHidden()
{
    TestListener listener;
    TestObject object(&listener);
    SessionModel model("TestModel");
    SessionItem* item1 = model.insertNewItem(Constants::BasicAxisType);
    SessionItem* item2 = model.insertNewItem(Constants::BasicAxisType);

    object.setVisible(false);

    object.setItem(item1);
    QCOMPARE(object.currentItem(), item1);

    item1->setItemValue(BasicAxisItem::P_MAX, 4.0);
    QCOMPARE(listener.m_onItemDestroyedCount, 0);
    QCOMPARE(listener.m_onPropertyChangeCount, 0);

    // changing the item
    object.setItem(item2);
    QCOMPARE(object.currentItem(), item2);

    // changing the value of previous item, widget shouldn't react
    item1->setItemValue(BasicAxisItem::P_MAX, 5.0);
    QCOMPARE(listener.m_onItemDestroyedCount, 0);
    QCOMPARE(listener.m_onPropertyChangeCount, 0);

    // changing the value of new item, widget shouldn't react
    item2->setItemValue(BasicAxisItem::P_MAX, 6.0);
    QCOMPARE(listener.m_onPropertyChangeCount, 0);
}

//! Deleting the widget when item still alive.

inline void TestSessionItemController::test_deleteWidget()
{
    TestListener listener;
    TestObject* object = new TestObject(&listener);
    SessionModel model("TestModel");
    SessionItem* item = model.insertNewItem(Constants::BasicAxisType);

    object->setItem(item);
    object->setVisible(true);

    item->setItemValue(BasicAxisItem::P_MAX, 4.0);

    QCOMPARE(listener.m_onItemDestroyedCount, 0);
    QCOMPARE(listener.m_onPropertyChangeCount, 1);
    QCOMPARE(listener.m_onWidgetDestroyed, 0);

    delete object;

    QCOMPARE(listener.m_onItemDestroyedCount, 0);
    QCOMPARE(listener.m_onPropertyChangeCount, 1);
    QCOMPARE(listener.m_onWidgetDestroyed, 1);

    item->setItemValue(BasicAxisItem::P_MAX, 4.1);
    QCOMPARE(listener.m_onItemDestroyedCount, 0);
    QCOMPARE(listener.m_onPropertyChangeCount, 1);
}

