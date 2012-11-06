#include "OutputData.h"
#include "Exceptions.h"
#include "Numeric.h"
#include <cmath>
#include <fftw3.h>


void toFftw3Array(complex_t *source, size_t length, fftw_complex *destination);
void fromFftw3Array(fftw_complex *source, size_t length, complex_t *destination);

/* ************************************************************************* */
//
/* ************************************************************************* */
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


/* ************************************************************************* */
//
/* ************************************************************************* */
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


/* ************************************************************************* */
//
/* ************************************************************************* */
std::vector<size_t> MultiIndex::getCurrentIndices()
{
    updateCurrentIndices();
    return m_current_coordinate;
}


/* ************************************************************************* */
//
/* ************************************************************************* */
size_t MultiIndex::getCurrentIndexOfAxis(std::string axis_name)
{
    if (m_label_index_map.count(axis_name) == 0)
    {
        std::string message = "MultiIndex::getCurrentIndexOfAxis() -> Error! Label not found: " + axis_name;
        throw NullPointerException(message);
    }
    return getCurrentIndices()[m_label_index_map.find(axis_name)->second];
}


/* ************************************************************************* */
//
/* ************************************************************************* */
void MultiIndex::reset()
{
    m_current_position = 0;
    m_end_passed = false;
    updateCurrentIndices();
}


/* ************************************************************************* */
//
/* ************************************************************************* */
void MultiIndex::updateCurrentIndices()
{
    size_t remainder = m_current_position;
    for (size_t i=0; i<m_dimension; ++i)
    {
        m_current_coordinate[m_dimension-1-i] = remainder % m_axis_sizes[m_dimension-1-i];
        remainder /= m_axis_sizes[m_dimension-1-i];
    }
}


/* ************************************************************************* */
//
/* ************************************************************************* */
void MultiIndex::updateCurrentPosition()
{
    m_end_passed = false;
    m_current_position = 0;
    for (size_t i=0; i<m_dimension; ++i)
    {
        m_current_position += m_current_coordinate[i]*m_steps[i];
    }
}


/* ************************************************************************* */
//
/* ************************************************************************* */
void MultiIndex::setPosition(size_t position)
{
    if (position>=m_total_size) {
        throw OutOfBoundsException("MultiIndex::setPosition() -> Error! Position value out of bounds!");
    }
    m_current_position = position;
    updateCurrentIndices();
}



/* ************************************************************************* */
//
/* ************************************************************************* */
void MultiIndex::setIndexOfAxis(std::string axis_name, size_t value)
{
    if (m_label_index_map.count(axis_name) == 0) return;
    size_t index = m_label_index_map[axis_name];
    if (value >= m_axis_sizes[index])
    {
        throw OutOfBoundsException(" MultiIndex::setIndexOfAxis() -> Coordinate value out of bounds!");
    }
    m_current_coordinate[index] = value;
    updateCurrentPosition();
}

/* ************************************************************************* */
//
/* ************************************************************************* */
void MultiIndex::setAllIndices(std::vector<size_t> indices)
{
    if (indices.size()!=m_dimension) {
        throw OutOfBoundsException(" MultiIndex::setAllIndices() -> Indices vector not of the right size!");
    }
    m_current_coordinate = indices;
    updateCurrentPosition();
}

/* ************************************************************************* */
//
/* ************************************************************************* */
void MultiIndex::incrementIndexOfAxis(std::string axis_name)
{
    if (m_label_index_map.count(axis_name) == 0) return;
    size_t index = m_label_index_map[axis_name];
    if (m_current_coordinate[index] < m_axis_sizes[index]-2)
    {
        ++m_current_coordinate[index];
        updateCurrentPosition();
        return;
    }
    throw OutOfBoundsException("MultiIndex::incrementIndexOfAxis() -> Error! Coordinate value out of bounds!");
}


/* ************************************************************************* */
//
/* ************************************************************************* */
void MultiIndex::decrementIndexOfAxis(std::string axis_name)
{
    if (m_label_index_map.count(axis_name) == 0) return;
    size_t index = m_label_index_map[axis_name];
    if (m_current_coordinate[index] > 1)
    {
        --m_current_coordinate[index];
        updateCurrentPosition();
        return;
    }
    throw OutOfBoundsException("MultiIndex::decrementIndexOfAxis() -> Error! Coordinate value out of bounds!");
}


/* ************************************************************************* */
//
/* ************************************************************************* */
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
            throw ClassInitializationException("MultiIndex::init() -> Error! Axis labels for OutputData object should be unique!");
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


/* ************************************************************************* */
//
/* ************************************************************************* */
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


/* ************************************************************************* */
// addition-assignment operator for two output data
/* ************************************************************************* */
const OutputData<double> &operator+=(OutputData<double> &left, const OutputData<double> &right)
{
    if( &left == &right) throw LogicErrorException("OutputData &operator+=() -> Error. Left And right can't be the same");

    size_t total_size = left.getAllocatedSize();
    if (right.getAllocatedSize()!= total_size) {
        throw LogicErrorException("OutputData<double> &operator+=() -> Error! Cannot add OutputData objects of different size.");
    }
    left.resetIndex();
    right.resetIndex();
    while (right.hasNext()) {
        left.currentValue() += right.currentValue();
        left.next(); right.next();
    }
    return left;
}


/* ************************************************************************* */
// substraction-assignment operator for two output data
/* ************************************************************************* */
const OutputData<double> &operator-=(OutputData<double> &left, const OutputData<double> &right)
{
    if( &left == &right) throw LogicErrorException("OutputData &operator-=() -> Error. Left And right can't be the same");

    size_t total_size = left.getAllocatedSize();
    if (right.getAllocatedSize()!= total_size) {
        throw LogicErrorException("OutputData<double> &operator-=() -> Error! Cannot substract OutputData objects of different size.");
    }
    left.resetIndex();
    right.resetIndex();
    while (right.hasNext()) {
        left.currentValue() -= right.currentValue();
        left.next(); right.next();
    }
    return left;
}


/* ************************************************************************* */
// division-assignment operator for two output data
/* ************************************************************************* */
const OutputData<double> &operator/=(OutputData<double> &left, const OutputData<double> &right)
{
    if( &left == &right) throw LogicErrorException("OutputData &operator/=() -> Error. Left And right can't be the same");

    size_t total_size = left.getAllocatedSize();
    if (right.getAllocatedSize()!= total_size) {
        throw LogicErrorException("OutputData<double> &operator/=() -> Error! Cannot substract OutputData objects of different size.");
    }
    left.resetIndex();
    right.resetIndex();
    while ( right.hasNext() ) {
        double xleft = left.currentValue();
        double xright = right.currentValue();
        double ratio(0);
        if( fabs(xleft) <= Numeric::double_epsilon && fabs(xright) <= Numeric::double_epsilon) {
            ratio = 0.0;
        } else if (fabs(xright) <= Numeric::double_epsilon) {
            ratio = xleft/Numeric::double_epsilon;
        } else {
            ratio = xleft/xright;
        }
        left.currentValue() = ratio;
        left.next(); right.next();
    }
    return left;
}

/* ************************************************************************* */
// multiplication-assignment operator for two output data
/* ************************************************************************* */
const OutputData<double> &operator*=(OutputData<double> &left, const OutputData<double> &right)
{
    if( &left == &right) throw LogicErrorException("OutputData &operator*=() -> Error. Left And right can't be the same");

    size_t total_size = left.getAllocatedSize();
    if (right.getAllocatedSize()!= total_size) {
        throw LogicErrorException("OutputData<double> &operator/=() -> Error! Cannot substract OutputData objects of different size.");
    }
    left.resetIndex();
    right.resetIndex();
    while ( right.hasNext() ) {
        double xleft = left.currentValue();
        double xright = right.currentValue();
        left.currentValue() = xleft*xright;
        left.next(); right.next();
    }
    return left;
}

/* ************************************************************************* */
// double the bin size for each dimension
/* ************************************************************************* */
OutputData<double> *doubleBinSize(const OutputData<double> &source)
{
    OutputData<double> *p_result = new OutputData<double>;
    size_t dimension = source.getDimension();
    std::vector<size_t> source_sizes = source.getAllSizes();
    std::vector<bool> needs_resizing;
    // create new axes
    for (size_t i=0; i<dimension; ++i) {
        needs_resizing.push_back(source_sizes[i] > 1);
        const NamedVector<double> *source_axis = dynamic_cast<const NamedVector<double> *>(source.getAxis(i));
        p_result->addAxis(source_axis->createDoubleBinSize());
    }
    // calculate new data content
    source.resetIndex();
    MultiIndex &source_index = source.getIndex();
    MultiIndex &result_index = p_result->getIndex();
    while (source.hasNext()) {
        std::vector<size_t> source_indices = source_index.getCurrentIndices();
        std::vector<size_t> dest_indices;
        double boundary_factor = 1.0;
        for (size_t i=0; i<source_indices.size(); ++i) {
            dest_indices.push_back(source_indices[i]/2);
            if (needs_resizing[i] &&
                    source_sizes[i]%2 == 1 &&
                    source_indices[i] == source_sizes[i]-1) {
                boundary_factor *= 2.0;
            }
        }
        result_index.setAllIndices(dest_indices);
        p_result->currentValue() = boundary_factor*source.next();
    }
    return p_result;
}

void fourierTransform(const OutputData<double>& source, OutputData<complex_t> *p_destination)
{
    // initialize dimensions
    std::vector<size_t> dimensions = source.getAllSizes();
    size_t rank = dimensions.size();
    int *n_real_dims = new int[rank];
    int *n_complex_dims = new int[rank];
    size_t total_real_size = 1;
    size_t total_complex_size = 1;
    for (size_t i=0; i<rank; ++i) {
        total_real_size *= (n_real_dims[i] = (int)dimensions[i]);
        if (i<rank-1) total_complex_size *= (n_complex_dims[i] = (int)dimensions[i]);
        else total_complex_size *= (n_complex_dims[i] = (int)dimensions[i]/2 +1);
    }
    // allocate result
    if (p_destination->getAllocatedSize() != total_complex_size) {
        p_destination->setAxisSizes(rank, n_complex_dims);
    }
    //  initialize temporary arrays
    double *input = fftw_alloc_real(total_real_size);
    fftw_complex *output = fftw_alloc_complex(total_complex_size);
    fftw_plan plan = fftw_plan_dft_r2c(rank, n_real_dims, input, output, FFTW_ESTIMATE);
    source.fillRawDataArray(input);

    // execute the plan
    fftw_execute(plan);
    // put output into result map
    complex_t *output2 = new complex_t[total_complex_size];
    fromFftw3Array(output, total_complex_size, output2);
    p_destination->setRawDataArray(output2);
    delete[] output2;

    // free allocated objects
    fftw_destroy_plan(plan);
    fftw_free(input);
    fftw_free(output);
    delete[] n_real_dims;
    delete[] n_complex_dims;
}

void fourierTransformR(const OutputData<complex_t>& source, OutputData<double> *p_destination)
{
    // initialize dimensions
    std::vector<size_t> dimensions = p_destination->getAllSizes();
    size_t rank = (int)dimensions.size();
    int *n_real_dims = new int[rank];
    int *n_complex_dims = new int[rank];
    size_t total_real_size = 1;
    size_t total_complex_size = 1;
    for (size_t i=0; i<rank; ++i) {
        total_real_size *= (n_real_dims[i] = (int)dimensions[i]);
        if (i<rank-1) total_complex_size *= (n_complex_dims[i] = (int)dimensions[i]);
        else total_complex_size *= (n_complex_dims[i] = (int)dimensions[i]/2 +1);
    }
    // allocate result
    if (source.getAllocatedSize() != total_complex_size) {
        throw ClassInitializationException("Inverse Fourier transform requires properly allocated map sizes");
    }
    //  initialize temporary arrays
    double *output = fftw_alloc_real(total_real_size);
    fftw_complex *input = fftw_alloc_complex(total_complex_size);
    fftw_plan plan = fftw_plan_dft_c2r(rank, n_real_dims, input, output, FFTW_ESTIMATE);
    complex_t *input2 = new complex_t[total_complex_size];
    source.fillRawDataArray(input2);
    toFftw3Array(input2, total_complex_size, input);
    delete[] input2;

    // execute the plan
    fftw_execute(plan);
    // put output into result map
    p_destination->setRawDataArray(output);

    // free allocated objects
    fftw_destroy_plan(plan);
    fftw_free(input);
    fftw_free(output);
    delete[] n_real_dims;
    delete[] n_complex_dims;
}

void toFftw3Array(complex_t *source, size_t length, fftw_complex *destination)
{
    for (size_t i=0; i<length; ++i) {
        destination[i][0] = source[i].real();
        destination[i][1] = source[i].imag();
    }
}

void fromFftw3Array(fftw_complex *source, size_t length, complex_t *destination)
{
    for (size_t i=0; i<length; ++i) {
        destination[i].real() = source[i][0];
        destination[i].imag() = source[i][1];
    }
}
