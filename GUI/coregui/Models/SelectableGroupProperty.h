#ifndef SELECTABLEGROUPPROPERTY_H
#define SELECTABLEGROUPPROPERTY_H

#include "FancyGroupProperty.h"
#include <QStringList>

class SelectableGroupProperty : public FancyGroupProperty
{
public:

    SelectableGroupProperty() {}
    ~SelectableGroupProperty(){}

    virtual GroupType type() const { return SelectableGroupType; }

    ParameterizedItem *createCorrespondingItem(const QString &name = QString());


    void setGroupMap(const QMap<QString, QString > &group_map);

    QStringList getValues() const;
    QStringList getValueLabels() const;
    QString getValueLabel() const;

    void setValue(const QString &value);

private:
    QMap<QString, QString > m_group_map;
    //!< Correspondance of item type to item label
};


Q_DECLARE_METATYPE(SelectableGroupProperty*)



#endif
