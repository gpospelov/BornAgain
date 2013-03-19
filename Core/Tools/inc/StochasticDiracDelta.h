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
//! @file      Tools/StochasticDiracDelta.h 
//! @brief     Defines class StochasticDiracDelta.
//
// ************************************************************************** //

#ifndef STOCHASTICDIRACDELTA_H
#define STOCHASTICDIRACDELTA_H

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

private:
    //! copy constructor and assignment operator are hidden since there is a clone method
    StochasticDiracDelta(const StochasticDiracDelta<T> &);
    StochasticDiracDelta<T> &operator=(const StochasticDiracDelta<T> &);
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
