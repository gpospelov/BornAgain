// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/FormFactorDWBAPol.h
//! @brief     Declares class FormFactorDWBAPol.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
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
    FormFactorDWBAPol(const IFormFactor &form_factor);
    virtual ~FormFactorDWBAPol();

    virtual FormFactorDWBAPol *clone() const;

    //! calls the ISampleVisitor's visit method
    virtual void accept(ISampleVisitor *visitor) const { visitor->visit(this); }

    //! Throws exception
    virtual complex_t evaluate(const WavevectorInfo& wavevectors) const;

    //! Calculates and returns a polarized form factor calculation in DWBA
    virtual Eigen::Matrix2cd evaluatePol(const WavevectorInfo& wavevectors) const;

    //! Returns the total volume of the particle of this form factor's shape
    virtual double getVolume() const;

    //! Returns the (approximate in some cases) radial size of the particle of this
    //! form factor's shape. This is used for SSCA calculations
    virtual double getRadius() const;

    //! Sets reflection/transmission info for scalar DWBA simulation
    virtual void setSpecularInfo(const ILayerRTCoefficients *p_in_coeffs,
                         const ILayerRTCoefficients *p_out_coeffs);

    friend class TestPolarizedDWBATerms;

protected:
    void calculateTerms(const WavevectorInfo& wavevectors) const;

    //! The matrix form factor for BA
    IFormFactor *mp_form_factor;

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
    const ILayerRTCoefficients *mp_in_coeffs;
    const ILayerRTCoefficients *mp_out_coeffs;
};

#endif /* FORMFACTORDWBAPOL_H_ */
