// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Python/PyEmbedded/PyEmbeddedUtils.h
//! @brief     Defines PyEmbeddedUtils namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PYEMBEDDEDUTILS_H
#define PYEMBEDDEDUTILS_H

#include <Python.h>
#include <string>
#include <vector>

#if PY_MAJOR_VERSION >= 3
#define PyString_FromString PyUnicode_FromString
#endif

namespace PyEmbeddedUtils {

//! Converts PyObject into string, if possible, or throws exception.
//! @param decref To automatically decrease reference counter after data is processed.
std::string toString(PyObject* obj, bool decref = true);

//! Converts PyObject into vector of strings, if possible, or throws exception.
//! @param decref To automatically decrease reference counter after data is processed.
std::vector<std::string> toVectorString(PyObject* obj, bool decref = true);

//! Converts char to string. In the case of nullptr will return an empty string.
std::string toString(char* c);

}

#endif

