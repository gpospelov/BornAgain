// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SimulationWidgets/SimulationSetupWidget.h
//! @brief     Declares class SimulationSetupWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef SIMULATIONSETUPWIDGET_H
#define SIMULATIONSETUPWIDGET_H

#include "WinDllMacros.h"
#include <QWidget>

class QPushButton;
class MultiLayerItem;
class InstrumentItem;
class SimulationDataSelectorWidget;
class SimulationOptionsWidget;
class ApplicationModels;

//! The SimulationSetupWidget class represents a main widget to define simulation settings
//! and run the simulation. Belongs to the SimulationView.

class BA_CORE_API_ SimulationSetupWidget : public QWidget
{
    Q_OBJECT

public:
    SimulationSetupWidget(QWidget *parent = 0);

    void setApplicationModels(ApplicationModels *model);
    void updateViewElements();

public slots:
    void onRunSimulation();
    void onExportToPythonScript();

private:
    QWidget *createButtonWidget();

    ApplicationModels *m_applicationModels;

    QPushButton *runSimulationButton;
    QPushButton *exportToPyScriptButton;

    SimulationDataSelectorWidget *m_simDataSelectorWidget;
    SimulationOptionsWidget *m_simOptionsWidget;
};

#endif
