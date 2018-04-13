// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/DetectorFunctions.h
//! @brief     Defines namespace DetectorFunctions.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef DETECTORFUNCTIONS_H
#define DETECTORFUNCTIONS_H

#include "WinDllMacros.h"
#include "IDetector.h"
#include <string>
#include <memory>
#include <functional>
template<class T> class OutputData;
class Instrument;
class IDetector;
class SimulationAreaIterator;


//! Contains set of detector-related convenience functions.
//! @ingroup simulation

namespace DetectorFunctions {

//! Returns true if the data has same axes size (nx,ny) with the detector.
BA_CORE_API_ bool hasSameDimensions(const IDetector& detector, const OutputData<double>& data);

// TODO replace two functions below with the template function after change of
// OutputData::getAxis signature

//! Returns string representation of axes dimension in the form "(nx,ny)"
BA_CORE_API_ std::string axesToString(const IDetector& detector);

//! Returns string representation of axes dimension in the form "(nx,ny)"
BA_CORE_API_ std::string axesToString(const OutputData<double>& data);

//! Creates real data containing original user data clipped to the ROI area of the detector.
//! If put_masked_areas_to_zero==true:
//!     resulting data will have 0.0 in all masked areas
//! If put_masked_areas_to_zero==false:
//!     resulting data will be only cropped, masked areas will still contain intensities
//! TODO: what users will like more (this appears on FitSuitePlotObserver)?

BA_CORE_API_ std::unique_ptr<OutputData<double>> createDataSet(const Instrument& instrument,
    const OutputData<double> &data, bool put_masked_areas_to_zero=true,
    AxesUnits units=AxesUnits::DEFAULT);

//! Iterates through detector area intended for simulation (over unmasked areas in the ROI).
//! @param visit_masks: Will visit masked areas too, if true.
BA_CORE_API_ void iterate(const IDetector& detector,
                          std::function<void(const SimulationAreaIterator&)> fun,
                          bool visit_masks=false);

}

#endif // DETECTORFUNCTIONS_H

