// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/src/OutputData.cpp
//! @brief     Just include OutputData.h.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "OutputData.h"

#ifdef BORNAGAIN_PYTHON
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <boost/python/detail/wrap_python.hpp>
#define PY_ARRAY_UNIQUE_SYMBOL BORNAGAIN_PYTHONAPI_ARRAY
#define NO_IMPORT_ARRAY
#include "numpy/arrayobject.h"


template<>
PyObject *OutputData<double>::getArray() const
{
    std::vector<int > dimensions;
    for(size_t i=0; i<getRank(); i++) {
        //const AxisDouble *axis = output_data.getAxis(i);
        const IAxis *axis = getAxis(i);
        dimensions.push_back( (int)axis->getSize() );
    }

    // creating ndarray objects describing size of dimensions
    npy_int ndim_numpy= (int)dimensions.size();
    npy_intp *ndimsizes_numpy = new npy_intp[dimensions.size()];
    for(size_t i=0; i<dimensions.size(); i++) {
        ndimsizes_numpy[i] = dimensions[i];
    }

    // creating standalone numpy array
    PyObject *pyarray = PyArray_SimpleNew(ndim_numpy, ndimsizes_numpy, NPY_DOUBLE);
    //std::vector<double> raw = getRawDataVector();
    //PyObject *pyarray = PyArray_SimpleNewFromData(ndim_numpy, ndimsizes_numpy, NPY_DOUBLE, &raw[0]);
    delete [] ndimsizes_numpy;
    if(pyarray == NULL ) {
        throw RuntimeErrorException(
                "ExportOutputData() -> Panic in PyArray_SimpleNew");
    }
    Py_INCREF(pyarray);

    // getting pointer to data buffer of numpy array
    double *array_buffer = (double *)PyArray_DATA((PyArrayObject*)pyarray);

    // filling numpy array with output_data
//    OutputData<double>::const_iterator it = begin();
//    while(it != end() ) {
//        *array_buffer++ = *it++;
//    }
    for(size_t index=0; index<getAllocatedSize(); ++index) {
        *array_buffer++ = (*this)[index];
    }

    return pyarray;
}

#endif

