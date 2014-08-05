#include "FixedBinAxis.h"
#include "Exceptions.h"

FixedBinAxis::FixedBinAxis(std::string name)
    : IAxis(name)
    , m_nbins(0)
    , m_start(0)
    , m_end(0)
{

}

FixedBinAxis::FixedBinAxis(std::string name, size_t nbins, double start, double end)
    : IAxis(name)
    , m_nbins(nbins)
    , m_start(start)
    , m_end(end)
{

}


FixedBinAxis *FixedBinAxis::clone() const
{
    FixedBinAxis *result = new FixedBinAxis(getName(), m_nbins, m_start, m_end);
    return result;
}


size_t FixedBinAxis::getSize() const
{
    return m_nbins;
}


double FixedBinAxis::operator[](size_t index) const
{
    if(index >= m_nbins)
        throw Exceptions::OutOfBoundsException("FixedBinAxis::operator[] -> Error. Wrong index.");

    double step = (m_end - m_start)/m_nbins;
    return m_start + (index + 0.5)*step;
}


Bin1D FixedBinAxis::getBin(size_t index) const
{
    if(index >= m_nbins)
        throw Exceptions::OutOfBoundsException("FixedBinAxis::getBin() -> Error. Wrong index.");

    double step = (m_end - m_start)/m_nbins;
    Bin1D result = { m_start + step*index, m_start + step*(index+1) };
    return result;
}


double FixedBinAxis::getMin() const
{
    return m_start;
}


double FixedBinAxis::getMax() const
{
    return m_end;
}


size_t FixedBinAxis::findClosestIndex(double value) const
{
    if (value < getMin() || value >= getMax()) {
        std::ostringstream ostr;
        ostr << "FixedBinAxis::findClosestIndex() -> Error! Given value not in any bin. ";
        ostr << "value:" << value << " name:" << getName() << " min:" << getMin() << " max:" << getMax();
        throw OutOfBoundsException(ostr.str());
    }

    double step = (m_end - m_start)/m_nbins;
    return int( (value-m_start)/step);
}


void FixedBinAxis::print(std::ostream& ostr) const
{
    ostr << "FixedBinAxis '" << m_name << "'" << getSize() << " " << getMin() << " " << getMax();
}


bool FixedBinAxis::equals(const IAxis& other) const
{
    if (!IAxis::equals(other)) return false;
    if (const FixedBinAxis *otherAxis = dynamic_cast<const FixedBinAxis *>(&other)) {
        if (getSize() != otherAxis->getSize()) return false;
        if ( std::abs(getMin() - otherAxis->getMin()) > Numeric::double_epsilon) return false;
        if ( std::abs(getMax() - otherAxis->getMax()) > Numeric::double_epsilon) return false;
        return true;
    }
    return false;
}



