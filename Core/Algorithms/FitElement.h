// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FitKernel/FitElement.h
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
#include <cstddef>

//! @class FitElement
//! @ingroup fitting_internal
//! @brief Data stucture containing real data and simulation results for single detector cell.
//! Used for chi2/residual calculations.

class BA_CORE_API_ FitElement
{
public:
    FitElement();
    FitElement(size_t index, double simul_value, double real_value, double weight = 1.0);
    FitElement(const FitElement &other);
    FitElement &operator=(const FitElement &other);

    size_t getIndex() const;

    double getSimulValue() const;

    double getRealValue() const;

    double getWeight() const;

    double getSquaredDifference() const;
    void setSquaredDifference(double value);

    double getResidual() const;
    void setResidual(double value);

private:
    void swapContent(FitElement &other);
    size_t m_index;
    double m_simul_value;
    double m_real_value;
    double m_weight;
    double m_squared_difference;
    double m_residual;
};


inline size_t FitElement::getIndex() const
{
    return m_index;
}

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

