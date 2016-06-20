// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Tools/IFactory.h
//! @brief     Declares interface class IFactory.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef IFACTORY_H
#define IFACTORY_H

#include "Exceptions.h"
#include <map>
#include <iostream>
#include <vector>
#include <functional>

//! @class IFactory
//! @ingroup tools_internal
//! @brief Base class for all factories.

template<class Key, class AbstractProduct >
class IFactory
{
public:
    //! function which will be used to create object of AbstractProduct base type
    typedef typename std::function<AbstractProduct*()> CreateItemCallback;

    //! map for correspondance between object identifier and object creation function
    typedef std::map<Key, CreateItemCallback> CallbackMap_t;

    //! map for correspondance between object identifier and object description
    typedef std::map<Key, std::string> DescriptionMap_t;
    typedef typename DescriptionMap_t::iterator iterator;
    typedef typename DescriptionMap_t::const_iterator const_iterator;

    IFactory() : m_own_objects(false) {}

    //! Creates object by calling creation function corresponded to given identifier
    AbstractProduct* createItem(const Key& item_key) {
        auto it = m_callbacks.find(item_key);
        if( it == m_callbacks.end() ) // unexpectedly not found
            throw UnknownClassRegistrationException(
                    "IFactory::createItem() -> Panic. Unknown item key");
        // invoke the creation function
        AbstractProduct* x = (it->second)();
        if(m_own_objects)
            m_objects.push_back(x);
        return x;
    }

    //! Registers object's creation function
    bool registerItem(const Key& item_key, CreateItemCallback CreateFn) {
        if( m_callbacks.find(item_key) != m_callbacks.end() )
            throw ExistingClassRegistrationException(
                    "IFactory::registerItem() -> Panic! Already registered item key");
        return m_callbacks.insert( typename CallbackMap_t::value_type(item_key, CreateFn)).second;
    }

    //! Registers object's creation function and store object description
    bool registerItem(const Key& item_key, CreateItemCallback CreateFn,
                      const std::string& itemDescription) {
        if( m_callbacks.find(item_key) != m_callbacks.end() )
            throw ExistingClassRegistrationException(
                    "IFactory::registerItem() -> Panic! Already registered item key");
        m_descriptions.insert( typename DescriptionMap_t::value_type(item_key, itemDescription));
        return m_callbacks.insert( typename CallbackMap_t::value_type(item_key, CreateFn)).second;
    }

    ~IFactory() { clear(); }

    //! clear everything
    void clear() {
        m_callbacks.clear();
        if(m_own_objects) {
            for(auto it: m_objects)
                delete it;
        }
        m_objects.clear();
    }

    //! Sets flag to delete objects on descruction
    void setOwnObjects(bool own_objects) { m_own_objects = own_objects; }

    //! Returns number of registered objects
    size_t getNumberOfRegistered() const { return m_callbacks.size(); }

    iterator begin() { return m_descriptions.begin(); }
    const_iterator begin() const { return m_descriptions.begin(); }

    iterator end() { return m_descriptions.end(); }
    const_iterator end() const { return m_descriptions.end(); }

protected:
    //! will store created objects in the list and then delete them on exit then true
    bool m_own_objects;
    CallbackMap_t m_callbacks;     //!< map of correspondence of objectsId and creation functions
    DescriptionMap_t m_descriptions;     //!< map of correspondence of objectsId and description
    //! vector of all created objects (if m_store_objects==true)
    std::vector<AbstractProduct*> m_objects;
};

#endif // IFACTORY_H
