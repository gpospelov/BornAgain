// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Device/Detector/DetectorFunctions.h
//! @brief     Defines namespace DetectorFunctions.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_DETECTOR_DETECTORFUNCTIONS_H
#define BORNAGAIN_CORE_DETECTOR_DETECTORFUNCTIONS_H

#include "Device/Detector/IDetector.h"
#include <functional>
#include <memory>
#include <string>
template <class T> class OutputData;
class Instrument;
class IDetector;
class SimulationAreaIterator;

//! Contains set of detector-related convenience functions.
//! @ingroup detector

namespace DetectorFunctions
{

//! Returns true if the data has same axes size (nx,ny) with the detector.
bool hasSameDimensions(const IDetector& detector, const OutputData<double>& data);

} // namespace DetectorFunctions

#endif // BORNAGAIN_CORE_DETECTOR_DETECTORFUNCTIONS_H
