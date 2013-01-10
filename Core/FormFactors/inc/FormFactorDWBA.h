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

#include "IFormFactorDecorator.h"
#include "IDoubleToComplexFunction.h"


class FormFactorDWBA: public IFormFactorDecorator
{
public:
    FormFactorDWBA(IFormFactor* p_form_factor);
    virtual ~FormFactorDWBA();

    virtual FormFactorDWBA *clone() const;

    void setReflectionTransmissionFunction(const IDoubleToPairOfComplexMap &p_rt)
    {
        delete mp_RT;
        mp_RT = p_rt.clone();
    }

    virtual complex_t evaluate(const cvector_t &k_i, const Bin1DCVector &k_f_bin, double alpha_i, double alpha_f) const;

protected:
    const complexpair_t &getRT(double alpha) const;
    void calculateTerms(const cvector_t &k_i, const Bin1DCVector &k_f_bin, double alpha_i, double alpha_f) const;

    IDoubleToPairOfComplexMap *mp_RT;

    mutable complex_t m_term_S, m_term_RS, m_term_SR, m_term_RSR;

private:
    FormFactorDWBA(const FormFactorDWBA &);
    FormFactorDWBA &operator=(const FormFactorDWBA &);
};


inline const complexpair_t &FormFactorDWBA::getRT(double alpha) const
{
    return mp_RT->evaluate(alpha);
}


#endif /* FORMFACTORDWBA_H_ */
