// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/GroupProperty.h
//! @brief     Defines class GroupProperty
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef GROUPPROPERTY_H
#define GROUPPROPERTY_H

#include "WinDllMacros.h"
#include <QSharedPointer>
#include <QStringList>

class SessionItem;

//! The GroupProperty class represents a composition of the basic properties
//! corresponding to a SessionItem object.
//! Its construction is handled by a GroupPropertyRegistry object.
class BA_CORE_API_ GroupProperty
{
public:
    void setGroupItem(SessionItem *groupItem);

    SessionItem *getCurrentItem();

    SessionItem *createCorrespondingItem();

    QString getCurrentType() const;
    void setCurrentType(const QString &type, bool = true);

    QString getCurrentLabel() const;

    QStringList getTypes() const;
    QStringList getLabels() const;

    int index() const;
    int toIndex(const QString &type) const;
    QString toString(int index) const;

    friend class GroupPropertyRegistry;

private:
    GroupProperty(QString group_name);
    void setGroupMap(std::map<QString, QString> group_map);

    QString m_group_name;
    SessionItem *m_groupItem;
    QString m_current_type;
    std::map<QString, QString > m_type_label_map;
};

typedef QSharedPointer<GroupProperty> GroupProperty_t;
Q_DECLARE_METATYPE(GroupProperty_t)

#endif // GROUPPROPERTY_H
