// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/TestMachinery/IRegistry.h
//! @brief     Declares templated registry for ICloneable objects
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef IREGISTRY_H
#define IREGISTRY_H


//! @class IRegistry
//! @ingroup tools_internal
//! @brief Templated object registry

template<class ValueType>
class IRegistry
{
public:
    const ValueType* getItem(const std::string& key) const {
        auto it = m_data.find(key);
        if(it == m_data.end()) {
            std::ostringstream message;
            message << "IRegistry::createItem() -> Error. Not existing item key "
                    << "'" << key << "'";
            throw Exceptions::UnknownClassRegistrationException(message.str());
        }
        return it->second.get();
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
            throw Exceptions::ExistingClassRegistrationException(message.str());
        }
        m_data[key] = std::unique_ptr<ValueType>(item);
    }

private:
    std::map<std::string, std::unique_ptr<ValueType>> m_data;
};

#endif // IREGISTRY_H
