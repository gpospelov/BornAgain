#ifndef TESTPARACRYSTALITEMS_H
#define TESTPARACRYSTALITEMS_H

#include <QtTest>
#include "InterferenceFunctionItems.h"
#include "GroupProperty.h"

class TestParaCrystalItems : public QObject {
    Q_OBJECT

private slots:
    void test_Para1D_InitialState();
    void test_Para1D_PDFGroupProperty();

};

inline void TestParaCrystalItems::test_Para1D_InitialState()
{
    InterferenceFunctionRadialParaCrystalItem item;
    QCOMPARE(item.modelType(), Constants::InterferenceFunctionRadialParaCrystalType);
    QCOMPARE(item.itemName(), Constants::InterferenceFunctionRadialParaCrystalType);
    QCOMPARE(item.getChildrenOfType(Constants::GroupItemType).size(), 1);

    QCOMPARE(item.getItemValue(InterferenceFunctionRadialParaCrystalItem::P_PEAK_DISTANCE).toDouble(), 20.0*Units::nanometer);
    QCOMPARE(item.getItemValue(InterferenceFunctionRadialParaCrystalItem::P_DAMPING_LENGTH).toDouble(), 1000.0*Units::micrometer);
    QCOMPARE(item.getItemValue(InterferenceFunctionRadialParaCrystalItem::P_DOMAIN_SIZE).toDouble(), 20.0*Units::micrometer);
    QCOMPARE(item.getItemValue(InterferenceFunctionRadialParaCrystalItem::P_KAPPA).toDouble(), 0.0);

    QCOMPARE(item.getGroupItem(InterferenceFunctionRadialParaCrystalItem::P_PDF)->modelType(), Constants::FTDistribution1DCauchyType);

    GroupProperty_t group_property = item.getItemValue(InterferenceFunctionRadialParaCrystalItem::P_PDF).value<GroupProperty_t>();
    QCOMPARE(group_property->type(), GroupProperty::SELECTABLE);

}

inline void TestParaCrystalItems::test_Para1D_PDFGroupProperty()
{
    InterferenceFunctionRadialParaCrystalItem item;

    // check that request for new subItem generates item of correct modelType and
    // correct signals (one propertyItemChanged, and no propertyChanged)
    QStringList pdfs;
    pdfs << Constants::FTDistribution1DCauchyType
         << Constants::FTDistribution1DGaussType
         << Constants::FTDistribution1DGateType
         << Constants::FTDistribution1DTriangleType
         << Constants::FTDistribution1DCosineType
         << Constants::FTDistribution1DVoigtType;

    foreach(QString pdf_name, pdfs) {
//        QSignalSpy spyItem(&item, SIGNAL(propertyChanged(QString)));
//        QSignalSpy spyPropertyItem(&item, SIGNAL(subItemChanged(QString)));
        SessionItem *pdfItem = item.setGroupProperty(InterferenceFunctionRadialParaCrystalItem::P_PDF, pdf_name);
        QVERIFY(pdfItem);
        QCOMPARE(item.getChildrenOfType(Constants::GroupItemType).size(), 1);
        QCOMPARE(pdfItem, item.getGroupItem(InterferenceFunctionRadialParaCrystalItem::P_PDF));

//        QCOMPARE(spyItem.count(), 0);
        if(pdf_name == Constants::FTDistribution1DCauchyType) { // default ff
//            QCOMPARE(spyPropertyItem.count(), 0);
        } else {
//            QCOMPARE(spyPropertyItem.count(), 1);
//            QList<QVariant> arguments = spyPropertyItem.takeFirst(); // take the first signal
//            QCOMPARE(arguments.at(0).toString(), InterferenceFunctionRadialParaCrystalItem::P_PDF);
        }

        QCOMPARE(pdfItem->modelType(), pdf_name);
    }
}

#endif

