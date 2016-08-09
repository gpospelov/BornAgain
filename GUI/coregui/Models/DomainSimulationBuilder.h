// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/DomainSimulationBuilder.h
//! @brief     Defines class DomainSimulationBuilder
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef DOMAINSIMULATIONBUILDER_H
#define DOMAINSIMULATIONBUILDER_H


class GISASSimulation;
class MultiLayerItem;
class InstrumentItem;
class SimulationOptionsItem;

//! The DomainSimulationBuilder class builds the domain simulation
//! from instrument and sample models.
class DomainSimulationBuilder
{
public:
    static GISASSimulation *getSimulation(const MultiLayerItem *sampleItem,
                                          const InstrumentItem *instrumentItem,
                                          const SimulationOptionsItem *optionsItem = 0);
};

#endif // DOMAINSIMULATIONBUILDER_H
