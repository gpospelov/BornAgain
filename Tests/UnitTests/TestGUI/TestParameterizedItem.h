#ifndef TESTPARAMETERIZEDITEM_H
#define TESTPARAMETERIZEDITEM_H


#include <QtTest>
#include "ParameterizedItem.h"

class TestParameterizedItem : public QObject {
    Q_OBJECT

private slots:
    void test_ItemName();
    void test_SelectableGroupProperty();
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

//const QString FormFactorGroup = "Form Factor";
//const QString LayerRoughnessGroup = "Roughness";
//const QString DetectorGroup = "Detector group";
//const QString FTDistribution1DGroup = "PDF 1D";
//const QString FTDistribution2DGroupA = "PDF 2D #1";
//const QString FTDistribution2DGroupB = "PDF 2D #2";
//const QString LatticeGroup = "Lattice_type";



inline void TestParameterizedItem::test_SelectableGroupProperty()
{
    ParameterizedItem item;
    QCOMPARE(item.getSubItems().size(), 0);
}


#endif

