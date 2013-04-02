// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/inc/RealParameterWrapper.h
//! @brief     Defines class RealParameterWrapper.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef REALPARAMETERWRAPPER_H
#define REALPARAMETERWRAPPER_H

#include "Exceptions.h"

#include <ostream>

//! Wrapper to real parameter for remote access to its value and callback abilities

class RealParameterWrapper {
 public:
    explicit RealParameterWrapper(double *par) : m_data(par) {}
    // explicit RealParameterWrapper(double *par) : m_data(par), m_signal() {}
    RealParameterWrapper(const RealParameterWrapper& other );
    RealParameterWrapper& operator=(const RealParameterWrapper& other);
    ~RealParameterWrapper(){}

    //! Sets value of wrapped parameter and emmit signal
    void setValue(double value)
    {
        checkNull();
        if(value != *m_data) {
            *m_data = value;
            // m_signal();
        }
    }

    //! Returns value of wrapped parameter
    double getValue() const { checkNull(); return *m_data; }

    //! Returns true if wrapped parameter was not initialized with proper real value
    bool isNull() const { return (m_data ? false : true); }

    //! throw exception if parameter was not initialized with proper value
    void checkNull() const { if(isNull()) throw NullPointerException("RealParameterWrapper::getValue() -> Attempt to access uninitialised pointer."); }

    //! Prints the parameter's address to an output stream
    friend std::ostream& operator<<(std::ostream& ostr, const RealParameterWrapper& p) { ostr << p.m_data; return ostr; }
 private:
    //! swap function
    void swapContent(RealParameterWrapper& other);

    volatile double *m_data;
};

#endif // REALPARAMETERPROXY_H


