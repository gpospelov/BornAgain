#ifndef MEMBERFUNCTIONCOMPLEXINTEGRATOR_H
#define MEMBERFUNCTIONCOMPLEXINTEGRATOR_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   MemberFunctionComplexIntegrator.h
//! @brief  Definition of MemberFunctionComplexIntegrator template
//! @author Scientific Computing Group at FRM II
//! @date   30.01.2013

#include "MemberFunctionIntegrator.h"
#include "Types.h"


template <class C> class MemberComplexFunctionIntegrator
{
public:
    //! member function type
    typedef complex_t (C::*mem_function)(double, void*) const;

    //! constructor taking a member function and the object whose member function to integrate
    MemberComplexFunctionIntegrator(mem_function p_member_function, const C *const p_object);

    complex_t integrate(double lmin, double lmax);

private:

    double integrand_real(double z, void* pars) const {
        return ((mp_object->*m_member_function)(z, pars)).real();
    }

    double integrand_imag(double z, void* pars) const {
        return ((mp_object->*m_member_function)(z, pars)).imag();
    }

    mem_function m_member_function; //!< the member function to integrate
    const C *mp_object; //!< the object whose member function to integrate

    MemberFunctionIntegrator<MemberComplexFunctionIntegrator<C > >  m_integrator;
};


template<class C> MemberComplexFunctionIntegrator<C>::MemberComplexFunctionIntegrator(
        mem_function p_member_function, const C *const p_object)
: m_member_function(p_member_function)
, mp_object(p_object)
{
    m_integrator.setIntegrand(0,this);
}


template<class C> complex_t MemberComplexFunctionIntegrator<C>::integrate(double lmin, double lmax)
{
    typename MemberFunctionIntegrator<MemberComplexFunctionIntegrator<C > >::mem_function integrand = &MemberComplexFunctionIntegrator::integrand_real;
    m_integrator.setIntegrand(integrand);
    double real = m_integrator.integrate(lmin, lmax, (void *)0);

    integrand = &MemberComplexFunctionIntegrator::integrand_imag;
    m_integrator.setIntegrand(integrand);
    double imag = m_integrator.integrate(lmin, lmax, (void *)0);

    return complex_t( real, imag );
}

#endif // MEMBERFUNCTIONCOMPLEXINTEGRATOR_H

