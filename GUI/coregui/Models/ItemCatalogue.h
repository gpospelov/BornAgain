// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ItemCatalogue.h
//! @brief     Defines class ItemCatalogue
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef ITEMCATALOGUE_H
#define ITEMCATALOGUE_H

#include "Core/StandardSamples/IFactory.h"
#include "Wrap/WinDllMacros.h"
#include <QStringList>
#include <memory>

class SessionItem;

class BA_CORE_API_ ItemCatalogue
{
public:
    using factory_function_t = std::function<SessionItem*()>;

    ItemCatalogue();

    bool contains(const QString& modelType) const;

    std::unique_ptr<SessionItem> create(const QString& modelType) const;

    QStringList validTopItemTypes() const;

private:
    void add(const QString& modelType, factory_function_t f);
    void init_top_item_types();

    IFactory<QString, SessionItem> m_data;
    QStringList m_valid_top_item_types;
};

#endif // ITEMCATALOGUE_H
