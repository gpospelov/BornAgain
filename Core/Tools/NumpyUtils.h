// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Tools/NumpyUtils.h
//! @brief     Declares various functions to interact from numpy on Python side
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifdef BORNAGAIN_PYTHON

#ifndef NUMPYUTILS_H
#define NUMPYUTILS_H

#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include "Python.h"

#include <vector>

namespace Utils
{
    PyObject* createNumpyArray(const std::vector<double>& data);
}

#endif // NUMPYUTILS_H

#endif // NUMPYUTILS_H
