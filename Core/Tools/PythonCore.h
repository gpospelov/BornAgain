// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Tools/PythonCore.h
//! @brief     Includes python header and takes care of warnings.
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PYTHONCORE_H

#ifdef BORNAGAIN_PYTHON

#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION

#undef _POSIX_C_SOURCE
#undef _XOPEN_SOURCE

#include <Python.h>

#define PY_ARRAY_UNIQUE_SYMBOL BORNAGAIN_PYTHONAPI_ARRAY
#define NO_IMPORT_ARRAY
#include <numpy/arrayobject.h>

#endif // BORNAGAIN_PYTHON


#endif

