#include "ConstKBinAxis.h"
#include "Exceptions.h"
#include <iomanip>
#include <iostream>

ConstKBinAxis::ConstKBinAxis(std::string name, size_t nbins, double start, double end)
    : VariableBinAxis(name)
    , m_start(start)
    , m_end(end)
{
    // FIXME How to protect agains angles given in degrees by mistake?
    if(m_start >= m_end)
        throw Exceptions::LogicErrorException("ConstKBinAxis::ConstKBinAxis() -> Error. start >= end is not allowed.");

    m_nbins = nbins;

    double start_sin = std::sin(m_start);
    double end_sin = std::sin(m_end);
    double step = (end_sin-start_sin)/(m_nbins);

    m_bin_boundaries.resize(m_nbins + 1, 0.0);
    for(size_t i=0; i<m_bin_boundaries.size(); ++i) {
        m_bin_boundaries[i] = std::asin(start_sin + step*i);
    }

}

ConstKBinAxis *ConstKBinAxis::clone() const
{
    return new ConstKBinAxis(getName(), m_nbins, m_start, m_end);
}

void ConstKBinAxis::print(std::ostream &ostr) const
{
    ostr << "ConstKBinAxis(\"" << m_name << "\", " << getSize() << ", " << std::setprecision(std::numeric_limits<double>::digits10+2) << getMin() << ", " << getMax() << ")";
}

