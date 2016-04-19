// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/GroupPropertyRegistry.h
//! @brief     Declares class GroupPropertyRegistry
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef GROUPPROPERTYREGISTRY_H
#define GROUPPROPERTYREGISTRY_H

#include "WinDllMacros.h"
#include "item_constants.h"
#include "GroupProperty.h"

#include <map>
#include <QString>

class SessionItem;

//! The GroupPropertyRegistry is responsible for constructing GroupProperty objects
//! according to the given name of the group.
class BA_CORE_API_ GroupPropertyRegistry
{
public:
    using SelectableGroupMap_t = std::map<QString, std::map<QString, QString>>;

    static bool isValidGroup(const QString &group_type);

    static GroupProperty_t createGroupProperty(const QString &group_name,
            const Constants::ModelType &group_type);

private:
    static SelectableGroupMap_t m_selectable_group_map;
    //!< Contains correspondance of selectable group names to their content,
    //!< which is a map between item types and item labels
};


#endif
