#ifndef FORMFACTORDWBA_H_
#define FORMFACTORDWBA_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   FormFactorDWBA.h
//! @brief  Definition of FormFactorDWBA
//! @author herck
//! @date   01.05.2012

#include "IFormFactor.h"
#include "IDoubleToComplexFunction.h"


class FormFactorDWBA: public IFormFactorDecorator
{
public:
    FormFactorDWBA(IFormFactor* p_form_factor);
    virtual ~FormFactorDWBA();

    virtual FormFactorDWBA *clone() const;

    void setTransmissionFunction(const IDoubleToComplexFunction &p_T)
    {
        mp_T = p_T.clone();
    }
    void setReflectionFunction(const IDoubleToComplexFunction &p_R)
    {
        mp_R = p_R.clone();
    }

    virtual complex_t evaluate(const cvector_t &k_i, const cvector_t &k_f, double alpha_i, double alpha_f) const;
protected:
    //! copy constructor and assignment operator are hidden since there is a clone method
    FormFactorDWBA(const FormFactorDWBA &);
    FormFactorDWBA &operator=(const FormFactorDWBA &);

    complex_t getT(double alpha) const;
    complex_t getR(double alpha) const;
    complex_t getX(double alpha) const;
    void calculateTerms(const cvector_t &k_i, const cvector_t &k_f, double alpha_i, double alpha_f) const;

    IDoubleToComplexFunction *mp_T;
    IDoubleToComplexFunction *mp_R;

    mutable complex_t m_term_S, m_term_RS, m_term_SR, m_term_RSR;
};

inline complex_t FormFactorDWBA::getT(double alpha) const
{
    return mp_T->evaluate(alpha);
}

inline complex_t FormFactorDWBA::getR(double alpha) const
{
    return mp_R->evaluate(alpha);
}

inline complex_t FormFactorDWBA::getX(double alpha) const
{
    return getR(alpha)/getT(alpha);
}

#endif /* FORMFACTORDWBA_H_ */
