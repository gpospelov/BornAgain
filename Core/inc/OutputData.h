#ifndef OUTPUTDATA_H
#define OUTPUTDATA_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   OutputData.h
//! @brief  Definition of OutputData class
//! @author Scientific Computing Group at FRM II
//! @date   01.04.2012

#include "NamedVector.h"
#include <map>


template <class T> class OutputData;

class MultiIndex
{
    template <class T> friend class OutputData;
public:
    std::vector<std::string> getLabels() { return m_labels; }
    std::vector<size_t> getCoordinate();
    size_t getCoordinate(std::string label);
    size_t getPosition() { return m_current_position; }
    size_t getSize() { return m_total_size; }
    void reset();
    void setCoordinate(std::string label, size_t value);
    void incrementCoordinate(std::string label);
    void decrementCoordinate(std::string label);
    MultiIndex& operator++();
    bool endPassed() { return m_end_passed; }
private:
    MultiIndex();
    ~MultiIndex();
    // Disabling copy constructor and assignment
    MultiIndex(const MultiIndex& source);
    MultiIndex operator=(const MultiIndex& source);
    void updateCurrentCoordinate();
    void updateCurrentPosition();

    void init(const std::vector<NamedVectorBase*>& value_axes);
    void clear();
    std::vector<std::string> m_labels;
    std::map<std::string, size_t> m_label_index_map;
    size_t m_dimension;
    size_t m_total_size;
    size_t m_current_position;
    std::vector<size_t> m_axis_sizes;
    std::vector<size_t> m_current_coordinate;
    std::vector<size_t> m_steps;
    bool m_end_passed;
};

template <class T> class OutputData
{
public:
    OutputData();
    virtual ~OutputData();

    void addAxis(NamedVectorBase* p_new_axis);
    std::vector<NamedVectorBase*> getAxes() { return m_value_axes; }
    NamedVectorBase* getAxis(std::string label);
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
    allocate();
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
        allocate();
    }
}

template <class T> NamedVectorBase* OutputData<T>::getAxis(std::string label)
{
    for (std::vector<NamedVectorBase*>::iterator it = m_value_axes.begin(); it != m_value_axes.end(); ++it)
    {
        if ((*it)->getName() == label)
        {
            return (*it);
        }
    }
    return 0;
}

template <class T> inline MultiIndex& OutputData<T>::getIndex()
{
    return m_index;
}

template <class T> inline T& OutputData<T>::currentValue()
{
    return m_data_vector[m_index.m_current_position];
}

template <class T> void OutputData<T>::allocate()
{
    m_index.init(m_value_axes );
    if (m_data_vector.size() != m_data_size)
    {
        m_data_vector.resize(m_data_size);
    }
}


#endif // OUTPUTDATA_H
