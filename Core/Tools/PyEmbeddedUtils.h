// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Tools/PyEmbeddedUtils.h
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

#include "PythonCore.h"
#include "swig_runtime.h"
#include "WinDllMacros.h"
#include <string>
#include <vector>
#include <memory>

class MultiLayer;

namespace PyEmbeddedUtils {

//! Converts PyObject into string, if possible, or throws exception.
//! @param decref To automatically decrease reference counter after data is processed.
BA_CORE_API_ std::string toString(PyObject* obj, bool decref = true);

//! Converts PyObject into vector of strings, if possible, or throws exception.
//! @param decref To automatically decrease reference counter after data is processed.
BA_CORE_API_ std::vector<std::string> toVectorString(PyObject* obj);

//! Converts char to string. In the case of nullptr will return an empty string.
BA_CORE_API_ std::string toString(char* c);
BA_CORE_API_ std::string toString(wchar_t* c);

//! Imports BornAgain from given location. If path is empty, tries to rely on PYTHONPATH.
BA_CORE_API_ void import_bornagain(const std::string& path = std::string());

//! Returns multi-line string representing PATH, PYTHONPATH, sys.path and other info.
BA_CORE_API_ std::string pythonRuntimeInfo();

//! Returns string representing python stack trace.
BA_CORE_API_ std::string pythonStackTrace();
}

#endif

