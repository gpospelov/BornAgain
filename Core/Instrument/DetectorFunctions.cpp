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
#include <sstream>

bool DetectorFunctions::hasSameDimensions(const IDetector2D &detector,
                                          const OutputData<double> &data)
{
    if (data.getRank() != detector.getDimension())
        return false;

    for (size_t i = 0; i < detector.getDimension(); ++i)
        if(data.getAxis(i)->getSize() != detector.getAxis(i).getSize())
            return false;

    return true;
}

std::string DetectorFunctions::axesToString(const IDetector2D &detector)
{
    std::ostringstream result;

    result << "(";
    for (size_t i = 0; i < detector.getDimension(); ++i) {
        result << detector.getAxis(i).getSize();
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
        result << data.getAxis(i)->getSize();
        if(i!=data.getRank()-1)
            result << ",";
    }
    result << ")";

    return result.str();
}

std::unique_ptr<OutputData<double>> DetectorFunctions::createDataSet(const Instrument &instrument,
    const OutputData<double> &data, bool put_masked_areas_to_zero)
{
    if(!DetectorFunctions::hasSameDimensions(*instrument.getDetector(), data)){
        std::ostringstream message;
        message << "DetectorFunctions::createDataSet -> Error. Axes of the real data doesn't match "
                << "the detector. Real data:" << DetectorFunctions::axesToString(data)
                        << ", detector:"
                        << DetectorFunctions::axesToString(*instrument.getDetector()) << ".";
        throw Exceptions::RuntimeErrorException(message.str());
    }

    std::unique_ptr<OutputData<double>> result(instrument.createDetectorMap());

    if(put_masked_areas_to_zero) {

        SimulationArea area(instrument.getDetector());
        for(SimulationArea::iterator it = area.begin(); it!=area.end(); ++it) {
            (*result)[it.roiIndex()] = data[it.index()];
        }

    } else {
        //    if(const Geometry::Rectangle *roi = regionOfInterest()) {
        //        size_t roi_x = getAxis(BornAgain::X_AXIS_INDEX).findClosestIndex(roi->getXlow());
        //        size_t roi_y = getAxis(BornAgain::Y_AXIS_INDEX).findClosestIndex(roi->getYlow());
        //        size_t index0 = getGlobalIndex(roi_x, roi_y);
        //        const IAxis &yAxisOfDetector = getAxis(BornAgain::Y_AXIS_INDEX);

        //        const IAxis &xAxisOfMap = *detectorMap.getAxis(BornAgain::X_AXIS_INDEX);
        //        const IAxis &yAxisOfMap = *detectorMap.getAxis(BornAgain::Y_AXIS_INDEX);
        //        for(size_t ix=0; ix<xAxisOfMap.getSize(); ++ix) {
        //            for(size_t iy=0; iy<yAxisOfMap.getSize(); ++iy) {
        //                size_t mapIndex = iy + ix*yAxisOfMap.getSize();
        //                size_t globalIndex = index0 + iy + ix*yAxisOfDetector.getSize();
        //                detectorMap[mapIndex] = data[globalIndex];
        //            }
        //        }
        //    }


        throw Exceptions::RuntimeErrorException("DetectorFunctions::createDataSet() -> Error. "
                                                "Not implemented");
    }

    return result;
}
