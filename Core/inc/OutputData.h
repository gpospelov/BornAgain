#ifndef OUTPUTDATA_H
#define OUTPUTDATA_H

#include "NamedVector.h"

class MultiIndex
{
    template <class T> friend class OutputData;
public:
    std::vector<std::string> getLabels() { return m_labels; }
    MultiIndex& operator++();
private:
    MultiIndex();
    ~MultiIndex();
    // Disabling copy constructor and assignment
    MultiIndex(const MultiIndex& source);
    MultiIndex operator=(const MultiIndex& source);

    void init(const std::vector<NamedVectorBase*>& value_axes);
    void clear();
    std::vector<std::string> m_labels;
    size_t m_dimension;
    size_t m_total_size;
    size_t m_current_position;
    size_t* m_axis_sizes;
    size_t* m_current_coordinate;
};

template <class T> class OutputData
{
public:
    OutputData();
    virtual ~OutputData();

    void addAxis(NamedVectorBase* p_new_axis);
    std::vector<NamedVectorBase*> getAxes() { return m_value_axes; }
    size_t getDimension() const { return m_dimension; }
    size_t getAllocatedSize() const { return m_data_vector.size(); }
    MultiIndex& getIndex();
    T& currentValue();

private:
    void allocate();
    size_t m_dimension;
    size_t m_data_size;
    std::vector<NamedVectorBase*> m_value_axes;
    MultiIndex m_index;
    std::vector<T> m_data_vector;
};

template <class T> OutputData<T>::OutputData()
    : m_dimension(0)
    , m_data_size(1)
{
}

template <class T> OutputData<T>::~OutputData()
{
    for (size_t i=0; i<m_dimension; ++i)
    {
        delete m_value_axes[i];
    }
}

template <class T> void OutputData<T>::addAxis(NamedVectorBase* p_new_axis)
{
    if (p_new_axis->getSize()>0)
    {
        ++m_dimension;
        m_data_size *= p_new_axis->getSize();
        m_value_axes.push_back(p_new_axis);
    }
}

template <class T> MultiIndex& OutputData<T>::getIndex()
{
    allocate();
    return m_index;
}

template <class T> void OutputData<T>::allocate()
{
    if (m_data_vector.size() != m_data_size)
    {
        m_index.init(m_value_axes );
        m_data_vector.resize(m_data_size);
    }
}


#endif // OUTPUTDATA_H
