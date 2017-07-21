// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/DetectorFunctions.cpp
//! @brief     Implements namespace DetectorFunctions.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "DetectorFunctions.h"
#include "OutputData.h"
#include "IDetector2D.h"
#include "Instrument.h"
#include "SimulationArea.h"
#include "StringUtils.h"
#include <sstream>
#include <algorithm>
#include <map>
#include <cctype>

namespace
{
std::map<std::string, IDetector2D::EAxesUnits> init_name_to_units_map()
{
    std::map<std::string, IDetector2D::EAxesUnits> result;
    result["nbins"] = IDetector2D::NBINS;
    result["radians"] = IDetector2D::RADIANS;
    result["rad"] = IDetector2D::RADIANS;
    result["degrees"] = IDetector2D::DEGREES;
    result["deg"] = IDetector2D::DEGREES;
    result["mm"] = IDetector2D::MM;
    result["qyqz"] = IDetector2D::QYQZ;
    return result;
}

std::map<IDetector2D::EAxesUnits, std::string> init_units_to_name_map()
{
    std::map<IDetector2D::EAxesUnits, std::string> result;
    result[IDetector2D::NBINS] = "nbins";
    result[IDetector2D::RADIANS] = "rad";
    result[IDetector2D::DEGREES] = "deg";
    result[IDetector2D::MM] = "mm";
    result[IDetector2D::QYQZ] = "qyqz";
    result[IDetector2D::DEFAULT] = "";
    return result;
}

}

bool DetectorFunctions::hasSameDimensions(const IDetector2D &detector,
                                          const OutputData<double> &data)
{
    if (data.getRank() != detector.getDimension())
        return false;

    for (size_t i = 0; i < detector.getDimension(); ++i)
        if(data.getAxis(i).size() != detector.getAxis(i).size())
            return false;

    return true;
}

std::string DetectorFunctions::axesToString(const IDetector2D &detector)
{
    std::ostringstream result;

    result << "(";
    for (size_t i = 0; i < detector.getDimension(); ++i) {
        result << detector.getAxis(i).size();
        if(i!=detector.getDimension()-1)
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
    const OutputData<double> &data, bool put_masked_areas_to_zero, IDetector2D::EAxesUnits units)
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

IDetector2D::EAxesUnits DetectorFunctions::detectorUnits(const std::string& unitName)
{
    if(unitName.empty())
        return IDetector2D::DEFAULT;

    static auto units_map = init_name_to_units_map();

    std::string lowercase = StringUtils::to_lower(unitName);
    auto it = units_map.find(lowercase);
    if(it == units_map.end())
        throw std::runtime_error("DetectorFunctions::detectorUnits() -> Error. No such "
                                 "detector unit '"+unitName+"'");

    return it->second;
}

std::string DetectorFunctions::detectorUnitsName(IDetector2D::EAxesUnits units)
{
    static auto units_map = init_units_to_name_map();
    auto it = units_map.find(units);
    if(it == units_map.end())
        throw std::runtime_error("DetectorFunctions::detectorUnitsName() -> Error. No such "
                                 "detector unit '"+std::to_string(units)+"'");
    return it->second;
}
