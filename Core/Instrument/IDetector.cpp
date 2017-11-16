#include "IDetector.h"

IDetector::IDetector()
{
    registerChild(&m_detection_properties);
}

IDetector::IDetector(const IDetector& other)
    : m_axes(other.m_axes)
    , m_detection_properties(other.m_detection_properties)
{
    setName(other.getName());
    registerChild(&m_detection_properties);
}

void IDetector::addAxis(const IAxis& axis)
{
    m_axes.push_back(axis.clone());
}

const IAxis& IDetector::getAxis(size_t index) const
{
    if (isCorrectAxisIndex(index))
        return *m_axes[index];
    throw std::runtime_error("Error in IDetector::getAxis: not so many axes in this detector.");
}

size_t IDetector::getAxisBinIndex(size_t index, size_t selected_axis) const
{
    size_t remainder(index);
    for (size_t i=0; i<getDimension(); ++i)
    {
        size_t i_axis = getDimension()-1-i;
        size_t result = remainder % m_axes[i_axis]->size();
        if(selected_axis == i_axis ) return result;
        remainder /= m_axes[i_axis]->size();
    }
    throw std::runtime_error("IDetector::getAxisBinIndex() -> "
                             "Error! No axis with given number");
}

size_t IDetector::getTotalSize() const
{
    const size_t dimension = getDimension();
    if (dimension == 0)
        return 0;
    size_t result = 1;
    for (size_t i_axis = 0; i_axis < dimension; ++i_axis) {
        result *= m_axes[i_axis]->size();
    }
    return result;
}

void IDetector::setAnalyzerProperties(const kvector_t direction, double efficiency,
                                        double total_transmission)
{
    m_detection_properties.setAnalyzerProperties(direction, efficiency, total_transmission);
}

std::vector<const INode*> IDetector::getChildren() const
{
    return std::vector<const INode*>() << &m_detection_properties;
}

