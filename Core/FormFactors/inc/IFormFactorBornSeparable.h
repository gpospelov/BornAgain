#ifndef IFORMFACTORBORNSEPARABLE_H_
#define IFORMFACTORBORNSEPARABLE_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   IFormFactorBornSeparable.h
//! @brief  Definition of IFormFactorBornSeparable interface
//! @author Scientific Computing Group at FRM II
//! @date   Nov 28, 2012

#include "IFormFactorBorn.h"

//- -------------------------------------------------------------------
//! @class IFormFactorBornSeparable
//! @brief Definition of IFormFactorBornSeparable interface
//!
//! IFormFactorBornSeparable defines a Born formfactor, whose scattering amplitude
//! only depends on the scattering vector \f$q\equiv k_i-k_f\f$ and that separates
//! into a radial and a z-dependent part
//- -------------------------------------------------------------------
class IFormFactorBornSeparable : public IFormFactorBorn
{
public:
    IFormFactorBornSeparable();
    virtual ~IFormFactorBornSeparable() {}
    virtual IFormFactorBornSeparable *clone() const=0;

    virtual complex_t evaluate(const cvector_t &k_i, const Bin1DCVector &k_f_bin, double alpha_i, double alpha_f) const;

    virtual complex_t evaluate_for_q(const cvector_t &q) const;

protected:
    //! evaluate radial part of scattering amplitude for complex wavevector
    virtual complex_t evaluate_for_q_radial(const cvector_t &q) const=0;

    //! evaluate z-part of scattering amplitude for complex wavevector
    virtual complex_t evaluate_for_q_z(const cvector_t &q) const=0;
};

inline complex_t IFormFactorBornSeparable::evaluate(const cvector_t& k_i,
        const Bin1DCVector& k_f_bin, double alpha_i, double alpha_f) const
{
    (void)alpha_i;
    (void)alpha_f;
    complex_t radial, zpart;
    Bin1DCVector q_bin(k_i - k_f_bin.m_q_lower, k_i - k_f_bin.m_q_upper);
    double delta_qr = std::abs( q_bin.getDelta().magxy() );
    if ( delta_qr > M_PI/2.0/getRadius() ) {
        radial = bigRadialPart(q_bin);
    } else {
    radial = evaluate_for_q_radial(q_bin.getMidPoint());
    }
    double delta_qz = std::abs( q_bin.getDelta().z() );
    if ( delta_qz > M_PI/2.0/getHeight() ) {
        zpart = bigZPart(q_bin);
    } else {
        zpart = evaluate_for_q_z(q_bin.getMidPoint());
    }
    return getVolume()*radial*zpart;
}

inline complex_t IFormFactorBornSeparable::evaluate_for_q(const cvector_t& q) const
{
    return getVolume()*evaluate_for_q_radial(q)*evaluate_for_q_z(q);
}

#endif /* IFORMFACTORBORNSEPARABLE_H_ */
