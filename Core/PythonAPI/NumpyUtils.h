// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      PythonAPI/NumpyUtils.h
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
#ifndef PyObject_HEAD
struct _object;
typedef _object PyObject;
#endif
#endif

#include <vector>

namespace Utils
{


#ifdef BORNAGAIN_PYTHON
    PyObject *createNumpyArray(const std::vector<double> &data);
#endif


} // namespace Utils

#endif

