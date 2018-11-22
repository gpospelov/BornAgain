// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/ScientificSpinBox.cpp
//! @brief     Implements class ScientificSpinBox
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "ScientificSpinBox.h"
#include <cmath>
#include <QLineEdit>

namespace
{
const double upper_switch = 100;
const double lower_switch = 0.1;
const double min_val = std::numeric_limits<double>::min();
const double max_val = std::numeric_limits<double>::max();

bool useExponentialNotation(double val);
} // namespace

ScientificSpinBox::ScientificSpinBox(QWidget* parent)
    : QAbstractSpinBox(parent)
    , m_min(-max_val)
    , m_max(max_val)
    , m_decimal_points(3)
{
    lineEdit()->setValidator(nullptr); // disables validation on input

    QLocale locale;
    locale.setNumberOptions(QLocale::RejectGroupSeparator);
    m_validator.setLocale(locale);
    m_validator.setNotation(QDoubleValidator::ScientificNotation);
}

double ScientificSpinBox::value() const
{
    return m_value;
}

void ScientificSpinBox::setValue(double val)
{
    if(val != m_value) {
        m_value = val;
        updateLineEdit(val);
        emit valueChanged(val);
    }
}

ScientificSpinBox::~ScientificSpinBox() = default;

double ScientificSpinBox::valueFromText(const QString& text) const
{
    return toDouble(text, m_validator, minimum(), maximum(), value());
}

QString ScientificSpinBox::textFromValue(double val) const
{
    return toString(val, m_decimal_points);
}

double ScientificSpinBox::singleStep() const
{
    return m_step;
}

void ScientificSpinBox::setSingleStep(double step)
{
    m_step = step;
}

double ScientificSpinBox::minimum() const
{
    return m_min;
}

void ScientificSpinBox::setMinimum(double min)
{
    m_min = min;
}

double ScientificSpinBox::maximum() const
{
    return m_max;
}

void ScientificSpinBox::setMaximum(double max)
{
    m_max = max;
}

void ScientificSpinBox::setDecimalPoints(int val)
{
    if (val > 0)
        m_decimal_points = val;
}

int ScientificSpinBox::decimalPoints() const
{
    return m_decimal_points;
}

QString ScientificSpinBox::toString(double val, int decimal_points)
{
    QString result = useExponentialNotation(val) ? QString::number(val, 'e', decimal_points)
                                                 : QString::number(val, 'f', decimal_points);

    return result.replace(QRegExp("(\\.?0+)?((e{1}[\\+|-]{1})(0+)?([1-9]{1}.*))?$"), "\\3\\5");
}

double ScientificSpinBox::toDouble(QString text, const QDoubleValidator& validator,
                                   double min, double max, double default_value)
{
    int pos = 0;
    if (validator.validate(text, pos) == QValidator::Acceptable) {
        double new_val = validator.locale().toDouble(text);
        if (std::abs(new_val) < min_val)
            new_val = 0.0;
        return new_val >= min && new_val <= max ? new_val : default_value;
    }
    return default_value;
}

void ScientificSpinBox::updateLineEdit(double val)
{
    lineEdit()->setText(toString(val, m_decimal_points));
}

namespace
{
bool useExponentialNotation(double val)
{
    const double abs_val = std::abs(val);

    if (abs_val <= min_val)
        return false;

    return abs_val >= upper_switch || abs_val < lower_switch;
}
} // namespace
