//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Export/MaterialKeyHandler.cpp
//! @brief     Implement class MaterialKeyHandler.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Core/Export/MaterialKeyHandler.h"
#include "Sample/Material/Material.h"
#include <algorithm>
#include <set>
#include <stdexcept>

std::string MaterialKeyHandler::mat2key(const Material* mat) const {
    return m_MatMap.at(mat);
}

std::map<const std::string, const Material*> MaterialKeyHandler::materialMap() const {
    return {};
}

void MaterialKeyHandler::insertMaterial(const Material* mat) {
    for (const auto& it: m_MatMap)
        if (*it.first == *mat) {
            m_MatMap.emplace(mat, it.second);
            return;
        }
    // material not found => create new key
    std::set<std::string> unique_keys;
    for (const auto& it: m_MatMap)
        unique_keys.insert(it.second);

    const std::string key = "material_" + std::to_string(unique_keys.size() + 1);
    m_MatMap.emplace(mat, key);
}
