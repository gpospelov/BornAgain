#include "AngleBinAxis.h"
#include "Exceptions.h"


AngleBinAxis::AngleBinAxis(std::string name, size_t nbins, double start, double end)
    : IAxis(name)
    , m_nbins(nbins)
    , m_start(start)
    , m_end(end)
{
    m_start_sin = std::sin(m_start);
    m_end_sin = std::sin(m_end);
    m_step_sin = (m_end_sin-m_start_sin)/m_nbins;
}


AngleBinAxis *AngleBinAxis::clone() const
{
    AngleBinAxis *result = new AngleBinAxis(getName(), m_nbins, m_start, m_end);
    return result;
}


size_t AngleBinAxis::getSize() const
{
    return m_nbins;
}


double AngleBinAxis::operator[](size_t index) const
{
    if(index >= m_nbins)
        throw Exceptions::OutOfBoundsException("FixedBinAxis::operator[] -> Error. Wrong index.");

    return std::asin(m_start_sin + (index + 0.5)*m_step_sin);
}


Bin1D AngleBinAxis::getBin(size_t index) const
{
    if(index >= m_nbins)
        throw Exceptions::OutOfBoundsException("FixedBinAxis::getBin() -> Error. Wrong index.");

//    Bin1D result = { std::asin(m_start_sin + m_step_sin*index), std::asin(m_start_sin + m_step_sin*(index+1)) };
    double x = std::asin(m_start_sin + (index + 0.5)*m_step_sin);
    Bin1D result = { x, x };
    return result;
}


double AngleBinAxis::getMin() const
{
    return m_start;
}


double AngleBinAxis::getMax() const
{
    return m_end;
}


size_t AngleBinAxis::findClosestIndex(double value) const
{
    if (value < getMin() || value >= getMax()) {
        std::ostringstream ostr;
        ostr << "AngleBinAxis::findClosestIndex() -> Error! Given value not in any bin. ";
        ostr << "value:" << value << " name:" << getName() << " min:" << getMin() << " max:" << getMax();
        throw OutOfBoundsException(ostr.str());
    }
    double value_sin = std::sin(value);
    return int( (value_sin-m_start_sin)/m_step_sin);
}


void AngleBinAxis::print(std::ostream& ostr) const
{
    ostr << "AngleBinAxis '" << m_name << "'" << getSize() << " " << getMin() << " " << getMax();
}


bool AngleBinAxis::equals(const IAxis& other) const
{
    if (!IAxis::equals(other)) return false;
    if (const AngleBinAxis *otherAxis = dynamic_cast<const AngleBinAxis *>(&other)) {
        if (getSize() != otherAxis->getSize()) return false;
        if ( std::abs(getMin() - otherAxis->getMin()) > Numeric::double_epsilon) return false;
        if ( std::abs(getMax() - otherAxis->getMax()) > Numeric::double_epsilon) return false;
        return true;
    }
    return false;
}


AngleBinAxis *AngleBinAxis::createIsGISAXSAxis(std::string name, size_t nbins, double start, double end)
{
    double start_sin = std::sin(start);
    double end_sin = std::sin(end);
    double step = (end_sin-start_sin)/(nbins-1);
    return new AngleBinAxis(name, nbins, std::asin(start_sin - step/2.), std::asin(end_sin + step/2.));
}


