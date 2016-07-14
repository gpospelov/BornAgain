// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Tools/OutputDataFunctions.h
//! @brief     Declares functions in namespace OutputDataFunctions.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef OUTPUTDATAFUNCTIONS_H
#define OUTPUTDATAFUNCTIONS_H

#include "Complex.h"
#include "IIntensityFunction.h"
#include "OutputData.h"

//! Collection of functions to deal with OutputData

namespace OutputDataFunctions
{
    //! double the bin size for each dimension
    BA_CORE_API_ OutputData<double>* doubleBinSize(const OutputData<double>& source);

    //! unnormalized Fourier transformation for real data
    BA_CORE_API_ void FourierTransform(
        const OutputData<double>& source, OutputData<complex_t>* p_destination);

    //! unnormalized reverse Fourier transformation for real data
    BA_CORE_API_ void FourierTransformR(
        const OutputData<complex_t>& source, OutputData<double>* p_destination);

    //! reduces the data to the element-wise real, imaginary or modulus part
    BA_CORE_API_ OutputData<double>* getRealPart(const OutputData<complex_t>& source);
    BA_CORE_API_ OutputData<double>* getImagPart(const OutputData<complex_t>& source);
    BA_CORE_API_ OutputData<double>* getModulusPart(const OutputData<complex_t>& source);

#ifndef SWIG
    //! Selects an element-wise component of the matrix-valued OutputData
    //! structure and returns a new double-valued one
    BA_CORE_API_ OutputData<double>* getComponentData(
        const OutputData<Eigen::Matrix2d>& source, int row, int column);
    //! Assembles a matrix-valued OuputData structure from its component maps
    BA_CORE_API_ OutputData<Eigen::Matrix2d>* createFromComponents(
        const OutputData<double>& component_00,
        const OutputData<double>& component_01,
        const OutputData<double>& component_10,
        const OutputData<double>& component_11);
#endif

    //! Slice data, having one bin on selected axis fixed. Resulting output
    //! data will have one axis less (without axis 'fixed_axis_name')
    BA_CORE_API_ OutputData<double>* sliceAccrossOneAxis(
        const OutputData<double>& data, const std::string& fixed_axis_name,
        double fixed_axis_value);

    //! Select range on one of the axis. Resulting output data will have same
    //! number of axes
    BA_CORE_API_ OutputData<double>* selectRangeOnOneAxis(
        const OutputData<double>& data, const std::string& selected_axis_name,
        double axis_value1, double axis_value2);

    //! apply intensity function to values stored in output data
    BA_CORE_API_ void applyFunction(OutputData<double>& data, const IIntensityFunction* func);
}

#endif // OUTPUTDATAFUNCTIONS_H
