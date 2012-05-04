#ifndef FORMFACTORCYLINDER_H
#define FORMFACTORCYLINDER_H

#include "IFormFactor.h"
#include "IStochasticParameter.h"

class FormFactorCylinder : public IBornFormFactor
{
public:
    FormFactorCylinder(double height, double radius);
    FormFactorCylinder(StochasticParameter<double> *p_height, StochasticParameter<double> *p_radius);
    ~FormFactorCylinder();

    virtual int getNumberOfStochasticParameters() { return 2; }

protected:
    virtual complex_t evaluate_for_q(kvector_t q) const;

private:
    StochasticParameter<double> *mp_height;
    StochasticParameter<double> *mp_radius;
};

#endif // FORMFACTORCYLINDER_H
