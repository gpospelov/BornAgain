// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/FancyGroupProperty.h
//! @brief     Defines class FancyGroupProperty
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FANCYGROUPPROPERTY_H
#define FANCYGROUPPROPERTY_H

#include "WinDllMacros.h"
#include "item_constants.h"

#include <QString>
#include <QMap>
#include <QMetaType>
#include <QSharedPointer>
#include <QVariant>

class ParameterizedItem;

class BA_CORE_API_ FancyGroupProperty
{
public:
    enum EGroupType { UNDEFINED, FIXED, SELECTABLE };

    FancyGroupProperty(const QString &group_name);
    virtual ~FancyGroupProperty(){}

    virtual EGroupType type() const;

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

    friend class GroupPropertyRegistry;

protected:
    void setGroupMap(const QMap<Constants::ModelType, QString> &group_map);
    void setGroupType(EGroupType group_type);

    QString m_group_name;
    EGroupType m_group_type;
    ParameterizedItem *m_parent;
    QString m_value;

    QMap<QString, QString > m_group_map;
};

typedef QSharedPointer<FancyGroupProperty> FancyGroupProperty_t;

Q_DECLARE_METATYPE(FancyGroupProperty_t)


#endif
