//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Export/MaterialKeyHandler.h
//! @brief     Defines class MaterialKeyHandler.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_CORE_EXPORT_MATERIALKEYHANDLER_H
#define BORNAGAIN_CORE_EXPORT_MATERIALKEYHANDLER_H

#include <map>
#include <string>
#include <vector>

class Material;

//! Stores Material instances, associates them with given tag, and provides unique keys.
//! @ingroup tools_internal

class MaterialKeyHandler {
public:
    std::map<const Material*, const std::string> materialMap() const;
    std::string mat2key(const Material* sample) const;
    void insertMaterial(const Material* sample);

private:
    std::map<const Material*, const std::string> m_MatMap;
};

#endif // BORNAGAIN_CORE_EXPORT_MATERIALKEYHANDLER_H
