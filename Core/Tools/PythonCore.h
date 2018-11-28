// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Tools/PythonCore.h
//! @brief     Includes python header and takes care of warnings.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef PYTHONCORE_H
#define PYTHONCORE_H

#ifdef BORNAGAIN_PYTHON

#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION

#undef _POSIX_C_SOURCE
#undef _XOPEN_SOURCE

#include <Python.h>

#define PY_ARRAY_UNIQUE_SYMBOL BORNAGAIN_PYTHONAPI_ARRAY
#define NO_IMPORT_ARRAY
#include <numpy/arrayobject.h>

#include "swig_runtime.h"

#endif // BORNAGAIN_PYTHON

#endif // PYTHONCORE_H


