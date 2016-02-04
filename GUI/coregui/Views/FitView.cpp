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
#include "FitSettingsWidget.h"
#include "FitModel.h"
#include "ImportDataWidget.h"
#include "projectmanager.h"
#include <QVBoxLayout>
#include <QTabWidget>


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
    , m_tabs(new QTabWidget)
    , m_importDataWidget(new ImportDataWidget(mainWindow->getFitModel(), this))
    , m_fitSettingsWidget(new FitSettingsWidget(mainWindow->getFitModel(), this))
    , m_runFitWidget(new RunFitWidget(mainWindow->getFitModel(), this))
{
    QVBoxLayout *layout = new QVBoxLayout;
    m_tabs->addTab(m_importDataWidget , "Import Experimental Data");
    m_tabs->addTab(m_fitSettingsWidget, "Fit Settings");
    m_tabs->addTab(m_runFitWidget, "Run Fit");
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_tabs);
    setLayout(layout);

    connect(mainWindow->getProjectManager(), SIGNAL(projectOpened()),
            m_fitSettingsWidget, SLOT(onUpdateGUI()));
    connect(mainWindow->getProjectManager(), SIGNAL(projectOpened()),
            m_importDataWidget, SLOT(onUpdateGUI()));

    m_tabs->setCurrentIndex(1);
}
