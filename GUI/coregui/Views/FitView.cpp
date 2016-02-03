// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/FitView.cpp
//! @brief     Implements class FitView
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
#include "SampleModel.h"
#include "InstrumentModel.h"
#include "ParameterizedItem.h"
#include <QVBoxLayout>
#include <QTabWidget>
#include <QLineEdit>
#include <QFileInfo>
#include <QTreeView>
#include <QModelIndex>


// ------------------------------------------------------------------------------------------------
// FIXME_DAVID
// ------------------------------------------------------------------------------------------------

// FitView --> Add narrow toolbar (QToolBar) on top of whole widget as in InstrumentView


// FitParameterWidget --> Move KeyboardFilter to GUI/coregui/utils/CustomEventFilters,
// rename it to know what it is doing


// FitParameterWidget --> Replace splitter with Manhattan::MiniSplitter(this) as in JobView


// FitParameterWidget or FitSettingsWidget --> Where to add second horizontal splitter to have minimizer settings?
// From layout point of view it should be FitParameterWidget, from responsibility point of view, it should be FitSettingsWidget
// Lets discuss it


// FitParameterWidget --> Move SelectorModel into corresponding *.h and *.cpp in GUI/coregui/Models


// FitParameterWidget --> Move FitParameterModel into corresponding *.h and *.cpp in GUI/coregui/Models


// FitParameterWidget --> Refactor ContextMenu part. m_contextMenu should not be member variable.
// * It has to be dynamically generated on right click. See MaskEditorActions::onItemContextMenuRequest
// * Think of creating separate class and isolating all actions activity there.
//   See MaskEditor <--> MaskEditorActions (FitParameterWIdget <---> FitParameterWidgetActions ?)
// * Context menu should be always the same --> if given action is not available for underlying item,
//   the action should be disabled. See MaskEditorActions::initItemContextMenu(QMenu &menu)
// * Use horizonal delimeter in context menu:
// > Remove parameter   <---- this guy can be disabled(gray) if there is no appropriate item beneath
// > ----------------   <---- horizontal delimeter
// > Add parameter


// FitParameterWidget --> Add context menu to right m_selectorTreeView
// * There should be
// > create fit parameter
// > add to existing parameter --> and then dynamic menu of existing fit parameters


// FitParameterWidget --> Refactor a bit getTopItemFromSelection
// The call  QString selectedSample = m_fitModel->itemForIndex(QModelIndex())->getChildOfType(Constants::FitSelectionType)->getRegisteredProperty(selectionType).toString();
// could be implemented as method in FitModel


// General --> Remove all fitting related Obsolete*, if you do not need them


// General --> Try to provide comments for major functions in cpp files, explaining in general what they are doing, e.g.
// //! reports to FitObserver current status of something
// int MyClass::MyFunction() {
// ...
// }
// >
// > No need to have lots of comments inside the function (i.e. it is ok, like you are doing now), just before function
// > implementation a short line with comment, what will be going on inside



// FitParameterWidget -> Refactor FitParameterWidget::buildTree and buildSelectorModel()
// Part of code should be moved into separate class with static method, similar to
// GUI/coregui/Models/ParameterModelBuilder; you can create there SelectorModelBuilder class
// which will act on QStringList (for example) and return QStandardItemModel


// FitParameterItem and its TreeView -> Additional functionality --> TO DISCUSS
// So we need following parameters
// Name  |  Use  |  Starting Value | Min | Max
// Could you please try to do the following:
// * Use should be QComboBox with values "free", "fixed", "limited"
// When the user selects "fixed" -> than Min,Max fields become disabled (gray and non-editable)
// When the user selects "free" -> the same
// When the user selects "limited" -> than Min,Max fields become active


// FitParameterItem and its TreeView -> Additional functionality --> TO DISCUSS
// Please make tooltips for tree header
// "parameter name", "parameter mode: fixed, limited in the interval or free", "starting value of the parameter", "lower parameter bound", "upper parameter bound"


// ------------------------------------------------------------------------------------------------

// RunFitWidget --> Refactoring -> It should not act on observer, always address to FitProgressWidget
// * For example, m_interval_slider should be connected with FitProgressWidget, and not observer
// * In the method RunFitWidget::onStartClicked() something like m_fitprogress->attachFitSuite() should be used


// void RunFitManager::runFitting() -> Please do not use short variables FittingWorker *fw = new FittingWorker(m_fitSuite);
// Use fittingWorker for variable name

// FitProgressWidget --> m_guifitobserver , may be it should be unique_ptr instead of shared_ptr?

// FitProgressWidget, FitObserver --> signal refactoring, ownership --> TO DISCUSS
// > I fill myself not very comfortable with the idea of heavy OutputData's flying around, especially if they are flying separately (real data, chi_squared)
// Possible solution:
// FitObserver reports through signal:
// - There is a log String ready
// - There is data to plot ready (they seats in unique_pt, owned by FitObserver)
// --> And then FitSuite, take it out (throgh std::move, or some other trick) and permits FitObserver to conrinue


// RunFitWidget -> intervalSlider -> TO DISCUSS
// * I agree that slider is very nice and impressive, but
// * What if I have very fast simulation (simple model), and I want to update every 1000 iteration?
//   It's not nice to have a slider up to 1000.
// * Can we replace a slider with some DropDownBox (every 1 iteration, every 5, 10 and 1000)
//   Such boxes also have possibility to type inside any custom number too
// * What if I want to update plotting every 100 iterations, and output every 10. Do I need this actually? :)
// Alternatives ?


// ------------------------------------------------------------------------------------------------
// ImportExperimentalData --> To discuss





// ------------------------------------------------------------------------------------------------


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
    m_runFitWidget = new RunFitWidget(mainWindow->getFitModel(),
                                                  mainWindow->getSampleModel(),
                                                  mainWindow->getInstrumentModel(), this);

    QVBoxLayout *layout = new QVBoxLayout;
    QTabWidget *tabs = new QTabWidget;

    QTreeView *view = new QTreeView;
    m_testplot = new ColorMapPlot(this);

    view->setModel(fitmodel);

    m_line = new QLineEdit();

    connect(m_line, SIGNAL(textChanged(QString)), this, SLOT(onUpdatePath()));

    tabs->addTab(m_line , "Import Experimental Data");
    tabs->addTab(settings, "Fit Settings");
    tabs->addTab(m_runFitWidget, "Run Fit");
    tabs->addTab(view, "SessionModel test");
    tabs->addTab(fitting, "Parameters only");
    tabs->addTab(m_testplot, "test plot");
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(tabs);
    setLayout(layout);

    tabs->setCurrentIndex(1);
}

void FitView::onUpdatePath() {
    m_runFitWidget->path = m_line->text();
    QFileInfo chk(m_line->text());
    if (chk.exists()) {
        IHistogram *data = IntensityDataIOFactory::readIntensityData(m_line->text().toStdString());
        IntensityDataItem *item = new IntensityDataItem();
        item->setOutputData(data->createOutputData());
        m_testplot->setItem(item);
    }
}
