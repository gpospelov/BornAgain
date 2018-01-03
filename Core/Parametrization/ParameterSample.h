// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Parametrization/ParameterSample.h
//! @brief     Defines class ParameterSample.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef PARAMETERSAMPLE_H
#define PARAMETERSAMPLE_H

//! A parameter value with a weight, as obtained when sampling from a distribution.
//! @ingroup algorithms_internal

class ParameterSample
{
public:
    ParameterSample(double _value=0., double _weight=1.) : value(_value), weight(_weight) {}
    double value;
    double weight;
};

#endif // PARAMETERSAMPLE_H
