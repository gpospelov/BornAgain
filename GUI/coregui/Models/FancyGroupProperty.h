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

    FancyGroupProperty(ParameterizedItem *parent = 0);
    virtual ~FancyGroupProperty(){}

    virtual GroupType type() const { return UndefinedGroupType; }

    virtual ParameterizedItem *createCorrespondingItem(const QString &name=QString());

    virtual QString getGroupName() const;
    virtual void setGroupName(const QString &group_name);

//    virtual QString getGroupLabel() const;
//    virtual void setGroupLabel(const QString &group_label);

    virtual QString getValue() const;
    virtual void setValue(const QString &value);

    virtual QString getValueLabel() const;
    virtual void setValueLabel(const QString &value_label);

    virtual QStringList getValues() const;
    virtual QStringList getValueLabels() const;

    virtual void setParent(ParameterizedItem *parent);

    virtual int index() const;
    virtual int toIndex(const QString &value) const;
    virtual QString toString(int index) const;

protected:
    ParameterizedItem *m_parent;
    QString m_group_name;
//    QString m_group_label;
    QString m_value;
    QString m_value_label;
};

Q_DECLARE_METATYPE(FancyGroupProperty *)





#endif
