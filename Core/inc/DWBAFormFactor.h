/*
 * DWBAFormFactor.h
 *
 *  Created on: Apr 26, 2012
 *      Author: herck
 */

#ifndef DWBAFORMFACTOR_H_
#define DWBAFORMFACTOR_H_

#include "IFormFactor.h"
#include "IDoubleToComplexFunction.h"

class DWBAFormFactor: public IFormFactor
{
public:
    DWBAFormFactor(IFormFactor* p_form_factor);
    virtual ~DWBAFormFactor();

    void setTransmissionFunction(IDoubleToComplexFunction *p_T)
    {
        mp_T = p_T;
    }
    void setReflectionFunction(IDoubleToComplexFunction *p_R)
    {
        mp_R = p_R;
    }
    virtual complex_t evaluate(kvector_t k_i, kvector_t k_f) const;
protected:
    IFormFactor *mp_form_factor;
    IDoubleToComplexFunction *mp_T;
    IDoubleToComplexFunction *mp_R;
    complex_t getT(double alpha) const;
    complex_t getR(double alpha) const;
    complex_t getX(double alpha) const;
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
