// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Tools/PyImport.h
//! @brief     Defines PyImport namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PYIMPORT_H
#define PYIMPORT_H

#include "WinDllMacros.h"
#include <string>
#include <memory>

class MultiLayer;

namespace PyImport {

//! Creates a multi layer by running python code in embedded interpreter.
//! @param script: Python script
//! @param functionName: A function name in this script which produces a MultiLayer.
BA_CORE_API_ std::unique_ptr<MultiLayer> createFromPython(const std::string& script,
                                                          const std::string& functionName,
                                                          const std::string& path = std::string());
}

#endif

