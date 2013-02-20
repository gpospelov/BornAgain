#ifndef REALPARAMETERWRAPPER_H
#define REALPARAMETERWRAPPER_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   RealParameterWrapper.h
//! @brief  Definition of RealParameterWrapper class
//! @author Scientific Computing Group at FRM II
//! @date   14.12.2012

#include "Exceptions.h"
//#include <boost/signal.hpp>


//- -------------------------------------------------------------------
//! @class RealParameterWrapper
//! @brief Definition of wrapper to real parameter for remote access to its
//! value and callback abilities
//- -------------------------------------------------------------------
class RealParameterWrapper {
public:
    //! type of the signal parameter can emmit
//    typedef boost::signal<void ()>  signal_t;

    explicit RealParameterWrapper(double *par) : m_data(par) {}
    // explicit RealParameterWrapper(double *par) : m_data(par), m_signal() {}
    RealParameterWrapper(const RealParameterWrapper &other );
    RealParameterWrapper &operator=(const RealParameterWrapper &other);
    ~RealParameterWrapper(){}

    //! set value of wrapped parameter and emmit signal
    void setValue(double value)
    {
        checkNull();
        if(value != *m_data) {
            *m_data = value;
            // m_signal();
        }
    }

    //! get value of wrapped parameter
    double getValue() const { checkNull(); return *m_data; }

    //! connect external slot with signal which parameter will emmit
 //   void connect(const signal_t::slot_type &slot) { m_signal.connect(slot); }

    //! return true if wrapped parameter was not initialized with proper real value
    bool isNull() const { return (m_data ? false : true); }

    //! throw exception if parameter was not initialized with proper value
    void checkNull() const { if(isNull()) throw NullPointerException("RealParameterWrapper::getValue() -> Attempt to access uninitialised pointer."); }

    friend std::ostream &operator<<(std::ostream &ostr, const RealParameterWrapper &p) { ostr << p.m_data; return ostr; }
private:
    //! swap function
    void swapContent(RealParameterWrapper &other);

    volatile double *m_data;
//    signal_t m_signal;
};


#endif // REALPARAMETERPROXY_H
