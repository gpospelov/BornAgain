#include "AsymmetricBinAxis.h"
#include "Exceptions.h"
#include <iostream>
#include <algorithm>


AsymmetricBinAxis::AsymmetricBinAxis(std::string name, size_t nbins, const std::vector<double> &bin_centers)
    : IAxis(name)
    , m_nbins(nbins)
    , m_bin_centers(bin_centers)
{
    if(m_nbins != m_bin_centers.size())
        throw Exceptions::LogicErrorException("AsymmetricBinAxis::AsymmetricBinAxis() -> Error. The size of bin_centers vector should be of size [nbins].");

    // checking that values are sorted
    std::vector<double> vec1 = bin_centers;
    std::sort( vec1.begin(), vec1.end());
    for(size_t i=0; i<bin_centers.size(); ++i) {
        if(vec1[i] != bin_centers[i])
            throw Exceptions::LogicErrorException("AsymmetricBinAxis::AsymmetricBinAxis() -> Error. Array with bin centers is not sorted.");
    }

    std::vector<double> vec2 = bin_centers;
    vec2.erase(std::unique(vec2.begin(), vec2.end()), vec2.end());
    if(vec2.size() != bin_centers.size())
       throw Exceptions::LogicErrorException("AsymmetricBinAxis::AsymmetricBinAxis() -> Error. Array with bin centers contains repeating values.");

    init_bin_edges();
}


AsymmetricBinAxis *AsymmetricBinAxis::clone() const
{
    AsymmetricBinAxis *result = new AsymmetricBinAxis(getName(), m_nbins, m_bin_centers);
    return result;
}


AsymmetricBinAxis *AsymmetricBinAxis::createDoubleBinSize() const
{
    throw Exceptions::NotImplementedException("AsymmetricBinAxis::createDoubleBinSize() -> Not implemented");
}


size_t AsymmetricBinAxis::getSize() const
{
    return m_nbins;
}


double AsymmetricBinAxis::operator[](size_t index) const
{
    if(index >= m_nbins)
        throw Exceptions::OutOfBoundsException("AsymmetricBinAxis::operator[] -> Error. Wrong index.");

    return m_bin_centers[index];
}


Bin1D AsymmetricBinAxis::getBin(size_t index) const
{
    if(index >= m_nbins)
        throw Exceptions::OutOfBoundsException("AsymmetricBinAxis::getBin() -> Error. Wrong index.");

    double left = m_bin_edges[index];
    double center = m_bin_centers[index];
    double right = m_bin_edges[index+1];
    double bin_size_2 = std::min( std::abs(center - left), std::abs(center - right));
    std::cout << "AAA left:" << left << " center:" << center << " right:" << right << " bin_size_2:" << bin_size_2 << std::endl;
    Bin1D result = { center - bin_size_2, center + bin_size_2 };
    return result;
}


double AsymmetricBinAxis::getMin() const
{
    return m_bin_edges.front();
}


double AsymmetricBinAxis::getMax() const
{
    return m_bin_edges.back();
}


size_t AsymmetricBinAxis::findClosestIndex(double value) const
{
    if(m_bin_edges.size()<2) {
        throw ClassInitializationException("AsymmetricBinAxis::findClosestIndex() -> Error! AsymmetricBinAxis not correctly initialized");
    }
    if (value < getMin() || value >= getMax()) {
        std::ostringstream ostr;
        ostr << "AsymmetricBinAxis::findClosestIndex() -> Error! Given value not in any bin. ";
        ostr << "value:" << value << " name:" << getName() << " min:" << getMin() << " max:" << getMax();
        throw OutOfBoundsException(ostr.str());
    }
    std::vector<double>::const_iterator top_limit = std::lower_bound(m_bin_edges.begin(), m_bin_edges.end(), value);
    if( *top_limit != value ) --top_limit;
    size_t nbin = top_limit - m_bin_edges.begin();
    return nbin;

}


void AsymmetricBinAxis::init_bin_edges()
{
    m_bin_edges.clear();
    double bin_size(0);
    for(size_t i=0; i<m_bin_centers.size(); ++i) {
        if(m_bin_centers.size() > 1) {
            if(i == 0) {
                bin_size = m_bin_centers[1] - m_bin_centers[0];
            } else if (i == m_bin_centers.size()-1) {
                bin_size = m_bin_centers[m_bin_centers.size()-1] - m_bin_centers[m_bin_centers.size()-2];
            } else {
                bin_size = m_bin_centers[i] - m_bin_centers[i-1];
            }
        }
        if(bin_size == 0) bin_size = 1.0;
        double xleft = m_bin_centers[i] - bin_size/2.;
        m_bin_edges.push_back(xleft);
        std::cout << "XXX  i:" << i << " bin_size:" << bin_size << " bin_edge:" << m_bin_edges[i] << std::endl;
    }
    m_bin_edges.push_back(m_bin_centers.back() + bin_size/2.);
    std::cout << "      XXX last bin, bin_size:" << bin_size << " bin_edge:" << m_bin_edges.back() << std::endl;

    for(size_t i=0; i<m_bin_edges.size(); ++i) {
        std::cout << "   >>> " << i << " " << m_bin_edges[i] << std::endl;
    }
}



void AsymmetricBinAxis::print(std::ostream& ostr) const
{
    ostr << "AsymmetricBinAxis '" << m_name << "'" << getSize() << " " << getMin() << " " << getMax();
}


bool AsymmetricBinAxis::equals(const IAxis& other) const
{
    if (!IAxis::equals(other)) return false;
    if (const AsymmetricBinAxis *p_other_cast = dynamic_cast<const AsymmetricBinAxis *>(&other)) {
        if (getSize() != p_other_cast->getSize()) return false;
        for(size_t i=0; i<m_bin_centers.size(); ++i) {
            if( std::abs(m_bin_centers[i] - p_other_cast->m_bin_centers[i]) > Numeric::double_epsilon ) {
                return false;
            }
        }
        return true;
    }
    return false;
}





