#include "SessionItemController.h"
#include "SessionModel.h"
#include "AxesItems.h"
#include <QtTest>
#include <QDebug>

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

//! Setting item properties when widget is in hidden/shown state

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

    // setting invisible and changing item
    object.setVisible(false);
    QCOMPARE(object.m_is_subscribed, false);
    item->setItemValue(BasicAxisItem::P_MAX, 5.0);
    QCOMPARE(listener.m_onItemDestroyedCount, 0);
    QCOMPARE(listener.m_onPropertyChangeCount, 3);
}

//! Deleting item when widget is visible

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

    delete item->parent()->takeRow(0);
    QCOMPARE(listener.m_onItemDestroyedCount, 1);
    QCOMPARE(listener.m_onItemDestroyedCount, 1);
    QCOMPARE(object.m_is_subscribed, false);
    QCOMPARE(object.currentItem(), nullptr);

    object.setVisible(true);
    QCOMPARE(listener.m_onItemDestroyedCount, 1);
    QCOMPARE(listener.m_onItemDestroyedCount, 1);
    QCOMPARE(object.m_is_subscribed, false);
    QCOMPARE(object.currentItem(), nullptr);
}

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

