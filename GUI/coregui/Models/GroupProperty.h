#ifndef GROUPPROPERTY_H
#define GROUPPROPERTY_H

//#include "ParameterizedItem.h"

class ParameterizedItem;
#include <QString>
#include <QStringList>
#include <QMap>
#include <QMetaType>
#include <QVariant>

//! The GroupProperty defines ParameterizedItem's property with a value
//! from predefined list
class GroupProperty
{
public:
    typedef QMap<QString, QMap<QString, ParameterizedItem *(*)()> > GroupMap_t;

    enum GroupType {ComboGroup, FixedGroup};

    GroupProperty(QString group_name=QString(), QString value=QString());
    virtual ~GroupProperty(){}
    QString getValue() const { return m_value; }
    QString getGroupName() const { return m_group_name; }



    void setValue(const QString &name) { m_value = name; }
    bool operator!=(const GroupProperty &other) {
        return (getValue() != other.getValue()) || (getGroupName() != other.getGroupName()) ;
    }
    bool isDefined() { return m_value != QStringLiteral("Undefined"); }

    QStringList getValues() const {
        return m_group_map[m_group_name].keys();
    }

    int index() const;
    int toIndex(const QString &value) const;
    QString toString(int index) const;

    ParameterizedItem *createCorrespondingItem(QString name);

    GroupType getGroupType() const { return m_group_type; }
    void setGroupType(GroupType type) { m_group_type = type; }

    QString getGroupLabel() const { return m_group_label; }
    void setGroupLabel(QString label) { m_group_label = label; }

    QVariant getVariant() const {
        QVariant result;
        result.setValue(*this);
        return result;
    }

    QString getText() const {
        if(m_group_label.isEmpty()) {
            return m_value;
        } else {
            return m_group_label;
        }
    }

private:
    static GroupMap_t m_group_map;
    QString m_value;
    QString m_group_name;
    GroupType m_group_type;
    QString m_group_label;
};

Q_DECLARE_METATYPE(GroupProperty)

#endif // GROUPPROPERTY_H
