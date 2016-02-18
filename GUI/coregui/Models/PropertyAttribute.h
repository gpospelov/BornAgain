// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/PropertyAttribute.h
//! @brief     Defines class PropertyAttribute
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PROPERTYATTRIBUTE_H
#define PROPERTYATTRIBUTE_H


#include <QString>
#include "AttLimits.h"
#include <QMetaType>


//! Class to handle visual appearance of ParameterizedItem's property in
//! different kind of property editors.
class BA_CORE_API_ PropertyAttribute {
public:
    enum EAppearance {
        VISIBLE = 0x0000,
        HIDDEN = 0x0001,
        DISABLED = 0x0002,
        READONLY = 0x0004
    };

    explicit PropertyAttribute(EAppearance appearance = VISIBLE,
                               const AttLimits &limits = AttLimits::lowerLimited(0.0),
                               int decimals = 2, const QString &label = QString(),
                               const QString &tooltip = QString());

    explicit PropertyAttribute(const AttLimits &limits, int decimals=2);

    static PropertyAttribute labeled(const QString &label);

    EAppearance getAppearance() const;
    void setAppearance(EAppearance appearance);

    AttLimits getLimits() const;
    PropertyAttribute& setLimits(const AttLimits &limits);
    PropertyAttribute& lowerLimited(double value);
    PropertyAttribute& upperLimited(double value);
    PropertyAttribute& limited(double left_bound_value, double right_bound_value);
    PropertyAttribute& limitless();

    int getDecimals() const;
    PropertyAttribute& setDecimals(int decimals);

    QString getLabel() const;
    PropertyAttribute& setLabel(const QString &label);

    QString getToolTip() const;
    PropertyAttribute& setToolTip(const QString &tooltip);

    bool isVisible() const;
    PropertyAttribute& setVisible();

    bool isHidden() const;
    PropertyAttribute& setHidden();

    bool isDisabled() const;
    PropertyAttribute& setDisabled();

    bool isReadOnly() const;
    PropertyAttribute& setReadOnly();

private:
    EAppearance m_appearance;
    AttLimits m_limits;
    int m_decimals; // number of digits
    QString m_label;
    QString m_tooltip;
};

Q_DECLARE_METATYPE(PropertyAttribute);
#endif

