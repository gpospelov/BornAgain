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
    QVERIFY(property.getColor().isValid() == false);
    QVERIFY(property.getIdentifier().isEmpty() == true);
    QVERIFY(property.getName().isEmpty() == true);
}
