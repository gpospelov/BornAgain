// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Parametrization/Length.h
//! @brief     Declares class Length.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef LENGTH_H
#define LENGTH_H

#include "RealParameter.h" // inheriting from

//! A parameter of physical dimension "length". Values are in nm.

class Length : public RealParameter
{
public:
    Length(const std::string& name, ParameterPool* parent, volatile double* par,
          const AttLimits& limits)
        : RealParameter( name, parent, par, limits ) {}

    Length(const std::string& name, ParameterPool* parent, volatile double* par)
        : Length( name, parent, par, AttLimits::n_positive() ) {}

    virtual Length* clone( const std::string& new_name="" ) const {
        return new Length( new_name!="" ? new_name : m_name, m_parent, m_data, m_limits ); }

    std::string unit() const final { return "nm"; }
};

#endif // LENGTH_H
