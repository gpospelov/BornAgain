#ifndef ISTOCHASTICPARAMETER_H
#define ISTOCHASTICPARAMETER_H

class IStochasticParameter
{
public:
    virtual ~IStochasticParameter() {}
    virtual void setToRandom()=0;
    virtual void setToAverage()=0;
};

template <class T> class StochasticParameter : public IStochasticParameter
{
public:
    StochasticParameter(T average);
    virtual ~StochasticParameter() {}

    virtual void setToAverage();
    T getCurrent() { return m_current; }
    T getAverage();
    virtual T getRandom();
    virtual double probabilityDensity(T value) const=0;

protected:
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
