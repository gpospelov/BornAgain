// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/FormFactorDecoratorDebyeWaller.h
//! @brief     Defines class FormFactorDecoratorDebyeWaller.
//!
//! @homepage  apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef FORMFACTORDECORATORDEBYEWALLER_H_
#define FORMFACTORDECORATORDEBYEWALLER_H_

#include "IFormFactorDecorator.h"

//! ?

class FormFactorDecoratorDebyeWaller : public IFormFactorDecorator
{
public:
    FormFactorDecoratorDebyeWaller(IFormFactor *p_form_factor, double dw_factor);
    FormFactorDecoratorDebyeWaller(IFormFactor *p_form_factor, double dw_h_factor, double dw_r_factor);
    FormFactorDecoratorDebyeWaller(const IFormFactor &p_form_factor, double dw_h_factor, double dw_r_factor);
    virtual FormFactorDecoratorDebyeWaller *clone() const;
    virtual ~FormFactorDecoratorDebyeWaller() {}

    virtual complex_t evaluate(const cvector_t &k_i, const Bin1DCVector &k_f_bin, double alpha_i, double alpha_f) const;

    virtual int getNumberOfStochasticParameters() const;

protected:
    //! initialize pool parameters, i.e. register some of class members for later access via parameter pool
    virtual void init_parameters() {
        getParameterPool()->clear();
        getParameterPool()->registerParameter("hfactor", &m_h_dw_factor);
        getParameterPool()->registerParameter("rfactor", &m_r_dw_factor);
    }

private:
    double m_h_dw_factor; //!< the Debye-Waller factor in the z-direction
    double m_r_dw_factor; //!< the Debye-Waller factor in the radial direction
};

inline FormFactorDecoratorDebyeWaller::FormFactorDecoratorDebyeWaller(
        IFormFactor* p_form_factor, double dw_factor)
: IFormFactorDecorator(p_form_factor)
, m_h_dw_factor(dw_factor)
, m_r_dw_factor(dw_factor)
{
    setName("FormFactorDecoratorDebyeWaller");
    init_parameters();
}

inline FormFactorDecoratorDebyeWaller::FormFactorDecoratorDebyeWaller(
        IFormFactor* p_form_factor, double dw_h_factor, double dw_r_factor)
: IFormFactorDecorator(p_form_factor)
, m_h_dw_factor(dw_h_factor)
, m_r_dw_factor(dw_r_factor)
{
    setName("FormFactorDecoratorDebyeWaller");
    init_parameters();
}

inline FormFactorDecoratorDebyeWaller::FormFactorDecoratorDebyeWaller(
        const IFormFactor &p_form_factor, double dw_h_factor, double dw_r_factor)
: IFormFactorDecorator(p_form_factor.clone())
, m_h_dw_factor(dw_h_factor)
, m_r_dw_factor(dw_r_factor)
{
    setName("FormFactorDecoratorDebyeWaller");
    init_parameters();
}

inline FormFactorDecoratorDebyeWaller* FormFactorDecoratorDebyeWaller::clone() const
{
    return new FormFactorDecoratorDebyeWaller(mp_form_factor->clone(), m_h_dw_factor, m_r_dw_factor);
}

inline complex_t FormFactorDecoratorDebyeWaller::evaluate(const cvector_t& k_i,
        const Bin1DCVector& k_f_bin, double alpha_i, double alpha_f) const
{
    cvector_t q = k_i - k_f_bin.getMidPoint();
    double qr2 = std::norm(q.x()) + std::norm(q.y());
    double qz2 = std::norm(q.z());
    double dw = std::exp(-qz2*m_h_dw_factor-qr2*m_r_dw_factor);
    return dw*mp_form_factor->evaluate(k_i, k_f_bin, alpha_i, alpha_f);
}

inline int FormFactorDecoratorDebyeWaller::getNumberOfStochasticParameters() const
{
    return mp_form_factor->getNumberOfStochasticParameters();
}

#endif /* FORMFACTORDECORATORDEBYEWALLER_H_ */
