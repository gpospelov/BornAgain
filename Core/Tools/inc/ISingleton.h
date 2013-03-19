// ************************************************************************** //
//                                                                           
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @copyright Forschungszentrum Jülich GmbH 2013
//             
//  Homepage:  apps.jcns.fz-juelich.de/BornAgain
//  License:   GNU General Public License v3 or higher (see COPYING)
//
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
//! @file      Tools/ISingleton.h 
//! @brief     Defines class ISingleton.
//
// ************************************************************************** //

#ifndef ISINGLETON_H
#define ISINGLETON_H

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
        //std::cout << "ISingleton::instance() -> Info. Accesing instance... " << m_instance << std::endl;
        return *m_instance;
    }

protected:
    ISingleton(){}
    virtual ~ISingleton()
    {
        //std::cout << "ISingleton::~ISingleton() -> Deleting singleton" << std::endl;
        m_instance = 0;
        m_destroyed = true;
    }

    static void create_singleton()
    {
        static T theInstance;
        m_instance = &theInstance;
        //std::cout << "ISingleton::create_singleton() -> Info. Creating singleton " << m_instance << " of type '" << (typeid(theInstance).name()) << "'." << std::endl;
    }

    static void onDeadReference()
    {
        throw std::runtime_error("ISingleton::onDeadReference()");
    }

    typedef T* T_Pointer;


private:
    ISingleton(const ISingleton<T> &) {}
    ISingleton &operator=(const ISingleton<T> &) { throw std::runtime_error("ISingleton::operator=()"); }

    static T_Pointer m_instance;
    static bool m_destroyed;

};

template<class T > typename ISingleton<T>::T_Pointer ISingleton<T>::m_instance = 0;
template< class T> bool ISingleton<T>::m_destroyed = false;

#endif // ISINGLETON_H
