#ifndef FANCYGROUPPROPERTY_H
#define FANCYGROUPPROPERTY_H


#include <QString>
#include <QMap>
#include <QMetaType>
#include <QVariant>

class ParameterizedItem;

class FancyGroupProperty
{
public:
    enum GroupType
    {
        UndefinedGroupType,
        FixedGroupType,
        SelectableGroupType
    };

    FancyGroupProperty(const QString &group_name);
    virtual ~FancyGroupProperty(){}

    virtual GroupType type() const;

    virtual void setParent(ParameterizedItem *parent);

    virtual ParameterizedItem *createCorrespondingItem();

    virtual QString getGroupName() const;

    virtual QString getValue() const;
    virtual void setValue(const QString &value);

    virtual QString getValueLabel() const;
    virtual void setValueLabel(const QString &value_label);

    virtual QStringList getValues() const;
    virtual QStringList getValueLabels() const;

    virtual int index() const;
    virtual int toIndex(const QString &value) const;
    virtual QString toString(int index) const;

    QVariant getVariant();

    friend class GroupPropertyRegistry;

protected:
    void setGroupMap(const QMap<QString, QString> &group_map);
    void setGroupType(GroupType group_type) { m_group_type = group_type; }

    QString m_group_name;
    GroupType m_group_type;
    ParameterizedItem *m_parent;
    QString m_value;

    QMap<QString, QString > m_group_map;
};

Q_DECLARE_METATYPE(FancyGroupProperty *)





#endif
