// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/PropertyAttribute.h
//! @brief     Defines class ParticleLayoutItem
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

class QGraphicsItem;


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

    explicit PropertyAttribute(EAppearance appearance=VISIBLE, const AttLimits &limits=AttLimits::lowerLimited(0.0), int decimals=2, const QString &label = QString())
        : m_appearance(appearance)
        , m_label(label)
        , m_limits(limits)
        , m_decimals(decimals){ }

    explicit PropertyAttribute(const AttLimits &limits, int decimals=2)
        : m_appearance(VISIBLE)
        , m_label(QString())
        , m_limits(limits)
        , m_decimals(decimals){ }

    static PropertyAttribute visibleProperty() { return PropertyAttribute(VISIBLE); }
    static PropertyAttribute hiddenProperty() { return PropertyAttribute(HIDDEN); }
    static PropertyAttribute disabledProperty() { return PropertyAttribute(DISABLED); }
    static PropertyAttribute labeled(const QString &label) { return PropertyAttribute(VISIBLE, AttLimits::lowerLimited(0.0), 2, label); }

    EAppearance getAppearance() const { return m_appearance; }
    void setAppearance(EAppearance appearance) { m_appearance = appearance; }

    QString getLabel() const { return m_label; }
    void setLabel(const QString &label) { m_label = label; }

    AttLimits getLimits() const {return m_limits;}
    void setLimits(AttLimits limits) {m_limits = limits;}

    int getDecimals() const { return m_decimals; }
    void setDecimals(int decimals) { m_decimals = decimals; }

private:
    EAppearance m_appearance;
    QString m_label;
    AttLimits m_limits;
    int m_decimals; // number of digits
};



#endif

