#include "IDetector.h"
#include "OutputData.h"

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
    if (index < dimension())
        return *m_axes[index];
    throw std::runtime_error("Error in IDetector::getAxis: not so many axes in this detector.");
}

size_t IDetector::getAxisBinIndex(size_t index, size_t selected_axis) const
{
    size_t remainder(index);
    for (size_t i=0; i<dimension(); ++i)
    {
        size_t i_axis = dimension()-1-i;
        size_t result = remainder % m_axes[i_axis]->size();
        if(selected_axis == i_axis ) return result;
        remainder /= m_axes[i_axis]->size();
    }
    throw std::runtime_error("IDetector::getAxisBinIndex() -> "
                             "Error! No axis with given number");
}

IAxis* IDetector::createAxis(size_t index, size_t n_bins, double min, double max) const
{
    if (max <= min)
        throw Exceptions::LogicErrorException(
            "IDetector::createAxis() -> Error! max <= min");
    if (n_bins == 0)
        throw Exceptions::LogicErrorException(
            "IDetector::createAxis() -> Error! Number n_bins can't be zero.");
    return new FixedBinAxis(getAxisName(index), n_bins, min, max);
}

size_t IDetector::getTotalSize() const
{
    const size_t dim = dimension();
    if (dim == 0)
        return 0;
    size_t result = 1;
    for (size_t i_axis = 0; i_axis < dim; ++i_axis) {
        result *= m_axes[i_axis]->size();
    }
    return result;
}

void IDetector::setAnalyzerProperties(const kvector_t direction, double efficiency,
                                        double total_transmission)
{
    m_detection_properties.setAnalyzerProperties(direction, efficiency, total_transmission);
}

void IDetector::initOutputData(OutputData<double> &data) const {
  data.clear();
  for (size_t i = 0; i < dimension(); ++i)
      data.addAxis(getAxis(i));
  data.setAllTo(0.);
}

void IDetector::checkAxesUnits(AxesUnits units) const
{
    if(units == AxesUnits::DEFAULT)
        return;

    auto validUnits = getValidAxesUnits();
    if(std::find(validUnits.begin(), validUnits.end(), units) == validUnits.end()) {
        std::ostringstream message;
        message << "IDetector::createDetectorMap() -> Error. Unknown axes unit " << static_cast<int>(units) << "\n";
        message << "Available units for this detector type \n";
        for(size_t i=0; i<validUnits.size(); ++i)
        for(auto unit : validUnits)
            message << static_cast<int>(unit) << " ";
        message << "\n";
        throw std::runtime_error(message.str());
    }
}

std::vector<const INode*> IDetector::getChildren() const
{
    return std::vector<const INode*>() << &m_detection_properties;
}

