#ifndef DWBAFORMFACTOR_H_
#define DWBAFORMFACTOR_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   DWBAFormFactor.h
//! @brief  Definition of DWBAFormFactor
//! @author herck
//! @date   01.05.2012

#include "IFormFactor.h"
#include "IDoubleToComplexFunction.h"


class DWBAFormFactor: public IFormFactorDecorator
{
public:
    DWBAFormFactor(IFormFactor* p_form_factor);
    virtual ~DWBAFormFactor();

    virtual DWBAFormFactor *clone() const;

//    void setTransmissionFunction(IDoubleToComplexFunction *p_T)
//    {
//        mp_T = p_T;
//    }
//    void setReflectionFunction(IDoubleToComplexFunction *p_R)
//    {
//        mp_R = p_R;
//    }
    void setTransmissionFunction(const IDoubleToComplexFunction &p_T)
    {
        mp_T = p_T.clone();
    }
    void setReflectionFunction(const IDoubleToComplexFunction &p_R)
    {
        mp_R = p_R.clone();
    }

    virtual complex_t evaluate(kvector_t k_i, kvector_t k_f) const;
    virtual complex_t evaluateForComplexkz(kvector_t k_i, kvector_t k_f,
    		complex_t k_iz, complex_t k_fz) const;
protected:
    //! copy constructor and assignment operator are hidden since there is a clone method
    DWBAFormFactor(const DWBAFormFactor &);
    DWBAFormFactor &operator=(const DWBAFormFactor &);

    complex_t getT(double alpha) const;
    complex_t getR(double alpha) const;
    complex_t getX(double alpha) const;
    void calculateTerms(kvector_t k_i, kvector_t k_f) const;
    void calculateTerms(kvector_t k_i, kvector_t k_f,
            complex_t k_iz, complex_t k_fz) const;

    IDoubleToComplexFunction *mp_T;
    IDoubleToComplexFunction *mp_R;

    mutable complex_t m_term_S, m_term_RS, m_term_SR, m_term_RSR;
};

inline complex_t DWBAFormFactor::getT(double alpha) const
{
    return mp_T->evaluate(alpha);
}

inline complex_t DWBAFormFactor::getR(double alpha) const
{
    return mp_R->evaluate(alpha);
}

inline complex_t DWBAFormFactor::getX(double alpha) const
{
    return getR(alpha)/getT(alpha);
}

#endif /* DWBAFORMFACTOR_H_ */
