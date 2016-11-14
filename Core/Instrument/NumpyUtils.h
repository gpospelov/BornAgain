// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/NumpyUtils.h
//! @brief     Defines various functions to interact from numpy on Python side
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef NUMPYUTILS_H
#define NUMPYUTILS_H

#ifdef BORNAGAIN_PYTHON

#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <vector>

namespace Utils
{
    PyObject* createNumpyArray(const std::vector<double>& data);
}

#endif // BORNAGAIN_PYTHON

#endif // NUMPYUTILS_H
