#include "ConstKBinAxis.h"
#include "Exceptions.h"
#include <iomanip>
#include <iostream>

ConstKBinAxis::ConstKBinAxis(const std::string &name, size_t nbins, double start, double end)
    : VariableBinAxis(name, nbins)
    , m_start(start)
    , m_end(end)
{
    if(m_start >= m_end)
        throw Exceptions::LogicErrorException("ConstKBinAxis::ConstKBinAxis() -> Error. start >= end is not allowed.");

    double start_sin = std::sin(m_start);
    double end_sin = std::sin(m_end);
    double step = (end_sin-start_sin)/(m_nbins);

    std::vector<double> bin_boundaries;
    bin_boundaries.resize(m_nbins + 1, 0.0);
    for(size_t i=0; i<bin_boundaries.size(); ++i) {
        bin_boundaries[i] = std::asin(start_sin + step*i);
    }
    setBinBoundaries(bin_boundaries);

}

ConstKBinAxis *ConstKBinAxis::clone() const
{
    return new ConstKBinAxis(getName(), m_nbins, m_start, m_end);
}


bool ConstKBinAxis::equals(const IAxis& other) const
{
    if (!IAxis::equals(other)) return false;
    if (const ConstKBinAxis *otherAxis = dynamic_cast<const ConstKBinAxis *>(&other)) {
        if (getSize() != otherAxis->getSize()) return false;
        if ( std::abs(m_start - otherAxis->m_start) > Numeric::double_epsilon) return false;
        if ( std::abs(m_end - otherAxis->m_end) > Numeric::double_epsilon) return false;
        return true;
    }
    return false;
}


void ConstKBinAxis::print(std::ostream &ostr) const
{
    ostr << "ConstKBinAxis(\"" << m_name << "\", " << getSize() << ", " << std::setprecision(std::numeric_limits<double>::digits10+2) << m_start << ", " << m_end << ")";
}

