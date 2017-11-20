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
#include <QDoubleSpinBox>
#include <QSpinBox>

namespace {
QDoubleSpinBox* createCustomDoubleEditor(SessionItem& item);
QSpinBox* createCustomIntEditor(SessionItem& item);

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

bool isGroupProperty(const QVariant& variant)
{
    return variant.canConvert<GroupProperty_t>();
}

}


QWidget* PropertyEditorFactory::CreateEditor(SessionItem& item, QWidget* parent)
{
    QWidget* result(nullptr);

    if (isDoubleProperty(item.value())) {
        auto editor = createCustomDoubleEditor(item);
        editor->setValue(item.value().toDouble());
        result = editor;
    }

    else if(isIntProperty(item.value())) {
        auto editor = createCustomIntEditor(item);
        editor->setValue(item.value().toInt());
        result = editor;
    }

    else if(isMaterialProperty(item.value())) {
        auto editor = new MaterialPropertyEditor;
        editor->setData(item.value());
        result = editor;
    }

    else if(isGroupProperty(item.value())) {
        auto editor = new GroupPropertyEditor;
        editor->setData(item.value());
        result = editor;
    }

    if (parent && result)
        result->setParent(parent);

    return result;
}



namespace {

QDoubleSpinBox* createCustomDoubleEditor(SessionItem& item)
{
    auto result = new QDoubleSpinBox;

    result->setDecimals(item.decimals());
    result->setSingleStep(singleStep(item));

    RealLimits limits = item.limits();
    if (limits.hasLowerLimit())
        result->setMinimum(limits.getLowerLimit());
    if (limits.hasUpperLimit())
        result->setMaximum(limits.getUpperLimit());

    return result;
}

QSpinBox* createCustomIntEditor(SessionItem& item)
{
    auto result = new QSpinBox;

    RealLimits limits = item.limits();
    if (limits.hasLowerLimit())
        result->setMinimum(static_cast<int>(limits.getLowerLimit()));
    if (limits.hasUpperLimit())
        result->setMaximum(static_cast<int>(limits.getUpperLimit()));

    return result;
}

}
