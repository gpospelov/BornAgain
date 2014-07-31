#ifndef TESTPARACRYSTALITEMS_H
#define TESTPARACRYSTALITEMS_H

#include <QtTest>
#include "ParaCrystalItems.h"
#include "FancyGroupProperty.h"

class TestParaCrystalItems : public QObject {
    Q_OBJECT

private slots:
    void test_Para1D_InitialState();
    void test_Para1D_PDFGroupProperty();

};

inline void TestParaCrystalItems::test_Para1D_InitialState()
{
    InterferenceFunction1DParaCrystalItem item;
    QCOMPARE(item.modelType(), Constants::InterferenceFunction1DParaCrystalType);
    QCOMPARE(item.itemName(), Constants::InterferenceFunction1DParaCrystalType);
    QCOMPARE(item.getSubItems().size(), 1);

    QCOMPARE(item.getRegisteredProperty(InterferenceFunction1DParaCrystalItem::P_PEAK_DISTANCE).toDouble(), 20.0*Units::nanometer);
    QCOMPARE(item.getRegisteredProperty(InterferenceFunction1DParaCrystalItem::P_DAMPING_LENGTH).toDouble(), 1000.0*Units::micrometer);
    QCOMPARE(item.getRegisteredProperty(InterferenceFunction1DParaCrystalItem::P_DOMAIN_SIZE).toDouble(), 20.0*Units::micrometer);
    QCOMPARE(item.getRegisteredProperty(InterferenceFunction1DParaCrystalItem::P_KAPPA).toDouble(), 0.0);

    QCOMPARE(item.getSubItems()[InterferenceFunction1DParaCrystalItem::P_PDF]->modelType(), Constants::FTDistribution1DCauchyType);

    FancyGroupProperty *group_property = item.getRegisteredProperty(InterferenceFunction1DParaCrystalItem::P_PDF).value<FancyGroupProperty *>();
    QCOMPARE(group_property->type(), FancyGroupProperty::SelectableGroupType);

}

inline void TestParaCrystalItems::test_Para1D_PDFGroupProperty()
{
    InterferenceFunction1DParaCrystalItem item;

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
        QSignalSpy spyItem(&item, SIGNAL(propertyChanged(QString)));
        QSignalSpy spyPropertyItem(&item, SIGNAL(propertyItemChanged(QString)));
        ParameterizedItem *pdfItem = item.setGroupProperty(InterferenceFunction1DParaCrystalItem::P_PDF, pdf_name);
        QVERIFY(pdfItem);
        QCOMPARE(item.getSubItems().size(), 1);
        QCOMPARE(pdfItem, item.getSubItems()[InterferenceFunction1DParaCrystalItem::P_PDF]);

        QCOMPARE(spyItem.count(), 0);
        if(pdf_name == Constants::FTDistribution1DCauchyType) { // default ff
            QCOMPARE(spyPropertyItem.count(), 0);
        } else {
            QCOMPARE(spyPropertyItem.count(), 1);
            QList<QVariant> arguments = spyPropertyItem.takeFirst(); // take the first signal
            QCOMPARE(arguments.at(0).toString(), InterferenceFunction1DParaCrystalItem::P_PDF);
        }

        QCOMPARE(pdfItem->modelType(), pdf_name);
    }
}

#endif

