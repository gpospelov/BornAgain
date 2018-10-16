// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/ArrayUtils.h
//! @brief     Defines various functions to interact from numpy on Python side
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef ARRAYUTILS_H
#define ARRAYUTILS_H

#include <vector>
#include "WinDllMacros.h"
#include "PythonCore.h"
#include "OutputData.h"
#include <stdexcept>
#include <memory>

//! Array and Numpy utility functions getShape, createNumpyArray.

namespace ArrayUtils
{

//! Returns shape nrows, ncols of 2D array.
template<class T> std::pair<size_t, size_t> getShape(const T& data);

#ifdef BORNAGAIN_PYTHON
PyObject* createNumpyArray(const std::vector<double>& data);
#endif // BORNAGAIN_PYTHON

//! Creates OutputData from 1D vector.
//! @param vec: std::vector<double>
//! @return std::unique_ptr<OutputData<double>>
template<class T> decltype(auto) createData1D(const T& vec);

//! Creates 1D vector from OutputData.
//! @param vec: OutputData<double>
//! @return vector<double>
template<class T> decltype(auto) createVector1D(const T& data);

//! Creates OutputData from 2D vector.
//! @param vec: std::vector<std::vector<double>>
//! @return std::unique_ptr<OutputData<double>>
template<class T> decltype(auto) createData2D(const T& vec);

//! Creates 2D vector from OutputData.
//! @param vec: OutputData<double>
//! @return vector<vector<double>>
template<class T> decltype(auto) createVector2D(const T& data);

}

template<class T>  std::pair<size_t, size_t> ArrayUtils::getShape(const T& data){
    size_t nrows = data.size();
    size_t ncols(0);
    if(nrows) ncols = data[0].size();
    for(size_t row=0; row<nrows; row++)
        if(data[row].size() != ncols)
            throw std::runtime_error("Util::getShape() -> Error. "
                                     "Number of elements is different from row to row.");
    return std::make_pair(nrows, ncols);
}


template<class T> decltype(auto) ArrayUtils::createData1D(const T& vec)
{
    using value_type = typename T::value_type;
    std::unique_ptr<OutputData<value_type>> result(new OutputData<value_type>());
    const size_t length = vec.size();
    result->addAxis(FixedBinAxis("axis0", length, 0.0, static_cast<double>(length)));
    result->setRawDataVector(vec);
    return result;
}

template<class T> decltype(auto) ArrayUtils::createVector1D(const T& data)
{
    if (data.getRank() != 1)
        throw std::runtime_error("ArrayUtils::createVector1D() -> Error. Not 1D data.");

    using value_type = typename T::value_type;
    std::vector<value_type> result = data.getRawDataVector();
    return result;
}

template<class T> decltype(auto) ArrayUtils::createData2D(const T& vec)
{
    using value_type = typename T::value_type::value_type;
    std::unique_ptr<OutputData<value_type>> result(new OutputData<value_type>());

    auto shape = ArrayUtils::getShape(vec);
    const size_t nrows = shape.first;
    const size_t ncols = shape.second;

    if(nrows == 0 || ncols == 0)
        throw Exceptions::LogicErrorException("ArrayUtils::createData2D() -> Error. "
                                              "Not a two-dimensional array");

    result->addAxis(FixedBinAxis("axis0", ncols, 0.0, static_cast<double>(ncols)));
    result->addAxis(FixedBinAxis("axis1", nrows, 0.0, static_cast<double>(nrows)));

    // filling the data
    for(size_t row=0; row<nrows; ++row) {
        for(size_t col=0; col<ncols; ++col) {
            size_t globalbin = nrows - row - 1 + col*nrows;
            (*result)[globalbin] = vec[row][col];
        }
    }

    return result;
}

template<class T> decltype(auto) ArrayUtils::createVector2D(const T& data)
{
    using value_type = typename T::value_type;
    std::vector<std::vector<value_type>> result;
    std::vector<value_type> buffer1d;

    const size_t nrows = data.getAxis(1).size();
    const size_t ncols = data.getAxis(0).size();

    for(size_t i = 0 ; i < nrows; i++){
        buffer1d.clear();
        for(size_t j = 0 ; j < ncols; j++){
            size_t globalbin = nrows * (j+1) - i - 1;
            buffer1d.push_back(data[globalbin]);
        }
        result.push_back(buffer1d);
    }
    return result;
}


#endif // ARRAYUTILS_H
