// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/IFormFactorBorn.h
//! @brief     Defines class IFormFactorBorn.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef IFORMFACTORBORN_H_
#define IFORMFACTORBORN_H_

#include "IFormFactor.h"

//! Born formfactor interface (scattering amplitude only depends q=ki-kf)

class IFormFactorBorn : public IFormFactor
{
public:
    IFormFactorBorn();
    virtual ~IFormFactorBorn() {}
    virtual IFormFactorBorn *clone() const=0;

    virtual complex_t evaluate(
        const cvector_t &k_i, const Bin1DCVector &k_f_bin,
        double alpha_i, double alpha_f) const;

    //! evaluate scattering amplitude for complex wavevector
    //! @param q  wavevector transfer \f$q\equiv k_i-k_f\f$
    virtual complex_t evaluate_for_q(const cvector_t &q) const=0;

    //! override volume getter to avoid endless loop caused by big bin approximation
    virtual double getVolume() const;

protected:
    //! calculate radial part of scattering amplitude for large bins
    double bigRadialPart(const Bin1DCVector& q_bin) const;

    //! calculate z-part of scattering amplitude for large bins
    complex_t bigZPart(const Bin1DCVector& q_bin) const;

private:
    //! determine if a large bin size approximation should be used
    bool useLargeBinApproximation(const Bin1DCVector &q_bin) const;

    //! approximate intensity that does not contain rapid oscillations
    double bigRadialIntegrand(double qR, void *params) const;

    //! calculates the integrated intensity along the z-direction
    double bigZPartIntegral(double qH2) const;
};

inline complex_t IFormFactorBorn::evaluate(
    const cvector_t& k_i, const Bin1DCVector& k_f_bin,
    double alpha_i, double alpha_f) const
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

inline bool IFormFactorBorn::useLargeBinApproximation(
    const Bin1DCVector &q_bin) const
{
    double delta_qr = std::abs( q_bin.getDelta().magxy() );
    double delta_qz = std::abs( q_bin.getDelta().z() );
    if(delta_qr == 0 || delta_qz == 0) return false;
    if ( delta_qr > M_PI/(2.0*getRadius()) ) {
        return true;
    }
    if ( delta_qz > M_PI/(2.0*getHeight()) ) {
        return true;
    }
    return false;
}

#endif /* IFORMFACTORBORN_H_ */
