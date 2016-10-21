// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/DetectorFunctions.h
//! @brief     Defines namespace DetectorFunctions.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef DETECTORFUNCTIONS_H
#define DETECTORFUNCTIONS_H

#include "WinDllMacros.h"
#include <string>
template<class T> class OutputData;
class IDetector2D;


//! Contains set of detector-related convenience functions.
//! @ingroup simulation

namespace DetectorFunctions {

//! Returns true if the data has same axes size (nx,ny) with the detector.
bool hasSameDimensions(const IDetector2D& detector, const OutputData<double>& data);

// TODO replace two functions below with the template function after change of
// OutputData::getAxis signature

//! Returns string representation of axes dimension in the form "(nx,ny)"
std::string axesToString(const IDetector2D& detector);

//! Returns string representation of axes dimension in the form "(nx,ny)"
std::string axesToString(const OutputData<double>& data);

}

#endif

