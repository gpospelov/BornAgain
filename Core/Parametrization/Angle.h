// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Parametrization/Angle.h
//! @brief     Declares class Angle.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ANGLE_H
#define ANGLE_H

#include "RealParameter.h" // inheriting from

//! A parameter of physical dimension "angle". Values are in rad? deg? TODO clarify

class Angle : public RealParameter
{
public:
    Angle(const std::string& name, ParameterPool* parent, volatile double* par,
          const AttLimits& limits)
        : RealParameter( name, parent, par, limits ) {}

    Angle(const std::string& name, ParameterPool* parent, volatile double* par, double upperLimit)
        : Angle( name, parent, par, AttLimits::limited(0.,upperLimit) ) {}

    virtual Angle* clone( const std::string& new_name="" ) const {
        return new Angle( new_name!="" ? new_name : m_name, m_parent, m_data, m_limits ); }

    std::string unit() const final { return "deg"; }
};

#endif // ANGLE_H
