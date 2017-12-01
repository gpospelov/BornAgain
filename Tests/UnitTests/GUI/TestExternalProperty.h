#include <QtTest>
#include "ExternalProperty.h"

class TestExternalProperty : public QObject
{
    Q_OBJECT

private slots:
    void test_initialState();
    void test_equalityOperators();
    void test_variantEquality();
};

inline void TestExternalProperty::test_initialState()
{
    ExternalProperty property;
    QVERIFY(property.isValid() == false);
    QVERIFY(property.color().isValid() == false);
    QVERIFY(property.identifier().isEmpty() == true);
    QVERIFY(property.text().isEmpty() == true);

    // changing any property should change state to valid
    property.setColor(QColor(Qt::red));
    QVERIFY(property.color() == QColor(Qt::red));
    QVERIFY(property.isValid() == true);
    property.setColor(QColor());
    QVERIFY(property.isValid() == false);
    property.setText("aaa");
    QVERIFY(property.text() == QString("aaa"));
    QVERIFY(property.isValid() == true);
    property.setText(QString());
    QVERIFY(property.isValid() == false);
}

inline void TestExternalProperty::test_equalityOperators()
{
    ExternalProperty prop1;
    ExternalProperty prop2;

    QVERIFY (prop1 == prop2);
    prop1.setColor(QColor(Qt::red));
    QVERIFY (prop1 != prop2);
    prop2.setColor(QColor(Qt::red));
    QVERIFY (prop1 == prop2);

    prop1.setIdentifier("aaa");
    QVERIFY (prop1 != prop2);
    prop2.setIdentifier("aaa");
    QVERIFY (prop1 == prop2);
}

inline void TestExternalProperty::test_variantEquality()
{
    ExternalProperty prop1;
    ExternalProperty prop2;

    QVERIFY(prop1.variant() == prop2.variant());
    prop1.setIdentifier("aaa");
    QVERIFY(prop1.variant() != prop2.variant());
    prop2.setIdentifier("aaa");
    QVERIFY(prop1.variant() == prop2.variant());

}
