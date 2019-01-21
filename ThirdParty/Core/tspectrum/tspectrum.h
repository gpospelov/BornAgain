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
    //! @params: data sigma of searched peaks
    //! @params: "nobackground" to not remove the background before peak search,
    //!          "nomarkov"
    //! @params: threshold peaks with amplitude less than threshold*highest_peak are discarded.
    std::vector<std::pair<double, double>> find_peaks(const std::vector<std::vector<double>>& data,
                                                      double sigma=2,
                                                      const std::string& option={},
                                                      double threshold=0.05);

private:
    std::unique_ptr<class Spectrum2DImpl> m_impl;
};

}

#endif
