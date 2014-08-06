#include "IsGisaxsAxis.h"
#include "Units.h"
#include <iomanip>

IsGisaxsAxis::IsGisaxsAxis(std::string name, size_t nbins, double start, double end)
    : VariableBinAxis(name)
    , m_start(start)
    , m_end(end)
{
    // FIXME How to protect agains angles given in degrees by mistake?
    if(m_start >= m_end)
        throw Exceptions::LogicErrorException("ConstKBinAxis::ConstKBinAxis() -> Error. start >= end is not allowed.");

    m_nbins = nbins;

    double start_sin = std::sin(start);
    double end_sin = std::sin(end);
    double step = (end_sin - start_sin)/(m_nbins-1);  // m_nbins-1 is intentionally

    m_bin_centers.resize(m_nbins, 0.0);
    for(size_t i=0; i<m_bin_centers.size(); ++i) {
        m_bin_centers[i] = std::asin(start_sin + i*step);
    }

    m_bin_boundaries.resize(m_nbins + 1, 0.0);
    for(size_t i=0; i<m_bin_boundaries.size(); ++i) {
        m_bin_boundaries[i] = std::asin(start_sin -step/2. + step*i);
    }

//    for(size_t i=0; i<m_centers.size(); ++i) {
//        std::cout << i << " " << Units::rad2deg(m_bin_boundaries[i]) << " " << Units::rad2deg(m_centers[i]) << Units::rad2deg(m_bin_boundaries[i+1]) << std::endl;
//    }

}


IsGisaxsAxis *IsGisaxsAxis::clone() const
{
    return new IsGisaxsAxis(getName(), m_nbins, m_start, m_end);
}

Bin1D IsGisaxsAxis::getBin(size_t index) const
{
    if(index >= m_nbins)
        throw Exceptions::OutOfBoundsException("IsGisaxsAxis::getBin() -> Error. Wrong index.");

    Bin1D result = { m_bin_centers[index], m_bin_centers[index] };
    return result;
}


void IsGisaxsAxis::print(std::ostream &ostr) const
{
    ostr << "IsGisaxsAxis(\"" << m_name << "\", " << getSize() << ", " << std::setprecision(std::numeric_limits<double>::digits10+2) << getMin() << ", " << getMax() << ")";
}
