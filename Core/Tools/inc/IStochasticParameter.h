// ************************************************************************** //
//                                                                           
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @copyright Forschungszentrum Jülich GmbH 2013
//             
//  Homepage:  apps.jcns.fz-juelich.de/BornAgain
//  License:   GNU General Public License v3 or higher (see COPYING)
//
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
//! @file      Tools/IStochasticParameter.h 
//! @brief     Defines class IStochasticParameter.
//
// ************************************************************************** //

#ifndef ISTOCHASTICPARAMETER_H
#define ISTOCHASTICPARAMETER_H

#include "ICloneable.h"

class IStochasticParameter : public ICloneable
{
public:
    virtual ~IStochasticParameter() {}
//    virtual IStochasticParameter *clone() const=0;
    virtual void setToRandom()=0;
    virtual void setToAverage()=0;
};

template <class T> class StochasticParameter : public IStochasticParameter
{
public:
    StochasticParameter(T average);
    virtual ~StochasticParameter() {}
    virtual StochasticParameter<T> *clone() const=0;

    virtual void setToAverage();
    T getCurrent() const { return m_current; }
    T getAverage();
    virtual T getRandom();
    virtual double probabilityDensity(T value) const=0;
    virtual double getFWHM() const { return 0.0;}

protected:
//    //! copy constructor and assignment operator are hidden since there is a clone method
//    StochasticParameter(const StochasticParameter<T> &);
//    StochasticParameter<T> &operator=(const StochasticParameter<T> &);

    T m_current;
    T m_average;
};

template <class T> StochasticParameter<T>::StochasticParameter(T average)
    : m_average(average)
{
    setToAverage();
}

template <class T> inline void StochasticParameter<T>::setToAverage()
{
    m_current = m_average;
}

template <class T> inline T StochasticParameter<T>::getAverage()
{
    setToAverage();
    return m_current;
}

template <class T> inline T StochasticParameter<T>::getRandom()
{
    setToRandom();
    return m_current;
}

#endif // ISTOCHASTICPARAMETER_H
