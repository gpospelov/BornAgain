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

#include "IFormFactor.h"
#include "LayerSpecularInfo.h"

//! @class FormFactorDWBAPol
//! @ingroup formfactors_internal
//! @brief Evaluates a coherent sum of the 16 matrix DWBA terms in a polarized formfactor.

class BA_CORE_API_ FormFactorDWBAPol : public IFormFactor
{
public:
    FormFactorDWBAPol(IFormFactor *p_form_factor);
    virtual ~FormFactorDWBAPol();

    virtual FormFactorDWBAPol *clone() const;

    //! calls the ISampleVisitor's visit method
    virtual void accept(ISampleVisitor *visitor) const { visitor->visit(this); }

    //! Throws exception
    virtual complex_t evaluate(const cvector_t& k_i,
            const Bin1DCVector& k_f_bin, const Bin1D &alpha_f) const;

    //! Calculates and returns a polarized form factor calculation in DWBA
    virtual Eigen::Matrix2cd evaluatePol(const cvector_t& k_i,
            const Bin1DCVector& k_f_bin, const Bin1D &alpha_f, const Bin1D &phi_f) const;

    //! Sets reflection/transmission info for polarized DWBA
    void setSpecularInfo(const LayerSpecularInfo& layer_specular_info);

    friend class TestPolarizedDWBATerms;

protected:
    const ILayerRTCoefficients *getOutCoeffs(double alpha_f,
            double phi_f) const;
    void calculateTerms(const cvector_t& k_i, const Bin1DCVector& k_f_bin,
            const Bin1D &alpha_f, const Bin1D &phi_f) const;

    //! The matrix form factor for BA
    IFormFactor *mp_form_factor;

    //! The reflection/transmission coefficients in the layer
    LayerSpecularInfo *mp_specular_info;

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

inline const ILayerRTCoefficients *FormFactorDWBAPol::getOutCoeffs(
        double alpha_f, double phi_f) const
{
    return mp_specular_info->getOutCoefficients(alpha_f, phi_f);
}

#endif /* FORMFACTORDWBAPOL_H_ */
