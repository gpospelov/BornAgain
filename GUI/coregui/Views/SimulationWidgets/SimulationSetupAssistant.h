// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SimulationWidgets/SimulationSetupAssistant.h
//! @brief     Defines class SimulationSetupAssistant
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef SIMULATIONSETUPASSISTANT_H
#define SIMULATIONSETUPASSISTANT_H

#include "WinDllMacros.h"
#include <QStringList>

class MultiLayerItem;
class InstrumentItem;
class RealDataItem;

//! The SimulationSetupAssistant class provides sample, instrument and real data validation before
//! submitting the job.

class BA_CORE_API_ SimulationSetupAssistant {
public:
    SimulationSetupAssistant();

    bool isValidSimulationSetup(const MultiLayerItem *multiLayerItem,
                                const InstrumentItem *instrumentItem,
                                const RealDataItem *realData = 0);
private:
    void clear();
    void checkMultiLayerItem(const MultiLayerItem *multiLayerItem);
    void checkInstrumentItem(const InstrumentItem *instrumentItem);
    void checkFittingSetup(const InstrumentItem *instrumentItem, const RealDataItem *realData);
    QString composeMessage();

    bool m_isValid;
    QStringList m_messages;
};


#endif // SIMULATIONSETUPASSISTANT_H
