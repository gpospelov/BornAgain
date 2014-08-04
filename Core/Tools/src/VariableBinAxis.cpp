#include "VariableBinAxis.h"
#include "Exceptions.h"
#include <iostream>
#include <algorithm>

//VariableBinAxis::VariableBinAxis(std::string name)
//    : IAxis(name)
//    , m_nbins(0)
//    , m_start(0)
//    , m_end(0)
//{

//}


VariableBinAxis::VariableBinAxis(std::string name, size_t nbins, const std::vector<double> &value_vector)
    : IAxis(name)
    , m_nbins(nbins)
    , m_value_vector(value_vector)
{
    if(m_nbins != m_value_vector.size()-1)
        throw Exceptions::LogicErrorException("VariableBinAxis::VariableBinAxis() -> Error! The size of value_vector should be of nbins+1.");

    // checking that values are sorted
    std::vector<double> sorted = value_vector;
    std::sort( sorted.begin(), sorted.end());
    for(size_t i=0; i<m_value_vector.size(); ++i) {
        if(sorted[i] != m_value_vector[i])
            throw Exceptions::LogicErrorException("VariableBinAxis::VariableBinAxis() -> Error. Array with bin edges is not sorted.");
    }

    std::vector<double> vec = value_vector;
    vec.erase(std::unique(vec.begin(), vec.end()),vec.end());

    if(vec.size() != value_vector.size())
       throw Exceptions::LogicErrorException("VariableBinAxis::VariableBinAxis() -> Error. Array with bin edges contains repeating values.");
}


VariableBinAxis *VariableBinAxis::clone() const
{
    VariableBinAxis *result = new VariableBinAxis(getName(), m_nbins, m_value_vector);
    return result;
}


VariableBinAxis *VariableBinAxis::createDoubleBinSize() const
{
    throw Exceptions::NotImplementedException("VariableBinAxis::createDoubleBinSize() -> Not implemented");
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

    Bin1D result = { m_value_vector[index], m_value_vector[index+1] };
    return result;
}


double VariableBinAxis::getMin() const
{
    return m_value_vector.front();
}


double VariableBinAxis::getMax() const
{
    return m_value_vector.back();
}


size_t VariableBinAxis::findClosestIndex(double value) const
{
    if(m_value_vector.size()<2) {
        throw ClassInitializationException("AxisBin::findClosestIndex() -> Error! AxisBin not (yet) correctly initialized");
    }
    if (value < getMin() || value >= getMax()) {
        std::ostringstream ostr;
        ostr << "VariableBinAxis::findClosestIndex() -> Error! Given value not in any bin. ";
        ostr << "value:" << value << " name:" << getName() << " min:" << getMin() << " max:" << getMax();
        throw OutOfBoundsException(ostr.str());
    }
    std::vector<double>::const_iterator top_limit = std::lower_bound(m_value_vector.begin(), m_value_vector.end(), value);
    if( *top_limit != value ) --top_limit;
    size_t nbin = top_limit - m_value_vector.begin();
    return nbin;
}


void VariableBinAxis::print(std::ostream& ostr) const
{
    ostr << "VariableBinAxis '" << m_name << "'" << getSize() << " " << getMin() << " " << getMax();
}


bool VariableBinAxis::equals(const IAxis& other) const
{
    if (!IAxis::equals(other)) return false;
    if (const VariableBinAxis *p_other_cast = dynamic_cast<const VariableBinAxis *>(&other)) {
        if (getSize() != p_other_cast->getSize()) return false;
        for(size_t i=0; i<m_value_vector.size(); ++i) {
            if( std::abs(m_value_vector[i] - p_other_cast->m_value_vector[i]) > Numeric::double_epsilon ) {
                return false;
            }
        }
        return true;
    }
    return false;
}




