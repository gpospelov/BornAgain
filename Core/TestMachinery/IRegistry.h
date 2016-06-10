// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/IRegistry.h
//! @brief     Declares templated registry for ICloneable objects
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ICLONEABLEREGISTRY_H
#define ICLONEABLEREGISTRY_H

#include "Exceptions.h"
#include "WinDllMacros.h"
#include <map>
#include <sstream>

//! @class IRegistry
//! @ingroup tools_internal
//! @brief Templated object registry

template<class ValueType>
class IRegistry
{
public:
    ValueType* getItem(const std::string& key) const {
        auto it = m_data.find(key);
        if(it == m_data.end()) {
            std::ostringstream message;
            message << "IRegistry::createItem() -> Error. Not existing item key "
                    << "'" << key << "'";
            throw UnknownClassRegistrationException(message.str());
        }
        return it->second;
    }

    std::vector<std::string> keys() {
        std::vector<std::string> result;
        for( auto it=m_data.begin(); it!=m_data.end(); ++it )
            result.push_back( it->first );
        return result;
    }

protected:
    void add(const std::string& key, ValueType* item) {
        if(m_data.find(key) != m_data.end()) {
            std::ostringstream message;
            message << "IRegistry::createItem() -> Error. Already existing item with key "
                    << "'" << key << "'";
            throw ExistingClassRegistrationException(message.str());
        }
        m_data[key] = item;
    }

private:
    std::map<std::string, ValueType*> m_data;
};

#endif
