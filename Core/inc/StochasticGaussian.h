#ifndef STOCHASTICGAUSSIAN_H
#define STOCHASTICGAUSSIAN_H

#include "IStochasticParameter.h"

class StochasticDoubleGaussian : public StochasticParameter<double>
{
public:
    StochasticDoubleGaussian(double average, double std_dev);
    ~StochasticDoubleGaussian();

    virtual void setToRandom();
    virtual double probabilityDensity(double value) const;

    double getStdDev() { return m_std_dev; }

private:
    double m_std_dev;
};


#endif // STOCHASTICGAUSSIAN_H
