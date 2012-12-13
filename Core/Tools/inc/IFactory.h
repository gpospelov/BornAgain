#ifndef IFACTORY_H
#define IFACTORY_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   IFactory.h
//! @brief  Definition of IFactory class
//! @author Scientific Computing Group at FRM II
//! @date   01.05.2012


#include "Exceptions.h"
#include <map>
#include <iostream>
#include <vector>


//- -------------------------------------------------------------------
//! @class IFactory
//! @brief Base class for all factories
//- -------------------------------------------------------------------
template<class IdentifierType, class AbstractProduct >
class IFactory
{
public:
    //! pointer to function which will be used to create object of AbstractProduct base type
    typedef AbstractProduct* (*CreateItemCallback) ();

    //! typedef for map which stores correspondance between object identifier and object creation function
    typedef std::map<IdentifierType, CreateItemCallback> CallbackMap_t;

    //! typedef for map which stores correspondance between object identifier and object description
    typedef std::map<IdentifierType, IdentifierType> DescriptionMap_t;

    IFactory() : m_own_objects(false) { }

    //! create object by calling creation function corresponded to given identifier
    AbstractProduct *createItem(const IdentifierType &itemId)
    {
        typename CallbackMap_t::const_iterator it = m_callbacks.find(itemId);
        if( it == m_callbacks.end() ) {
            // item with such itemId have not been registered in the database
            throw UnknownClassRegistrationException("IFactory::createItem() -> Panic. Unknown itemId '"+std::string(itemId)+"'");
        }
        // invoke the creation function
        AbstractProduct *x = (it->second)();
        if(m_own_objects) m_objects.push_back(x);
        return x;
    }

    //! register object's creation function
    bool registerItem(const IdentifierType &itemId, CreateItemCallback CreateFn)
    {
        typename CallbackMap_t::const_iterator it = m_callbacks.find(itemId);
        if( it != m_callbacks.end() ) {
            throw ExistingClassRegistrationException("IFactory::registerItem() -> Panic! Already registered itemId '"+std::string(itemId)+"'");
        }
        //std::cout << "IFactory::registerItem() -> Info. Registering item '" << itemId << "'." << std::endl;
        return m_callbacks.insert( typename CallbackMap_t::value_type(itemId, CreateFn)).second;
    }

    //! register object's creation function and store object description
    bool registerItem(const IdentifierType &itemId, CreateItemCallback CreateFn, const IdentifierType &itemDescription)
    {
        typename CallbackMap_t::const_iterator it = m_callbacks.find(itemId);
        if( it != m_callbacks.end() ) {
            throw ExistingClassRegistrationException("IFactory::registerItem() -> Panic! Already registered itemId '"+std::string(itemId)+"'");
        }
        //std::cout << "IFactory::registerItem() -> Info. Registering item '" << itemId << "'." << std::endl;
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

    //! set flag to delete objects on descruction
    void setOwnObjects(bool own_objects) { m_own_objects = own_objects; }

    //! return number of registered objects
    size_t getNumberOfRegistered() const { return m_callbacks.size(); }

protected:
    bool m_own_objects;         //!< will store created objects in the list and then delete them on exit then true
    CallbackMap_t m_callbacks;     //!< map of correspondance of objectsId and creation functions
    DescriptionMap_t m_descriptions;     //!< map of correspondance of objectsId and description
    std::vector<AbstractProduct *> m_objects; //! vector of all created objects (if m_store_objects==true)
};

//! creation function
template<class Derived, class Base >
Base *IFactoryCreateFunction()
{
    return new Derived;
}




#endif // IFACTORY_H


