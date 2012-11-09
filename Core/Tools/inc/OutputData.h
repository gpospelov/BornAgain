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
#include "Types.h"
#include "LLData.h"
#include <map>
#include <string>
#include <sstream>

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
    std::vector<size_t> getAllSizes() { return m_axis_sizes; }
    void reset();
    void setIndexOfAxis(std::string axis_name, size_t value);
    void setAllIndices(std::vector<size_t> indices);
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

    const NamedVectorBase *getAxis(std::string label) const;
    const NamedVectorBase *getAxis(size_t index) const;

    //! return number of dimensions
    size_t getRank() const { return m_value_axes.size(); }

    //! return number of dimensions (same as above)
    size_t getNdimensions() const { return getRank(); }

    //! return total size of data buffer (product of bin number in every dimension)
    size_t getAllocatedSize() const {
        if (mp_ll_data) return mp_ll_data->getTotalSize();
        return 0;
    }

    //! return all sizes of its axes
    std::vector<size_t> getAllSizes() const;

    //! return copy of raw data vector
    std::vector<T> getRawDataVector() const;

    //! fill raw array with data
    void fillRawDataArray(T *destination) const;

    //! return multi index
    MultiIndex& getIndex() const;

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
    T totalSum() const;

    // ---------
    // modifiers
    // ---------

    //! set object into initial state (no dimensions, data)
    void clear();

    //! set content of output data to specific value
    void setAllTo(const T& value);

    //! multiply every item of this output data by value
    void scaleAll(const T& factor);

    //! add <rank> axes with indicated sizes
    void setAxisSizes(size_t rank, int *n_dims);

    //! set new values to raw data vector
    void setRawDataVector(const std::vector<T> &data_vector);

    //! set new values to raw data array
    void setRawDataArray(const T *source);

private:
    //! hidden copy constructor and assignment operators
    OutputData(const OutputData& source);
    const OutputData& operator=(const OutputData& right);

    //! memory allocation for current dimensions configuration
    void allocate();

    std::vector<NamedVectorBase*> m_value_axes;
    mutable MultiIndex m_index;
    LLData<T> *mp_ll_data;
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

//! multiplication-assignment operator for two output data
const OutputData<double> &operator*=(OutputData<double> &left, const OutputData<double> &right);

//! double the bin size for each dimension
OutputData<double> *doubleBinSize(const OutputData<double> &source);

//! unnormalized Fourier transformations for real data
void fourierTransform(const OutputData<double> &source, OutputData<complex_t> *p_destination);
void fourierTransformR(const OutputData<complex_t> &source, OutputData<double> *p_destination);

OutputData<double> *getRealPart(const OutputData<complex_t> &source);
OutputData<double> *getImagPart(const OutputData<complex_t> &source);
OutputData<double> *getModulusPart(const OutputData<complex_t> &source);

/* ***************************************************************************/
// definitions
/* ***************************************************************************/

// default constructor
template <class T> OutputData<T>::OutputData()
: mp_ll_data(0)
{
    allocate();
}

// destructor
template <class T> OutputData<T>::~OutputData()
{
    clear();
}

// make object clone
template <class T> OutputData<T>* OutputData<T>::clone() const
{
	OutputData<T>* p_result = new OutputData<T>();
    for (size_t i=0; i<getRank(); ++i)
    {
        p_result->addAxis(getAxis(i)->clone());
    }
    (*p_result->mp_ll_data) = *mp_ll_data;

	return p_result;
}

template <class T> void OutputData<T>::copyFrom(const OutputData<T> &other)
{
    clear();
    for (size_t i=0; i<other.getNdimensions(); ++i)
    {
        addAxis(other.getAxis(i)->clone());
    }
    (*mp_ll_data) = *other.mp_ll_data;
}



template <class T> void OutputData<T>::addAxis(NamedVectorBase* p_new_axis)
{
    if (p_new_axis->getSize()>0)
    {
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

template <class T> const NamedVectorBase *OutputData<T>::getAxis(std::string label) const
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

template <class T> const NamedVectorBase *OutputData<T>::getAxis(size_t index) const
{
    return m_value_axes.at(index);
}

template<class T>
inline std::vector<size_t> OutputData<T>::getAllSizes() const
{
    std::vector<size_t> result;
    for (size_t i=0; i<getRank(); ++i) {
        int dim = mp_ll_data->getDimensions()[i];
        result.push_back(dim);
    }
    return result;
}

template<class T>
inline std::vector<T> OutputData<T>::getRawDataVector() const
{
    std::vector<T> result;
    for (size_t i=0; i<getAllocatedSize(); ++i) {
        result.push_back((*mp_ll_data)[i]);
    }
    return result;
}

//! fill raw array with data
template <class T> void OutputData<T>::fillRawDataArray(T *destination) const
{
    for (size_t i=0; i<getAllocatedSize(); ++i) {
        destination[i] = (*mp_ll_data)[i];
    }
    return;
}


// return multi index
template <class T> inline MultiIndex& OutputData<T>::getIndex() const
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
    return (*mp_ll_data)[m_index.m_current_position];
}


// return reference to current value
template <class T> inline T& OutputData<T>::currentValue()
{
    return (*mp_ll_data)[m_index.m_current_position];
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
inline T OutputData<T>::totalSum() const
{
    return mp_ll_data->getTotalSum();
}

// set object into initial state (no dimensions, data)
template <class T> void OutputData<T>::clear()
{
    for (size_t i=0; i<getRank(); ++i)
    {
        delete m_value_axes[i];
    }
    m_value_axes.clear();
    delete mp_ll_data;
    mp_ll_data = 0;
}


// set content of output data to specific value
template <class T> void OutputData<T>::setAllTo(const T &value)
{
    mp_ll_data->setAll(value);
}


// multiply every item of this output data by value
template <class T> void OutputData<T>::scaleAll(const T &factor)
{
    mp_ll_data->scaleAll(factor);
}

// add <rank> axes with indicated sizes
template <class T> void OutputData<T>::setAxisSizes(size_t rank, int *n_dims)
{
    clear();
    std::string basename("axis");
    for (size_t i=0; i<rank; ++i) {
        std::ostringstream name;
        name << basename << i;
        addAxis(name.str(), 0.0, (double)(n_dims[i]-1), n_dims[i]);
    }
}


template <class T> void OutputData<T>::allocate()
{
    delete mp_ll_data;
    size_t rank = m_value_axes.size();
    int *dims =  new int[rank];
    for (size_t i=0; i<rank; ++i) {
        dims[i] = getAxis(i)->getSize();
    }
    mp_ll_data = new LLData<T>(rank, dims);
    T default_value = T();
    mp_ll_data->setAll(default_value);
    delete[] dims;
    m_index.init(m_value_axes);
}


// set new values to raw data vector
template<class T> inline void OutputData<T>::setRawDataVector(const std::vector<T> &data_vector)
{
    if (data_vector.size() != getAllocatedSize()) {
        throw RuntimeErrorException("setRawDataVector can only be called with a data vector of the correct size.");
    }
    for (size_t i=0; i<getAllocatedSize(); ++i) {
        (*mp_ll_data)[i] = data_vector[i];
    }
}

// set new values to raw data array
template<class T> inline void OutputData<T>::setRawDataArray(const T *source)
{
    for (size_t i=0; i<getAllocatedSize(); ++i) {
        (*mp_ll_data)[i] = source[i];
    }
}

#endif // OUTPUTDATA_H
