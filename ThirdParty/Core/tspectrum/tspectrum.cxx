#include "tspectrum.h"
#include "TSpectrum2.h"

namespace tspectrum
{

class Spectrum2DImpl
{
public:
    Spectrum2DImpl(int max_peaks) : m_max_peaks(max_peaks) {}
    int m_max_peaks;
};

Spectrum2D::Spectrum2D(int max_peaks) : m_impl(new Spectrum2DImpl(max_peaks))
{
}

Spectrum2D::~Spectrum2D() = default;

std::vector<std::pair<double, double>>
tspectrum::Spectrum2D::find_peaks(const std::vector<std::vector<double>>& data, double sigma,
                                  const std::string& option, double threshold)
{
    TSpectrum2 spec(m_impl->m_max_peaks);
    size_t npeaks = static_cast<size_t>(spec.Search(data, sigma, option, threshold));

    auto xpos = spec.GetPositionX();
    auto ypos = spec.GetPositionY();

    std::vector<std::pair<double, double>> result;
    for (size_t i = 0; i < npeaks; ++i)
        result.push_back(std::make_pair(xpos[i], ypos[i]));

    return result;
}
}
