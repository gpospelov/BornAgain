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

    virtual complex_t evaluate(const cvector_t &k_i, const Bin1DCVector &k_f_bin, double alpha_i, double alpha_f) const;

    //! evaluate scattering amplitude for complex wavevector
    //! @param q  wavevector transfer \f$q\equiv k_i-k_f\f$
    virtual complex_t evaluate_for_q(const cvector_t &q) const=0;

protected:
    //! override volume getter to avoid infinite loop caused by big bin approximation
    virtual double getVolume() const;

    //! calculate radial part of scattering amplitude for large bins
    double bigRadialPart(const Bin1DCVector& q_bin) const;

    //! calculate z-part of scattering amplitude for large bins
    complex_t bigZPart(const Bin1DCVector& q_bin) const;

private:
    //! determine if a large bin size approximation should be used
    bool useLargeBinApproximation(const Bin1DCVector &q_bin) const;

    //! calculates an approximate intensity that does not contain rapid oscillations
    double bigRadialIntegrand(double qR, void *params) const;

    //! calculates the integrated intensity along the z-direction
    double bigZPartIntegral(double qH2) const;
};

inline complex_t IFormFactorBorn::evaluate(const cvector_t& k_i, const Bin1DCVector& k_f_bin, double alpha_i, double alpha_f) const
{
    (void)alpha_i;
    (void)alpha_f;
    Bin1DCVector q_bin(k_i - k_f_bin.m_q_lower, k_i - k_f_bin.m_q_upper);
    if (useLargeBinApproximation(q_bin)) {
        return getVolume()*bigZPart(q_bin)*bigRadialPart(q_bin);
    }
    return evaluate_for_q(q_bin.getMidPoint());
}

inline double IFormFactorBorn::getVolume() const
{
    cvector_t zero;
    return std::abs(evaluate_for_q(zero));
}

inline bool IFormFactorBorn::useLargeBinApproximation(const Bin1DCVector &q_bin) const
{
//    (void)q_bin;
    double delta_qr = std::abs( q_bin.getDelta().magxy() );
    if ( delta_qr > M_PI/2.0/getRadius() ) {
        return true;
    }
    double delta_qz = std::abs( q_bin.getDelta().z() );
    if ( delta_qz > M_PI/2.0/getHeight() ) {
        return true;
    }
    return false;
}

#endif /* IFORMFACTORBORN_H_ */
