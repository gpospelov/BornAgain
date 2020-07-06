// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SimulationView.h
//! @brief     Defines class SimulationView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef SIMULATIONVIEW_H
#define SIMULATIONVIEW_H

#include "Wrap/WinDllMacros.h"
#include <QWidget>

class MainWindow;
class SimulationSetupWidget;
class StyledToolBar;

class BA_CORE_API_ SimulationView : public QWidget
{
    Q_OBJECT

public:
    SimulationView(MainWindow* mainWindow);

protected:
    void showEvent(QShowEvent*);

public slots:
    void onRunSimulationShortcut();

private:
    void updateSimulationViewElements();

    SimulationSetupWidget* m_simulationSetupWidget;
    StyledToolBar* m_toolBar;
};

#endif // SIMULATIONVIEW_H
