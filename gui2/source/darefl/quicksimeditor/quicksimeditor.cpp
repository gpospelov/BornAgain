// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QTabWidget>
#include <QVBoxLayout>
#include <darefl/mainwindow/styleutils.h>
#include <darefl/model/applicationmodels.h>
#include <darefl/model/experimentaldataitems.h>
#include <darefl/model/jobmodel.h>
#include <darefl/quicksimeditor/quicksimcontroller.h>
#include <darefl/quicksimeditor/quicksimeditor.h>
#include <darefl/quicksimeditor/quicksimeditortoolbar.h>
#include <darefl/quicksimeditor/simplotcontroller.h>
#include <darefl/quicksimeditor/simplotwidget.h>
#include "mvvm/model/modelutils.h"
#include "mvvm/plotting/graphcanvas.h"
#include "mvvm/standarditems/graphviewportitem.h"

using namespace ModelView;

namespace DaRefl {

QuickSimEditor::QuickSimEditor(QWidget* parent)
    : QWidget(parent)
    , m_simController(new QuickSimController(this))
    , m_plotController(new SimPlotController(this))
    , m_plotWidget(new SimPlotWidget)
    , m_toolBar(new QuickSimEditorToolBar) {
    setWindowTitle(QString("Reflectivity plot"));
    auto layout = new QVBoxLayout(this);
    layout->addWidget(m_toolBar);
    layout->addWidget(m_plotWidget);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    setup_toolbar_connections();
    setup_controller_connections();
}

QuickSimEditor::~QuickSimEditor() = default;

//! Set the mododel for the different items
void QuickSimEditor::setModels(ApplicationModels* models) {
    m_appModels = models;
    m_simController->setModels(models);
    m_plotController->setModels(models);
    m_plotWidget->setModels(models);
}

QSize QuickSimEditor::sizeHint() const {
    return StyleUtils::DockSizeHint();
}

QSize QuickSimEditor::minimumSizeHint() const {
    return StyleUtils::DockMinimumSizeHint();
}

//! Connects signals from toolbar.

void QuickSimEditor::setup_toolbar_connections() {
    // Request to reset plot is propagated from toolbar to viewports.
    auto on_reset_view = [this]() { m_plotWidget->updateViewport(); };
    connect(dynamic_cast<QuickSimEditorToolBar*>(m_toolBar),
            &QuickSimEditorToolBar::resetViewRequest, on_reset_view);

    // Simulation interrupt request is propagated from toolbar to controller.
    connect(dynamic_cast<QuickSimEditorToolBar*>(m_toolBar), &QuickSimEditorToolBar::cancelPressed,
            m_simController, &QuickSimController::onInterruptRequest);

    // Request for real time mode is propagated from toobar to controller.
    connect(dynamic_cast<QuickSimEditorToolBar*>(m_toolBar),
            &QuickSimEditorToolBar::realTimeRequest, m_simController,
            &QuickSimController::onRealTimeRequest);

    // Run simulation is propagated from toobar to controller.
    connect(dynamic_cast<QuickSimEditorToolBar*>(m_toolBar),
            &QuickSimEditorToolBar::runSimulationRequest, m_simController,
            &QuickSimController::onRunSimulationRequest);
}

//! Connects signals from controller.

void QuickSimEditor::setup_controller_connections() {
    // Progress values propagated from controller to toolbar.
    connect(m_simController, &QuickSimController::progressChanged,
            dynamic_cast<QuickSimEditorToolBar*>(m_toolBar),
            &QuickSimEditorToolBar::onProgressChanged);
}

} // namespace DaRefl
