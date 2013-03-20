// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      PythonAPI/src/PythonOutputData.cpp
//! @brief     Implements a few global functions: GetOutputDataNdimensions,
//!              GetOutputData, GetOutputDataAxis
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#include "Python.h"
#define PY_ARRAY_UNIQUE_SYMBOL BORNAGAIN_PYTHONAPI_ARRAY
#define NO_IMPORT_ARRAY
#include "numpy/arrayobject.h"
// the order of 4 guys above is important, see explanation in PythonAPI/src/PythonModule.cpp

#include "PythonOutputData.h"
#include "OutputData.h"
#include "Exceptions.h"

#include <iostream>
#include <vector>

// export output data array to python-numpy array object
PyObject *ExportOutputData(const OutputData<double > &output);

// export axis of output data array as python-numpy array object
PyObject *ExportOutputDataAxis(const OutputData<double > &output, int naxis);

//! return number of dimensions in output data of simulation

int GetOutputDataNdimensions(const Simulation &simulation)
{
    const OutputData<double > *data = simulation.getOutputData();
    int ndims = data->getNdimensions();
    return ndims;
}

//! export output data array of simulation to python-numpy array object

PyObject *GetOutputData(const Simulation &simulation)
{
    const OutputData<double > *data = simulation.getOutputData();
    PyObject *obj = ExportOutputData(*data);
    return obj;
}

//! return one-dim numpy array representing binning of the axis with given index of simulation's output data

PyObject *GetOutputDataAxis(const Simulation &simulation, int naxis)
{
    const OutputData<double > *data = simulation.getOutputData();
    PyObject *obj = ExportOutputDataAxis(*data, naxis);
    return obj;
}

//! export axis of output data array as python-numpy array object

PyObject *ExportOutputData(const OutputData<double > &output_data)
{
    // getting size of dimensions from output_data
    std::vector<int > dimensions;
    for(size_t i=0; i<output_data.getNdimensions(); i++) {
        //const AxisDouble *axis = output_data.getAxis(i);
        const IAxis *axis = output_data.getAxis(i);
        dimensions.push_back( axis->getSize() );
    }

    // creating ndarray objects describing size of dimensions
    npy_int ndim_numpy= dimensions.size();
    npy_intp *ndimsizes_numpy = new npy_intp[dimensions.size()];
    //npy_intp *ndimsizes_numpy = (npy_intp *) malloc(sizeof(npy_intp)*dimensions.size());
     for(size_t i=0; i<dimensions.size(); i++) {
        ndimsizes_numpy[i] = dimensions[i];
    }

    // creating standalone numpy array
    PyObject *pyarray = PyArray_SimpleNew(ndim_numpy, ndimsizes_numpy, NPY_DOUBLE);
    delete [] ndimsizes_numpy;
    if(pyarray == NULL ) {
        throw RuntimeErrorException("ExportOutputData() -> Panic in PyArray_SimpleNew");
    }
    Py_INCREF(pyarray);

    // getting pointer to data buffer of numpy array
    double *array_buffer = (double *)PyArray_DATA(pyarray);

    // filling numpy array with output_data
    OutputData<double>::const_iterator it = output_data.begin();
    while(it != output_data.end() ) {
        *array_buffer++ = *it++;
    }

    return pyarray;
}

//! return one dimensional python-numpy array representing binning of given axis of oputput data object

PyObject *ExportOutputDataAxis(const OutputData<double > &output_data, int naxis)
{
    // getting size of dimensions from output_data
    std::vector<int > dimensions;
    for(size_t i=0; i<output_data.getNdimensions(); i++) {
        const IAxis *axis = output_data.getAxis(i);
        dimensions.push_back( axis->getSize() );
    }
    size_t nbins(0);
    if (naxis < (int) dimensions.size() ) {
        nbins = dimensions[naxis];
    } else {
        throw OutOfBoundsException("ExportOutputDataAxis() -> Error. Wrong axis number");
    }

    // creating ndarray objects describing size of dimensions, in given case it is one dimensional array, with length=1
    npy_int ndim_numpy= 1;
    npy_intp ndimsizes_numpy[1];
    ndimsizes_numpy[0] = nbins;

    // creating standalone numpy array
    PyObject *pyarray = PyArray_SimpleNew(ndim_numpy, ndimsizes_numpy, NPY_DOUBLE);
    if(pyarray == NULL ) {
        throw RuntimeErrorException("ExportOutputDataAxis() -> Panic in in PyArray_SimpleNew");
    }
    Py_INCREF(pyarray);

    // getting pointer to data buffer of numpy array
    double *array_buffer = (double *)PyArray_DATA(pyarray);

    // filling numpy array with output_data
    const IAxis *axis = output_data.getAxis(naxis);
    for(size_t i=0; i<nbins; i++) {
        *array_buffer++ = (*axis)[i];
    }
    return pyarray;
}
