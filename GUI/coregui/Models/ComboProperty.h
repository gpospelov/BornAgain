#ifndef COMBO_PROPERTY_H
#define COMBO_PROPERTY_H

#include <QStringList>
#include <QMetaType>
#include <QVariant>

//! The ComboProperty defines ParameterizedItem's property with a value
//! from predefined list.
//!
//! This is a light version of GroupProperty without SubItem mechanism
class ComboProperty
{
public:

    ComboProperty(const QStringList &values = QStringList(), const QString &current_value = QString("Undefined"));
    virtual ~ComboProperty(){}
    QString getValue() const { return m_current_value; }

    void setValue(const QString &name);
    bool operator!=(const ComboProperty &other) {
        return (getValue() != other.getValue());
    }
    bool isDefined() { return m_current_value != QStringLiteral("Undefined"); }

    QStringList getValues() const { return m_values;}

    int index() const;
    int toIndex(const QString &value) const;
    QString toString(int index) const;

    inline ComboProperty &operator<<(const QString &str)
    {
        m_values.append(str);
        if(m_values.size()) m_current_value=m_values.at(0);
        return *this;
    }


    QVariant getVariant() const {
        QVariant result;
        result.setValue(*this);
        return result;
    }

private:
    QStringList m_values;
    QString m_current_value;
};

Q_DECLARE_METATYPE(ComboProperty)



#endif
