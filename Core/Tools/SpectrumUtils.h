// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Tools/SpectrumUtils.h
//! @brief     PyObvject forward declaration.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef SPECTRUMUTILS_H
#define SPECTRUMUTILS_H

#include "Core/Instrument/Histogram2D.h"
#include "Wrap/WinDllMacros.h"
#include <string>
#include <vector>

class Histogram2D;

//! Collection of utils for 1D and 2D spectrum processing (background, peaks, ets).

namespace SpectrumUtils
{

BA_CORE_API_ std::vector<std::pair<double, double>> FindPeaks(const Histogram2D& hist,
                                                              double sigma = 2,
                                                              const std::string& option = {},
                                                              double threshold = 0.05);
}

#endif // SPECTRUMUTILS_H
