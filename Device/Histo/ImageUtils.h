//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Device/Histo/ImageUtils.h
//! @brief     PyObvject forward declaration.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_DEVICE_INSTRUMENT_SPECTRUMUTILS_H
#define BORNAGAIN_DEVICE_INSTRUMENT_SPECTRUMUTILS_H

#include "Device/Histo/Histogram2D.h"
#include <string>
#include <vector>

class Histogram2D;

//! Collection of utils for 1D and 2D image processing (background, peaks, ets).

namespace ImageUtils {

//! Returns vector of peak center coordinates, for peaks in given histogram.

std::vector<std::pair<double, double>> FindPeaks(const Histogram2D& hist, double sigma = 2,
                                                 const std::string& option = {},
                                                 double threshold = 0.05);
}

#endif // BORNAGAIN_DEVICE_INSTRUMENT_SPECTRUMUTILS_H
