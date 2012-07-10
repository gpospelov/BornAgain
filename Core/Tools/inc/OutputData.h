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
#include "Exceptions.h"

#include <map>

template <class T> class OutputData;

class MultiIndex
{
    template <class T> friend class OutputData;
public:
    std::vector<std::string> getLabels() { return m_labels; }
    std::vector<size_t> getCurrentIndices();
    size_t getCurrentIndexOfAxis(std::string axis_name);
    size_t getPosition() { return m_current_position; }
    size_t getSize() { return m_total_size; }
    void reset();
    void setIndexOfAxis(std::string axis_name, size_t value);
    void incrementIndexOfAxis(std::string axis_name);
    void decrementIndexOfAxis(std::string axis_name);
    MultiIndex& operator++();
    bool endPassed() { return m_end_passed; }
private:
    MultiIndex();
    ~MultiIndex();
    // Disabling copy constructor and assignment
    MultiIndex(const MultiIndex& source);
    MultiIndex operator=(const MultiIndex& source);
    void updateCurrentIndices();
    void updateCurrentPosition();
    void setPosition(size_t position);

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
    OutputData* clone() const;

    void addAxis(NamedVectorBase* p_new_axis);
    template <class U> void addAxis(std::string name, U start, U end, size_t size);
    std::vector<NamedVectorBase*> getAxes() { return m_value_axes; }
    NamedVectorBase* getAxis(std::string label);
    size_t getDimension() const { return m_dimension; }
    size_t getAllocatedSize() const { return m_data_vector.size(); }
    std::vector<T> getRawDataVector() const { return m_data_vector; }
    void setRawDataVector(const std::vector<T> &data_vector);
    MultiIndex& getIndex();
    void resetIndex();
    bool hasNext();
    T& next();
    T& currentValue();
    size_t getCurrentIndexOfAxis(std::string axis_name);
    template <class U> U getCurrentValueOfAxis(std::string axis_name);
    void clear();
    void setAllTo(const T& value);

private:
    OutputData(const OutputData& source);
    const OutputData& operator=(const OutputData& right);
    void allocate();
    size_t m_dimension;
    size_t m_data_size;
    std::vector<NamedVectorBase*> m_value_axes;
    MultiIndex m_index;
    std::vector<T> m_data_vector;
};

const OutputData<double> &operator+=(OutputData<double> &left, const OutputData<double> &right);
const OutputData<double> &operator-=(OutputData<double> &left, const OutputData<double> &right);

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

template <class T> OutputData<T>* OutputData<T>::clone() const
{
	OutputData<T>* p_result = new OutputData<T>();
    for (size_t i=0; i<m_dimension; ++i)
    {
        p_result->addAxis(m_value_axes[i]->clone());
    }
	p_result->resetIndex();
	size_t source_index = 0;
	size_t source_size = this->getAllocatedSize();
	while (p_result->hasNext() && source_index<source_size) {
	    p_result->next() = m_data_vector[source_index];
	    ++source_index;
	}
	return p_result;
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

template <class T>
template <class U> void OutputData<T>::addAxis(std::string name, U start, U end, size_t size)
{
    NamedVector<U> *p_new_axis = new NamedVector<U>(name, start, end, size);
    addAxis(p_new_axis);
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

template<class T> inline void OutputData<T>::setRawDataVector(const std::vector<T> &data_vector)
{
    if (data_vector.size() != m_data_size) {
        throw RuntimeErrorException("setRawDataVector can only be called with a data vector of the correct size.");
    }
    m_data_vector = data_vector;
}

template <class T> inline MultiIndex& OutputData<T>::getIndex()
{
    return m_index;
}

template <class T> inline void OutputData<T>::resetIndex()
{
    m_index.reset();
}

template <class T> inline bool OutputData<T>::hasNext()
{
    return !m_index.endPassed();
}

template <class T> inline T& OutputData<T>::next()
{
    T &temp = currentValue();
    ++m_index;
    return temp;
}

template <class T> inline T& OutputData<T>::currentValue()
{
    return m_data_vector[m_index.m_current_position];
}

template <class T> inline size_t OutputData<T>::getCurrentIndexOfAxis(std::string axis_name)
{
    return m_index.getCurrentIndexOfAxis(axis_name);
}

template <class T>
template <class U> inline U OutputData<T>::getCurrentValueOfAxis(std::string axis_name)
{
    NamedVector<U> *p_axis = dynamic_cast<NamedVector<U>*>(getAxis(axis_name));
    size_t index = getCurrentIndexOfAxis(axis_name);
    return (*p_axis)[index];
}

template <class T> void OutputData<T>::clear()
{
    for (size_t i=0; i<m_dimension; ++i)
    {
        delete m_value_axes[i];
    }
    m_value_axes.clear();
    m_dimension = 0;
    m_data_size = 1;
    allocate();
}

template <class T> void OutputData<T>::setAllTo(const T &value)
{
    for (size_t index=0; index<m_data_size; ++index) {
        m_data_vector[index] = value;
    }
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
