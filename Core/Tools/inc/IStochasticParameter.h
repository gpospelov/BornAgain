#ifndef ISTOCHASTICPARAMETER_H
#define ISTOCHASTICPARAMETER_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   IStochasticParameter.h
//! @brief  Definition of IStochasticParameter class
//! @author Scientific Computing Group at FRM II
//! @date   01.04.2012


class IStochasticParameter
{
public:
    virtual ~IStochasticParameter() {}
    virtual IStochasticParameter *clone() const=0;
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
    T getCurrent() { return m_current; }
    T getAverage();
    virtual T getRandom();
    virtual double probabilityDensity(T value) const=0;

protected:
    //! copy constructor and assignment operator are hidden since there is a clone method
    StochasticParameter(const StochasticParameter<T> &);
    StochasticParameter<T> &operator=(const StochasticParameter<T> &);

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
