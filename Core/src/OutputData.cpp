#include "OutputData.h"
#include "Exceptions.h"

MultiIndex& MultiIndex::operator++()
{
    if (m_current_position<m_total_size-1)
    {
        ++m_current_position;
    }
    else
    {
        m_end_passed = true;
    }
    return *this;
}

MultiIndex::MultiIndex()
    : m_dimension(0)
    , m_total_size(1)
    , m_current_position(0)
    , m_end_passed(false)
{
}

MultiIndex::~MultiIndex()
{
    clear();
}

std::vector<size_t> MultiIndex::getCoordinate()
{
    updateCurrentCoordinate();
    return m_current_coordinate;
}

size_t MultiIndex::getCoordinate(std::string label)
{
    if (m_label_index_map.count(label) == 0)
    {
        std::string message = "Label not found: " + label;
        throw NullPointerException(message);
    }
    return getCoordinate()[m_label_index_map.find(label)->second];
}

void MultiIndex::reset()
{
    m_current_position = 0;
    m_end_passed = false;
    updateCurrentCoordinate();
}

void MultiIndex::updateCurrentCoordinate()
{
    size_t remainder = m_current_position;
    for (size_t i=0; i<m_dimension; ++i)
    {
        m_current_coordinate[m_dimension-1-i] = remainder % m_axis_sizes[m_dimension-1-i];
        remainder /= m_axis_sizes[m_dimension-1-i];
    }
}

void MultiIndex::updateCurrentPosition()
{
    m_end_passed = false;
    m_current_position = 0;
    for (size_t i=0; i<m_dimension; ++i)
    {
        m_current_position += m_current_coordinate[i]*m_steps[i];
    }
}

void MultiIndex::setCoordinate(std::string label, size_t value)
{
    if (m_label_index_map.count(label) == 0) return;
    size_t index = m_label_index_map[label];
    if (value >= m_axis_sizes[index])
    {
        throw OutOfBoundsException("Coordinate value out of bounds!");
    }
    m_current_coordinate[index] = value;
    updateCurrentPosition();
}

void MultiIndex::incrementCoordinate(std::string label)
{
    if (m_label_index_map.count(label) == 0) return;
    size_t index = m_label_index_map[label];
    if (m_current_coordinate[index] < m_axis_sizes[index]-2)
    {
        ++m_current_coordinate[index];
        updateCurrentPosition();
        return;
    }
    throw OutOfBoundsException("Coordinate value out of bounds!");
}

void MultiIndex::decrementCoordinate(std::string label)
{
    if (m_label_index_map.count(label) == 0) return;
    size_t index = m_label_index_map[label];
    if (m_current_coordinate[index] > 1)
    {
        --m_current_coordinate[index];
        updateCurrentPosition();
        return;
    }
    throw OutOfBoundsException("Coordinate value out of bounds!");
}

void MultiIndex::init(const std::vector<NamedVectorBase*>& value_axes)
{
    clear();
    m_dimension = value_axes.size();
    if (m_dimension==0) return;
    m_axis_sizes.resize(m_dimension);
    m_current_coordinate.resize(m_dimension);
    m_steps.resize(m_dimension);
    for (size_t i=0; i<m_dimension; ++i)
    {
        NamedVectorBase* p_axis = value_axes[i];
        if (m_label_index_map.count(p_axis->getName()) != 0)
        {
            throw ClassInitializationException("Axis labels for OutputData object should be unique!");
        }
        m_label_index_map[p_axis->getName()] = i;
        m_labels.push_back(p_axis->getName());
        m_axis_sizes[i] = p_axis->getSize();
        m_total_size *= p_axis->getSize();
        m_current_coordinate[i] = 0;
    }
    size_t remaining_size = m_total_size;
    for (size_t i=0; i<m_dimension; ++i)
    {
        m_steps[i] = remaining_size / m_axis_sizes[i];
        remaining_size = m_steps[i];
    }
}

void MultiIndex::clear()
{
    m_axis_sizes.clear();
    m_current_coordinate.clear();
    m_labels.clear();
    m_label_index_map.clear();
    m_steps.clear();
    m_dimension = 0;
    m_total_size = 1;
    m_current_position = 0;
    m_end_passed = false;
}

