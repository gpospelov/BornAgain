// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/src/AxisBin.cpp
//! @brief     Implements class AxisBin.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "AxisBin.h"
#include "Numeric.h"
#include "Exceptions.h"
#include <algorithm>

AxisBin::AxisBin(std::string name)
: IAxis(name)
{
}

AxisBin::AxisBin(std::string name, size_t nbr_bins, double start, double end)
: IAxis(name)
{
    initBins(nbr_bins, start, end);
}

AxisBin *AxisBin::clone() const
{
    AxisBin *p_clone = new AxisBin(getName());
    p_clone->m_value_vector = this->m_value_vector;
    return p_clone;
}

AxisBin *AxisBin::createDoubleBinSize() const
{
    if (getSize() < 2) {
        return clone();
    }
    AxisBin *p_result = new AxisBin(getName());
    for (size_t source_index=0; source_index<getSize(); source_index+=2)
    {
        p_result->push_back(m_value_vector[source_index]);
    }
    p_result->push_back(m_value_vector[getSize()]);
    return p_result;
}

size_t AxisBin::getSize() const
{
    if (m_value_vector.size()<2) {
        return 0;
    }
    return m_value_vector.size() - 1;
}

double AxisBin::operator[](size_t index) const
{
    return getBin(index).getMidPoint();
}

Bin1D AxisBin::getBin(size_t index) const
{
    Bin1D result = { m_value_vector[index], m_value_vector[index+1] };
    return result;
}

void AxisBin::initBins(size_t nbr_bins, double start, double end)
{
    double step = (end - start)/(nbr_bins);
    for (size_t i=0; i<nbr_bins+1; ++i)
    {
        push_back(start + step*(int)i);
    }
}

size_t AxisBin::findClosestIndex(double value) const
{
    if(m_value_vector.size()<2) {
        throw ClassInitializationException("AxisBin::findClosestIndex() -> Error! AxisBin not (yet) correctly initialized");
    }
    if (value < getMin() || value > getMax()) {
        std::ostringstream ostr;
        ostr << "AxisBin::findClosestIndex() -> Error! Given value not in any bin. ";
        ostr << "value:" << value << " name:" << getName() << " min:" << getMin() << " max:" << getMax();
        throw OutOfBoundsException(ostr.str());
    }
    std::vector<double>::const_iterator top_limit = std::lower_bound(m_value_vector.begin(), m_value_vector.end(), value);
    if(top_limit != m_value_vector.begin() ) --top_limit;
    size_t nbin = top_limit - m_value_vector.begin();
    return nbin;
}

bool AxisBin::equals(const IAxis& other) const
{
    if (!IAxis::equals(other)) return false;
    if (const AxisBin *p_other_cast = dynamic_cast<const AxisBin *>(&other)) {
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


