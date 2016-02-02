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
#include "projectmanager.h"
#include "ColorMapPlot.h"
#include "IntensityDataIOFactory.h"
#include "IntensityDataItem.h"
#include "IHistogram.h"
#include <QVBoxLayout>
#include <QTabWidget>
#include <QLineEdit>
#include <QFileInfo>




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

    //connect (mainWindow->getProjectManager(), SIGNAL(projectOpened()),
    //         settings, SLOT(onUpdateGUI()));
    FitParameterWidget *fitting = new FitParameterWidget(mainWindow->getSampleModel(),
                                                         mainWindow->getInstrumentModel(),
                                                         fitmodel, this);
    runFitWidget = new RunFitWidget(mainWindow->getFitModel(),
                                                  mainWindow->getSampleModel(),
                                                  mainWindow->getInstrumentModel(), this);

    QVBoxLayout *layout = new QVBoxLayout;
    QTabWidget *tabs = new QTabWidget;

    QTreeView *view = new QTreeView;
    testplot = new ColorMapPlot(this);

    view->setModel(fitmodel);

    line = new QLineEdit();

    connect(line, SIGNAL(textChanged(QString)), this, SLOT(onUpdatePath()));

    tabs->addTab(line , "Import Experimental Data");
    tabs->addTab(settings, "Fit Settings");
    tabs->addTab(runFitWidget, "Run Fit");
    tabs->addTab(view, "SessionModel test");
    tabs->addTab(fitting, "Parameters only");
    tabs->addTab(testplot, "test plot");
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(tabs);
    setLayout(layout);

    tabs->setCurrentIndex(1);
}

void FitView::onUpdatePath() {
    runFitWidget->path = line->text();
    QFileInfo chk(line->text());
    if (chk.exists()) {
        IHistogram *data = IntensityDataIOFactory::readIntensityData(line->text().toStdString());
        IntensityDataItem *item = new IntensityDataItem();
        item->setOutputData(data->createOutputData());
        testplot->setItem(item);
    }
}
