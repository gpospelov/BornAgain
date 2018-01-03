// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/DomainSimulationBuilder.h
//! @brief     Defines class DomainSimulationBuilder
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef DOMAINSIMULATIONBUILDER_H
#define DOMAINSIMULATIONBUILDER_H

#include "WinDllMacros.h"

class GISASSimulation;
class MultiLayerItem;
class InstrumentItem;
class SimulationOptionsItem;

//! The DomainSimulationBuilder class builds the domain simulation
//! from instrument and sample models.
class BA_CORE_API_ DomainSimulationBuilder
{
public:
    static GISASSimulation *getSimulation(const MultiLayerItem *sampleItem,
                                          const InstrumentItem *instrumentItem,
                                          const SimulationOptionsItem *optionsItem = 0);
};

#endif // DOMAINSIMULATIONBUILDER_H
