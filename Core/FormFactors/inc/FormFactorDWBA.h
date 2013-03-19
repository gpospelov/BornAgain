// ************************************************************************** //
//                                                                           
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @copyright Forschungszentrum Jülich GmbH 2013
//             
//  Homepage:  apps.jcns.fz-juelich.de/BornAgain
//  License:   GNU General Public License v3 or higher (see COPYING)
//
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
//! @file      FormFactors/FormFactorDWBA.h 
//! @brief     Defines class FormFactorDWBA.
//
// ************************************************************************** //

#ifndef FORMFACTORDWBA_H_
#define FORMFACTORDWBA_H_

#include "IFormFactorDecorator.h"
#include "IDoubleToComplexFunction.h"

//! ?

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
};

inline const complexpair_t &FormFactorDWBA::getRT(double alpha) const
{
    return mp_RT->evaluate(alpha);
}

#endif /* FORMFACTORDWBA_H_ */
