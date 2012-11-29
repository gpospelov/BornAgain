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

protected:
    //! evaluate scattering amplitude for complex wavevector
    //! @param q  wavevector transfer \f$q\equiv k_i-k_f\f$
    virtual complex_t evaluate_for_q(const cvector_t &q) const=0;

    //! override volume getter to avoid infinite loop caused by big bin approximation
    virtual double getVolume() const;

    //! calculate radial part of scattering amplitude for large bins
    double bigRadialPart(const cvector_t& q) const;

    //! calculate z-part of scattering amplitude for large bins
    complex_t bigZPart(const cvector_t& q) const;

    bool m_use_large_bin_approximation_radial;  //!< indicates if large bin size approximation should be used in the qx-qy direction
    bool m_use_large_bin_approximation_z;  //!< indicates if large bin size approximation should be used in the qz direction
    double m_bin_qy, m_bin_qz;  //!< the sizes of the bins in q space
private:
    //! calculates an approximate intensity that does not contain rapid oscillations
    double bigRadialIntegrand(double qR, void *params) const;

    //! calculates the integrated intensity along the z-direction
    double bigZPartIntegral(double qH2) const;
};

inline complex_t IFormFactorBorn::evaluate(const cvector_t &k_i, const cvector_t &k_f, double alpha_i, double alpha_f) const
{
    (void)alpha_i;
    (void)alpha_f;
    cvector_t q = k_i - k_f;
    if (m_use_large_bin_approximation_radial || m_use_large_bin_approximation_z) {
        return getVolume()*bigZPart(q)*bigRadialPart(q);
    }
    return evaluate_for_q(q);
}

inline double IFormFactorBorn::getVolume() const
{
    cvector_t zero;
    return std::abs(evaluate_for_q(zero));
}

#endif /* IFORMFACTORBORN_H_ */
