// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/inc/IntegratorReal.h
//! @brief     Defines and implements class template IntegratorReal.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef INTEGRATORREAL_H
#define INTEGRATORREAL_H

#include "gsl/gsl_integration.h"
#include <cassert>
#include <memory>

//! Alias template for member function with signature double f(double, void*)
template <class T>
using real_integrand = double (T::*)(double, void*) const;

//! @class IntegratorReal
//! @ingroup tools_internal
//! @brief Template class to integrate class member functions
//!
//! Wraps an integrator from the GNU Scientific Library.
//! Since this class holds a persistent workspace, we need at least one instance per thread.
//! Standard usage for integration inside a class T:
//! - Create a handle to an integrator: 'auto integrator = make_real_integrator(this, mem_function)'
//! - Call: 'integrator.integrate(lmin, lmax)'
template <class T> class IntegratorReal
{
public:
    //! member function type
    using mem_function = real_integrand<T>;

    //! structure holding the object and possible extra parameters
    struct CallBackHolder {
        const T *m_object_pointer;
        mem_function m_member_function;
        void *m_data;
    };

    IntegratorReal();
    //! to integrate p_member_function, which must belong to p_object
    IntegratorReal(const T *p_object, mem_function p_member_function);
    ~IntegratorReal();

    //! perform the actual integration over the range [lmin, lmax]
    double integrate(double lmin, double lmax, void *params);

    //! Sets integrand
    void setIntegrand(mem_function member_function)
    { m_member_function = member_function; }
    void setIntegrand(mem_function member_function, const T *const p_object)
    { m_member_function = member_function; mp_object = p_object; }

private:
    //! static function that can be passed to gsl integrator
    static double StaticCallBack(double d, void *v) {
        CallBackHolder *p_cb = static_cast<CallBackHolder *>(v);
        mem_function mf = p_cb->m_member_function;
        return (p_cb->m_object_pointer->*mf)(d, p_cb->m_data);
    }
    mem_function m_member_function; //!< the member function to integrate
    const T *mp_object; //!< the object whose member function to integrate
    gsl_integration_workspace *m_gsl_workspace;
};

//! Alias template for handle to a real integrator
template <class T>
using P_integrator_real = std::unique_ptr<IntegratorReal<T>>;

//! @fn make_integrator
//! @ingroup tools_internal
//! @brief Template function to create an integrator object
template <class T>
P_integrator_real<T> make_integrator(const T *object, real_integrand<T> mem_function)
{
    P_integrator_real<T> P_integrator(new IntegratorReal<T>(object, mem_function));
    return P_integrator;
}

template<class T> IntegratorReal<T>::IntegratorReal(
        const T *p_object, mem_function p_member_function)
: m_member_function(p_member_function)
, mp_object(p_object)
, m_gsl_workspace(0)
{
    m_gsl_workspace = gsl_integration_workspace_alloc(200);
}

template<class T> IntegratorReal<T>::IntegratorReal()
: m_member_function(0)
, mp_object(0)
, m_gsl_workspace(0)
{
    m_gsl_workspace = gsl_integration_workspace_alloc(200);
}

template<class T> IntegratorReal<T>::~IntegratorReal()
{
    gsl_integration_workspace_free(m_gsl_workspace);
}

template<class T> double IntegratorReal<T>::integrate(
        double lmin, double lmax, void* params)
{
    assert(mp_object);
    assert(m_member_function);

    CallBackHolder cb = { mp_object, m_member_function, params };
//    const T* p_object = mp_object;

    gsl_function f;
//    f.function =
//        [this](double d, void *pars) { return mp_object->*m_member_function(d, pars); };
//    f.params = params;
    f.function = StaticCallBack;
    f.params =& cb;

    double result, error;
    gsl_integration_qag(&f, lmin, lmax, 1e-10, 1e-8, 50, 1,
                        m_gsl_workspace, &result, &error);

    return result;
}
#endif // INTEGRATORREAL_H

