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
#include <QVBoxLayout>
#include <QTabWidget>




#include "SampleModel.h"
#include "InstrumentModel.h"
#include "ParameterizedItem.h"
#include <QTreeView>
#include <QModelIndex>




// FIXME_DAVID Move your activity from TestView to FitView.
// - FitView should contain QTabWidget with 3 tabs:
// - 1) ImportDataWidget (empty for the moment) 2) FitSettingsWidget 3) RunFitWidget

// FIXME_DAVID FitSettingsWidget should contain
// - FitParametersWidget (for the moment), and later sample/instrument selector + MinimizerSettingsWidgert


FitView::FitView(MainWindow *mainWindow)
    : QWidget(mainWindow)
{
    FitParameterWidget *fitting = new FitParameterWidget(mainWindow);
    RunFitWidget *runFitWidget = new RunFitWidget();

    QVBoxLayout *layout = new QVBoxLayout;
    QTabWidget *tabs = new QTabWidget;

    QTreeView *view = new QTreeView;

    /*TestModel *model = new TestModel("TestModel");
    auto fit = model->insertNewItem(Constants::FitParameterType, QModelIndex());
    model->insertNewItem(Constants::FitParameterLinkType, model->indexOfItem(fit));
    model->insertNewItem(Constants::FitParameterLinkType, model->indexOfItem(fit));

    auto layer = model->insertNewItem(Constants::MultiLayerType, QModelIndex());
    model->insertNewItem(Constants::LayerType, model->indexOfItem(layer));

    view->setModel(model);
    view->setRootIndex(model->indexOfItem(fit));*/


    tabs->addTab(new QWidget(), "Import Experimental Data");
    tabs->addTab(fitting, "Fit Settings");
    tabs->addTab(runFitWidget, "Run Fit");
    tabs->addTab(view, "SessionModel test");
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(tabs);
    setLayout(layout);

    tabs->setCurrentIndex(1);
}
