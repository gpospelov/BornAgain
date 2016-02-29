// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/GroupProperty.h
//! @brief     Defines class GroupProperty
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef GROUPPROPERTY_H
#define GROUPPROPERTY_H

#include "WinDllMacros.h"
#include "item_constants.h"

#include <map>
#include <QString>
#include <QMetaType>
#include <QSharedPointer>

class ParameterizedItem;

//! The GroupProperty class represents a composition of the basic properties
//! corresponding to a ParameterizedItem object.
//! Its construction is handled by a GroupPropertyRegistry object.
class BA_CORE_API_ GroupProperty
{
public:
    enum EGroupType { UNDEFINED, FIXED, SELECTABLE };

    EGroupType type() const;

    void setParent(ParameterizedItem *parent);

    ParameterizedItem *getCurrentItem();

    ParameterizedItem *createCorrespondingItem();

    QString getGroupName() const;

    QString getCurrentType() const;
    void setCurrentType(const QString &type, bool persistent = true);

    QString getCurrentLabel() const;
    void setCurrentLabel(const QString &label);

    QStringList getTypes() const;
    QStringList getLabels() const;

    int index() const;
    int toIndex(const QString &type) const;
    QString toString(int index) const;

    friend class GroupPropertyRegistry;
private:
    GroupProperty(QString group_name);

    void setGroupMap(std::map<QString, QString> group_map);
    void setGroupType(EGroupType group_type);

    QString m_group_name;
    EGroupType m_group_type;
    ParameterizedItem *m_parent;
    QString m_current_type;

    std::map<QString, QString > m_type_label_map;
};

typedef QSharedPointer<GroupProperty> GroupProperty_t;

Q_DECLARE_METATYPE(GroupProperty_t)


#endif
