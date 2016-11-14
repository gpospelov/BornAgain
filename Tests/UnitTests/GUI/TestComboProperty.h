#ifndef TESTCOMBOPROPERTY_H
#define TESTCOMBOPROPERTY_H

#include <QtTest>
#include "ComboProperty.h"
#include <QDebug>

class TestComboProperty : public QObject {
    Q_OBJECT

private slots:
    void test_ComboEquality();
    void test_VariantEquality();
};

inline void TestComboProperty::test_ComboEquality()
{
        ComboProperty c1;
        ComboProperty c2;
        QVERIFY(c1 == c2);

        c1 << "a1" << "a2";
        c2 << "a1" << "a2";
        QVERIFY(c1 == c2);

        c2 << "a3";
        QVERIFY(c1 != c2);
        c2.setValue("a2");
        QVERIFY(c1 != c2);

        c1 << "a3";
        c1.setValue("a2");
        QVERIFY(c1 == c2);
}

inline void TestComboProperty::test_VariantEquality()
{
    QVariant v1(1.0);
    QVariant v2(2.0);
    QVariant v3(2.0);
    QVERIFY(v1 != v2);
    QVERIFY(v2 == v3);

    ComboProperty c1 = ComboProperty() << "a1" << "a2";
    ComboProperty c2 = ComboProperty() << "a1" << "a2";
    QVERIFY(c1.getVariant() == c2.getVariant());

    c2 << "a3";
    QVERIFY(c1.getVariant() != c2.getVariant());
    c2.setValue("a2");
    QVERIFY(c1.getVariant() != c2.getVariant());

    c1 << "a3";
    c1.setValue("a2");
    QVERIFY(c1.getVariant() == c2.getVariant());
}

#endif // TESTCOMBOPROPERTY_H
