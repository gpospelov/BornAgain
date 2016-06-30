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
    item.setItemValue(AnisoPyramidItem::P_LENGTH, 20.0);
    item.setItemValue(AnisoPyramidItem::P_WIDTH, 16.0);
    item.setItemValue(AnisoPyramidItem::P_HEIGHT, 13.0);
    item.setItemValue(AnisoPyramidItem::P_ALPHA, 60.0);
    auto P_ff = item.createFormFactor();
    FormFactorAnisoPyramid *p_ff = dynamic_cast<FormFactorAnisoPyramid *>(P_ff.get());
    QVERIFY(p_ff);
    QVERIFY(p_ff->getLength() == 20.0);
    QVERIFY(p_ff->getWidth() == 16.0);
    QVERIFY(p_ff->getHeight() == 13.0);
    QVERIFY( Numeric::areAlmostEqual(p_ff->getAlpha(), Units::deg2rad(60.0)));
}

#endif
