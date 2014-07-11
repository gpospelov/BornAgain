// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/inc/MemberFunctionMCMiserIntegrator.h
//! @brief     Defines and implements template class MemberFunctionMCMiserIntegrator.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MEMBERFUNCTIONMCMISERINTEGRATOR_H
#define MEMBERFUNCTIONMCMISERINTEGRATOR_H

#include "gsl/gsl_monte_miser.h"

//! @class MemberFunctionMCMiserIntegrator
//! @ingroup tools_internal
//! @brief Template class to use Monte Carlo MISER integration of class member functions
//!
//! Wrap integrator from GNU Scientific Library.

template <class C> class MemberFunctionMCMiserIntegrator
{
public:
    //! member function type
    typedef double (C::*mem_function)(double *, size_t, void*) const;

    //! structure holding the object and possible extra parameters
    struct CallBackHolder {
        const C *m_object_pointer;
        mem_function m_member_function;
        void *m_data;
    };

    //! to integrate p_member_function, which must belong to p_object
    MemberFunctionMCMiserIntegrator(
        mem_function p_member_function, const C *const p_object, size_t dim);
    ~MemberFunctionMCMiserIntegrator();

    //! perform the actual integration over the ranges [min_array, max_array]
    double integrate(double *min_array, double *max_array, void* params,
                     size_t nbr_points);

private:
    //! static function that can be passed to gsl integrator
    static double StaticCallBack(double *d_array, size_t dim, void *v) {
        CallBackHolder *p_cb = static_cast<CallBackHolder *>(v);
        mem_function mf = p_cb->m_member_function;
        return (p_cb->m_object_pointer->*mf)(d_array, dim, p_cb->m_data);
    }
    mem_function m_member_function; //!< the member function to integrate
    const C *mp_object; //!< the object whose member function to integrate
    size_t m_dim; //!< dimension of the integration
    gsl_monte_miser_state *m_gsl_workspace;
    gsl_rng *m_random_gen;
};

template<class C> MemberFunctionMCMiserIntegrator<C>::MemberFunctionMCMiserIntegrator(
        mem_function p_member_function, const C *const p_object, size_t dim)
: m_member_function(p_member_function)
, mp_object(p_object)
, m_dim(dim)
, m_gsl_workspace(0)
{
    m_gsl_workspace = gsl_monte_miser_alloc(m_dim);

    const gsl_rng_type * random_type;
    gsl_rng_env_setup();
    random_type = gsl_rng_default;
    m_random_gen = gsl_rng_alloc(random_type);
}

template<class C> MemberFunctionMCMiserIntegrator<C>::~MemberFunctionMCMiserIntegrator()
{
    gsl_monte_miser_free(m_gsl_workspace);
    gsl_rng_free(m_random_gen);
}

template<class C> double MemberFunctionMCMiserIntegrator<C>::integrate(
        double *min_array, double *max_array, void* params, size_t nbr_points)
{
    assert(mp_object);
    assert(m_member_function);

    CallBackHolder cb = { mp_object, m_member_function, params };

    gsl_monte_function f;
    f.f = StaticCallBack;
    f.dim = m_dim;
    f.params =& cb;

    double result, error;
    gsl_monte_miser_integrate(&f, min_array, max_array, m_dim, nbr_points,
                                    m_random_gen, m_gsl_workspace, &result, &error);
    return result;
}

#endif // MEMBERFUNCTIONMCMISERINTEGRATOR_H
