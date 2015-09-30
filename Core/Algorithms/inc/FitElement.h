// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FitKernel/inc/FitElement.h
//! @brief     Defines class FitElement.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FITELEMENT_H
#define FITELEMENT_H

#include "WinDllMacros.h"

//! @class FitElement
//! @ingroup fitting_internal
//! @brief Data stucture containing real data and simulation results for single detector cell.
//! Used for chi2/residual calculations.

class BA_CORE_API_ FitElement
{
public:
    FitElement();
    FitElement(double simul_value, double real_value);
    FitElement(const FitElement &other);
    FitElement &operator=(const FitElement &other);

    double getSimulValue() const;

    double getRealValue() const;

    double getWeight() const;

    double getSquaredDifference() const;
    void setSquaredDifference(double value);

    double getResidual() const;
    void setResidual(double value);

private:
    void swapContent(FitElement &other);

    double m_simul_value;
    double m_real_value;
    double m_weight;
    double m_squared_difference;
    double m_residual;
};


inline double FitElement::getSimulValue() const
{
    return m_simul_value;
}

inline double FitElement::getRealValue() const
{
    return m_real_value;
}

inline double FitElement::getWeight() const
{
    return m_weight;
}

inline double FitElement::getSquaredDifference() const
{
    return m_squared_difference;
}

inline void FitElement::setSquaredDifference(double value)
{
    m_squared_difference = value;
}

inline double FitElement::getResidual() const
{
    return m_residual;
}

inline void FitElement::setResidual(double value)
{
    m_residual = value;
}

#endif

