#include "VariableBinAxis.h"
#include "Exceptions.h"
#include <iostream>
#include <algorithm>
#include <iomanip>


VariableBinAxis::VariableBinAxis(std::string name, size_t nbins, const std::vector<double> &bin_boundaries)
    : IAxis(name)
    , m_nbins(nbins)
    , m_bin_boundaries(bin_boundaries)
{
    if(m_nbins != m_bin_boundaries.size()-1)
        throw Exceptions::LogicErrorException("VariableBinAxis::VariableBinAxis() -> Error! The size of value_vector should be of size [nbins+1].");

    // checking that values are sorted
    std::vector<double> sorted = bin_boundaries;
    std::sort( sorted.begin(), sorted.end());
    for(size_t i=0; i<m_bin_boundaries.size(); ++i) {
        if(sorted[i] != m_bin_boundaries[i])
            throw Exceptions::LogicErrorException("VariableBinAxis::VariableBinAxis() -> Error. Array with bin edges is not sorted.");
    }

    std::vector<double> vec = bin_boundaries;
    vec.erase(std::unique(vec.begin(), vec.end()),vec.end());

    if(vec.size() != bin_boundaries.size())
       throw Exceptions::LogicErrorException("VariableBinAxis::VariableBinAxis() -> Error. Array with bin edges contains repeating values.");
}


VariableBinAxis::VariableBinAxis(std::string name)
    : IAxis(name)
    , m_nbins(0)
{

}


VariableBinAxis *VariableBinAxis::clone() const
{
    VariableBinAxis *result = new VariableBinAxis(getName(), m_nbins, m_bin_boundaries);
    return result;
}


size_t VariableBinAxis::getSize() const
{
    return m_nbins;
}


double VariableBinAxis::operator[](size_t index) const
{
    return getBin(index).getMidPoint();
}


Bin1D VariableBinAxis::getBin(size_t index) const
{
    if(index >= m_nbins)
        throw Exceptions::OutOfBoundsException("VariableBinAxis::getBin() -> Error. Wrong index.");

    Bin1D result = { m_bin_boundaries[index], m_bin_boundaries[index+1] };
    return result;
}


double VariableBinAxis::getMin() const
{
    return m_bin_boundaries.front();
}


double VariableBinAxis::getMax() const
{
    return m_bin_boundaries.back();
}


size_t VariableBinAxis::findClosestIndex(double value) const
{
    if(m_bin_boundaries.size()<2) {
        throw ClassInitializationException("VariableBinAxis::findClosestIndex() -> Error! VariableBinAxis not  correctly initialized");
    }
    if (value < getMin() || value >= getMax()) {
        std::ostringstream ostr;
        ostr << "VariableBinAxis::findClosestIndex() -> Error! Given value not in any bin. ";
        ostr << "value:" << value << " name:" << getName() << " min:" << getMin() << " max:" << getMax();
        throw OutOfBoundsException(ostr.str());
    }
    std::vector<double>::const_iterator top_limit = std::lower_bound(m_bin_boundaries.begin(), m_bin_boundaries.end(), value);
    if( *top_limit != value ) --top_limit;
    size_t nbin = top_limit - m_bin_boundaries.begin();
    return nbin;
}

std::vector<double> VariableBinAxis::getBinCenters() const
{
    std::vector<double> result;
    result.resize(getSize(), 0.0);
    for(size_t i=0; i<getSize(); ++i) {
        result[i] = getBin(i).getMidPoint();
    }
    return result;
}

std::vector<double> VariableBinAxis::getBinBoundaries() const
{
    return m_bin_boundaries;
}


void VariableBinAxis::print(std::ostream& ostr) const
{
    ostr << "VariableBinAxis(\"" << m_name << "\", " << getSize() << ", [";
    for(size_t i=0; i<m_bin_boundaries.size(); ++i) {
        ostr << std::setprecision(std::numeric_limits<double>::digits10+2) << m_bin_boundaries[i];
        if(i!=m_bin_boundaries.size()-1) ostr << ", ";
    }
    ostr << "])";
}


bool VariableBinAxis::equals(const IAxis& other) const
{
    if (!IAxis::equals(other)) return false;
    if (const VariableBinAxis *p_other_cast = dynamic_cast<const VariableBinAxis *>(&other)) {
        if (getSize() != p_other_cast->getSize()) return false;
        for(size_t i=0; i<m_bin_boundaries.size(); ++i) {
            if( std::abs(m_bin_boundaries[i] - p_other_cast->m_bin_boundaries[i]) > Numeric::double_epsilon ) {
                return false;
            }
        }
        return true;
    }
    return false;
}






