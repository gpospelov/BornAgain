#ifndef ISINGLETON_H
#define ISINGLETON_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   ISingleton.h
//! @brief  Definition of singleton base template
//! @author Scientific Computing Group at FRM II
//! @date   20.04.2012

#include <stdexcept>
#include <iostream>
#include <typeinfo>


template <class T>
class ISingleton
{
public:

    static T &instance()
    {
        // check if exists, if not, then initialise
        if( !m_instance) {
            // check for dead reference (i.e. object has been initialised but then somebody managed to delete it)
            if( m_destroyed ) {
                onDeadReference();
            } else {
                // first call initalise
                create_singleton();
            }
        }
        std::cout << "ISingleton::instance() -> Info. Accesing instance... " << m_instance << std::endl;
        return *m_instance;
    }

    virtual ~ISingleton()
    {
        std::cout << "ISingleton::~ISingleton() -> Deleting singleton" << std::endl;
        m_instance = 0;
        m_destroyed = true;
    }

protected:
    ISingleton() {}
    ISingleton(const ISingleton &);

    static void create_singleton()
    {
        static T theInstance;
        m_instance = &theInstance;
        std::cout << "ISingleton::create_singleton() -> Info. Creating singleton " << m_instance << " of type '" << (typeid(theInstance).name()) << "'." << std::endl;
    }

    static void onDeadReference()
    {
        throw std::runtime_error("ISingleton::onDeadReference()");
    }

    typedef T* T_Pointer;

    static T_Pointer m_instance;
    static bool m_destroyed;
};

template<class T > typename ISingleton<T>::T_Pointer ISingleton<T>::m_instance = 0;
template< class T> bool ISingleton<T>::m_destroyed = false;


#endif // ISINGLETON_H
