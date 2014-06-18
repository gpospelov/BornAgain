#ifndef TESTFORMFACTORITEMS_H
#define TESTFORMFACTORITEMS_H


#include <QtTest>
#include "FormFactors.h"
#include "FormFactorItems.h"
#include "TransformToDomain.h"
#include "TransformFromDomain.h"
#include "Units.h"
#include "Numeric.h"

class TestFormFactorItems : public QObject {
    Q_OBJECT

private slots:
    void test_AnisoPyramidItem();
};


inline void TestFormFactorItems::test_AnisoPyramidItem()
{
    // to domain
    AnisoPyramidItem item;
    item.setRegisteredProperty(AnisoPyramidItem::P_LENGTH, 20.0);
    item.setRegisteredProperty(AnisoPyramidItem::P_WIDTH, 16.0);
    item.setRegisteredProperty(AnisoPyramidItem::P_HEIGHT, 13.0);
    item.setRegisteredProperty(AnisoPyramidItem::P_ALPHA, 60.0);
    FormFactorAnisoPyramid *ff = dynamic_cast<FormFactorAnisoPyramid *>(TransformToDomain::createFormFactor(item));
    QVERIFY(ff);
    QVERIFY(ff->getLength() == 20.0);
    QVERIFY(ff->getWidth() == 16.0);
    QVERIFY(ff->getHeight() == 13.0);
    QVERIFY( Numeric::areAlmostEqual(ff->getAlpha(), Units::deg2rad(60.0)));
    delete ff;

    // from domain
    FormFactorAnisoPyramid ff2(2.0, 1.6, 1.3, 70.0*Units::degree);
    AnisoPyramidItem item2;
    TransformFromDomain::setItemFromSample(&item2, &ff2);
    QVERIFY(item2.getRegisteredProperty(AnisoPyramidItem::P_LENGTH).toDouble() == 2.0);
    QVERIFY(item2.getRegisteredProperty(AnisoPyramidItem::P_WIDTH).toDouble() == 1.6);
    QVERIFY(item2.getRegisteredProperty(AnisoPyramidItem::P_HEIGHT).toDouble() == 1.3);
    QVERIFY(item2.getRegisteredProperty(AnisoPyramidItem::P_ALPHA).toDouble() == 70.0);
}


#endif

