// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/inc/OutputDataFunctions.h
//! @brief     Defines functions in namespace OutputDataFunctions.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef OUTPUTDATAFUNCTIONS_H
#define OUTPUTDATAFUNCTIONS_H

#include "WinDllMacros.h"
#include "Types.h"
#include "OutputData.h"
#include "IIntensityFunction.h"
#include "Mask.h"
#include "EigenCore.h"

//! Collection of functions to deal with OutputData

namespace OutputDataFunctions
{
    //! double the bin size for each dimension
    BA_CORE_API_ OutputData<double> *doubleBinSize(
            const OutputData<double>& source);

    //! unnormalized Fourier transformation for real data
    BA_CORE_API_ void FourierTransform(
        const OutputData<double>& source, OutputData<complex_t> *p_destination);

    //! unnormalized reverse Fourier transformation for real data
    BA_CORE_API_ void FourierTransformR(
        const OutputData<complex_t>& source, OutputData<double> *p_destination);

    //! reduces the data to the element-wise real, imaginary or modulus part
    BA_CORE_API_ OutputData<double> *getRealPart(
            const OutputData<complex_t>& source);
    BA_CORE_API_ OutputData<double> *getImagPart(
            const OutputData<complex_t>& source);
    BA_CORE_API_ OutputData<double> *getModulusPart(
            const OutputData<complex_t>& source);

#ifndef GCCXML_SKIP_THIS
    //! Selects an element-wise component of the matrix-valued OutputData
    //! structure and returns a new double-valued one
    BA_CORE_API_ OutputData<double> *getComponentData(
            const OutputData<Eigen::Matrix2d> &source, int row, int column);
    //! Assembles a matrix-valued OuputData structure from its component
    //! maps
    BA_CORE_API_ OutputData<Eigen::Matrix2d> *createFromComponents(
            const OutputData<double> &component_00,
            const OutputData<double> &component_01,
            const OutputData<double> &component_10,
            const OutputData<double> &component_11);
#endif

    //! Slice data, having one bin on selected axis fixed. Resulting output
    //! data will have one axis less (without axis 'fixed_axis_name')
    BA_CORE_API_ OutputData<double> *sliceAccrossOneAxis(
        const OutputData<double>& data, const std::string& fixed_axis_name,
        double fixed_axis_value);

    //! Select range on one of the axis. Resulting output data will have same
    //! number of axes
    BA_CORE_API_ OutputData<double> *selectRangeOnOneAxis(
        const OutputData<double>& data, const std::string& selected_axis_name,
        double axis_value1, double axis_value2);

    //! apply intensity function to values stored in output data
    BA_CORE_API_ void applyFunction(
        OutputData<double>& data, const IIntensityFunction *func);

    //! Creates a rectangular mask based on the given OutputData object and
    //! limits
    BA_CORE_API_ Mask *CreateRectangularMask(
        const OutputData<double>& data,
        const double *minima, const double *maxima, bool invert_flag = false);
    BA_CORE_API_ Mask *CreateRectangularMask(
        const OutputData<double>& data,
        double x1, double y1, double x2, double y2, bool invert_flag = false);

    //! Creates a elliptic mask based on the given OutputData object and limits
    BA_CORE_API_ Mask *CreateEllipticMask(
        const OutputData<double>& data,
        const double *center, const double *radii);
    BA_CORE_API_ Mask *CreateEllipticMask(
        const OutputData<double>& data,
        double xc, double yc, double rx, double ry);

    // compare result with reference and return the difference
//    BA_CORE_API_ double GetDifference(const OutputData<double> &result,
//                         const OutputData<double> &reference);
}

#endif // OUTPUTDATAFUNCTIONS_H


