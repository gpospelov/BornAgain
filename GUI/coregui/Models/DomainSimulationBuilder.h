// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/DomainSimulationBuilder.h
//! @brief     Defines class DomainSimulationBuilder
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef DOMAINSIMULATIONBUILDER_H
#define DOMAINSIMULATIONBUILDER_H

#include <QString>

class Simulation;
class SampleModel;
class InstrumentModel;
class Instrument;
class MultiLayer;


//! The DomainSimulationBuilder class builds the domain simulation
//! from instrument and sample models.
class DomainSimulationBuilder
{
public:

    static Simulation *getSimulation(SampleModel *sampleModel, const QString &sample_name, InstrumentModel *instrumentModel, const QString &instrument_name);

    static Simulation *getSimulation(SampleModel *sampleModel, InstrumentModel *instrumentModel);

private:
    static Instrument *getInstrument(InstrumentModel *instrumentModel, const QString &instrument_name = QString());

    static MultiLayer *getMultiLayer(SampleModel *sampleModel, const QString &sample_name = QString());
};

#endif
