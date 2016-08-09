// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Parametrization/DimensionedParameters.h
//! @brief     Defines the dimensioned parameter classes Angle, Length, Scalar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef DIMENSIONEDPARAMETERS_H
#define DIMENSIONEDPARAMETERS_H

#include "RealParameter.h"

//! A parameter of physical dimension "angle".

class Angle : public RealParameter
{
public:
    Angle(const std::string& name, ParameterPool* parent, volatile double* par,
          const AttLimits& limits)
        : RealParameter( name, parent, par, limits ) {}

    virtual Angle* clone( const std::string& new_name="" ) const {
        return new Angle( new_name!="" ? new_name : m_name, m_parent, m_data, m_limits ); }

    std::string unit() const final { return "rad"; }
};

//! A parameter of physical dimension "length". Values are in nm.

class Length : public RealParameter
{
public:
    Length(const std::string& name, ParameterPool* parent, volatile double* par,
           const AttLimits& limits)
        : RealParameter( name, parent, par, limits ) {}

    virtual Length* clone( const std::string& new_name="" ) const {
        return new Length( new_name!="" ? new_name : m_name, m_parent, m_data, m_limits ); }

    std::string unit() const final { return "nm"; }
};

//! A parameter of that is physically dimensionless.

class Scalar : public RealParameter
{
public:
    Scalar(const std::string& name, ParameterPool* parent, volatile double* par,
           const AttLimits& limits)
        : RealParameter( name, parent, par, limits ) {}

    virtual Scalar* clone( const std::string& new_name="" ) const {
        return new Scalar( new_name!="" ? new_name : m_name, m_parent, m_data, m_limits ); }

    std::string unit() const final { return ""; }
};

#endif // DIMENSIONEDPARAMETERS_H
