//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Device/Instrument/PyFmt2.h
//! @brief     Defines namespace pyfmt2.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_DEVICE_INSTRUMENT_PYFMT2_H
#define BORNAGAIN_DEVICE_INSTRUMENT_PYFMT2_H

#include <functional>
#include <string>

class IDistribution1D;
class IParameterized;
class IShape2D;
class RealParameter;
class ParameterDistribution;

//! Utility functions for writing Python code snippets.

namespace pyfmt2 {

std::string representShape2D(const std::string& indent, const IShape2D* ishape, bool mask_value,
                             std::function<std::string(double)> printValueFunc);

std::string valueTimesUnit(const RealParameter* par);
std::string argumentList(const IParameterized* ip);

std::string printDistribution(const IDistribution1D& par_distr, const std::string& units = "");

std::string printParameterDistribution(const ParameterDistribution& par_distr,
                                       const std::string& distVarName,
                                       const std::string& units = "");
} // namespace pyfmt2

#endif // BORNAGAIN_DEVICE_INSTRUMENT_PYFMT2_H
