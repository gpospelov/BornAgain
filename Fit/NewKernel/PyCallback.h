// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/NewKernel/PyCallback.h
//! @brief     Defines class PyCallback.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef PYCALLBACK_H
#define PYCALLBACK_H

#include "WinDllMacros.h"
#include "Parameters.h"
#include <vector>


//! Base class to wrap Python callable and pass it to C++. Used in swig interface file.

class BA_CORE_API_ PyCallback
{
public:
    PyCallback();
    virtual ~PyCallback();

    //! Call Python callable and returns its result. Should be overloaded in swig interface.
    //! Intentionally pass by value.
    virtual double call(Fit::Parameters);
};

#endif  // PYCALLBACK_H

