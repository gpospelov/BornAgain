// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/GroupInfoCatalogue.h
//! @brief     Defines class GroupInfoCatalogue
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef GROUPINFOCATALOGUE_H
#define GROUPINFOCATALOGUE_H

#include "GroupInfo.h"

//! Catalogue to hold info for GroupProperty creation.

class BA_CORE_API_ GroupInfoCatalogue
{
public:
    GroupInfoCatalogue();

private:
    bool containsGroup(const QString& groupType) const;
    void addInfo(const GroupInfo& info);
    QVector<GroupInfo> m_groups;
};

#endif // GROUPINFOCATALOGUE_H
