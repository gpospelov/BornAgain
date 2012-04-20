#ifndef STOCHASTICGAUSSIAN_H
#define STOCHASTICGAUSSIAN_H

#include "IStochasticParameter.h"

class StochasticDoubleGaussian : public IStochasticParameter
{
public:
    StochasticDoubleGaussian(double average, double std_dev);
    ~StochasticDoubleGaussian();

    virtual void setToRandom();
    virtual void setToAverage();

    double getCurrent() { return m_current; }
    double getRandom();
    double getAverage();
    double getStdDev() { return m_std_dev; }
    double getCurrentProbDensity();

private:
    double m_current;
    double m_average;
    double m_std_dev;
};


#endif // STOCHASTICGAUSSIAN_H
