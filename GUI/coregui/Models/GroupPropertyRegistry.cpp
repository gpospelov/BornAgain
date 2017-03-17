// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/GroupPropertyRegistry.cpp
//! @brief     Implements class GroupPropertyRegistry
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "GroupPropertyRegistry.h"
#include "GroupInfoCatalogue.h"

bool GroupPropertyRegistry::isValidGroup(const QString& group_type)
{
    return catalogue().containsGroup(group_type);
}

GroupProperty_t GroupPropertyRegistry::createGroupProperty(const QString& group_name,
                                                           const Constants::ModelType& group_type)
{
    GroupProperty_t result(new GroupProperty(group_name));
    result->setGroupInfo(catalogue().groupInfo(group_type));
    return result;
}

const GroupInfoCatalogue& GroupPropertyRegistry::catalogue()
{
    static GroupInfoCatalogue s_catalogue = GroupInfoCatalogue();
    return s_catalogue;
}
