// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/IResolutionFunction2D.h
//! @brief     Defines interface class IResolutionFunction2D.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Instrument/IResolutionFunction2D.h"

IResolutionFunction2D::IResolutionFunction2D(
    const INode* parent, const std::vector<const char*> PName,
                                 const std::vector<const char*> PUnit,
                                 const std::vector<double> PMin, const std::vector<double> PMax,
                                 const std::vector<double> PDefault, std::vector<double> P)
    : INode{parent, PName, PUnit, PMin, PMax, PDefault, P}
{
}
