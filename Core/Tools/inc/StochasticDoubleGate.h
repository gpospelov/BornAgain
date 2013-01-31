#ifndef STOCHASTICDOUBLEGATE_H_
#define STOCHASTICDOUBLEGATE_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   StochasticDoubleGate.h
//! @brief  Definition of StochasticDoubleGate class
//! @author Scientific Computing Group at FRM II
//! @date   Jan 31, 2013

#include "IStochasticParameter.h"
#include "MathFunctions.h"

#include <cmath>

class StochasticDoubleGate : public StochasticParameter<double>
{
public:
    StochasticDoubleGate(double min, double max);
    ~StochasticDoubleGate() {}
    virtual StochasticDoubleGate *clone() const {
        return new StochasticDoubleGate(m_min, m_max);
    }

    virtual void setToRandom();
    virtual double probabilityDensity(double value) const {
        (void)value;
        return 1.0/(m_max-m_min);
    }

    double getStdDev() const { return (m_max-m_min)/(2.0*std::sqrt(3.0)); }

    virtual double getFWHM() const { return m_max-m_min; }

private:
    double m_min, m_max;
};

inline void StochasticDoubleGate::setToRandom()
{
    double uniform_random = MathFunctions::GenerateUniformRandom();
    m_current = m_min + (m_max-m_min)*uniform_random;
}

inline StochasticDoubleGate::StochasticDoubleGate(double min, double max)
: StochasticParameter<double>((m_min+m_max)/2.0)
, m_min(min)
, m_max(max)
{
}

#endif /* STOCHASTICDOUBLEGATE_H_ */
