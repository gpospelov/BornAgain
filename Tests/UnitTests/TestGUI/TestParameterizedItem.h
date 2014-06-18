#ifndef TESTPARAMETERIZEDITEM_H
#define TESTPARAMETERIZEDITEM_H


#include <QtTest>
#include "ParameterizedItem.h"

class TestParameterizedItem : public QObject {
    Q_OBJECT

private slots:
    void test_ItemName();
};

inline void TestParameterizedItem::test_ItemName()
{
    ParameterizedItem item;
    QSignalSpy spy(&item, SIGNAL(propertyChanged(QString)));
    item.setItemName("NewName");
    QCOMPARE(spy.count(), 1); // make sure the signal was emitted exactly one time
    QList<QVariant> arguments = spy.takeFirst(); // take the first signal
    QCOMPARE(arguments.at(0).toString(), QString("Name"));
    QCOMPARE(item.getRegisteredProperty(ParameterizedItem::P_NAME).toString(), QString("NewName"));
}


#endif

