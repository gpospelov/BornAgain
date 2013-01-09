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

#include "AxisDouble.h"
#include "Exceptions.h"
#include "Types.h"
#include "LLData.h"
#include "OutputDataIterator.h"
#include "SafePointerVector.h"

//#include <string>
#include <sstream>

//- -------------------------------------------------------------------
//! @class OutputData
//! @brief Definition of OutputData class to store data of any type in
//! multi-dimensional space
//- -------------------------------------------------------------------
template <class T> class OutputData
{
public:
    OutputData();
    ~OutputData();
    //! make object clone
    OutputData* clone() const;

    void copyFrom(const OutputData<T> &x);

    void addAxis(const IAxis &new_axis);
    void addAxis(std::string name, size_t size, double start, double end);

    const IAxis *getAxis(size_t index) const;
    const IAxis *getAxis(std::string label) const;
    size_t getAxisIndex(const std::string &label) const;

    // ---------------------------------
    // retrieve basic info
    // ---------------------------------

    //! return number of dimensions
    size_t getRank() const { return m_value_axes.size(); }

    //! return number of dimensions (same as above)
    size_t getNdimensions() const { return getRank(); }

    //! return total size of data buffer (product of bin number in every dimension)
    size_t getAllocatedSize() const {
        if (mp_ll_data) return mp_ll_data->getTotalSize();
        return 0;
    }

    //! return total size of data buffer (product of bin number in every dimension)
    //!
    //! copy of getAllocatedSize() for use in OutputDataIterator
    size_t size() const {
        return getAllocatedSize();
    }

    //! return all sizes of its axes
    std::vector<size_t> getAllSizes() const;

    //! return copy of raw data vector
    std::vector<T> getRawDataVector() const;

    //! fill raw array with data
    void fillRawDataArray(T *destination) const;

    //! get sum of all values in the data structure
    T totalSum() const;

    // ---------------------------------
    // external iterators (with their possible masking)
    // ---------------------------------

    friend class OutputDataIterator<T, OutputData<T> >;
    friend class OutputDataIterator<const T, const OutputData<T> >;

    //! read/write iterator type
    typedef OutputDataIterator<T, OutputData<T> > iterator;

    //! read-only iterator type
    typedef OutputDataIterator<const T, const OutputData<T> > const_iterator;

    //! return a read/write iterator that points to the first element
    iterator begin();

    //! return a read-only iterator that points to the first element
    const_iterator begin() const;

    //! return a read/write iterator that points to the one past last element
    iterator end() { return iterator(this, getAllocatedSize()); }

    //! return a read-only iterator that points to the one past last element
    const_iterator end() const  { return const_iterator(this, getAllocatedSize()); }

    //! get mask that will be used by iterators
    Mask *getMask() const { return mp_mask; }

    //! set mask (or a stack of masks)
    void setMask(const Mask &mask);

    //! add mask that will be used by iterators
    void addMask(const Mask &mask);

    //! remove all masks
    void removeAllMasks();

    // ---------------------------------
    // coordinate and index functions
    // ---------------------------------

    //! return vector of coordinates for given index
    std::vector<int> toCoordinates(size_t index) const;

    //! return coordinate for given index and axis number
    int toCoordinate(size_t index, size_t i_selected_axis) const;

    //! return index for specified coordinates
    size_t toIndex(std::vector<int> coordinates) const;

    //! return index of axis with given name for given total index
    size_t getIndexOfAxis(const std::string &axis_name, size_t total_index) const;

    //! return value of axis with given name at given index
    double getValueOfAxis(const std::string &axis_name, size_t index) const;

    //! return bin of axis with given name and index
    Bin1D getBinOfAxis(const std::string &axis_name, size_t index) const;

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

    //! addition-assignment operator for two output data
    const OutputData<T> &operator+=(const OutputData<T> &right);

    //! substraction-assignment operator for two output data
    const OutputData<T> &operator-=(const OutputData<T> &right);

    //! division-assignment operator for two output data
    const OutputData<T> &operator/=(const OutputData<T> &right);

    //! multiplication-assignment operator for two output data
    const OutputData<T> &operator*=(const OutputData<T> &right);

   //! indexed accessor
    T &operator[](size_t index) {
        if (mp_ll_data) return (*mp_ll_data)[index];
        throw ClassInitializationException("Low-level data object was not yet initialized");
    }

    //! indexed accessor (const)
    const T &operator[](size_t index) const {
        if (mp_ll_data) return (*mp_ll_data)[index];
        throw ClassInitializationException("Low-level data object was not yet initialized");
    }

    // --------
    // helpers
    // --------

    //! return true if object have same dimensions
    bool hasSameDimensions(const OutputData<T> &right) const;

    //! return true if object have same dimensions and shape of axises
    bool hasSameShape(const OutputData<T> &right) const;
private:
    //! disabled copy constructor and assignment operators
    OutputData(const OutputData &);
    const OutputData& operator=(const OutputData &);

    //! memory allocation for current dimensions configuration
    void allocate();

    SafePointerVector<IAxis> m_value_axes;
    LLData<T> *mp_ll_data;
    Mask *mp_mask;
};


/* ***************************************************************************/
// definitions
/* ***************************************************************************/

template <class T> OutputData<T>::OutputData()
: mp_ll_data(0)
, mp_mask(0)
{
    allocate();
}

template <class T> OutputData<T>::~OutputData()
{
    clear();
}

template <class T> OutputData<T>* OutputData<T>::clone() const
{
	OutputData<T>* p_result = new OutputData<T>();
	p_result->m_value_axes = m_value_axes;
    (*p_result->mp_ll_data) = *mp_ll_data;

    if (mp_mask) {
        p_result->mp_mask = mp_mask->clone();
    }

	return p_result;
}

template <class T> void OutputData<T>::copyFrom(const OutputData<T> &other)
{
    clear();
    m_value_axes = other.m_value_axes;
    delete mp_ll_data;
    mp_ll_data = 0;
    if(other.mp_ll_data) {
        mp_ll_data = new LLData<T>(*other.mp_ll_data);
    }
    if (other.getMask()) {
        mp_mask = other.getMask()->clone();
    }
}



template <class T> void OutputData<T>::addAxis(const IAxis &new_axis)
{
    if( getAxis(new_axis.getName()) ) throw LogicErrorException("OutputData<T>::addAxis(const IAxis &new_axis) -> Error! Attempt to add axis with already existing name '"+ new_axis.getName()+std::string("'"));
    if (new_axis.getSize()>0)
    {
        m_value_axes.push_back(new_axis.clone());
        allocate();
    }
}

template <class T>
void OutputData<T>::addAxis(std::string name, size_t size, double start, double end)
{
    if( getAxis(name) ) throw LogicErrorException("OutputData<T>::addAxis(std::string name) -> Error! Attempt to add axis with already existing name '"+name+std::string("'"));
    AxisDouble new_axis(name, size, start, end);
    addAxis(new_axis);
}

template <class T> const IAxis *OutputData<T>::getAxis(size_t index) const
{
    return m_value_axes[index];
}

template <class T> const IAxis *OutputData<T>::getAxis(std::string label) const
{
    for (size_t i = 0; i < m_value_axes.size(); ++i)
    {
        if (m_value_axes[i]->getName() == label)
        {
            return m_value_axes[i];
        }
    }
    return 0;
}

// return index of axis
template <class T> size_t OutputData<T>::getAxisIndex(const std::string &label) const
{
    for (size_t i = 0; i < m_value_axes.size(); ++i)
    {
        if (m_value_axes[i]->getName() == label) return i;
    }
    throw LogicErrorException("OutputData<T>::getAxisIndex() -> Error! Axis with given name not found '"+label+std::string("'"));
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

template <class T>
inline std::vector<T> OutputData<T>::getRawDataVector() const
{
    std::vector<T> result;
    for (size_t i=0; i<getAllocatedSize(); ++i) {
        result.push_back((*mp_ll_data)[i]);
    }
    return result;
}

template <class T> void OutputData<T>::fillRawDataArray(T *destination) const
{
    for (size_t i=0; i<getAllocatedSize(); ++i) {
        destination[i] = (*mp_ll_data)[i];
    }
    return;
}

template <class T> typename OutputData<T>::iterator OutputData<T>::begin()
{
    typename OutputData<T>::iterator result(this);
    if (mp_mask) {
        result.setMask(*mp_mask);
    }
    return result;
}

template <class T> typename OutputData<T>::const_iterator OutputData<T>::begin() const
{
    typename OutputData<T>::const_iterator result(this);
    if (mp_mask) {
        result.setMask(*mp_mask);
    }
    return result;
}

template <class T> void OutputData<T>::setMask(const Mask &mask)
{
    if (mp_mask != &mask) {
        delete mp_mask;
        mp_mask = mask.clone();
        mp_mask->setMaxIndex(getAllocatedSize());
    }
}

template <class T> void OutputData<T>::addMask(const Mask &mask)
{
    if (mask.mp_submask) {
        throw RuntimeErrorException("One can only add single masks to OutputDataIterator at a time");
    }
    Mask *p_old_mask = getMask();
    mp_mask = mask.clone();
    mp_mask->mp_submask = p_old_mask;
    mp_mask->setMaxIndex(getAllocatedSize());
}

template<class T> void OutputData<T>::removeAllMasks()
{
    delete mp_mask;
    mp_mask = 0;
}

template<class T> std::vector<int> OutputData<T>::toCoordinates(size_t index) const
{
    size_t remainder = index;
    std::vector<int> result;
    result.resize(mp_ll_data->getRank());
    for (size_t i=0; i<mp_ll_data->getRank(); ++i)
    {
        result[mp_ll_data->getRank()-1-i] = (int)(remainder % m_value_axes[mp_ll_data->getRank()-1-i]->getSize());
        remainder /= m_value_axes[mp_ll_data->getRank()-1-i]->getSize();
    }
    return result;
}

template<class T> int OutputData<T>::toCoordinate(size_t index, size_t i_selected_axis) const
{
    size_t remainder(index);
    for (size_t i=0; i<mp_ll_data->getRank(); ++i)
    {
        size_t i_axis = mp_ll_data->getRank()-1-i;
        int result = (int)(remainder % m_value_axes[i_axis]->getSize());
        if(i_selected_axis == i_axis ) return result;
        remainder /= m_value_axes[i_axis]->getSize();
    }
    throw LogicErrorException("OutputData<T>::toCoordinate() -> Error! No axis with given number");
}


template <class T> size_t OutputData<T>::toIndex(std::vector<int> coordinates) const
{
    if (coordinates.size() != mp_ll_data->getRank()) {
        throw LogicErrorException("size_t OutputData<T>::toIndex() -> Error! Number of coordinates must match rank of data structure");
    }
    size_t result = 0;
    int step_size = 1;
    for (size_t i=mp_ll_data->getRank(); i>0; --i)
    {
        result += coordinates[i-1]*step_size;
        step_size *= m_value_axes[i-1]->getSize();
    }
    return result;
}

template <class T> size_t OutputData<T>::getIndexOfAxis(const std::string &axis_name, size_t total_index) const
{
    std::vector<int> coordinates = toCoordinates(total_index);
    for (size_t i=0; i<m_value_axes.size(); ++i) {
        if (m_value_axes[i]->getName() == axis_name) {
            return coordinates[i];
        }
    }
    throw LogicErrorException("OutputData<T>::getIndexOfAxis() -> Error! Axis with given name not found '"+std::string(axis_name)+std::string("'"));
}


template <class T>
double OutputData<T>::getValueOfAxis(const std::string &axis_name, size_t index) const
{
    for (size_t i=0; i<m_value_axes.size(); ++i) {
        if (m_value_axes[i]->getName() == axis_name) {
            int axis_index = toCoordinate(index, i);
            return (*m_value_axes[i])[axis_index];
        }
    }
    throw LogicErrorException("OutputData<T>::getValueOfAxis() -> Error! Axis with given name not found '"+std::string(axis_name)+std::string("'"));
}

template <class T>
Bin1D OutputData<T>::getBinOfAxis(const std::string &axis_name, size_t index) const
{
    for (size_t i=0; i<m_value_axes.size(); ++i) {
        if (m_value_axes[i]->getName() == axis_name) {
            int axis_index = toCoordinate(index, i);
            return m_value_axes[i]->getBin(axis_index);
        }
    }
    throw LogicErrorException("OutputData<T>::getBinOfAxis() -> Error! Axis with given name not found '"+std::string(axis_name)+std::string("'"));
}

template<class T>
inline T OutputData<T>::totalSum() const
{
    return mp_ll_data->getTotalSum();
}

template <class T> void OutputData<T>::clear()
{
    m_value_axes.clear();
    delete mp_ll_data;
    mp_ll_data = 0;
    delete mp_mask;
    mp_mask = 0;
}

template <class T> void OutputData<T>::setAllTo(const T &value)
{
    mp_ll_data->setAll(value);
}

template <class T> void OutputData<T>::scaleAll(const T &factor)
{
    mp_ll_data->scaleAll(factor);
}

template <class T> void OutputData<T>::setAxisSizes(size_t rank, int *n_dims)
{
    clear();
    std::string basename("axis");
    for (size_t i=0; i<rank; ++i) {
        std::ostringstream name;
        name << basename << i;
        addAxis(name.str(), n_dims[i], 0.0, (double)(n_dims[i]-1));
    }
}

template<class T> const OutputData<T> &OutputData<T>::operator+=(const OutputData<T>& right)
{
    *this->mp_ll_data += *right.mp_ll_data;
    return *this;
}

template<class T> const OutputData<T> &OutputData<T>::operator-=(const OutputData<T>& right)
{
    *this->mp_ll_data -= *right.mp_ll_data;
    return *this;
}

template<class T> const OutputData<T> &OutputData<T>::operator*=(const OutputData<T>& right)
{
    *this->mp_ll_data *= *right.mp_ll_data;
    return *this;
}

template<class T> const OutputData<T> &OutputData<T>::operator/=(const OutputData<T>& right)
{
    *this->mp_ll_data /= *right.mp_ll_data;
    return *this;
}

template <class T> void OutputData<T>::allocate()
{
    delete mp_ll_data;
    size_t rank = m_value_axes.size();
    int *dims =  new int[rank];
    for (size_t i=0; i<rank; ++i) {
        dims[i] = (int)getAxis(i)->getSize();
    }
    mp_ll_data = new LLData<T>(rank, dims);
    T default_value = T();
    mp_ll_data->setAll(default_value);
    delete[] dims;
}

template<class T> inline void OutputData<T>::setRawDataVector(const std::vector<T> &data_vector)
{
    if (data_vector.size() != getAllocatedSize()) {
        throw RuntimeErrorException("OutputData<T>::setRawDataVector() -> Error! setRawDataVector can only be called with a data vector of the correct size.");
    }
    for (size_t i=0; i<getAllocatedSize(); ++i) {
        (*mp_ll_data)[i] = data_vector[i];
    }
}

template<class T> inline void OutputData<T>::setRawDataArray(const T *source)
{
    for (size_t i=0; i<getAllocatedSize(); ++i) {
        (*mp_ll_data)[i] = source[i];
    }
}


//! return true if object have same dimensions
template<class T> inline bool OutputData<T>::hasSameDimensions(const OutputData<T> &right) const
{
    if(!mp_ll_data || !right.mp_ll_data ) return false;
    return HaveSameDimensions(*mp_ll_data, *right.mp_ll_data);
}

//! return true if object have same dimensions and shape of axis
template<class T>
bool OutputData<T>::hasSameShape(const OutputData<T> &right) const
{
    if(!hasSameDimensions(right)) return false;

    if( (mp_ll_data->getRank() != m_value_axes.size()) || (right.mp_ll_data->getRank() != right.m_value_axes.size()) ) {
        throw LogicErrorException("OutputData<T>::hasSameShape() -> Panic! Inconsistent dimensions in LLData and axes");
    }
    for (size_t i=0; i<m_value_axes.size(); ++i) {
        const IAxis *p_axis_left = m_value_axes[i];
        const IAxis *p_axis_right = right.m_value_axes[i];

        if( !HaveSameNameAndShape(*p_axis_left, *p_axis_right)) return false;
    }
    return true;
}


#endif // OUTPUTDATA_H
