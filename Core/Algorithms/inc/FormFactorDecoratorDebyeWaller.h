#ifndef FORMFACTORDECORATORDEBYEWALLER_H_
#define FORMFACTORDECORATORDEBYEWALLER_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   FormFactorDecoratorDebyeWaller.h
//! @brief  Definition of Formfactor decorator which includes a Debye-Waller factor
//! @author Scientific Computing Group at FRM II
//! @date   Aug 31, 2012

class FormFactorDecoratorDebyeWaller : public IFormFactorDecorator
{
public:
    FormFactorDecoratorDebyeWaller(IFormFactor *p_form_factor, double dw_factor);
    virtual FormFactorDecoratorDebyeWaller *clone() const;
    virtual ~FormFactorDecoratorDebyeWaller();

    virtual complex_t evaluate(cvector_t k_i, cvector_t k_f, double alpha_i, double alpha_f) const;

    virtual int getNumberOfStochasticParameters() const;

protected:
    double m_dw_factor; //!< This factor is <u^2>/6 where <u^2> is the variance of the thermal movement of the particle
};

inline FormFactorDecoratorDebyeWaller::FormFactorDecoratorDebyeWaller(
        IFormFactor* p_form_factor, double dw_factor)
: IFormFactorDecorator(p_form_factor)
, m_dw_factor(dw_factor)
{
}

inline FormFactorDecoratorDebyeWaller* FormFactorDecoratorDebyeWaller::clone() const
{
    return new FormFactorDecoratorDebyeWaller(mp_form_factor->clone(), m_dw_factor);
}

inline FormFactorDecoratorDebyeWaller::~FormFactorDecoratorDebyeWaller()
{
    delete mp_form_factor;
}

inline complex_t FormFactorDecoratorDebyeWaller::evaluate(cvector_t k_i,
        cvector_t k_f, double alpha_i, double alpha_f) const
{
    cvector_t q = k_i - k_f;
    double q2 = std::norm(q.x()) + std::norm(q.y()) + std::norm(q.z());
    double dw = std::exp(-q2*m_dw_factor);
    return dw*mp_form_factor->evaluate(k_i, k_f, alpha_i, alpha_f);
}

inline int FormFactorDecoratorDebyeWaller::getNumberOfStochasticParameters() const
{
    return mp_form_factor->getNumberOfStochasticParameters();
}


#endif /* FORMFACTORDECORATORDEBYEWALLER_H_ */
