// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SimulationView.h
//! @brief     Defines class SimulationView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef SIMULATIONVIEW_H
#define SIMULATIONVIEW_H

#include "WinDllMacros.h"
#include <QWidget>

class MainWindow;
class SimulationSetupWidget;
class StyledToolBar;

class BA_CORE_API_ SimulationView : public QWidget
{
    Q_OBJECT

public:
    enum ETabViewId { SIMULATION_SETUP, QUICK_SIMULATION};
    SimulationView(MainWindow *mainWindow);

    void updateSimulationViewElements();

public slots:
    void onRunSimulationShortcut();

private:
    SimulationSetupWidget *m_simulationSetupWidget;
    StyledToolBar *m_toolBar;
};


#endif // SIMULATIONVIEW_H

