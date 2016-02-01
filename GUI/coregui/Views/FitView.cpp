// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/TestView.cpp
//! @brief     Implements class TestView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //
#include "FitView.h"
#include "RunFitWidget.h"
#include "mainwindow.h"
#include "FitParameterWidget.h"
#include "FitSettingsWidget.h"
#include "FitModel.h"
#include "FitParameterItems.h"
#include <QVBoxLayout>
#include <QTabWidget>




#include "SampleModel.h"
#include "InstrumentModel.h"
#include "ParameterizedItem.h"
#include <QTreeView>
#include <QModelIndex>




FitView::FitView(MainWindow *mainWindow)
    : QWidget(mainWindow)
{
    // FitModel is constructed here, should be moved to mainwindow in sometime
    FitModel *fitmodel = mainWindow->getFitModel();

    FitSettingsWidget *settings = new FitSettingsWidget(mainWindow->getFitModel(),
                                                        mainWindow->getSampleModel(),
                                                        mainWindow->getInstrumentModel(), this);
    FitParameterWidget *fitting = new FitParameterWidget(mainWindow->getSampleModel(),
                                                         mainWindow->getInstrumentModel(),
                                                         fitmodel, this);
    RunFitWidget *runFitWidget = new RunFitWidget();

    QVBoxLayout *layout = new QVBoxLayout;
    QTabWidget *tabs = new QTabWidget;

    QTreeView *view = new QTreeView;


    view->setModel(fitmodel);


    tabs->addTab(new QWidget(), "Import Experimental Data");
    tabs->addTab(settings, "Fit Settings");
    tabs->addTab(runFitWidget, "Run Fit");
    tabs->addTab(view, "SessionModel test");
    tabs->addTab(fitting, "Parameters only");
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(tabs);
    setLayout(layout);

    tabs->setCurrentIndex(1);
}
