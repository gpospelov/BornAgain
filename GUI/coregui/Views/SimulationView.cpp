// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SimulationView.cpp
//! @brief     Implements class SimulationView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "SimulationSetupWidget.h"
#include "StyledToolBar.h"
#include "mainwindow.h"
#include "SimulationView.h"
#include <QVBoxLayout>

SimulationView::SimulationView(MainWindow *mainWindow)
    : QWidget(mainWindow)
    , m_simulationSetupWidget(new SimulationSetupWidget)
    , m_toolBar(new StyledToolBar)
{
    m_toolBar->setMinimumSize(24, 24);

    m_simulationSetupWidget->setApplicationModels(mainWindow->models());

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setSizeConstraint(QLayout::SetNoConstraint);
    mainLayout->addWidget(m_toolBar);
    mainLayout->addWidget(m_simulationSetupWidget);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);
}


void SimulationView::updateSimulationViewElements()
{
    m_simulationSetupWidget->updateViewElements();
}

void SimulationView::onRunSimulationShortcut()
{
    m_simulationSetupWidget->onRunSimulation();
}
