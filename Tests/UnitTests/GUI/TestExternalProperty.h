#include <QtTest>
#include "ExternalProperty.h"

class TestExternalProperty : public QObject
{
    Q_OBJECT

private slots:
    void test_initialState();
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
