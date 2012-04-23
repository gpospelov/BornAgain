#ifndef IFORMFACTOR_H
#define IFORMFACTOR_H

#include "Types.h"

class IFormFactor
{
public:
    virtual ~IFormFactor() {}

    virtual complex_t evaluate(kvector_t q) const=0;
    virtual int getNumberOfStochasticParameters() { return 0; }
};

#endif // IFORMFACTOR_H
