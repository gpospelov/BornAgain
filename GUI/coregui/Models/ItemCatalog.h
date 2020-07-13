// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ItemCatalog.h
//! @brief     Defines class ItemCatalog
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_ITEMCATALOG_H
#define BORNAGAIN_GUI_COREGUI_MODELS_ITEMCATALOG_H

#include "Core/StandardSamples/IFactory.h"
#include "Wrap/WinDllMacros.h"
#include <QStringList>
#include <memory>

class SessionItem;

class BA_CORE_API_ ItemCatalog
{
public:
    using factory_function_t = std::function<SessionItem*()>;

    ItemCatalog();

    bool contains(const QString& modelType) const;

    std::unique_ptr<SessionItem> create(const QString& modelType) const;

    QStringList validTopItemTypes() const;

private:
    void add(const QString& modelType, factory_function_t f);
    void init_top_item_types();

    IFactory<QString, SessionItem> m_data;
    QStringList m_valid_top_item_types;
};

#endif // BORNAGAIN_GUI_COREGUI_MODELS_ITEMCATALOG_H
