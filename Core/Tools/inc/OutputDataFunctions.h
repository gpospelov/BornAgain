#ifndef OUTPUTDATAFUNCTIONS_H
#define OUTPUTDATAFUNCTIONS_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   OutputDataFunctions.h
//! @brief  Definition of namespace containing function to deal with output data
//! @author Scientific Computing Group at FRM II
//! @date   November 22, 2012

#include "Types.h"
#include "OutputData.h"
#include "IIntensityFunction.h"
#include "Mask.h"

//- -------------------------------------------------------------------
//! @namespace OutputDataFunctions
//! @brief Collection of functions to deal with OutputData
//- -------------------------------------------------------------------
namespace OutputDataFunctions
{

    //! double the bin size for each dimension
    OutputData<double> *doubleBinSize(const OutputData<double> &source);

    //! unnormalized Fourier transformation for real data
    void fourierTransform(const OutputData<double> &source, OutputData<complex_t> *p_destination);

    //! unnormalized reverse Fourier transformation for real data
    void fourierTransformR(const OutputData<complex_t> &source, OutputData<double> *p_destination);

    OutputData<double> *getRealPart(const OutputData<complex_t> &source);
    OutputData<double> *getImagPart(const OutputData<complex_t> &source);
    OutputData<double> *getModulusPart(const OutputData<complex_t> &source);

    //! Slice data, having one bin on selected axis fixed. Resulting output data will have one axis less (without axis 'fixed_axis_name')
    OutputData<double> *sliceAccrossOneAxis(const OutputData<double > &data, const std::string &fixed_axis_name, double fixed_axis_value);

    //! Select range on one of the axis. Resulting output data will have same number of axes
    OutputData<double> *selectRangeOnOneAxis(const OutputData<double > &data, const std::string &selected_axis_name, double axis_value1,  double axis_value2);

    //! apply intensity function to values stored in output data
    void applyFunction(OutputData<double> &data, const IIntensityFunction *func);

    //! create a rectangular mask based on the given OutputData object and limits
    Mask *CreateRectangularMask(const OutputData<double> &data, const double *minima, const double *maxima);
    Mask *CreateRectangularMask(const OutputData<double> &data, double x1, double y1, double x2, double y2);

    //! create a elliptic mask based on the given OutputData object and limits
    Mask *CreateEllipticMask(const OutputData<double> &data, const double *center, const double *radii);
    Mask *CreateEllipticMask(const OutputData<double> &data, double xc, double yc, double rx, double ry);
}


#endif // OUTPUTDATAFUNCTIONS_H
