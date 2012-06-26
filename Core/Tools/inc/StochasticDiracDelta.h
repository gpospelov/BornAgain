#ifndef STOCHASTICDIRACDELTA_H
#define STOCHASTICDIRACDELTA_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   StochasticDiracDelta.h
//! @brief  Definition of StochasticDiracDelta class
//! @author Scientific Computing Group at FRM II
//! @date   01.04.2012

#include "IStochasticParameter.h"


template <class T> class StochasticDiracDelta : public StochasticParameter<T>
{
public:
    StochasticDiracDelta(T average);
    virtual ~StochasticDiracDelta() {}
    virtual StochasticDiracDelta *clone() const;

    virtual void setToAverage() {}
    virtual void setToRandom() {}
    virtual double probabilityDensity(T /*value*/) const { return 0.0; }

};

template <class T> StochasticDiracDelta<T>::StochasticDiracDelta(T average)
    : StochasticParameter<T>(average)
{
    this->m_current = this->m_average;
}

template <class T> StochasticDiracDelta<T> *StochasticDiracDelta<T>::clone() const
{
    return new StochasticDiracDelta<T>(this->m_average);
}

#endif // STOCHASTICDIRACDELTA_H
