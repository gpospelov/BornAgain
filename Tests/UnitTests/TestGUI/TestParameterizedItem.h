#ifndef TESTPARAMETERIZEDITEM_H
#define TESTPARAMETERIZEDITEM_H


#include <QtTest>
#include "ParameterizedItem.h"
#include "GUIHelpers.h"
#include "verify_throw_macro.h"



class TestParameterizedItem : public QObject {
    Q_OBJECT

private slots:
    void test_registerProperty();
    void test_SelectableGroupProperty();
};

inline void TestParameterizedItem::test_registerProperty()
{
    ParameterizedItem item("Modeltype");
    QString property_name("MyProperty");
    double value(1.0);
//    QSignalSpy spy(&item, SIGNAL(propertyChanged(QString)));

    // access non-existing property
    QCOMPARE(false, item.isRegisteredProperty(property_name));
//    QVERIFY_THROW(item.getRegisteredProperty(property_name), GUIHelpers::Error);
//    QVERIFY_THROW(item.setRegisteredProperty(property_name, value), GUIHelpers::Error);

    // registering new property
    item.registerProperty(property_name, value);
    QCOMPARE(true, item.isRegisteredProperty(property_name));
//    QCOMPARE(spy.count(), 1);
//    QList<QVariant> arguments = spy.takeFirst();
//    QCOMPARE(arguments.size(), 1);
//    QCOMPARE(arguments.at(0).toString(), property_name);
    QCOMPARE(item.getRegisteredProperty(property_name).toDouble(), value);
//    QCOMPARE(spy.count(), 0);

    // setting property value
    double new_value(2.0);
    item.setRegisteredProperty(property_name, new_value);
//    QCOMPARE(spy.count(), 1);
//    arguments = spy.takeFirst();
//    QCOMPARE(arguments.size(), 1);
//    QCOMPARE(arguments.at(0).toString(), property_name);
    QCOMPARE(item.getRegisteredProperty(property_name).toDouble(), new_value);

    // setting property value to wrong QVariant
    QVERIFY_THROW(item.setRegisteredProperty(property_name, QString("aaa")), GUIHelpers::Error);

    // attempt to register already existing property
//    QVERIFY_THROW(item.registerProperty(property_name, 1.0), GUIHelpers::Error);

    // remove registered property
    item.removeRegisteredProperty(property_name);
//    QCOMPARE(spy.count(), 1);
//    arguments = spy.takeFirst();
//    QCOMPARE(arguments.size(), 1);
//    QCOMPARE(arguments.at(0).toString(), property_name);
//    QVERIFY_THROW(item.getRegisteredProperty(property_name), GUIHelpers::Error);
}

inline void TestParameterizedItem::test_SelectableGroupProperty()
{
//    ParameterizedItem item;
//    QCOMPARE(item.getSubItems().size(), 0);
}


#endif

