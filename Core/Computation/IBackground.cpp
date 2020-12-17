//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      Core/Computation/IBackground.cpp
//! @brief     Implements interface IBackground.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Core/Computation/IBackground.h"

IBackground::IBackground(const NodeMeta& meta, const std::vector<double>& PValues)
    : INode(meta, PValues)
{
}

IBackground::~IBackground() = default;
