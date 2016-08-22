// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Simulation/ISimulation.cpp
//! @brief     Implements the interface class ISimulation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ISimulation.h"
#include "Exceptions.h"

ISimulation* ISimulation::clone() const
{
    throw Exceptions::NotImplementedException(
        "Bug: unexpected call to ISimulation::clone(); functionality not yet implemented");
}
