// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/GroupPropertyRegistry.h
//! @brief     Defines class GroupPropertyRegistry
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef GROUPPROPERTYREGISTRY_H
#define GROUPPROPERTYREGISTRY_H

#include "WinDllMacros.h"
#include "item_constants.h"
#include "FancyGroupProperty.h"
#include <QMap>
#include <QString>

//class FancyGroupProperty_t;
class SelectableGroupProperty;
class FixedGroupProperty;
class ParameterizedItem;

//! The GroupPropertyRegistry constructs FancyGroupProperty or SelectableGroupProperty
//! according to the given name of the group.
class BA_CORE_API_ GroupPropertyRegistry
{
public:
    //! correspondance of group name to ParameterizedItem's types to labels
    typedef QMap<QString, QMap<QString, QString> > SelectableGroupMap_t;

    static FancyGroupProperty_t createGroupProperty(const QString &group_name, const Constants::ModelType &group_model = Constants::ModelType());

private:
//    static SelectableGroupProperty *createSelectableGroupProperty(const QString &group_name, ParameterizedItem *parent = 0);
//    static FixedGroupProperty *createFixedGroupProperty(const QString &group_name, ParameterizedItem *parent = 0);

    static SelectableGroupMap_t m_selectable_group_map;
    //!< Contains correspondance of selectable group names to they content,
    //!< namely item type and item label
};


#endif
