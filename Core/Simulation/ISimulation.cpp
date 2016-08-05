// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Simulation/ISimulation.cpp
//! @brief     Implements interface class ISimulation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ISimulation.h"
#include "Exceptions.h"

ISimulation* ISimulation::clone() const
{
    throw Exceptions::NotImplementedException(
        "ISimulation::clone() -> Error: not implemented exception.");
}
