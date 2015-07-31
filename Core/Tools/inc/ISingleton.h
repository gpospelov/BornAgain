// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/inc/ISingleton.h
//! @brief     Defines the standard mix-in ISingleton.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ISINGLETON_H
#define ISINGLETON_H

#include <stdexcept>
#include <iostream>
#include <typeinfo>
#include "Macros.h"
GCC_DIAG_OFF(unused-parameter)
GCC_DIAG_OFF(strict-aliasing)
#include <boost/thread.hpp>
GCC_DIAG_ON(strict-aliasing)
GCC_DIAG_ON(unused-parameter)

//! @class ISingleton
//! @ingroup tools_internal
//! @brief Singleton pattern.

template <class T>
class ISingleton
{
public:
    static T& instance()
    {
        static boost::mutex single_mutex;
        boost::unique_lock<boost::mutex> single_lock( single_mutex );
        if( !m_instance) {
            if( m_destroyed ) {
                onDeadReference();
            } else {
                CreateSingleton();
            }
        }
        return *m_instance;
    }

protected:
    ISingleton(){}
    virtual ~ISingleton()
    {
        m_instance = 0;
        m_destroyed = true;
    }

    static void CreateSingleton()
    {
        static T theInstance;
        m_instance =& theInstance;
    }

    static void onDeadReference() { throw std::runtime_error("ISingleton::onDeadReference()"); }

    typedef T* T_Pointer;

private:
    ISingleton(const ISingleton<T>& ) {}
    ISingleton& operator=(const ISingleton<T>& ) { throw std::runtime_error("ISingleton::operator=()"); }

    static T_Pointer m_instance;
    static bool m_destroyed;

};

template<class T> typename ISingleton<T>::T_Pointer ISingleton<T>::m_instance = 0;
template<class T> bool ISingleton<T>::m_destroyed = false;

#endif // ISINGLETON_H


