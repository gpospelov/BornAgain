//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Device/Histo/ImageUtils.cpp
//! @brief     PyObvject forward declaration.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Device/Histo/ImageUtils.h"
#include <cmath>
#include <tspectrum.h> // third-party code, extracted from CERN ROOT (class TSpectrum2)

std::vector<std::pair<double, double>> ImageUtils::FindPeaks(const Histogram2D& hist,
                                                                double sigma,
                                                                const std::string& option,
                                                                double threshold) {
    std::unique_ptr<OutputData<double>> data(hist.createOutputData());
    std::vector<std::vector<double>> arr = ArrayUtils::createVector2D(*data);
    tspectrum::Spectrum2D spec;
    auto peaks = spec.find_peaks(arr, sigma, option, threshold);

    // coordinates of peaks in histogram axes units
    std::vector<std::pair<double, double>> result;

    for (const auto& p : peaks) {
        double row_value = p.first;
        double col_value = p.second;

        size_t xaxis_index = static_cast<size_t>(col_value);
        size_t yaxis_index = hist.yAxis().size() - 1 - static_cast<size_t>(row_value);

        Bin1D xbin = hist.xAxis().bin(xaxis_index);
        Bin1D ybin = hist.yAxis().bin(yaxis_index);

        double dx = col_value - static_cast<size_t>(col_value);
        double dy = -1.0 * (row_value - static_cast<size_t>(row_value));

        double x = xbin.center() + xbin.binSize() * dx;
        double y = ybin.center() + ybin.binSize() * dy;

        result.push_back(std::make_pair(x, y));
    }
    return result;
}
