#ifndef FORMFACTORCYLINDER_H
#define FORMFACTORCYLINDER_H

#include "IFormFactor.h"
#include "IStochasticParameter.h"

class FormFactorCylinder : public IFormFactor
{
public:
    FormFactorCylinder(double height, double radius);
    FormFactorCylinder(StochasticParameter<double> *p_height, StochasticParameter<double> *p_radius);
    ~FormFactorCylinder();

    virtual complex_t evaluate(kvector_t q) const;
    virtual int getNumberOfStochasticParameters() { return 2; }

private:
    StochasticParameter<double> *mp_height;
    StochasticParameter<double> *mp_radius;
};

#endif // FORMFACTORCYLINDER_H
