// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/GroupPropertyRegistry.h
//! @brief     Defines class GroupPropertyRegistry
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

#include "GroupProperty.h"
#include "GroupInfoCatalogue.h"
#include "item_constants.h"

//! Constructs GroupProperty objects according to the given group type.

class BA_CORE_API_ GroupPropertyRegistry
{
public:
    static bool isValidGroup(const QString& group_type);

    static GroupProperty_t createGroupProperty(const QString& group_name,
                                               const Constants::ModelType& group_type);

private:
    static const GroupInfoCatalogue& catalogue();
};

#endif // GROUPPROPERTYREGISTRY_H
