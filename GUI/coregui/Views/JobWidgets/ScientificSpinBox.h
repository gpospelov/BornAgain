// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/ScientificSpinBox.h
//! @brief     Defines class ScientificSpinBox
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef SCIENTIFICSPINBOX_H
#define SCIENTIFICSPINBOX_H

#include "WinDllMacros.h"
#include <QAbstractSpinBox>

class BA_CORE_API_ ScientificSpinBox : public QAbstractSpinBox
{
    Q_OBJECT
public:
    ScientificSpinBox(QWidget* parent = nullptr);
    ~ScientificSpinBox() override;

    double value() const;
    void setValue(double val);

    double valueFromText(const QString& text) const;
    QString textFromValue(double val) const;

    double singleStep() const;
    void setSingleStep(double step);

    double minimum() const;
    void setMinimum(double min);

    double maximum() const;
    void setMaximum(double max);

    void setDecimalPoints(int val);
    int decimalPoints() const;

    static QString toString(double val, int decimal_points);
    static double toDouble(QString text, const QDoubleValidator& validator,
                           double min, double max, double default_value);
signals:
    void valueChanged(double value);

private:
    void setDecimals(int);
    int decimals() const;
    void updateLineEdit(double val);

    double m_value, m_min, m_max;
    double m_step;
    int m_decimal_points;
    QDoubleValidator m_validator;
};

#endif // SCIENTIFICSPINBOX_H
