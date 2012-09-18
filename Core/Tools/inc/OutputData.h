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


//- -------------------------------------------------------------------
//! @class MultiIndex
//! @brief Definition of MultiIndex class to navigate trough OutputData
//- -------------------------------------------------------------------
class MultiIndex
{
    template <class T> friend class OutputData;
public:
    std::vector<std::string> getLabels() { return m_labels; }
    std::vector<size_t> getCurrentIndices();
    size_t getCurrentIndexOfAxis(std::string axis_name);
    size_t getPosition() const { return m_current_position; }
    size_t getSize() const { return m_total_size; }
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


//- -------------------------------------------------------------------
//! @class OutputData
//! @brief Definition of OutputData class to store data of any type in
//! multi-dimensional space
//- -------------------------------------------------------------------
template <class T> class OutputData
{
public:
    OutputData();
    virtual ~OutputData();
    //! make object clone
    OutputData* clone() const;

//    void copyInto(OutputData<T> &x) const;
    void copyFrom(const OutputData<T> &x);

    void addAxis(NamedVectorBase* p_new_axis);
    template <class U> void addAxis(std::string name, U start, U end, size_t size);
    std::vector<NamedVectorBase*> getAxes() const { return m_value_axes; }

    const NamedVectorBase* getAxis(std::string label) const;

    //! return number of dimensions
    size_t getDimension() const { return m_dimension; }

    //! return number of dimensions (same as above)
    size_t getNdimensions() const { return m_dimension; }

    //! return total size of data buffer (product of bin number in every dimension)
    size_t getAllocatedSize() const { return m_data_vector.size(); }

    //! return copy of raw data vector
    std::vector<T> getRawDataVector() const { return m_data_vector; }

    //! return multi index
    MultiIndex& getIndex();

    // ---------------------------------
    // navigation and access to stored elements
    // ---------------------------------

    //! reset index to point to the beginning of data structure
    void resetIndex() const;

    //! return true if next element exists
    bool hasNext() const;

    //! return const reference to current value and increment index
    const T& next() const;

    //! return reference to current value and increment index
    T& next();

    //! return const reference to current value
    const T& currentValue() const;

    //! return reference to current value
    T& currentValue();

    //! return current index of axis with given name
    size_t getCurrentIndexOfAxis(std::string axis_name) const;

    //! return current value of axis with given name
    template <class U> U getCurrentValueOfAxis(std::string axis_name) const;

    //! get sum of all values in the data structure
    T total() const;

    // ---------
    // modifiers
    // ---------

    //! set object into initial state (no dimensions, data)
    void clear();

    //! set content of output data to specific value
    void setAllTo(const T& value);

    //! multiply every item of this output data by value
    void scaleAll(const T& value);

    //! set new values to raw data vector
    void setRawDataVector(const std::vector<T> &data_vector);

private:
    //! hidden copy constructor and assignment operators
    OutputData(const OutputData& source);
    const OutputData& operator=(const OutputData& right);

    //! memory allocation for current dimensions configuration
    void allocate();

    size_t m_dimension;
    size_t m_data_size;
    std::vector<NamedVectorBase*> m_value_axes;
    mutable MultiIndex m_index;
    std::vector<T> m_data_vector;
};


/* **************** */
// global arithmetics
/* **************** */

//! addition-assignment operator for two output data
const OutputData<double> &operator+=(OutputData<double> &left, const OutputData<double> &right);

//! substraction-assignment operator for two output data
const OutputData<double> &operator-=(OutputData<double> &left, const OutputData<double> &right);

//! division-assignment operator for two output data
const OutputData<double> &operator/=(OutputData<double> &left, const OutputData<double> &right);


/* ***************************************************************************/
// definitions
/* ***************************************************************************/

// default constructor
template <class T> OutputData<T>::OutputData()
    : m_dimension(0)
    , m_data_size(1)
{
    allocate();
}

// destructor
template <class T> OutputData<T>::~OutputData()
{
    for (size_t i=0; i<m_dimension; ++i)
    {
        delete m_value_axes[i];
    }
}

// make object clone
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


//template <class T> void OutputData<T>::copyInto(OutputData<T> &other) const
//{
//    other.clear();
//    for (size_t i=0; i<m_dimension; ++i)
//    {
//        other.addAxis(m_value_axes[i]->clone());
//    }
//    other.resetIndex();
//    size_t source_index = 0;
//    size_t source_size = this->getAllocatedSize();
//    while (other.hasNext() && source_index<source_size) {
//        other.next() = m_data_vector[source_index];
//        ++source_index;
//    }

//}


template <class T> void OutputData<T>::copyFrom(const OutputData<T> &other)
{
    clear();
    for (size_t i=0; i<other.getNdimensions(); ++i)
    {
        const NamedVector<T> *axis = dynamic_cast<const NamedVector<T>*>(other.getAxes()[i]);
        addAxis(axis->clone());
    }
    resetIndex();
    other.resetIndex();
    while (other.hasNext()) {
        currentValue() = other.currentValue();
        next(); other.next();
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

template <class T>
template <class U> void OutputData<T>::addAxis(std::string name, U start, U end, size_t size)
{
    NamedVector<U> *p_new_axis = new NamedVector<U>(name, start, end, size);
    addAxis(p_new_axis);
}

template <class T> const NamedVectorBase* OutputData<T>::getAxis(std::string label) const
{
    for (std::vector<NamedVectorBase*>::const_iterator it = m_value_axes.begin(); it != m_value_axes.end(); ++it)
    {
        if ((*it)->getName() == label)
        {
            return (*it);
        }
    }
    return 0;
}


// return multi index
template <class T> inline MultiIndex& OutputData<T>::getIndex()
{
    return m_index;
}


// reset index to point to the beginning of data structure
template <class T> inline void OutputData<T>::resetIndex() const
{
    m_index.reset();
}


// return true if next element exists
template <class T> inline bool OutputData<T>::hasNext() const
{
    return !m_index.endPassed();
}


// return const reference to current value and increment index
template <class T> inline const T& OutputData<T>::next() const
{
    const T &temp = currentValue();
    ++m_index;
    return temp;
}


// return reference to current value and increment index
template <class T> inline T& OutputData<T>::next()
{
    T &temp = currentValue();
    ++m_index;
    return temp;
}


// return const reference to current value
template <class T> inline const T& OutputData<T>::currentValue() const
{
    return m_data_vector[m_index.m_current_position];
}


// return reference to current value
template <class T> inline T& OutputData<T>::currentValue()
{
    return m_data_vector[m_index.m_current_position];
}


template <class T> inline size_t OutputData<T>::getCurrentIndexOfAxis(std::string axis_name) const
{
    return m_index.getCurrentIndexOfAxis(axis_name);
}


// return current value of axis with given name
template <class T>
template <class U> inline U OutputData<T>::getCurrentValueOfAxis(std::string axis_name) const
{
    const NamedVector<U> *p_axis = dynamic_cast<const NamedVector<U>*>(getAxis(axis_name));
    size_t index = getCurrentIndexOfAxis(axis_name);
    return (*p_axis)[index];
}


template<class T>
inline T OutputData<T>::total() const
{
    T total = 0;
    for (size_t i=0; i<m_data_size; ++i) {
        total += m_data_vector[i];
    }
    return total;
}

// set object into initial state (no dimensions, data)
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


// set content of output data to specific value
template <class T> void OutputData<T>::setAllTo(const T &value)
{
    for (size_t index=0; index<m_data_size; ++index) {
        m_data_vector[index] = value;
    }
}


// multiply every item of this output data by value
template <class T> void OutputData<T>::scaleAll(const T &value)
{
    for (size_t index=0; index<m_data_size; ++index) {
        m_data_vector[index] *= value;
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


// set new values to raw data vector
template<class T> inline void OutputData<T>::setRawDataVector(const std::vector<T> &data_vector)
{
    if (data_vector.size() != m_data_size) {
        throw RuntimeErrorException("setRawDataVector can only be called with a data vector of the correct size.");
    }
    m_data_vector = data_vector;
}

#endif // OUTPUTDATA_H
