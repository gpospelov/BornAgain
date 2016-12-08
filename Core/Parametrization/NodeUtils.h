// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Parametrization/NodeUtils.h
//! @brief     Defines collection of utility functions for INode.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef NODEUTILS_H
#define NODEUTILS_H

#include "WinDllMacros.h"
#include<string>

class INode;

namespace NodeUtils {

    //! Returns multiline string representing tree structure starting from given node.
    BA_CORE_API_ std::string nodeToString(const INode& node);

} //namespace NodeUtils

#endif // NODEUTILS_H
