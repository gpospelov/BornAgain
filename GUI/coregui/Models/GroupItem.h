// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/GroupItem.h
//! @brief     Defines class GroupItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef GROUPITEM_H
#define GROUPITEM_H

#include "SessionItem.h"
#include "GroupProperty.h"

class BA_CORE_API_ GroupItem : public SessionItem
{

public:
    static const QString T_ITEMS;
    GroupItem();
    void setGroup(GroupProperty_t group);
    GroupProperty_t group() const;
    SessionItem *currentItem();
};

#endif // GROUPITEM_H

