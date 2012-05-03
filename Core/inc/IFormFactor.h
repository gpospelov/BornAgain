#ifndef IFORMFACTOR_H
#define IFORMFACTOR_H

#include "Types.h"

class IFormFactor
{
public:
    virtual ~IFormFactor() {}

    virtual complex_t evaluate(kvector_t k_i, kvector_t k_f) const=0;
    virtual int getNumberOfStochasticParameters() { return 0; }
};

class IBornFormFactor : public IFormFactor
{
public:
	virtual ~IBornFormFactor() {}

    virtual complex_t evaluate(kvector_t k_i, kvector_t k_f) const
    {
    	return evaluate_for_q(k_f - k_i);
    }
protected:
    virtual complex_t evaluate_for_q(kvector_t q) const=0;
};

#endif // IFORMFACTOR_H
