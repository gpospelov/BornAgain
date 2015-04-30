// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/DomainSimulationBuilder.h
//! @brief     Defines class DomainSimulationBuilder
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef DOMAINSIMULATIONBUILDER_H
#define DOMAINSIMULATIONBUILDER_H

#include <QString>

class Simulation;
class SampleModel;
class InstrumentModel;
class MultiLayerItem;
class InstrumentItem;

//! The DomainSimulationBuilder class builds the domain simulation
//! from instrument and sample models.
class DomainSimulationBuilder
{
public:        
    static Simulation *getSimulation(SampleModel *sampleModel, const QString &sample_name,
                                     InstrumentModel *instrumentModel,
                                     const QString &instrument_name);

    static Simulation *getSimulation(SampleModel *sampleModel, InstrumentModel *instrumentModel);

    static Simulation *getSimulation(MultiLayerItem *sampleItem, InstrumentItem *instrumentItem);

};

#endif
