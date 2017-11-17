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
#include <QDoubleSpinBox>

namespace {
QWidget* createCustomDoubleEditor(SessionItem& item);

//! Single step for QDoubleSpinBox.

double singleStep(const SessionItem& item) {
    // For item with decimals=3 (i.e. 0.001) single step will be 0.1
    return 1. / std::pow(10., item.decimals() - 1);
}

bool isDoubleProperty(const QVariant& variant)
{
    return variant.type() == QVariant::Double;
}

}


QWidget* PropertyEditorFactory::CreateEditor(SessionItem& item, QWidget* parent)
{
    QWidget* result(nullptr);

    if (isDoubleProperty(item.value())) {
        result = createCustomDoubleEditor(item);
    }

    if (parent && result)
        result->setParent(parent);

    return result;
}



namespace {

QWidget* createCustomDoubleEditor(SessionItem& item)
{
    auto result = new QDoubleSpinBox;

    result->setDecimals(item.decimals());
    result->setSingleStep(singleStep(item));

    RealLimits limits = item.limits();
    if (limits.hasLowerLimit())
        result->setMinimum(item.limits().getLowerLimit());
    if (limits.hasUpperLimit())
        result->setMaximum(item.limits().getUpperLimit());

    return result;
}

}
