// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/PyArrayImportUtils.h
//! @brief     Defines various functions to interact from numpy on Python side
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef PYARRAYIMPORTUTILS_H
#define PYARRAYIMPORTUTILS_H

#include "WinDllMacros.h"
#include <vector>

template<class T> class OutputData;

//! Set of functions for numpy array import to OutputData. Required solely
//! as a shortcut to produce OutputData from numpy arrays of doubles

namespace PyArrayImport {
    //! Provides functionality for importing 1D or 2D arrays of doubles from python into OutputData
    BA_CORE_API_ OutputData<double>* importArrayToOutputData(const std::vector<double>& vec);
    BA_CORE_API_ OutputData<double>* importArrayToOutputData(const std::vector<std::vector<double>>& vec);
}

#endif // PYARRAYIMPORTUTILS_H
