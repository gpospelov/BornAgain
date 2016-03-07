#ifndef TESTPROPERTYATTRIBUTES_H
#define TESTPROPERTYATTRIBUTES_H

#include "PropertyAttribute.h"
#include "ParameterizedItem.h"
#include <memory>
#include <QtTest>
/*
class TestPropertyAttributes : public QObject {
    Q_OBJECT

private slots:
    void test_Appearance();
    void test_ToolTips();
    void test_LimitsAndDecimals();
    void test_ItemAttribute();
    void test_ItemPropertyAttribute();
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

inline void TestPropertyAttributes::test_ToolTips()
{
    PropertyAttribute attr;
    QVERIFY(attr.getToolTip().isEmpty());
    QString tooltip("tooltip");
    attr.setToolTip(tooltip);
    QVERIFY(attr.getToolTip() == tooltip);
}

inline void TestPropertyAttributes::test_LimitsAndDecimals()
{
    PropertyAttribute attr;
    QVERIFY(attr.getLimits() == AttLimits::lowerLimited(0.0));
    attr.limited(0.0, 1.0);
    QVERIFY(attr.getLimits() == AttLimits::limited(0.0, 1.0));
    QVERIFY(attr.getDecimals() == 2);
    attr.setDecimals(3);
    QVERIFY(attr.getDecimals() == 3);
}

inline void TestPropertyAttributes::test_ItemAttribute()
{
    std::unique_ptr<ParameterizedItem> item(new ParameterizedItem("Test"));
    PropertyAttribute attr(PropertyAttribute::HIDDEN, AttLimits::limited(1.0, 2.0), 3, "label", "tooltip");
    item->setAttribute(attr);
    QVERIFY(item->getAttribute().isHidden());
    QVERIFY(item->getAttribute().getToolTip() == "tooltip");
    QVERIFY(item->getAttribute().getLabel() == "label");
    QVERIFY(item->getAttribute().getDecimals() == 3);
    QVERIFY(item->getAttribute().getLimits() == AttLimits::limited(1.0, 2.0));
    item->getAttribute().setVisible();
    item->getAttribute().setToolTip("another tooltip");
    QVERIFY(item->getAttribute().isVisible());
    QVERIFY(item->getAttribute().getToolTip() == "another tooltip");
}

inline void TestPropertyAttributes::test_ItemPropertyAttribute()
{
    std::unique_ptr<ParameterizedItem> item(new ParameterizedItem("Test"));
    PropertyAttribute attr(PropertyAttribute::HIDDEN, AttLimits::limited(1.0, 2.0), 3, "label", "tooltip");
    const QString thickness("Thickness");
    item->registerProperty(thickness, 3.0, attr);
    PropertyAttribute &propAttr = item->getPropertyAttribute(thickness);
    QVERIFY(propAttr.isHidden());
    QVERIFY(propAttr.getToolTip() == "tooltip");
    QVERIFY(propAttr.getLabel() == "label");
    QVERIFY(propAttr.getDecimals() == 3);
    QVERIFY(propAttr.getLimits() == AttLimits::limited(1.0, 2.0));

    const QString fatness("Fatness");
    item->registerProperty("Fatness", 99.0)
        .setToolTip("tooltip2")
        .setLabel("label2")
        .setReadOnly()
        .setHidden()
        .setDecimals(3);

    QVERIFY(item->getPropertyAttribute(fatness).getToolTip() == QStringLiteral("tooltip2"));
    QVERIFY(item->getPropertyAttribute(fatness).getLabel() == QStringLiteral("label2"));
    QVERIFY(item->getPropertyAttribute(fatness).isReadOnly());
    QVERIFY(item->getPropertyAttribute(fatness).isHidden());
    QVERIFY(item->getPropertyAttribute(fatness).getDecimals() == 3);

}
*/

#endif
