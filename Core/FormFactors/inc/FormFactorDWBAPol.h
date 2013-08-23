// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/FormFactorDWBAPol.h
//! @brief     Defines class FormFactorDWBAPol.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORDWBAPOL_H_
#define FORMFACTORDWBAPOL_H_

#include "FormFactorPol.h"

//! Evaluates a coherent sum of the 16 matrix DWBA terms in a polarized form factor

class FormFactorDWBAPol : public FormFactorPol
{
public:
    FormFactorDWBAPol(IFormFactor *p_formfactor);
    virtual ~FormFactorDWBAPol();

    virtual FormFactorDWBAPol *clone() const;

    //! Calculates and returns a polarized form factor calculation in DWBA
    virtual Eigen::Matrix2cd evaluatePol(const cvector_t& k_i,
            const Bin1DCVector& k_f1_bin, const Bin1DCVector& k_f2_bin,
            double alpha_i, double alpha_f, double phi_f) const;

protected:
    void calculateTerms(const cvector_t& k_i, const Bin1DCVector& k_f1_bin,
            const Bin1DCVector& k_f2_bin, double alpha_i, double alpha_f,
            double phi_f) const;

    //! The following matrices each contain the four polarization conditions
    //! (p->p, p->m, m->p, m->m)
    //! The first two indices indicate a scattering from the 1/2 eigenstate into
    //! the 1/2 eigenstate, while the capital indices indicate a reflection
    //! before and/or after the scattering event (first index is in-state,
    //! second is out-state; this also applies to the internal matrix indices)
    mutable Eigen::Matrix2cd m_M11_S;
    mutable Eigen::Matrix2cd m_M11_RS;
    mutable Eigen::Matrix2cd m_M11_SR;
    mutable Eigen::Matrix2cd m_M11_RSR;
    mutable Eigen::Matrix2cd m_M12_S;
    mutable Eigen::Matrix2cd m_M12_RS;
    mutable Eigen::Matrix2cd m_M12_SR;
    mutable Eigen::Matrix2cd m_M12_RSR;
    mutable Eigen::Matrix2cd m_M21_S;
    mutable Eigen::Matrix2cd m_M21_RS;
    mutable Eigen::Matrix2cd m_M21_SR;
    mutable Eigen::Matrix2cd m_M21_RSR;
    mutable Eigen::Matrix2cd m_M22_S;
    mutable Eigen::Matrix2cd m_M22_RS;
    mutable Eigen::Matrix2cd m_M22_SR;
    mutable Eigen::Matrix2cd m_M22_RSR;
};

#endif /* FORMFACTORDWBAPOL_H_ */
