// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/ICloneableRegistry.h
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

//! @class ICloneableRegistry
//! @ingroup tools_internal
//! @brief Templated registry for cloneable objects

template<class IdentifierType, class AbstractProduct >
class ICloneableRegistry
{
public:
    typedef std::map<IdentifierType, AbstractProduct*> map_t;
    typedef typename map_t::iterator iterator;
    typedef typename map_t::const_iterator const_iterator;

    AbstractProduct* createItem(const IdentifierType& key) const
    {
        const_iterator it = m_data.find(key);
        if(it == m_data.end()) {
            std::ostringstream message;
            message << "ICloneableRegistry::createItem() -> Error. Not existing item key "
                    << "'" << key << "'";
            throw UnknownClassRegistrationException(message.str());
        }
        return it->second->clone();
    }

    iterator begin() { return m_data.begin(); }
    const_iterator begin() const { return m_data.begin(); }
    iterator end() { return m_data.end(); }
    const_iterator end() const { return m_data.end(); }

protected:
    void add(const IdentifierType& key, AbstractProduct* item)
    {
        const_iterator it = m_data.find(key);
        if(it != m_data.end()) {
            std::ostringstream message;
            message << "ICloneableRegistry::createItem() -> Error. Already existing item with key "
                    << "'" << key << "'";
            throw ExistingClassRegistrationException(message.str());
        }
        m_data[key] = item;
    }

private:
    map_t m_data;
};


#endif
