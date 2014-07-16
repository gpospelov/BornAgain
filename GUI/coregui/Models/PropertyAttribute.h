#ifndef PROPERTYATTRIBUTE_H
#define PROPERTYATTRIBUTE_H


#include <QString>

class QGraphicsItem;


//! Class to handle visual appearance of ParameterizedItem's property in
//! different kind of property editors.
class PropertyAttribute {
public:
    enum Appearance {
        VisibleProperty = 0x0000,
        HiddenProperty = 0x0001,
        DisabledProperty = 0x0002
    };

    PropertyAttribute(Appearance appearance=VisibleProperty, const QString &label = QString())
        : m_appearance(appearance)
        , m_label(label) { }
    PropertyAttribute(const QString &label)
        : m_appearance(VisibleProperty)
        , m_label(label) { }

    static PropertyAttribute visibleProperty() { return PropertyAttribute(VisibleProperty); }
    static PropertyAttribute hiddenProperty() { return PropertyAttribute(HiddenProperty); }
    static PropertyAttribute disabledProperty() { return PropertyAttribute(DisabledProperty); }

    Appearance getAppearance() const { return m_appearance; }
    void setAppearance(Appearance appearance) { m_appearance = appearance; }
    QString getLabel() const { return m_label; }
    void setLabel(const QString &label) { m_label = label; }

private:
    Appearance m_appearance;
    QString m_label;
};



#endif

