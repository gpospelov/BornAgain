// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/src/AxisDouble.cpp
//! @brief     Implements class AxisDouble.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "AxisDouble.h"
#include "AxisBin.h"
#include "Numeric.h"
#include "Exceptions.h"

#include <algorithm>

AxisDouble::AxisDouble(std::string name)
: IAxis(name)
, m_bin_size(0)
{
}

AxisDouble::AxisDouble(std::string name, size_t size, double start, double end)
: IAxis(name)
, m_bin_size(0)
{
    initElements(size, start, end);
}

AxisDouble::AxisDouble(const AxisBin& source)
: IAxis(source.getName())
, m_bin_size(0)
{
    for (size_t i=0; i<source.getSize(); ++i) {
        m_sample_vector.push_back(source[i]);
    }
}

AxisDouble *AxisDouble::clone() const
{
    AxisDouble *p_clone = new AxisDouble(getName());
    p_clone->m_sample_vector = this->m_sample_vector;
    p_clone->m_bin_size = this->m_bin_size;
    return p_clone;
}

AxisDouble *AxisDouble::createDoubleBinSize() const
{
    if (getSize() < 2) {
        return clone();
    }
    AxisDouble *p_result = new AxisDouble(getName());
    for (size_t source_index=0; source_index<getSize(); source_index+=2)
    {
        double value;
        if (source_index==getSize()-1) {
            value = (3.0*m_sample_vector.at(source_index) - m_sample_vector.at(source_index-1))/2.0;
        }
        else {
            value =  (m_sample_vector.at(source_index) + m_sample_vector.at(source_index+1))/2.0;
        }
        p_result->push_back(value);
    }
    p_result->m_bin_size = m_bin_size*2.0;
    return p_result;
}

Bin1D AxisDouble::getBin(size_t index) const
{
    Bin1D result = { m_sample_vector[index] - m_bin_size/2.0, m_sample_vector[index] + m_bin_size/2.0 };
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
    if(m_sample_vector.size()<2) return 0;
    std::vector<double>::const_iterator before = std::lower_bound(m_sample_vector.begin(), m_sample_vector.end(), value);
    if(before == m_sample_vector.end() ) --before;
    if(before == m_sample_vector.begin() ) ++before;
    std::vector<double>::const_iterator after = before;
    --before;
    size_t nbin(0);
    ( *after-value) < (value - *before) ? nbin = std::distance(m_sample_vector.begin(), after) : nbin = std::distance(m_sample_vector.begin(), before);
    return nbin;
}

size_t AxisDouble::getLowerBoundIndex(double value) const
{
    if(m_sample_vector.size()<2) return 0;
    std::vector<double>::const_iterator lbound_it = std::lower_bound(m_sample_vector.begin(), m_sample_vector.end(), value);
    if(lbound_it == m_sample_vector.end() ) {
        throw RuntimeErrorException("Given lower bound higher than highest present value");
    }
    return lbound_it - m_sample_vector.begin();
}

size_t AxisDouble::getUpperBoundIndex(double value) const
{
    if(m_sample_vector.size()<2) return 0;
    std::vector<double>::const_iterator lbound_it = std::upper_bound(m_sample_vector.begin(), m_sample_vector.end(), value);
    return (lbound_it - m_sample_vector.begin()) - 1;
}

bool AxisDouble::equals(const IAxis& other) const
{
    if (!IAxis::equals(other)) return false;
    if (const AxisDouble *p_other_cast = dynamic_cast<const AxisDouble *>(&other)) {
        if (getSize() != p_other_cast->getSize()) return false;
        for(size_t i=0; i<m_sample_vector.size(); ++i) {
            if( std::abs(m_sample_vector[i] - p_other_cast->m_sample_vector[i]) > Numeric::double_epsilon ) {
                return false;
            }
        }
        return true;
    }
    return false;
}


