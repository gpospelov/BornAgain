// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ItemFactory.cpp
//! @brief     Implements class ItemFactory
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "ItemFactory.h"
#include "GUIHelpers.h"
#include "ItemCatalogue.h"

namespace
{
ItemCatalogue item_catalogue;
}

SessionItem* ItemFactory::CreateItem(const QString& model_name, SessionItem* parent)
{
    if (!item_catalogue.contains(model_name))
        throw GUIHelpers::Error("ItemFactory::createItem() -> Error: Model name does not exist: "
                                + model_name);

    SessionItem* result = item_catalogue.create(model_name).release();
    if (parent)
        parent->insertItem(-1, result);

    return result;
}

SessionItem* ItemFactory::CreateEmptyItem()
{
    return new SessionItem(QStringLiteral("ROOT_ITEM"));
}

QStringList ItemFactory::ValidTopItemTypes()
{
    return item_catalogue.validTopItemTypes();
}
