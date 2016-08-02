// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Parametrization/Scalar.h
//! @brief     Declares class Scalar.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef SCALAR_H
#define SCALAR_H

#include "RealParameter.h" // inheriting from

//! A parameter of that is physically dimensionless.

class Scalar : public RealParameter
{
public:
    Scalar(const std::string& name, ParameterPool* parent, volatile double* par,
          const AttLimits& limits)
        : RealParameter( name, parent, par, limits ) {}

    Scalar(const std::string& name, ParameterPool* parent, volatile double* par, double upperLimit)
        : Scalar( name, parent, par, AttLimits::limited(0.,upperLimit) ) {}

    virtual Scalar* clone( const std::string& new_name="" ) const {
        return new Scalar( new_name!="" ? new_name : m_name, m_parent, m_data, m_limits ); }

    std::string unit() const final { return ""; }
};

#endif // SCALAR_H
