// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/FormFactorDecoratorDebyeWaller.h
//! @brief     Defines and implements class FormFactorDecoratorDebyeWaller.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORDECORATORDEBYEWALLER_H_
#define FORMFACTORDECORATORDEBYEWALLER_H_

#include "IFormFactorDecorator.h"

//! Debye-Waller factors in radial and z directions.

class FormFactorDecoratorDebyeWaller : public IFormFactorDecorator
{
 public:
    //! Isotropic Debye-Waller factor.
    FormFactorDecoratorDebyeWaller(
        IFormFactor *p_form_factor, double dw_factor)
    : IFormFactorDecorator(p_form_factor)
    , m_h_dw_factor(dw_factor)
    , m_r_dw_factor(dw_factor)
    {
        setName("FormFactorDecoratorDebyeWaller");
        init_parameters();
    }

    //! Anisotropic Debye-Waller factor.
    FormFactorDecoratorDebyeWaller(
        IFormFactor *p_form_factor, double dw_h_factor, double dw_r_factor)
    : IFormFactorDecorator(p_form_factor)
    , m_h_dw_factor(dw_h_factor)
    , m_r_dw_factor(dw_r_factor)
    {
        setName("FormFactorDecoratorDebyeWaller");
        init_parameters();
    }

    //! Why the hell do we need this alternative form?
    FormFactorDecoratorDebyeWaller(
        const IFormFactor& p_form_factor,
        double dw_h_factor, double dw_r_factor)
    : IFormFactorDecorator(p_form_factor.clone())
    , m_h_dw_factor(dw_h_factor)
    , m_r_dw_factor(dw_r_factor)
    {
        setName("FormFactorDecoratorDebyeWaller");
        init_parameters();
    }

    virtual ~FormFactorDecoratorDebyeWaller() {}

    virtual FormFactorDecoratorDebyeWaller *clone() const
    {
        return new FormFactorDecoratorDebyeWaller(
            mp_form_factor->clone(), m_h_dw_factor, m_r_dw_factor);
    }

    virtual complex_t evaluate(
        const cvector_t& k_i, const Bin1DCVector& k_f_bin,
        double alpha_i, double alpha_f) const
    {
        cvector_t q = k_i - k_f_bin.getMidPoint();
        double qr2 = std::norm(q.x()) + std::norm(q.y());
        double qz2 = std::norm(q.z());
        double dw = std::exp(-qz2*m_h_dw_factor-qr2*m_r_dw_factor);
        return dw*mp_form_factor->evaluate(k_i, k_f_bin, alpha_i, alpha_f);
    }

    virtual int getNumberOfStochasticParameters() const
    { return mp_form_factor->getNumberOfStochasticParameters(); }

 protected:
    //! Registers some class members for later access via parameter pool
    virtual void init_parameters() {
        clearParameterPool();
        registerParameter("hfactor", &m_h_dw_factor);
        registerParameter("rfactor", &m_r_dw_factor);
    }

 private:
    double m_h_dw_factor; //!< the Debye-Waller factor in the z-direction
    double m_r_dw_factor; //!< the Debye-Waller factor in the radial direction
};

#endif /* FORMFACTORDECORATORDEBYEWALLER_H_ */


