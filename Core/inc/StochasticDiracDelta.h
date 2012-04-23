#ifndef STOCHASTICDIRACDELTA_H
#define STOCHASTICDIRACDELTA_H

#include "IStochasticParameter.h"

template <class T> class StochasticDiracDelta : public StochasticParameter<T>
{
public:
    StochasticDiracDelta(T average);
    virtual ~StochasticDiracDelta() {}

    virtual void setToAverage() {}
    virtual void setToRandom() {}
    virtual double probabilityDensity(T value) const { return 0.0; }

};

template <class T> StochasticDiracDelta<T>::StochasticDiracDelta(T average)
    : StochasticParameter<T>(average)
{
    this->m_current = this->m_average;
}

#endif // STOCHASTICDIRACDELTA_H
