#include "OutputData.h"

OutputData::OutputData()
    : m_dimension(0)
    , m_data_size(1)
    , m_allocated_size(0)
    , m_data_table(0)
{
}

void OutputData::addAxis(OutputData::value_vector* p_new_axis)
{
    if (p_new_axis->getSize()>0)
    {
        ++m_dimension;
        m_data_size *= p_new_axis->getSize();
        m_value_axes.push_back(p_new_axis);
    }
}

void OutputData::allocate()
{
    m_index.init(m_value_axes );
}

MultiIndex& MultiIndex::operator++()
{
    if (m_current_position<m_total_size-1)
    {
        ++m_current_position;
    }
    return *this;
}

MultiIndex::MultiIndex()
    : m_dimension(0)
    , m_total_size(1)
    , m_current_position(0)
    , m_axis_sizes(0)
    , m_current_coordinate(0)
{
}

MultiIndex::~MultiIndex()
{
    clear();
}

void MultiIndex::init(const std::vector<NamedVector<double>*>& value_axes)
{
    clear();
    m_dimension = value_axes.size();
    if (m_dimension==0) return;
    m_axis_sizes = new size_t[m_dimension];
    m_current_coordinate = new size_t[m_dimension];
    for (size_t i=0; i<m_dimension; ++i)
    {
        OutputData::value_vector* p_axis = value_axes[i];
        m_labels.push_back(p_axis->getName());
        m_axis_sizes[i] = p_axis->getSize();
        m_total_size *= p_axis->getSize();
        m_current_coordinate[i] = 0;
    }
}

void MultiIndex::clear()
{
    if (m_axis_sizes)
    {
        delete[] m_axis_sizes;
        m_axis_sizes = 0;
    }
    if (m_current_coordinate)
    {
        delete[] m_current_coordinate;
        m_current_coordinate = 0;
    }
    m_labels.clear();
    m_dimension = 0;
    m_total_size = 1;
    m_current_position = 0;
}

