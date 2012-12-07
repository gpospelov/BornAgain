#include "BinAxis.h"
#include "Numeric.h"
#include "Exceptions.h"

#include <cmath>

bool operator==(const Bin1D &left, const Bin1D &right)
{
    if (std::abs(left.m_lower - right.m_lower) > Numeric::double_epsilon) return false;
    if (std::abs(left.m_upper - right.m_upper) > Numeric::double_epsilon) return false;
    return true;
}

BinAxis::BinAxis(std::string name)
: m_name(name)
{
}

BinAxis::BinAxis(std::string name, size_t nbr_bins, double start, double end)
: m_name(name)
{
    initBins(nbr_bins, start, end);
}

BinAxis* BinAxis::clone() const
{
    BinAxis *p_clone = new BinAxis(getName());
    p_clone->m_value_vector = this->m_value_vector;
    return p_clone;
}

BinAxis BinAxis::createDoubleBinSize() const
{
    if (getSize() < 2) {
        return *this;
    }
    BinAxis result(getName());
    for (size_t source_index=0; source_index<getSize(); source_index+=2)
    {
        result.push_back(m_value_vector[source_index]);
    }
    result.push_back(m_value_vector[getSize()]);
    return result;
}

size_t BinAxis::getSize() const
{
    if (m_value_vector.size()<2) {
        return 0;
    }
    return m_value_vector.size()-1;
}

Bin1D BinAxis::operator[](size_t index)
{
    Bin1D result = { m_value_vector.at(index), m_value_vector.at(index+1) };
    return result;
}

const Bin1D BinAxis::operator[](size_t index) const
{
    Bin1D result = { m_value_vector.at(index), m_value_vector.at(index+1) };
    return result;
}

void BinAxis::initBins(size_t nbr_bins, double start, double end)
{
    double step = (end - start)/(nbr_bins);
    for (size_t i=0; i<nbr_bins+1; ++i)
    {
        push_back(start + step*(int)i);
    }
}

size_t BinAxis::findMatchingBinIndex(double value) const
{
    if(m_value_vector.size()<2) {
        throw ClassInitializationException("BinAxis not (yet) correctly initialized");
    }
    if (value < getMin() || value > getMax()) {
        throw OutOfBoundsException("Given value not in any bin");
    }
    std::vector<double>::const_iterator top_limit = std::lower_bound(m_value_vector.begin(), m_value_vector.end(), value);
    if(top_limit != m_value_vector.begin() ) --top_limit;
    size_t nbin = top_limit - m_value_vector.begin();
    return nbin;
}

Bin1D BinAxis::findMatchingBin(double value) const
{
    return (*this)[findMatchingBinIndex(value)];
}

bool HaveSameNameAndShape(const BinAxis& left, const BinAxis& right)
{
    if(left.getSize() != right.getSize()) return false;
    if(left.getName() != right.getName()) return false;
    for(size_t i=0; i<left.getSize(); ++i) if( left[i] != right[i])  return false;
    return true;
}
