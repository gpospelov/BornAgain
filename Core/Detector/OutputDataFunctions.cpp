 // ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Detector/OutputDataFunctions.cpp
//! @brief     Implements class OutputDataFunctions.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "OutputDataFunctions.h"
#include <fftw3.h>

void toFftw3Array(complex_t* source, size_t length, fftw_complex* destination);
void fromFftw3Array(fftw_complex* source, size_t length, complex_t* destination);

//! double the bin size for each dimension.

OutputData<double>* OutputDataFunctions::doubleBinSize(
    const OutputData<double>& source)
{
    OutputData<double>* p_result = new OutputData<double>;
    size_t dimension = source.getRank();
    std::vector<size_t> source_sizes = source.getAllSizes();
    std::vector<bool> needs_resizing;
    // create new axes
    for (size_t i=0; i<dimension; ++i) {
        needs_resizing.push_back(source_sizes[i] > 1);
        const IAxis* source_axis = source.getAxis(i);
        IAxis* p_new_axis = source_axis->createDoubleBinSize();
        p_result->addAxis(*p_new_axis);
        delete p_new_axis;
    }
    // calculate new data content
    OutputData<double>::const_iterator it_source = source.begin();
    while (it_source != source.end()) {
        std::vector<int> source_indices =
                source.getAxesBinIndices(it_source.getIndex());
        std::vector<int> dest_indices;
        double boundary_factor = 1.0;
        for (size_t i=0; i<source_indices.size(); ++i) {
            dest_indices.push_back(source_indices[i]/2);
            if (needs_resizing[i] &&
                    source_sizes[i]%2 == 1 &&
                    source_indices[i] == (int)source_sizes[i]-1) {
                boundary_factor *= 2.0;
            }
        }
        (*p_result)[p_result->toGlobalIndex(dest_indices)] =
                boundary_factor*(*it_source++);
    }
    return p_result;
}

//! Fourier transformation of output data

void OutputDataFunctions::FourierTransform(
    const OutputData<double>& source, OutputData<complex_t>* p_destination)
{
    // initialize dimensions
    std::vector<size_t> dimensions = source.getAllSizes();
    size_t rank = dimensions.size();
    int* n_real_dims = new int[rank];
    int* n_complex_dims = new int[rank];
    size_t total_real_size = 1;
    size_t total_complex_size = 1;
    for (size_t i=0; i<rank; ++i) {
        total_real_size *= (n_real_dims[i] = (int)dimensions[i]);
        if (i<rank-1) total_complex_size *=
                (n_complex_dims[i] = (int)dimensions[i]);
        else total_complex_size *=
                (n_complex_dims[i] = (int)dimensions[i]/2 +1);
    }
    // allocate result
    if (p_destination->getAllocatedSize() != total_complex_size) {
        p_destination->setAxisSizes(rank, n_complex_dims);
    }
    //  initialize temporary arrays
    double* input = fftw_alloc_real(total_real_size);
    fftw_complex* output = fftw_alloc_complex(total_complex_size);
    fftw_plan plan = fftw_plan_dft_r2c((int)rank, n_real_dims, input,
            output, FFTW_ESTIMATE);
    source.fillRawDataArray(input);

    // execute the plan
    fftw_execute(plan);
    // put output into result map
    complex_t* output2 = new complex_t[total_complex_size];
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


//! Fourier back transform

void OutputDataFunctions::FourierTransformR(
    const OutputData<complex_t>& source, OutputData<double>* p_destination)
{
    // initialize dimensions
    std::vector<size_t> dimensions = p_destination->getAllSizes();
    size_t rank = (int)dimensions.size();
    int* n_real_dims = new int[rank];
    int* n_complex_dims = new int[rank];
    size_t total_real_size = 1;
    size_t total_complex_size = 1;
    for (size_t i=0; i<rank; ++i) {
        total_real_size *= (n_real_dims[i] = (int)dimensions[i]);
        if (i<rank-1) total_complex_size *=
                (n_complex_dims[i] = (int)dimensions[i]);
        else total_complex_size *=
                (n_complex_dims[i] = (int)dimensions[i]/2 +1);
    }
    // allocate result
    if (source.getAllocatedSize() != total_complex_size) {
        delete[] n_real_dims;
        delete[] n_complex_dims;
        throw Exceptions::ClassInitializationException("Inverse Fourier transform requires"
                " properly allocated map sizes");
    }
    //  initialize temporary arrays
    double* output = fftw_alloc_real(total_real_size);
    fftw_complex* input = fftw_alloc_complex(total_complex_size);
    fftw_plan plan = fftw_plan_dft_c2r((int)rank, n_real_dims, input, output, FFTW_ESTIMATE);
    complex_t* input2 = new complex_t[total_complex_size];
    source.fillRawDataArray(input2);
    toFftw3Array(input2, total_complex_size, input);
    delete[] input2;

    // execute the plan
    fftw_execute(plan);
    // put output into result map and rescale
    p_destination->setRawDataArray(output);
    double scaling_factor = 1.0/p_destination->getAllocatedSize();
    p_destination->scaleAll(scaling_factor);

    // free allocated objects
    fftw_destroy_plan(plan);
    fftw_free(input);
    fftw_free(output);
    delete[] n_real_dims;
    delete[] n_complex_dims;
}

OutputData<double>* OutputDataFunctions::getRealPart(
    const OutputData<complex_t>& source)
{
    OutputData<double>* p_result = new OutputData<double>();
    for (size_t i=0; i<source.getRank(); ++i) {
        p_result->addAxis(*source.getAxis(i));
    }
    OutputData<complex_t>::const_iterator it_source = source.begin();
    OutputData<double>::iterator it_result = p_result->begin();
    while (it_source != source.end()) {
        *it_result = it_source->real();
        ++it_source, ++it_result;
    }
    return p_result;
}


OutputData<double>* OutputDataFunctions::getImagPart(
    const OutputData<complex_t>& source)
{
    OutputData<double>* p_result = new OutputData<double>();
    for (size_t i=0; i<source.getRank(); ++i) {
        p_result->addAxis(*source.getAxis(i));
    }
    OutputData<complex_t>::const_iterator it_source = source.begin();
    OutputData<double>::iterator it_result = p_result->begin();
    while (it_source != source.end()) {
        *it_result = it_source->imag();
        ++it_source, ++it_result;
    }
    return p_result;
}


OutputData<double>* OutputDataFunctions::getModulusPart(
        const OutputData<complex_t>& source)
{
    OutputData<double>* p_result = new OutputData<double>();
    for (size_t i=0; i<source.getRank(); ++i) {
        p_result->addAxis(*source.getAxis(i));
    }
    OutputData<complex_t>::const_iterator it_source = source.begin();
    OutputData<double>::iterator it_result = p_result->begin();
    while (it_source != source.end()) {
        *it_result = std::abs(*it_source);
        ++it_source, ++it_result;
    }
    return p_result;
}

OutputData<double>* OutputDataFunctions::getComponentData(
        const OutputData<Eigen::Matrix2d>& source, int row, int column)
{
    OutputData<double>* p_result = new OutputData<double>;
    p_result->copyShapeFrom(source);

    // no iterators to avoid use of masks
    size_t nbr_elements = source.getAllocatedSize();
    for (size_t i=0; i<nbr_elements; ++i) {
        (*p_result)[i] = source[i](row, column);
    }
    return p_result;
}

OutputData<Eigen::Matrix2d>* OutputDataFunctions::createFromComponents(
        const OutputData<double>& component_00,
        const OutputData<double>& component_01,
        const OutputData<double>& component_10,
        const OutputData<double>& component_11)
{
    if (!component_00.hasSameShape(component_01)
     || !component_00.hasSameShape(component_10)
     || !component_00.hasSameShape(component_11) ) {
        return 0;
    }
    OutputData<Eigen::Matrix2d>* p_result = new OutputData<Eigen::Matrix2d>;
    p_result->copyShapeFrom(component_00);

    // no iterators to avoid use of masks
    size_t nbr_elements = component_00.getAllocatedSize();
    for (size_t i=0; i<nbr_elements; ++i) {
        (*p_result)[i](0,0) = component_00[i];
        (*p_result)[i](0,1) = component_01[i];
        (*p_result)[i](1,0) = component_10[i];
        (*p_result)[i](1,1) = component_11[i];
    }
    return p_result;
}

//! Slice data, having one bin on selected axis fixed.
//!
//! Resulting output data will have one axis less
//! (without axis 'fixed_axis_name')
OutputData<double>* OutputDataFunctions::sliceAccrossOneAxis(
    const OutputData<double>& data, const std::string& fixed_axis_name,
    double fixed_axis_value)
{
<<<<<<< 8c6ec7d21339391fcfd36947f7e6c17b2267ff2f:Core/Simulation/OutputDataFunctions.cpp
    if (data.getRank() != 2) {
        throw Exceptions::LogicErrorException("OutputDataFunctions::sliceAccrossOneAxis()"
                " -> Error! It was checked only with number of dimensions"
                " equal 2.");
    }
    if( !data.getAxis(fixed_axis_name) ) {
        throw Exceptions::LogicErrorException("OutputDataFunctions::sliceAccrossOneAxis()"
=======
    if (data.getRank() != 2)
        throw LogicErrorException("OutputDataFunctions::sliceAccrossOneAxis()"
                " -> Error! It was checked only with number of dimensions equal 2.");
    if( !data.getAxis(fixed_axis_name) )
        throw LogicErrorException("OutputDataFunctions::sliceAccrossOneAxis()"
>>>>>>> Much of Core now nicely decoupled.:Core/Detector/OutputDataFunctions.cpp
                " -> Error! No axis with name "+fixed_axis_name);

    OutputData<double>* sliced_data = new OutputData<double>;

    const IAxis* fixed_axis(0);
    int fixed_axis_index(-1);
    for(size_t i_axis=0; i_axis<data.getRank(); i_axis++) {
        const IAxis* axis = data.getAxis(i_axis);
        if( axis->getName() != fixed_axis_name ) {
            sliced_data->addAxis(*axis);
        } else {
            fixed_axis = axis;
            fixed_axis_index = (int)i_axis;
        }
    }

    // finding bin number on fixed_axis which is closest to fixed_axis_value
    size_t nbin_found = fixed_axis->findClosestIndex(fixed_axis_value);

    // filling sliced data structure
    OutputData<double>::const_iterator it_data = data.begin();
    OutputData<double>::iterator it_sliced = sliced_data->begin();
    while (it_data != data.end())
    {
        size_t current_fixed_axis_nbin =
                data.getAxesBinIndices(it_data.getIndex())[fixed_axis_index];
        if( current_fixed_axis_nbin == nbin_found ) {
            *it_sliced = *it_data;
            ++it_sliced;
        }
        ++it_data;
    }

    return sliced_data;

}

//! Select range on one of the axis.

//! Resulting output data will have same number of axes
//!
OutputData<double>* OutputDataFunctions::selectRangeOnOneAxis(
    const OutputData<double>& data, const std::string& selected_axis_name,
    double axis_value1,  double axis_value2)
{
<<<<<<< 8c6ec7d21339391fcfd36947f7e6c17b2267ff2f:Core/Simulation/OutputDataFunctions.cpp
    if (data.getRank() != 2) {
        throw Exceptions::LogicErrorException("OutputDataFunctions::selectRangeOnOneAxis()"
                " -> Error! It was checked only with number of dimensions"
                " equal 2.");
    }

    const IAxis *selected_axis = data.getAxis(selected_axis_name);
    if( !selected_axis ) {
        throw Exceptions::LogicErrorException("OutputDataFunctions::selectRangeOnOneAxis()"
=======
    if (data.getRank() != 2)
        throw LogicErrorException("OutputDataFunctions::selectRangeOnOneAxis()"
                " -> Error! It was checked only with number of dimensions equal 2.");

    const IAxis* selected_axis = data.getAxis(selected_axis_name);
    if( !selected_axis )
        throw LogicErrorException("OutputDataFunctions::selectRangeOnOneAxis()"
>>>>>>> Much of Core now nicely decoupled.:Core/Detector/OutputDataFunctions.cpp
                " -> Error! No axis with name "+selected_axis_name);

<<<<<<< 8c6ec7d21339391fcfd36947f7e6c17b2267ff2f:Core/Simulation/OutputDataFunctions.cpp
    if(axis_value2 < axis_value1) {
        throw Exceptions::LogicErrorException("OutputDataFunctions::selectRangeOnOneAxis()"
=======
    if(axis_value2 < axis_value1)
        throw LogicErrorException("OutputDataFunctions::selectRangeOnOneAxis()"
>>>>>>> Much of Core now nicely decoupled.:Core/Detector/OutputDataFunctions.cpp
                " -> Error! Axis range xmax<xmin. ");

    size_t selected_axis_index = data.getAxisSerialNumber(selected_axis_name);
    size_t nbin1 = selected_axis->findClosestIndex(axis_value1);
    size_t nbin2 = selected_axis->findClosestIndex(axis_value2);
    double x1 = (*selected_axis)[nbin1];
    double x2 = (*selected_axis)[nbin2];

    // preparing new data with modified axes
    OutputData<double>* new_data = new OutputData<double>;
    for(size_t i_axis=0; i_axis<data.getRank(); i_axis++) {
        const IAxis* axis = data.getAxis(i_axis);
        if( axis->getName() != selected_axis_name ) {
            new_data->addAxis(*axis);
        } else {
            new_data->addAxis(selected_axis->getName(), nbin2-nbin1+1, x1, x2);
        }
    }
    new_data->setAllTo(0.0);

    // filling new data structure
    OutputData<double>::const_iterator it_data = data.begin();
    OutputData<double>::iterator it_new = new_data->begin();
    while (it_data != data.end())
    {
        std::vector<int> orig_coord = data.getAxesBinIndices(it_data.getIndex());
        size_t xbin = orig_coord[selected_axis_index];
        if( xbin>=nbin1 && xbin <= nbin2 ) {
//            std::vector<int> new_coord = orig_coord;
//            new_coord[selected_axis_index] = xbin - nbin1;
//            size_t general_index = new_data->toIndex(new_coord);
            *it_new = *it_data;
            ++it_new;
        }
        ++it_data;
    }
    return new_data;
}


void toFftw3Array(complex_t* source, size_t length, fftw_complex* destination)
{
    for (size_t i=0; i<length; ++i) {
        destination[i][0] = source[i].real();
        destination[i][1] = source[i].imag();
    }
}


void fromFftw3Array(fftw_complex* source, size_t length, complex_t* destination)
{
    for (size_t i=0; i<length; ++i) {
        destination[i] = complex_t( source[i][0], source[i][1] );
    }
}

//! apply intensity function to values stored in output data

void OutputDataFunctions::applyFunction(OutputData<double>& data, const IIntensityFunction* func)
{
    OutputData<double>::iterator it = data.begin();
    while (it != data.end()) {
        double value = *it;
        *it = func->evaluate(value);
        ++it;
    }
}
