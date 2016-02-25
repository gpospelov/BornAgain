#ifndef TESTPROPERTYATTRIBUTES_H
#define TESTPROPERTYATTRIBUTES_H

#include "PropertyAttribute.h"
#include <QtTest>

class TestPropertyAttributes : public QObject {
    Q_OBJECT

private slots:
    void test_Appearance();
};

inline void TestPropertyAttributes::test_Appearance()
{

    PropertyAttribute attr;
    QVERIFY(attr.isVisible() == true);
    QVERIFY(attr.isReadOnly() == false);
    QVERIFY(attr.isHidden() == false);
    QVERIFY(attr.isDisabled() == false);

    attr.setDisabled();
    QVERIFY(attr.isVisible() == true);
    QVERIFY(attr.isReadOnly() == false);
    QVERIFY(attr.isHidden() == false);
    QVERIFY(attr.isDisabled() == true);

    attr.setReadOnly();
    QVERIFY(attr.isVisible() == true);
    QVERIFY(attr.isReadOnly() == true);
    QVERIFY(attr.isHidden() == false);
    QVERIFY(attr.isDisabled() == true);

    attr.setHidden();
    QVERIFY(attr.isVisible() == false);
    QVERIFY(attr.isReadOnly() == true);
    QVERIFY(attr.isHidden() == true);
    QVERIFY(attr.isDisabled() == true);

    attr.setEnabled();
    QVERIFY(attr.isVisible() == false);
    QVERIFY(attr.isReadOnly() == true);
    QVERIFY(attr.isHidden() == true);
    QVERIFY(attr.isDisabled() == false);

    attr.setVisible();
    QVERIFY(attr.isVisible() == true);
    QVERIFY(attr.isReadOnly() == true);
    QVERIFY(attr.isHidden() == false);
    QVERIFY(attr.isDisabled() == false);

}



#endif
