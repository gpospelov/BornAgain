// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/inc/StochasticDoubleGate.h
//! @brief     Defines class StochasticDoubleGate.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef STOCHASTICDOUBLEGATE_H_
#define STOCHASTICDOUBLEGATE_H_

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
