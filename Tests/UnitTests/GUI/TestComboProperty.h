#include <QtTest>
#include "ComboProperty.h"
#include "test_utils.h"
#include <QPair>

class TestComboProperty : public QObject
{
    Q_OBJECT

private:
    ComboProperty propertyFromXML(const QString& buffer) {
        return TestUtils::propertyFromXML<ComboProperty>(buffer);
    }

private slots:
    void test_ComboEquality();
    void test_VariantEquality();
    void test_setValue();
    void test_currentIndex();
    void test_stringOfValues();
    void test_comboXML();
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
    QVERIFY(c1.variant() == c2.variant());

    c2 << "a3";
    QVERIFY(c1.variant() != c2.variant());
    c2.setValue("a2");
    QVERIFY(c1.variant() != c2.variant());

    c1 << "a3";
    c1.setValue("a2");
    QVERIFY(c1.variant() == c2.variant());
}

inline void TestComboProperty::test_setValue()
{
    QStringList expectedValues = QStringList() << "a1" << "a2";
    ComboProperty combo = ComboProperty() << expectedValues;

    QCOMPARE(combo.getValue(), QString("a1"));

    QStringList newValues = QStringList() << "b1" << "b2" << "b3";
    combo.setValues(newValues);
    QCOMPARE(combo.getValue(), QString("b1"));
    QCOMPARE(combo.getValues(), newValues);

    // checking that old value is preserved
    newValues = QStringList() << "c1" << "b1" << "c2";
    combo.setValues(newValues);
    QCOMPARE(combo.getValue(), QString("b1"));
    QCOMPARE(combo.getValues(), newValues);
}

inline void TestComboProperty::test_currentIndex()
{
    ComboProperty combo;
    QCOMPARE(combo.currentIndex(), -1);
    combo << "c1" << "c2";
    QCOMPARE(combo.currentIndex(), 0);
    combo.setValue("c2");
    QCOMPARE(combo.currentIndex(), 1);

    combo.setCurrentIndex(0);
    QCOMPARE(combo.getValue(), QString("c1"));
}

inline void TestComboProperty::test_stringOfValues()
{
    QStringList expectedValues = QStringList() << "a1" << "a2";
    ComboProperty combo = ComboProperty() << expectedValues;

    QCOMPARE(combo.stringOfValues(), QString("a1;a2"));

    // setting string of values, current value should change
    QString stringOfValues("b1;b2;b3");
    combo.setStringOfValues(stringOfValues);
    QCOMPARE(combo.stringOfValues(), stringOfValues);
    QCOMPARE(combo.getValue(), QString("b1"));

    // setting new string of values, containing current value. Current values should remain.
    stringOfValues = QString("c1;b1;c3");
    combo.setStringOfValues(stringOfValues);
    QCOMPARE(combo.stringOfValues(), stringOfValues);
    QCOMPARE(combo.getValue(), QString("b1"));
}

inline void TestComboProperty::test_comboXML()
{
    // Writing combo to XML
    ComboProperty combo = ComboProperty() << "a1" << "a2" << "a3";

    QString expected = "<Parameter ParType=\"ComboProperty\" ParRole=\"0\" ParValue=\"0\" "
                       "ParExt=\"a1;a2;a3\"/>";
    QCOMPARE(TestUtils::propertyToXML(combo), expected);

    // reading from XML
    ComboProperty combo_property = propertyFromXML(expected);
    QCOMPARE(combo_property.getValue(), QString("a1"));
    QCOMPARE(combo_property.stringOfValues(), QString("a1;a2;a3"));
    QVERIFY(combo_property == combo);
}
