#include "AxisDouble.h"
#include "Numeric.h"
#include "Exceptions.h"

#include <cmath>

AxisDouble::AxisDouble(std::string name)
: m_name(name)
{
}

AxisDouble::AxisDouble(std::string name, size_t size, double start, double end)
: m_name(name)
{
    initElements(size, start, end);
}

AxisDouble* AxisDouble::clone() const
{
    AxisDouble *p_clone = new AxisDouble(getName());
    p_clone->m_value_vector = this->m_value_vector;
    return p_clone;
}

AxisDouble AxisDouble::createDoubleBinSize() const
{
    if (getSize() < 2) {
        return *this;
    }
    AxisDouble result(getName());
    for (size_t source_index=0; source_index<getSize(); source_index+=2)
    {
        double value;
        if (source_index==getSize()-1) {
            value = (3.0*m_value_vector.at(source_index) - m_value_vector.at(source_index-1))/2.0;
        }
        else {
            value =  (m_value_vector.at(source_index) + m_value_vector.at(source_index+1))/2.0;
        }
        result.push_back(value);
    }
    return result;
}

void AxisDouble::initElements(size_t size, double start, double end)
{
    double step = size>1 ? (end - start)/(size-1) : end;
    for (size_t i=0; i<size; ++i)
    {
        push_back(start + step*(int)i);
    }
}

size_t AxisDouble::findClosestIndex(double value) const
{
    if(m_value_vector.size()<2) return 0;
    std::vector<double>::const_iterator before = std::lower_bound(m_value_vector.begin(), m_value_vector.end(), value);
    if(before == m_value_vector.end() ) --before;
    if(before == m_value_vector.begin() ) ++before;
    std::vector<double>::const_iterator after = before;
    --before;
    size_t nbin(0);
    ( *after-value) < (value - *before) ? nbin = std::distance(m_value_vector.begin(), after) : nbin = std::distance(m_value_vector.begin(), before);
    return nbin;
}

size_t AxisDouble::getLowerBoundIndex(double value) const
{
    if(m_value_vector.size()<2) return 0;
    std::vector<double>::const_iterator lbound_it = std::lower_bound(m_value_vector.begin(), m_value_vector.end(), value);
    if(lbound_it == m_value_vector.end() ) {
        throw RuntimeErrorException("Given lower bound higher than highest present value");
    }
    return lbound_it - m_value_vector.begin();
}

size_t AxisDouble::getUpperBoundIndex(double value) const
{
    if(m_value_vector.size()<2) return 0;
    std::vector<double>::const_iterator lbound_it = std::upper_bound(m_value_vector.begin(), m_value_vector.end(), value);
    return (lbound_it - m_value_vector.begin()) - 1;
}

bool HaveSameNameAndShape(const AxisDouble& left, const AxisDouble& right)
{
    if(left.getSize() != right.getSize()) return false;
    if(left.getName() != right.getName()) return false;
    for(size_t i=0; i<left.getSize(); ++i) if( std::abs(left[i] - right[i]) > Numeric::double_epsilon)  return false;
    return true;
}
