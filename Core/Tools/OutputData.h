// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/OutputData.h
//! @brief     Declares and implements template class OutputData.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef OUTPUTDATA_H
#define OUTPUTDATA_H

#ifdef BORNAGAIN_PYTHON
#ifndef PyObject_HEAD
struct _object;
typedef _object PyObject;
#endif
#endif

#include "FixedBinAxis.h"
#include "LLData.h"
#include "OutputDataIterator.h"
#include "SafePointerVector.h"
#include "ThreadInfo.h"
#include <sstream>
#include <cassert>

using std::size_t;

//! @class OutputData
//! @ingroup tools
//! @brief Template class to store data of any type in multi-dimensional space.

template <class T>
class OutputData
{
public:
    OutputData();
    ~OutputData();
    OutputData* clone() const;

    void copyFrom(const OutputData<T>& x);

    template <class U> void copyShapeFrom(const OutputData<U>& other);

    void addAxis(const IAxis& new_axis);
    void addAxis(const std::string& name, size_t size, double start, double end);

    //! returns axis with given serial number
    const IAxis *getAxis(size_t serial_number) const;

    //! returns axis with given name
    const IAxis *getAxis(const std::string& axis_name) const;

    //! returns serial number of axis with given name
    size_t getAxisSerialNumber(const std::string& axis_name) const;

    // ---------------------------------
    // retrieve basic info
    // ---------------------------------

    //! Returns number of dimensions.
    size_t getRank() const { return m_value_axes.size(); }

   //! Returns total size of data buffer (product of bin number in every dimension).
    size_t getAllocatedSize() const {
        if (mp_ll_data) return mp_ll_data->getTotalSize();
        return 0;
    }

    //! Returns all sizes of its axes
    std::vector<size_t> getAllSizes() const;

    //! Returns copy of raw data vector
    std::vector<T> getRawDataVector() const;

    //! fill raw array with data
    void fillRawDataArray(T *destination) const;

    //! Returns sum of all values in the data structure
    T totalSum() const;

    // ---------------------------------
    // external iterators (with their possible masking)
    // ---------------------------------

    friend class OutputDataIterator<T, OutputData<T> >;
    friend class OutputDataIterator<const T, const OutputData<T> >;

    //! Read/write iterator type
    typedef OutputDataIterator<T, OutputData<T> > iterator;

    //! Read-only iterator type
    typedef OutputDataIterator<const T, const OutputData<T> > const_iterator;

    //! Returns  read/write iterator that points to the first element
    iterator begin();

    //! Returns  read-only iterator that points to the first element
    const_iterator begin() const;

    //! Returns  read/write iterator that points to the one past last element
    iterator end() { return iterator(this, getAllocatedSize()); }

    //! Returns  read-only iterator that points to the one past last element
    const_iterator end() const {
        return const_iterator(this, getAllocatedSize());
    }

    //! Returns mask that will be used by iterators
    Mask *getMask() const { return mp_mask; }

    //! Sets mask (or a stack of masks)
    void setMask(const Mask& mask);

    //! Adds mask that will be used by iterators
    void addMask(const Mask& mask);

    //! Remove all masks
    void removeAllMasks();

    // ---------------------------------
    // coordinate and index functions
    // ---------------------------------

    //! Returns vector of axes indices for given global index
    //! @param global_index The global index of this data structure.
    //! @return Vector of bin indices for all axes defined
    std::vector<int> getAxesBinIndices(size_t global_index) const;

    //! Returns axis bin index for given global index
    //! @param global_index The global index of this data structure.
    //! @param i_selected_axis Serial number of selected axis.
    //! @return Corresponding bin index for selected axis
    int getAxisBinIndex(size_t global_index, size_t i_selected_axis) const;

    //! Returns axis bin index for given global index
    //! @param global_index The global index of this data structure.
    //! @param axis_name The name of selected axis.
    //! @return Corresponding bin index for selected axis
    int getAxisBinIndex(size_t global_index, const std::string &axis_name) const;

    //! Returns global index for specified indices of axes
    //! @param axes_indices Vector of axes indices for all specified axes in this dataset
    //! @return Corresponding global index
    size_t toGlobalIndex(const std::vector<int> &axes_indices) const;

    //! Returns global index for specified axes values
    //! @param coordinates Vector of axes coordinates for all specified axes in this dataset
    //! @return Closest global index
    size_t findGlobalIndex(const std::vector<double> &coordinates) const;

    //! Returns the value of selected axis for given global_index.
    //! @param global_index The global index of this data structure.
    //! @param i_selected_axis Serial number of selected axis.
    //! @return corresponding bin center of selected axis
    double getAxisValue(size_t global_index, size_t i_selected_axis) const;

    //! Returns the value of selected axis for given global_index.
    //! @param global_index The global index of this data structure.
    //! @param axis_name The name of selected axis.
    //! @return corresponding bin center of selected axis
    double getAxisValue(size_t global_index, const std::string& axis_name) const;

    //! Returns values on all defined axes for given globalbin number
    //! @param global_index The global index of this data structure.
    //! @return Vector of corresponding bin centers
    std::vector<double > getAxesValues(size_t global_index) const;

    //! Returns bin of selected axis for given global_index.
    //! @param global_index The global index of this data structure.
    //! @param i_selected_axis Serial number of selected axis.
    //! @return Corresponding Bin1D object
    Bin1D getAxisBin(size_t global_index, size_t i_selected_axis) const;

    //! Returns bin of selected axis for given global_index.
    //! @param global_index The global index of this data structure.
    //! @param axis_name The name of selected axis.
    //! @return Corresponding Bin1D object
    Bin1D getAxisBin(size_t global_index, const std::string& axis_name) const;

    // ---------
    // modifiers
    // ---------

    //! Sets object into initial state (no dimensions, data)
    void clear();

    //! Sets content of output data to specific value
    void setAllTo(const T& value);

    //! multiply every item of this output data by value
    void scaleAll(const T& factor);

    //! Adds <rank> axes with indicated sizes
    void setAxisSizes(size_t rank, int *n_dims);

    //! Sets new values to raw data vector
    void setRawDataVector(const std::vector<T>& data_vector);

    //! Sets new values to raw data array
    void setRawDataArray(const T *source);

    //! addition-assignment operator for two output data
    const OutputData<T>& operator+=(const OutputData<T>& right);

    //! substraction-assignment operator for two output data
    const OutputData<T>& operator-=(const OutputData<T>& right);

    //! division-assignment operator for two output data
    const OutputData<T>& operator/=(const OutputData<T>& right);

    //! multiplication-assignment operator for two output data
    const OutputData<T>& operator*=(const OutputData<T>& right);

    //! indexed accessor
    T& operator[](size_t index) {
        if (mp_ll_data) return (*mp_ll_data)[index];
        throw ClassInitializationException("Low-level data object was not yet initialized");
    }

    //! indexed accessor (const)
    const T& operator[](size_t index) const {
        if (mp_ll_data) return (*mp_ll_data)[index];
        throw ClassInitializationException("Low-level data object was not yet initialized");
    }

    // --------
    // helpers
    // --------

    //! Returns true if object have same dimensions and number of axes bins
    template <class U> bool hasSameDimensions(const OutputData<U>& right) const;

    //! Returns true if objects a) have same dimensions b) bin boundaries of axes coincide
    template <class U> bool hasSameShape(const OutputData<U>& right) const;

    //! returns data as Python numpy array
#ifdef BORNAGAIN_PYTHON
    PyObject *getArray() const;
#endif

    //! returns true if object is correctly initialized
    bool isInitialized() const;
private:
    //! disabled copy constructor and assignment operators
    OutputData(const OutputData& );
    const OutputData& operator=(const OutputData& );

    //! memory allocation for current dimensions configuration
    void allocate();

    SafePointerVector<IAxis> m_value_axes;
    LLData<T> *mp_ll_data;
    Mask *mp_mask;
};

/* ***************************************************************************/
// Implementation
/* ***************************************************************************/

template <class T>
OutputData<T>::OutputData()
: m_value_axes()
, mp_ll_data(0)
, mp_mask(0)
{
    allocate();
}

template <class T> OutputData<T>::~OutputData() {
    clear();
    delete mp_ll_data;
}

template <class T>
OutputData<T>* OutputData<T>::clone() const
{
    OutputData<T>* p_result = new OutputData<T>();
    p_result->m_value_axes = m_value_axes;
    (*p_result->mp_ll_data) = *mp_ll_data;
    if (mp_mask)
        p_result->mp_mask = mp_mask->clone();
    return p_result;
}

template <class T>
void OutputData<T>::copyFrom(const OutputData<T>& other)
{
    clear();
    m_value_axes = other.m_value_axes;
    delete mp_ll_data;
    mp_ll_data = 0;
    if(other.mp_ll_data)
        mp_ll_data = new LLData<T>(*other.mp_ll_data);
    if (other.getMask())
        mp_mask = other.getMask()->clone();
}

template <class T>
template <class U>
void OutputData<T>::copyShapeFrom(const OutputData<U>& other)
{
    clear();
    size_t rank = other.getRank();
    for (size_t i=0; i<rank; ++i) {
        addAxis(*other.getAxis(i));
    }
    if (other.getMask())
        mp_mask = other.getMask()->clone();
}


template <class T>
void OutputData<T>::addAxis(const IAxis& new_axis)
{
    if( getAxis(new_axis.getName()) )
        throw LogicErrorException(
            "OutputData<T>::addAxis(const IAxis& new_axis) -> "
            "Error! Attempt to add axis with already existing name '" +
            new_axis.getName() + "'");
    if (new_axis.getSize()>0) {
        m_value_axes.push_back(new_axis.clone());
        allocate();
    }
}

template <class T>
void OutputData<T>::addAxis(const std::string& name, size_t size,
                            double start, double end)
{
    if( getAxis(name) )
        throw LogicErrorException(
            "OutputData<T>::addAxis(std::string name) -> "
            "Error! Attempt to add axis with already existing name '" +
            name+"'");
    FixedBinAxis new_axis(name, size, start, end);
    addAxis(new_axis);
}

template <class T>
const IAxis *OutputData<T>::getAxis(size_t serial_number) const
{
    return m_value_axes[serial_number];
}

template <class T>
const IAxis *OutputData<T>::getAxis(const std::string& axis_name) const
{
    for (size_t i = 0; i < m_value_axes.size(); ++i) {
        if (m_value_axes[i]->getName() == axis_name) {
            return m_value_axes[i];
        }
    }
    return 0;
}

// return index of axis
template <class T>
size_t OutputData<T>::getAxisSerialNumber(const std::string &axis_name) const
{
    for (size_t i = 0; i < m_value_axes.size(); ++i) {
        if (m_value_axes[i]->getName() == axis_name) return i;
    }
    throw LogicErrorException(
        "OutputData<T>::getAxisSerialNumber() -> "
        "Error! Axis with given name not found '"+axis_name+std::string("'"));
}


template<class T>
inline std::vector<size_t> OutputData<T>::getAllSizes() const
{
    assert(mp_ll_data);
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
    assert(mp_ll_data);
    std::vector<T> result;
    for (size_t i=0; i<getAllocatedSize(); ++i)
        result.push_back((*mp_ll_data)[i]);
    return result;
}

template <class T>
void OutputData<T>::fillRawDataArray(T *destination) const
{
    assert(mp_ll_data);
    for (size_t i=0; i<getAllocatedSize(); ++i)
        destination[i] = (*mp_ll_data)[i];
    return;
}

template <class T>
typename OutputData<T>::iterator OutputData<T>::begin()
{
    typename OutputData<T>::iterator result(this);
    if (mp_mask)
        result.setMask(*mp_mask);
    return result;
}

template <class T>
typename OutputData<T>::const_iterator OutputData<T>::begin() const
{
    typename OutputData<T>::const_iterator result(this);
    if (mp_mask)
        result.setMask(*mp_mask);
    return result;
}

template <class T>
void OutputData<T>::setMask(const Mask& mask)
{
    if (mp_mask !=& mask) {
        delete mp_mask;
        mp_mask = mask.clone();
        mp_mask->setMaxIndex(getAllocatedSize());
    }
}

template <class T>
void OutputData<T>::addMask(const Mask& mask)
{
    if (mask.mp_submask) {
        throw RuntimeErrorException(
            "OutputData<T>::addMask() -> "
            "Error! One can only add single masks to OutputDataIterator "
            "at a time");
    }
    Mask *p_old_mask = getMask();
    mp_mask = mask.clone();
    mp_mask->mp_submask = p_old_mask;
    mp_mask->setMaxIndex(getAllocatedSize());
}

template<class T>
void OutputData<T>::removeAllMasks()
{
    delete mp_mask;
    mp_mask = 0;
}

template<class T>
std::vector<int> OutputData<T>::getAxesBinIndices(size_t global_index) const
{
    assert(mp_ll_data);
    size_t remainder = global_index;
    std::vector<int> result;
    result.resize(mp_ll_data->getRank());
    for (size_t i=0; i<mp_ll_data->getRank(); ++i)
    {
        result[mp_ll_data->getRank()-1-i] =
            (int)(remainder %
                  m_value_axes[mp_ll_data->getRank()-1-i]->getSize());
        remainder /= m_value_axes[mp_ll_data->getRank()-1-i]->getSize();
    }
    return result;
}

template<class T>
int OutputData<T>::getAxisBinIndex(size_t global_index, size_t i_selected_axis) const
{
    assert(mp_ll_data);
    size_t remainder(global_index);
    for (size_t i=0; i<mp_ll_data->getRank(); ++i)
    {
        size_t i_axis = mp_ll_data->getRank()-1-i;
        int result = (int)(remainder % m_value_axes[i_axis]->getSize());
        if(i_selected_axis == i_axis ) return result;
        remainder /= m_value_axes[i_axis]->getSize();
    }
    throw LogicErrorException("OutputData<T>::getAxisBinIndex() -> "
                              "Error! No axis with given number");
}


template<class T>
int OutputData<T>::getAxisBinIndex(size_t global_index, const std::string &axis_name) const
{
    return getAxisBinIndex(global_index, getAxisSerialNumber(axis_name));
}

template <class T>
size_t OutputData<T>::toGlobalIndex(const std::vector<int> &axes_indices) const
{
    assert(mp_ll_data);
    if (axes_indices.size() != mp_ll_data->getRank())
        throw LogicErrorException(
                    "size_t OutputData<T>::toGlobalIndex() -> "
                    "Error! Number of coordinates must match "
                    "rank of data structure");
    size_t result = 0;
    int step_size = 1;
    for (size_t i=mp_ll_data->getRank(); i>0; --i)
    {
        if(axes_indices[i-1] < 0 || axes_indices[i-1] >= (int)m_value_axes[i-1]->getSize()) {
            std::ostringstream message;
            message << "size_t OutputData<T>::toGlobalIndex() -> Error. Index ";
            message << axes_indices[i-1] << " is out of range. Axis ";
            message << m_value_axes[i-1]->getName();
            message << " size " << m_value_axes[i-1]->getSize() << ".\n";
            throw LogicErrorException(message.str());
        }
        result += axes_indices[i-1]*step_size;
        step_size *= m_value_axes[i-1]->getSize();
    }
    return result;
}


template <class T>
size_t OutputData<T>::findGlobalIndex(const std::vector<double> &coordinates) const
{
    assert(mp_ll_data);
    if (coordinates.size() != mp_ll_data->getRank())
        throw LogicErrorException(
                    "OutputData<T>::findClosestIndex() -> "
                    "Error! Number of coordinates must match "
                    "rank of data structure");
    std::vector<int> axes_indexes;
    axes_indexes.resize(mp_ll_data->getRank());
    for(size_t i = 0; i<mp_ll_data->getRank(); ++i) {
        axes_indexes[i] = m_value_axes[i]->findClosestIndex(coordinates[i]);
    }
    return toGlobalIndex(axes_indexes);
}

template <class T>
double OutputData<T>::getAxisValue(size_t global_index, size_t i_selected_axis) const
{
    int axis_index = getAxisBinIndex(global_index, i_selected_axis);
    return (*m_value_axes[i_selected_axis])[axis_index];
}

template <class T>
double OutputData<T>::getAxisValue(size_t global_index, const std::string& axis_name) const
{
    return getAxisValue(global_index, getAxisSerialNumber(axis_name));
}

template <class T>
std::vector<double> OutputData<T>::getAxesValues(size_t global_index) const
{
    std::vector<int> indices = getAxesBinIndices(global_index);
    std::vector<double > result;
    for(size_t i_axis=0; i_axis<indices.size(); ++i_axis) {
        result.push_back((*m_value_axes[i_axis])[indices[i_axis]]);
    }
    return result;
}

template <class T>
Bin1D OutputData<T>::getAxisBin(size_t global_index, size_t i_selected_axis) const
{
    int axis_index = getAxisBinIndex(global_index, i_selected_axis);
    return m_value_axes[i_selected_axis]->getBin(axis_index);
}

template <class T>
Bin1D OutputData<T>::getAxisBin(size_t global_index, const std::string& axis_name) const
{
    return getAxisBin(global_index, getAxisSerialNumber(axis_name));
}

template<class T>
inline T OutputData<T>::totalSum() const
{
    assert(mp_ll_data);
    return mp_ll_data->getTotalSum();
}

template <class T>
void OutputData<T>::clear()
{
    m_value_axes.clear();
    delete mp_mask;
    mp_mask = 0;
    allocate();
}

template <class T>
void OutputData<T>::setAllTo(const T& value)
{
    if(!mp_ll_data)
        throw ClassInitializationException("OutputData::setAllTo() -> Error! Low-level data object was not yet initialized.");
    mp_ll_data->setAll(value);
}

template <class T>
void OutputData<T>::scaleAll(const T& factor)
{
    if(!mp_ll_data)
        throw ClassInitializationException("OutputData::scaleAll() -> Error! Low-level data object was not yet initialized.");
    mp_ll_data->scaleAll(factor);
}

template <class T>
void OutputData<T>::setAxisSizes(size_t rank, int *n_dims)
{
    clear();
    std::string basename("axis");
    for (size_t i=0; i<rank; ++i) {
        std::ostringstream name;
        name << basename << i;
        addAxis(name.str(), n_dims[i], 0.0, (double)(n_dims[i]-1));
    }
}

template<class T>
const OutputData<T>& OutputData<T>::operator+=(const OutputData<T>& right)
{
    assert(mp_ll_data);
    *this->mp_ll_data += *right.mp_ll_data;
    return *this;
}

template<class T>
const OutputData<T>& OutputData<T>::operator-=(const OutputData<T>& right)
{
    assert(mp_ll_data);
    *this->mp_ll_data -= *right.mp_ll_data;
    return *this;
}

template<class T>
const OutputData<T>& OutputData<T>::operator*=(const OutputData<T>& right)
{
    assert(mp_ll_data);
    *this->mp_ll_data *= *right.mp_ll_data;
    return *this;
}

template<class T>
bool OutputData<T>::isInitialized() const
{
    if(!mp_ll_data) return false;
    if(getRank() != mp_ll_data->getRank()) return false;
    if(!getRank()) return false;
    return true;
}

template<class T>
const OutputData<T>& OutputData<T>::operator/=(const OutputData<T>& right)
{
    assert(mp_ll_data);
    *this->mp_ll_data /= *right.mp_ll_data;
    return *this;
}

template <class T>
void OutputData<T>::allocate()
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

template<class T>
inline void OutputData<T>::setRawDataVector(const std::vector<T>& data_vector)
{
    if (data_vector.size() != getAllocatedSize()) {
        throw RuntimeErrorException("OutputData<T>::setRawDataVector() -> Error! setRawDataVector can only be called with a data vector of the correct size.");
    }
    for (size_t i=0; i<getAllocatedSize(); ++i) {
        (*mp_ll_data)[i] = data_vector[i];
    }
}

template<class T>
inline void OutputData<T>::setRawDataArray(const T *source)
{
    for (size_t i=0; i<getAllocatedSize(); ++i) {
        (*mp_ll_data)[i] = source[i];
    }
}

//! Returns true if object have same dimensions
template<class T>
template<class U>
inline bool OutputData<T>::hasSameDimensions(
    const OutputData<U>& right) const
{
    if(!isInitialized()) return false;
    if(!right.isInitialized()) return false;
    if(getRank() != right.getRank()) return false;
    for(size_t i_axis=0; i_axis<getRank(); ++i_axis) {
        if(getAxis(i_axis)->getSize() != right.getAxis(i_axis)->getSize()) return false;
    }
    return true;
}

//! Returns true if object have same dimensions and shape of axis
template<class T>
template<class U>
bool OutputData<T>::hasSameShape(const OutputData<U>& right) const
{
    if(!hasSameDimensions(right)) return false;

    for (size_t i=0; i<m_value_axes.size(); ++i) {
        if( !HaveSameNameAndShape(*getAxis(i), *right.getAxis(i))) return false;
    }
    return true;
}

//! returns data as Python numpy array
#ifdef BORNAGAIN_PYTHON
template<> PyObject *OutputData<double>::getArray() const;
#endif

#endif // OUTPUTDATA_H
