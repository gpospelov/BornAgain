// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/inc/MemberComplexFunctionIntegrator.h
//! @brief     Defines and implements template class MemberComplexFunctionIntegrator.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MEMBERFUNCTIONCOMPLEXINTEGRATOR_H
#define MEMBERFUNCTIONCOMPLEXINTEGRATOR_H

#include "MemberFunctionIntegrator.h"
#include "Types.h"


//! @class MemberComplexFunctionIntegrator
//! @ingroup tools_internal
//! @brief Template class to integrate class member functions in 1D complex space

template <class C> class  MemberComplexFunctionIntegrator
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
    typename MemberFunctionIntegrator<MemberComplexFunctionIntegrator<C > >::mem_function integrand =& MemberComplexFunctionIntegrator::integrand_real;
    m_integrator.setIntegrand(integrand);
    double real = m_integrator.integrate(lmin, lmax, (void *)0);

    integrand =& MemberComplexFunctionIntegrator::integrand_imag;
    m_integrator.setIntegrand(integrand);
    double imag = m_integrator.integrate(lmin, lmax, (void *)0);

    return complex_t( real, imag );
}

#endif // MEMBERFUNCTIONCOMPLEXINTEGRATOR_H


