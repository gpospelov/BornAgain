// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/IFactory.h
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

//! @class IFactory
//! @ingroup tools_internal
//! @brief Base class for all factories.

template<class IdentifierType, class AbstractProduct >
class IFactory
{
public:
    //! function which will be used to create object of AbstractProduct base type
    typedef AbstractProduct* (*CreateItemCallback) ();

    //! map for correspondance between object identifier and object creation function
    typedef std::map<IdentifierType, CreateItemCallback> CallbackMap_t;

    //! map for correspondance between object identifier and object description
    typedef std::map<IdentifierType, IdentifierType> DescriptionMap_t;
    typedef typename DescriptionMap_t::iterator iterator;
    typedef typename DescriptionMap_t::const_iterator const_iterator;

    IFactory() : m_own_objects(false) { }

    //! Creates object by calling creation function corresponded to given identifier
    AbstractProduct *createItem(const IdentifierType& itemId)
    {
        typename CallbackMap_t::const_iterator it = m_callbacks.find(itemId);
        if( it == m_callbacks.end() ) {
            // item with such itemId have not been registered in the database
            throw UnknownClassRegistrationException(
                "IFactory::createItem() -> Panic. Unknown itemId '"+std::string(itemId)+"'" );
        }
        // invoke the creation function
        AbstractProduct *x = (it->second)();
        if(m_own_objects) m_objects.push_back(x);
        return x;
    }

    //! Registers object's creation function
    bool registerItem(const IdentifierType& itemId, CreateItemCallback CreateFn)
    {
        typename CallbackMap_t::const_iterator it = m_callbacks.find(itemId);
        if( it != m_callbacks.end() )
            throw ExistingClassRegistrationException(
                "IFactory::registerItem() -> Panic! "
                "Already registered itemId '"+std::string(itemId)+"'" );
        return m_callbacks.insert( typename CallbackMap_t::value_type(itemId, CreateFn)).second;
    }

    //! Registers object's creation function and store object description
    bool registerItem(const IdentifierType& itemId, CreateItemCallback CreateFn,
                      const IdentifierType& itemDescription)
    {
        typename CallbackMap_t::const_iterator it = m_callbacks.find(itemId);
        if( it != m_callbacks.end() )
            throw ExistingClassRegistrationException(
                "IFactory::registerItem() -> Panic! "
                "Already registered itemId '"+std::string(itemId)+"'" );
        m_descriptions.insert( typename DescriptionMap_t::value_type(itemId, itemDescription));
        return m_callbacks.insert( typename CallbackMap_t::value_type(itemId, CreateFn)).second;
    }

    ~IFactory()
    {
        clear();
    }

    //! clear everything
    void clear()
    {
        m_callbacks.clear();
        if(m_own_objects) {
            typename std::vector<AbstractProduct *>::iterator it;
            for(it=m_objects.begin(); it!=m_objects.end(); ++it) {
                delete (*it);
            }
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
    CallbackMap_t m_callbacks;     //!< map of correspondance of objectsId and creation functions
    DescriptionMap_t m_descriptions;     //!< map of correspondance of objectsId and description
    //! vector of all created objects (if m_store_objects==true)
    std::vector<AbstractProduct *> m_objects;
};

//! creation function
template<class Derived, class Base >
Base *IFactoryCreateFunction()
{
    return new Derived;
}

#endif // IFACTORY_H
