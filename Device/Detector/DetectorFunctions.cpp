// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Device/Detector/DetectorFunctions.cpp
//! @brief     Implements namespace DetectorFunctions.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Device/Detector/DetectorFunctions.h"
#include "Device/Data/OutputData.h"

bool DetectorFunctions::hasSameDimensions(const IDetector& detector, const OutputData<double>& data)
{
    if (data.getRank() != detector.dimension())
        return false;

    for (size_t i = 0; i < detector.dimension(); ++i)
        if (data.getAxis(i).size() != detector.getAxis(i).size())
            return false;

    return true;
}
