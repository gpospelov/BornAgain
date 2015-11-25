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

#include <map>
#include <QString>
#include <QMetaType>
#include <QSharedPointer>
#include <QVariant>

class ParameterizedItem;

class BA_CORE_API_ FancyGroupProperty
{
public:
    enum EGroupType { UNDEFINED, FIXED, SELECTABLE };

    FancyGroupProperty(const QString &group_name);

    EGroupType type() const;

    void setParent(ParameterizedItem *parent);

    ParameterizedItem *createCorrespondingItem();

    QString getGroupName() const;

    QString getCurrentType() const;
    void setCurrentType(const QString &type);

    QString getCurrentLabel() const;
    void setCurrentLabel(const QString &label);

    QStringList getTypes() const;
    QStringList getLabels() const;

    int index() const;
    int toIndex(const QString &type) const;
    QString toString(int index) const;

    friend class GroupPropertyRegistry;

private:
    void setGroupMap(std::map<QString, QString> group_map);
    void setGroupType(EGroupType group_type);

    QString m_group_name;
    EGroupType m_group_type;
    ParameterizedItem *m_parent;
    QString m_current_type;

    std::map<QString, QString > m_type_label_map;
};

typedef QSharedPointer<FancyGroupProperty> FancyGroupProperty_t;

Q_DECLARE_METATYPE(FancyGroupProperty_t)


#endif
