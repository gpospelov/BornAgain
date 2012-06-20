#ifndef STOCHASTICGAUSSIAN_H
#define STOCHASTICGAUSSIAN_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   StochasticGaussian.h
//! @brief  Definition of StochasticGaussian class
//! @author Scientific Computing Group at FRM II
//! @date   01.04.2012

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
