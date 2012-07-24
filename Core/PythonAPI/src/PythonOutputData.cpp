#include "Python.h"
#define PY_ARRAY_UNIQUE_SYMBOL scatt_ARRAY_API
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



/* ************************************************************************* */
// return number of dimensions in output data of GISASExperiment
/* ************************************************************************* */
int GetOutputDataNdimensions(const GISASExperiment &experiment)
{
    OutputData<double > *data = experiment.getOutputData();
    int ndims = data->getNdimensions();
    delete data;
    return ndims;
}


/* ************************************************************************* */
// export output data array of GISASExperiment to python-numpy array object
/* ************************************************************************* */
PyObject *GetOutputData(const GISASExperiment &experiment)
{
    OutputData<double > *data = experiment.getOutputData();
    PyObject *obj = ExportOutputData(*data);
    delete data;
    return obj;
}


/* ************************************************************************* */
// return one dimensional python-numpy array representing binning of the axis
// with given index of GISASExperiment's oputput data
/* ************************************************************************* */
PyObject *GetOutputDataAxis(const GISASExperiment &experiment, int naxis)
{
    OutputData<double > *data = experiment.getOutputData();
    PyObject *obj = ExportOutputDataAxis(*data, naxis);
    delete data;
    return obj;
}


/* ************************************************************************* */
// export axis of output data array as python-numpy array object
/* ************************************************************************* */
PyObject *ExportOutputData(const OutputData<double > &output_data)
{
    // getting size of dimensions from output_data
    std::vector<int > dimensions;
    for(size_t i=0; i<output_data.getNdimensions(); i++) {
        const NamedVector<double> *axis = dynamic_cast<const NamedVector<double>*>(output_data.getAxes()[i]);
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
    output_data.resetIndex();
    while(output_data.hasNext() ) {
        *array_buffer++ = output_data.next();
    }

    return pyarray;
}


/* ************************************************************************* */
// return one dimensional python-numpy array representing binning of given axis
// of oputput data object
/* ************************************************************************* */
PyObject *ExportOutputDataAxis(const OutputData<double > &output_data, int naxis)
{
    // getting size of dimensions from output_data
    std::vector<int > dimensions;
    for(size_t i=0; i<output_data.getNdimensions(); i++) {
        const NamedVector<double> *axis = dynamic_cast<const NamedVector<double>*>(output_data.getAxes()[i]);
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
    const NamedVector<double> *axis = dynamic_cast<const NamedVector<double>*>(output_data.getAxes()[naxis]);
    for(size_t i=0; i<nbins; i++) {
        *array_buffer++ = (*axis)[i];
    }
    return pyarray;
}
