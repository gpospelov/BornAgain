#ifndef IFORMFACTORBORN_H_
#define IFORMFACTORBORN_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   IFormFactorBorn.h
//! @brief  Definition of IFormFactorBorn interface
//! @author Scientific Computing Group at FRM II
//! @date   Nov 28, 2012

#include "IFormFactor.h"


//- -------------------------------------------------------------------
//! @class IFormFactorBorn
//! @brief Definition of IFormFactorBorn interface
//!
//! IFormFactorBorn defines a Born formfactor, whose scattering amplitude
//! only depends on the scattering vector \f$q\equiv k_i-k_f\f$
//- -------------------------------------------------------------------
class IFormFactorBorn : public IFormFactor
{
public:
    IFormFactorBorn();
    virtual ~IFormFactorBorn() {}
    virtual IFormFactorBorn *clone() const=0;

    virtual complex_t evaluate(const cvector_t &k_i, const cvector_t &k_f, double alpha_i, double alpha_f) const;

    virtual void setBinSizes(double delta_qy, double delta_qz);

    //! evaluate scattering amplitude for large bin sizes
    virtual complex_t evaluateForLargeBins(const cvector_t &q) const;
protected:
    //! evaluate scattering amplitude for complex wavevector
    //! @param q  wavevector transfer \f$q\equiv k_i-k_f\f$
    virtual complex_t evaluate_for_q(const cvector_t &q) const=0;

    //! override volume getter to avoid infinite loop caused by big bin approximation
    virtual double getVolume() const;

    bool m_use_large_bin_approximation_radial;  //!< indicates if large bin size approximation should be used in the qx-qy direction
    bool m_use_large_bin_approximation_z;  //!< indicates if large bin size approximation should be used in the qz direction
    double m_bin_qy, m_bin_qz;  //!< the sizes of the bins in q space
private:
    double bigRadialPart(double qR, void *params) const;
    double bigZPart(double qH2) const;
};

inline complex_t IFormFactorBorn::evaluate(const cvector_t &k_i, const cvector_t &k_f, double alpha_i, double alpha_f) const
{
    (void)alpha_i;
    (void)alpha_f;
    if (m_use_large_bin_approximation_radial || m_use_large_bin_approximation_z) {
        return evaluateForLargeBins(k_i - k_f);
    }
    return evaluate_for_q(k_i - k_f);
}

inline complex_t IFormFactorBorn::evaluateForLargeBins(const cvector_t& q) const
{
    // z parameters
    complex_t qzH2 = q.z()*getHeight()/2.0;
    double qzH2_d = std::abs(qzH2);
    double effective_bin_size_h = m_bin_qz*getHeight();

    // radial parameters
    double qrR = std::abs(q.magxy())*getRadius();
    double effective_bin_size_r = m_bin_qy*getRadius();
    double qRmin = qrR - effective_bin_size_r/2.0;
    double qRmax = qrR + effective_bin_size_r/2.0;

    // phase from the height of the particle
    complex_t z_phase = std::exp(complex_t(0.0, 1.0)*qzH2);

    // modulus of the height of the particle
    double z_average_intensity = (bigZPart(qzH2_d + effective_bin_size_h/2.0)
            - bigZPart(qzH2_d - effective_bin_size_h/2.0))/effective_bin_size_h;
    double z_modulus = std::sqrt(z_average_intensity);

    // modulus of the radial part
    MemberFunctionIntegrator<IFormFactorBorn>::mem_function p_mf = &IFormFactorBorn::bigRadialPart;
    MemberFunctionIntegrator<IFormFactorBorn> integrator(p_mf, this);
    double average_intensity = integrator.integrate(qRmin, qRmax, (void*)0)/effective_bin_size_r;
    double radial_part = std::sqrt(average_intensity);

    return getVolume()*radial_part*z_modulus*z_phase;
}

inline double IFormFactorBorn::getVolume() const
{
    cvector_t zero;
    return std::abs(evaluate_for_q(zero));
}



#endif /* IFORMFACTORBORN_H_ */
