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

#include <map>
#include <stdexcept>
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
    IFactory() : m_delete_objects(false), m_store_objects(false) { }

    //! pointer to function which will be used to create object of AbstractProduct base type
    typedef AbstractProduct* (*CreateItemCallback) ();

    //! typedef for map which stores correspondance between object identifier and object creation function
    typedef std::map<IdentifierType, CreateItemCallback> CallbackMap_t;

    //! create object by calling creation function corresponded to given identifier
    AbstractProduct *createItem(const IdentifierType &itemId)
    {
        typename CallbackMap_t::const_iterator it = m_callbacks.find(itemId);
        if( it == m_callbacks.end() ) {
            // item with such itemId have not been registered in the database
            //std::cout << "IFactory::createItem() -> Warning. No object '" << itemId << "' registered." << std::endl;
            throw std::runtime_error("IFactory::createItem() -> Panic. Unknown itemId");
            //return 0;
        }
        // invoke the creation function
        AbstractProduct *x = (it->second)();
        if(m_store_objects) m_objects.push_back(x);
        return x;
    }

    //! register object's creation function
    bool registerItem(const IdentifierType &itemId, CreateItemCallback CreateFn)
    {
        typename CallbackMap_t::const_iterator it = m_callbacks.find(itemId);
        if( it != m_callbacks.end() ) {
            throw std::runtime_error("IFactory::createItem() -> Panic. Unknown itemId ");
        }
        std::cout << "IFactory::RegisterSample() -> Info. Registering sample " << itemId << std::endl;
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
        if(m_delete_objects) {
            typename std::vector<AbstractProduct *>::iterator it;
            for(it=m_objects.begin(); it!=m_objects.end(); it++) {
                delete (*it);
            }
        }
        m_objects.clear();
    }

    //! set flag to delete objects on descruction
    void setDeleteObjects(bool delete_objects) { m_delete_objects = delete_objects; }

    //! set flag to store created objects
    void setStoreObjects(bool store_objects) { m_store_objects = store_objects; }

protected:
    bool m_delete_objects;         //!< will delete created objects on exit then true
    bool m_store_objects;          //!< will store created objects
    CallbackMap_t m_callbacks;     //!< map of correspondance of objectsId and creation functions
    std::vector<AbstractProduct *> m_objects;
};

//! creation function
template<class Derived, class Base >
Base *IFactoryCreateFunction()
{
    return new Derived;
}




#endif // IFACTORY_H


