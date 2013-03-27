// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/inc/MemberFunctionIntegrator.h
//! @brief     Defines and implements template class MemberFunctionIntegrator.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef MEMBERFUNCTIONINTEGRATOR_H_
#define MEMBERFUNCTIONINTEGRATOR_H_

#include "gsl/gsl_integration.h"
#include <cassert>

//! Wrap integrator from GNU Scientific Library.

template <class C> class MemberFunctionIntegrator
{
 public:
    //! member function type
    typedef double (C::*mem_function)(double, void*) const;

    //! structure holding the object and possible extra parameters
    struct CallBackHolder {
        const C *m_object_pointer;
        mem_function m_member_function;
        void *m_data;
    };

    MemberFunctionIntegrator();
    //! to integrate p_member_function, which must belong to p_object
    MemberFunctionIntegrator(
        mem_function p_member_function, const C *const p_object);
    ~MemberFunctionIntegrator();

    //! perform the actual integration over the range [lmin, lmax]
    double integrate(double lmin, double lmax, void *params);

    //! Sets integrand
    void setIntegrand(mem_function member_function)
    { m_member_function = member_function; }
    void setIntegrand(mem_function member_function, const C *const p_object)
    { m_member_function = member_function; mp_object = p_object; }

 private:
    //! static function that can be passed to gsl integrator
    static double StaticCallBack(double d, void *v) {
        CallBackHolder *p_cb = static_cast<CallBackHolder *>(v);
        mem_function mf = p_cb->m_member_function;
        return (p_cb->m_object_pointer->*mf)(d, p_cb->m_data);
    }
    mem_function m_member_function; //!< the member function to integrate
    const C *mp_object; //!< the object whose member function to integrate
    gsl_integration_workspace *m_gsl_workspace;
};

template<class C> MemberFunctionIntegrator<C>::MemberFunctionIntegrator(
        mem_function p_member_function, const C *const p_object)
: m_member_function(p_member_function)
, mp_object(p_object)
, m_gsl_workspace(0)
{
    m_gsl_workspace = gsl_integration_workspace_alloc(200);
}

template<class C> MemberFunctionIntegrator<C>::MemberFunctionIntegrator()
: m_member_function(0)
, mp_object(0)
, m_gsl_workspace(0)
{
    m_gsl_workspace = gsl_integration_workspace_alloc(200);
}

template<class C> MemberFunctionIntegrator<C>::~MemberFunctionIntegrator()
{
    gsl_integration_workspace_free(m_gsl_workspace);
}

template<class C> double MemberFunctionIntegrator<C>::integrate(
        double lmin, double lmax, void* params)
{
    assert(mp_object);
    assert(m_member_function);

    CallBackHolder cb = { mp_object, m_member_function, params };

    gsl_function f;
    f.function = StaticCallBack;
    f.params =& cb;

    double result, error;
    gsl_integration_qag(&f, lmin, lmax, 1e-10, 1e-8, 50, 1,
                        m_gsl_workspace,& result,& error);

    return result;
}

#endif /* MEMBERFUNCTIONINTEGRATOR_H_ */
