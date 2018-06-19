// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/PropertyEditor/PropertyEditorFactory.cpp
//! @brief     Implements PropertyEditorFactory namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "PropertyEditorFactory.h"
#include "SessionItem.h"
#include "RealLimits.h"
#include "ExternalProperty.h"
#include "GroupItemController.h"
#include "CustomEditors.h"
#include "ComboProperty.h"
#include "CustomEventFilters.h"
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QLineEdit>
#include <QLabel>
#include <limits>

namespace {
QWidget* createCustomStringEditor(const SessionItem& item);

bool isDoubleProperty(const QVariant& variant)
{
    return variant.type() == QVariant::Double;
}

bool isIntProperty(const QVariant& variant)
{
    return variant.type() == QVariant::Int;
}

bool isExternalProperty(const QVariant& variant)
{
    return variant.canConvert<ExternalProperty>();
}

bool isComboProperty(const QVariant& variant)
{
    return variant.canConvert<ComboProperty>();
}

bool isStringProperty(const QVariant& variant)
{
    return variant.type() == QVariant::String;
}

bool isBoolProperty(const QVariant& variant)
{
    return variant.type() == QVariant::Bool;
}

}

bool PropertyEditorFactory::IsCustomVariant(const QVariant& variant)
{
    if (isExternalProperty(variant))
        return true;
    if (isComboProperty(variant))
        return true;
    if (isBoolProperty(variant))
        return true;

    return false;
}

QString PropertyEditorFactory::ToString(const QVariant& variant)
{
    if (isExternalProperty(variant))
        return variant.value<ExternalProperty>().text();
    if (isComboProperty(variant))
        return variant.value<ComboProperty>().getValue();
    if (isBoolProperty(variant))
        return variant.toBool() ? "True" : "False";

    return QString();
}


QWidget* PropertyEditorFactory::CreateEditor(const SessionItem& item, QWidget* parent)
{
    QWidget* result(nullptr);

    if (isDoubleProperty(item.value())) {
        if (item.editorType() == Constants::ScientificEditorType) {
            auto editor = new ScientificDoublePropertyEditor;
            auto limits = item.limits();
            editor->setLimits(limits);
            editor->setData(item.value());
            result = editor;
        } else {
            auto editor = new DoubleEditor;
            editor->setLimits(item.limits());
            editor->setDecimals(item.decimals());
            editor->setData(item.value());
            result = editor;
        }
    }
    else if(isIntProperty(item.value())) {
        auto editor = new IntEditor;
        editor->setLimits(item.limits());
        editor->setData(item.value());
        result = editor;
    }
    else if(isBoolProperty(item.value())) {
        auto editor = new BoolEditor;
        editor->setData(item.value());
        result = editor;
    }
    else if(isStringProperty(item.value())) {
        result = createCustomStringEditor(item);
    }
    else if(isExternalProperty(item.value())) {
        auto editor = new ExternalPropertyEditor;
        editor->setData(item.value());
        if (item.editorType() != Constants::DefaultEditorType)
            editor->setExternalDialogType(item.editorType());
        result = editor;
    }
    else if(isComboProperty(item.value())) {
        auto editor = new ComboPropertyEditor;
        editor->setData(item.value());
        result = editor;
    }
    if (parent && result)
        result->setParent(parent);

    return result;
}



namespace {

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

