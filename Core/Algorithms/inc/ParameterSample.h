// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/ParameterSample.h
//! @brief     Defines class ParameterSample.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PARAMETERSAMPLE_H_
#define PARAMETERSAMPLE_H_

//! @class ParameterSample
//! @ingroup algorithms_internal
//! @brief Represents a sampled parameter value with its weight
struct ParameterSample
{
	double value;
	double weight;
};

#endif /* PARAMETERSAMPLE_H_ */
