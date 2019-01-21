#ifndef TSPECTRUM_H
#define TSPECTRUM_H

#include <vector>
#include <string>
#include <memory>

//! Adaptation of TSpectrum and TSpectrum2 classes from root.cern.ch to work standalone.

namespace tspectrum {

class Spectrum2D {
public:
    explicit Spectrum2D(int max_peaks=100);
    ~Spectrum2D();

    //! Finds peaks in 2D array.
    //! @param: data sigma of searched peaks
    //! @param: "nobackground" to not remove the background before peak search,
    //!          "nomarkov"
    //! @param: threshold peaks with amplitude less than threshold*highest_peak are discarded.
    //! @returns: Coordinates of peaks as vector of pair(xrow, xcol), where xrow, xcol represent
    //! precise position inside of bin
    std::vector<std::pair<double, double>> find_peaks(const std::vector<std::vector<double>>& data,
                                                      double sigma=2,
                                                      const std::string& option={},
                                                      double threshold=0.05);

private:
    std::unique_ptr<class Spectrum2DImpl> m_impl;
};

}

#endif
