#include <QtTest>
#include "ExternalProperty.h"
#include "SessionXML.h"
#include "PropertyItem.h"
#include <QXmlStreamWriter>

namespace {

QString propertyToXML(const ExternalProperty& property)
{
    QString result;
    QXmlStreamWriter writer(&result);
    SessionWriter::writeVariant(&writer, property.variant(), /*role*/0);
    return result;
}

ExternalProperty propertyFromXML(const QString& buffer) {
    std::unique_ptr<PropertyItem> item(new PropertyItem);
    QXmlStreamReader reader(buffer);

    while (!reader.atEnd()) {
        reader.readNext();
        if (reader.isStartElement()) {
            if (reader.name() == SessionXML::ParameterTag) {
                SessionReader::readProperty(&reader, item.get());
            }
        }
    }

    return item->value().value<ExternalProperty>();
}

}

class TestExternalProperty : public QObject
{
    Q_OBJECT

private slots:
    void test_initialState();
    void test_equalityOperators();
    void test_variantEquality();
    void test_toXML();
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

//! Testing equality operators.

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

//! Testing equality operators for QVariants based on ExternalProperty.
//! Comparators should be enabled in main.cpp

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

inline void TestExternalProperty::test_toXML()
{
    QString expected;

    // empty property to XML
    ExternalProperty property;
    expected = "<Parameter ParType=\"ExternalProperty\" ParRole=\"0\" Text=\"\" Color=\"\" Identifier=\"\"/>";
    QCOMPARE(propertyToXML(property), expected);

    // from XML to empty property
    QCOMPARE(propertyFromXML(expected).text(), property.text());
    QCOMPARE(propertyFromXML(expected).color(), property.color());
    QCOMPARE(propertyFromXML(expected).identifier(), property.identifier());
    QVERIFY(propertyFromXML(expected) == property);

    // initialized property to XML
    property.setIdentifier("{123456}");
    property.setText("abc");
    property.setColor(QColor(Qt::red));
    expected = "<Parameter ParType=\"ExternalProperty\" ParRole=\"0\" Text=\"abc\" Color=\"#ffff0000\" Identifier=\"{123456}\"/>";
    QCOMPARE(propertyToXML(property), expected);

    // from XML to initialized property
    QCOMPARE(propertyFromXML(expected).identifier(), property.identifier());
    QCOMPARE(propertyFromXML(expected).text(), property.text());
    QCOMPARE(propertyFromXML(expected).color(), property.color());
    QVERIFY(propertyFromXML(expected) == property);
}
