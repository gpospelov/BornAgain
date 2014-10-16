#ifndef PROPERTYATTRIBUTE_H
#define PROPERTYATTRIBUTE_H


#include <QString>
#include "AttLimits.h"

class QGraphicsItem;


//! Class to handle visual appearance of ParameterizedItem's property in
//! different kind of property editors.
class BA_CORE_API_ PropertyAttribute {
public:
    enum Appearance {
        VisibleProperty = 0x0000,
        HiddenProperty = 0x0001,
        DisabledProperty = 0x0002
    };

    explicit PropertyAttribute(Appearance appearance=VisibleProperty, const AttLimits &limits=AttLimits::lowerLimited(0.0), int decimals=3, const QString &label = QString())
        : m_appearance(appearance)
        , m_label(label)
        , m_limits(limits)
        , m_decimals(decimals){ }

    explicit PropertyAttribute(const AttLimits &limits, int decimals=2)
        : m_appearance(VisibleProperty)
        , m_label(QString())
        , m_limits(limits)
        , m_decimals(decimals){ }

    static PropertyAttribute visibleProperty() { return PropertyAttribute(VisibleProperty); }
    static PropertyAttribute hiddenProperty() { return PropertyAttribute(HiddenProperty); }
    static PropertyAttribute disabledProperty() { return PropertyAttribute(DisabledProperty); }

    Appearance getAppearance() const { return m_appearance; }
    void setAppearance(Appearance appearance) { m_appearance = appearance; }

    QString getLabel() const { return m_label; }
    void setLabel(const QString &label) { m_label = label; }

    AttLimits getLimits() const {return m_limits;}
    void setLimits(AttLimits limits) {m_limits = limits;}

    int getDecimals() const { return m_decimals; }
    void setDecimals(int decimals) { m_decimals = decimals; }

private:
    Appearance m_appearance;
    QString m_label;
    AttLimits m_limits;
    int m_decimals; // number of digits
};



#endif

