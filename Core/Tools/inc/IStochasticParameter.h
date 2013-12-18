// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/inc/IStochasticParameter.h
//! @brief     Defines class IStochasticParameter.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ISTOCHASTICPARAMETER_H
#define ISTOCHASTICPARAMETER_H

#include "ICloneable.h"


//! @class IStochasticParameter
//! @ingroup tools_internal
//! @brief Interface class to all parameters having a stochastic behaviour.

class BA_CORE_API_ IStochasticParameter : public ICloneable
{
public:
    virtual ~IStochasticParameter() {}
    virtual void setToRandom()=0;
    virtual void setToAverage()=0;
};


//! @class StochasticParameter
//! @ingroup tools
//! @brief Basic stochastic parameters

template <class T> class BA_CORE_API_ StochasticParameter : public IStochasticParameter
{
public:
    StochasticParameter(T average) : m_average(average)
	{
		setToAverage();
	}

    virtual ~StochasticParameter() {}
    virtual StochasticParameter<T> *clone() const=0;

    virtual void setToAverage() { m_current = m_average; }

    T getCurrent() const { return m_current; }

    T getAverage()
	{
		setToAverage();
		return m_current;
	}

    virtual T getRandom()
	{
	    setToRandom();
		return m_current;
	}

    virtual double probabilityDensity(T value) const=0;
    virtual double getFWHM() const { return 0.0;}

protected:
    T m_current;
    T m_average;
};

#endif // ISTOCHASTICPARAMETER_H


