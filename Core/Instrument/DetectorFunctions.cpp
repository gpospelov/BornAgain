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
#include <sstream>

bool DetectorFunctions::hasSameDimensions(const IDetector2D &detector,
                                          const OutputData<double> &data)
{
    if (data.getRank() != detector.getDimension())
        return false;

    for (size_t i = 0; i < detector.getDimension(); ++i)
        if(data.getAxis(i).getSize() != detector.getAxis(i).getSize())
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
        result << data.getAxis(i).getSize();
        if(i!=data.getRank()-1)
            result << ",";
    }
    result << ")";

    return result.str();
}
