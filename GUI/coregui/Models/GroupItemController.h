// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/GroupItemController.h
//! @brief     Defines class GroupItemController
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef GROUPITEMCONTROLLER_H
#define GROUPITEMCONTROLLER_H

#include "GroupInfo.h"
#include <QSharedPointer>
#include <QStringList>

class SessionItem;

//! Provides logic for manipulating items belonging to GroupItem parent.

class BA_CORE_API_ GroupItemController
{
public:
    void setGroupItem(SessionItem* groupItem);

    SessionItem* currentItem();

    QString currentType() const;
    void setCurrentType(const QString& type);
    void setCurrentTypeName(const QString& type);

    SessionItem* getItemOfType(const QString& type);

    int currentIndex() const;
    void setCurrentIndex(int index);

    QString currentLabel() const;

    QStringList itemTypes() const;
    QStringList itemLabels() const;

    GroupItemController();
    void setGroupInfo(GroupInfo groupInfo);

private:

    SessionItem* addItem(const QString& item_type);
    SessionItem* createCorrespondingItem();
    int toIndex(const QString& type) const;
    QString toString(int currentIndex) const;

    SessionItem* m_groupItem;
    QString m_current_type;
    GroupInfo m_groupInfo;
};

// TODO Remove simultaneously with qtpropertybrowserframework
typedef QSharedPointer<GroupItemController> ObsoleteGroupProperty_t;
Q_DECLARE_METATYPE(ObsoleteGroupProperty_t)

#endif // GROUPITEMCONTROLLER_H
