// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/DetectorFunctions.cpp
//! @brief     Implements namespace DetectorFunctions.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "DetectorFunctions.h"
#include "OutputData.h"
#include "Instrument.h"
#include "SimulationArea.h"
#include "StringUtils.h"
#include <sstream>
#include <algorithm>
#include <map>
#include <cctype>

namespace
{
std::map<std::string, AxesUnits> init_name_to_units_map()
{
    std::map<std::string, AxesUnits> result;
    result["nbins"] = AxesUnits::NBINS;
    result["radians"] = AxesUnits::RADIANS;
    result["rad"] = AxesUnits::RADIANS;
    result["degrees"] = AxesUnits::DEGREES;
    result["deg"] = AxesUnits::DEGREES;
    result["mm"] = AxesUnits::MM;
    result["qyqz"] = AxesUnits::QSPACE;
    return result;
}

std::map<AxesUnits, std::string> init_units_to_name_map()
{
    std::map<AxesUnits, std::string> result;
    result[AxesUnits::NBINS] = "nbins";
    result[AxesUnits::RADIANS] = "rad";
    result[AxesUnits::DEGREES] = "deg";
    result[AxesUnits::MM] = "mm";
    result[AxesUnits::QSPACE] = "qyqz";
    result[AxesUnits::DEFAULT] = "";
    return result;
}
}

bool DetectorFunctions::hasSameDimensions(const IDetector& detector, const OutputData<double>& data)
{
    if (data.getRank() != detector.dimension())
        return false;

    for (size_t i = 0; i < detector.dimension(); ++i)
        if(data.getAxis(i).size() != detector.getAxis(i).size())
            return false;

    return true;
}

std::string DetectorFunctions::axesToString(const IDetector& detector)
{
    std::ostringstream result;

    result << "(";
    for (size_t i = 0; i < detector.dimension(); ++i) {
        result << detector.getAxis(i).size();
        if(i!=detector.dimension()-1)
            result << ",";
    }
    result << ")";

    return result.str();
}

std::string DetectorFunctions::axesToString(const OutputData<double> &data)
{
    std::ostringstream result;

    result << "(";
    for (size_t i = 0; i < data.getRank(); ++i) {
        result << data.getAxis(i).size();
        if(i!=data.getRank()-1)
            result << ",";
    }
    result << ")";

    return result.str();
}

std::unique_ptr<OutputData<double>> DetectorFunctions::createDataSet(const Instrument &instrument,
    const OutputData<double> &data, bool put_masked_areas_to_zero, AxesUnits units)
{
    if(!DetectorFunctions::hasSameDimensions(*instrument.getDetector(), data)){
        std::ostringstream message;
        message << "DetectorFunctions::createDataSet -> Error. Axes of the real data doesn't match "
                << "the detector. Real data:" << DetectorFunctions::axesToString(data)
                        << ", detector:"
                        << DetectorFunctions::axesToString(*instrument.getDetector()) << ".";
        throw Exceptions::RuntimeErrorException(message.str());
    }

    std::unique_ptr<OutputData<double>> result(instrument.createDetectorMap(units));

    if(put_masked_areas_to_zero) {

        SimulationArea area(instrument.getDetector());
        for(SimulationArea::iterator it = area.begin(); it!=area.end(); ++it) {
            (*result)[it.roiIndex()] = data[it.detectorIndex()];
        }

    } else {
        SimulationRoiArea area(instrument.getDetector());
        for(SimulationRoiArea::iterator it = area.begin(); it!=area.end(); ++it) {
            (*result)[it.roiIndex()] = data[it.detectorIndex()];
        }
    }

    return result;
}

AxesUnits DetectorFunctions::detectorUnits(const std::string& unitName)
{
    if(unitName.empty())
        return AxesUnits::DEFAULT;

    static auto units_map = init_name_to_units_map();

    std::string lowercase = StringUtils::to_lower(unitName);
    auto it = units_map.find(lowercase);
    if(it == units_map.end())
        throw std::runtime_error("DetectorFunctions::detectorUnits() -> Error. No such "
                                 "detector unit '"+unitName+"'");

    return it->second;
}

std::string DetectorFunctions::detectorUnitsName(AxesUnits units)
{
    static auto units_map = init_units_to_name_map();
    auto it = units_map.find(units);
    if(it == units_map.end())
        throw std::runtime_error("DetectorFunctions::detectorUnitsName() -> Error. No such "
                                 "detector unit '"+std::to_string(static_cast<int>(units))+"'");
    return it->second;
}
