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

    explicit PropertyAttribute(Appearance appearance=VisibleProperty, const QString &label = QString())
        : m_appearance(appearance)
        , m_label(label)
        , m_limits(AttLimits::limitless()){ }
//    PropertyAttribute(const QString &label)
//        : m_appearance(VisibleProperty)
//        , m_label(label)
//        , m_limits(AttLimits::limitless()){ }

    explicit PropertyAttribute(AttLimits limits)
        : m_appearance(VisibleProperty)
        , m_label(QString())
        , m_limits(limits){ }

    static PropertyAttribute visibleProperty() { return PropertyAttribute(VisibleProperty); }
    static PropertyAttribute hiddenProperty() { return PropertyAttribute(HiddenProperty); }
    static PropertyAttribute disabledProperty() { return PropertyAttribute(DisabledProperty); }

    Appearance getAppearance() const { return m_appearance; }
    void setAppearance(Appearance appearance) { m_appearance = appearance; }
    QString getLabel() const { return m_label; }
    void setLabel(const QString &label) { m_label = label; }


    AttLimits getLimits() const {return m_limits;}
    void setLimits(AttLimits limits) {m_limits = limits;}

//    bool isHiddenProperty();

private:
    Appearance m_appearance;
    QString m_label;
    AttLimits m_limits;
};



#endif

