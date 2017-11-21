// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/PropertyEditor/PropertyEditorFactory.cpp
//! @brief     Implements PropertyEditorFactory namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "PropertyEditorFactory.h"
#include "SessionItem.h"
#include "RealLimits.h"
#include "MaterialProperty.h"
#include "GroupProperty.h"
#include "CustomEditors.h"
#include "ComboProperty.h"
#include "ColorProperty.h"
#include "ScientificDoubleProperty.h"
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QLineEdit>
#include <QLabel>

namespace {
QWidget* createCustomDoubleEditor(const SessionItem& item);
QWidget* createCustomIntEditor(const SessionItem& item);
QWidget* createCustomStringEditor(const SessionItem& item);

//! Single step for QDoubleSpinBox.

double singleStep(const SessionItem& item) {
    // For item with decimals=3 (i.e. 0.001) single step will be 0.1
    return 1. / std::pow(10., item.decimals() - 1);
}

bool isDoubleProperty(const QVariant& variant)
{
    return variant.type() == QVariant::Double;
}

bool isIntProperty(const QVariant& variant)
{
    return variant.type() == QVariant::Int;
}

bool isMaterialProperty(const QVariant& variant)
{
    return variant.canConvert<MaterialProperty>();
}

bool isColorProperty(const QVariant& variant)
{
    return variant.canConvert<ColorProperty>();
}

bool isGroupProperty(const QVariant& variant)
{
    return variant.canConvert<GroupProperty_t>();
}

bool isComboProperty(const QVariant& variant)
{
    return variant.canConvert<ComboProperty>();
}

bool isScientificDoubleProperty(const QVariant& variant)
{
    return variant.canConvert<ScientificDoubleProperty>();
}

bool isStringProperty(const QVariant& variant)
{
    return variant.type() == QVariant::String;
}

}

bool PropertyEditorFactory::IsCustomVariant(const QVariant& variant)
{
    if (isMaterialProperty(variant))
        return true;
    if (isColorProperty(variant))
        return true;
    if (isGroupProperty(variant))
        return true;
    if (isComboProperty(variant))
        return true;
    if (isScientificDoubleProperty(variant))
        return true;

    return false;
}

// TODO replace with template method when custom variants refactored
QString PropertyEditorFactory::ToString(const QVariant& variant)
{
    if (isMaterialProperty(variant))
        return variant.value<MaterialProperty>().getName();
    if (isColorProperty(variant))
        return variant.value<ColorProperty>().getText();
    if (isGroupProperty(variant))
        return variant.value<GroupProperty_t>()->currentLabel();
    if (isComboProperty(variant))
        return variant.value<ComboProperty>().getValue();
    if (isScientificDoubleProperty(variant))
        return variant.value<ScientificDoubleProperty>().getText();

    return QString();
}


QWidget* PropertyEditorFactory::CreateEditor(const SessionItem& item, QWidget* parent)
{
    QWidget* result(nullptr);

    if (isDoubleProperty(item.value())) {
        result = createCustomDoubleEditor(item);
    }

    else if(isIntProperty(item.value())) {
        result = createCustomIntEditor(item);
    }

    else if(isStringProperty(item.value())) {
        result = createCustomStringEditor(item);
    }

    else if(isMaterialProperty(item.value())) {
        auto editor = new MaterialPropertyEditor;
        editor->setData(item.value());
        result = editor;
    }

    else if(isColorProperty(item.value())) {
        auto editor = new ColorPropertyEditor;
        editor->setData(item.value());
        result = editor;
    }

    else if(isGroupProperty(item.value())) {
        auto editor = new GroupPropertyEditor;
        editor->setData(item.value());
        result = editor;
    }

    else if(isComboProperty(item.value())) {
        auto editor = new ComboPropertyEditor;
        editor->setData(item.value());
        result = editor;
    }

    else if(isScientificDoubleProperty(item.value())) {
        auto editor = new ScientificDoublePropertyEditor;
        editor->setData(item.value());
        result = editor;
    }

    if (parent && result)
        result->setParent(parent);

    return result;
}



namespace {

QWidget* createCustomDoubleEditor(const SessionItem& item)
{
    auto result = new QDoubleSpinBox;

    result->setDecimals(item.decimals());
    result->setSingleStep(singleStep(item));

    RealLimits limits = item.limits();
    if (limits.hasLowerLimit())
        result->setMinimum(limits.getLowerLimit());
    if (limits.hasUpperLimit())
        result->setMaximum(limits.getUpperLimit());

    result->setValue(item.value().toDouble());
    return result;
}

QWidget* createCustomIntEditor(const SessionItem& item)
{
    auto result = new QSpinBox;

    RealLimits limits = item.limits();
    if (limits.hasLowerLimit())
        result->setMinimum(static_cast<int>(limits.getLowerLimit()));
    if (limits.hasUpperLimit())
        result->setMaximum(static_cast<int>(limits.getUpperLimit()));

    result->setValue(item.value().toInt());

    return result;
}

QWidget* createCustomStringEditor(const SessionItem& item)
{
    QWidget* result(nullptr);

    if (item.isEditable()) {
        auto editor = new QLineEdit;
        editor->setText(item.value().toString());
        result = editor;
    } else {
        auto editor = new QLabel;
        editor->setText(item.value().toString());
        result = editor;
    }

    return result;
}

}

