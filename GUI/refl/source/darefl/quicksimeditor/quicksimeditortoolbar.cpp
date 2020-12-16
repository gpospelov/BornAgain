// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QAction>
#include <QCheckBox>
#include <QLabel>
#include <QProgressBar>
#include <QVBoxLayout>
#include <darefl/core/app_constants.h>
#include <darefl/quicksimeditor/quicksimeditortoolbar.h>

namespace DaRefl {

QuickSimEditorToolBar::QuickSimEditorToolBar(QWidget* parent)
    : QToolBar(parent), m_liveCheckbox(new QCheckBox), m_progressBar(new QProgressBar) {
    const int toolbar_icon_size = 24;
    setIconSize(QSize(toolbar_icon_size, toolbar_icon_size));
    setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    setup_simulation_elements();
    add_wide_separator();

    setup_plot_elements();
}

//! Set progress bar to given value.

void QuickSimEditorToolBar::onProgressChanged(int value) {
    m_progressBar->setValue(value);
}

void QuickSimEditorToolBar::add_wide_separator() {
    addWidget(new QLabel(" "));
    addSeparator();
    addWidget(new QLabel(" "));
}

//! Setups elements to run simulation.

void QuickSimEditorToolBar::setup_simulation_elements() {
    // live check box and label
    const QString live_tooltip = "Automatically run simulation and update plot\n"
                                 "on any multilayer change.";
    m_liveCheckbox->setCheckState(Constants::live_simulation_default_on ? Qt::Checked
                                                                        : Qt::Unchecked);
    m_liveCheckbox->setToolTip(live_tooltip);
    auto on_check_state = [this](int state) { realTimeRequest(state == Qt::Checked); };
    connect(m_liveCheckbox, &QCheckBox::stateChanged, on_check_state);
    addWidget(m_liveCheckbox);
    auto label = new QLabel("Live");
    label->setToolTip(live_tooltip);
    addWidget(label);

    // run simulation
    auto run_action = new QAction("Run", this);
    run_action->setIcon(QIcon(":/icons/play-circle-outline.svg"));
    run_action->setToolTip("Run simulation for current multilayer state");
    connect(run_action, &QAction::triggered, this, &QuickSimEditorToolBar::runSimulationRequest);
    addAction(run_action);

    // progress bar
    m_progressBar->setFixedWidth(150);
    m_progressBar->setTextVisible(false);
    addWidget(m_progressBar);

    // cancel simulation
    auto cancel_action = new QAction("Cancel", this);
    cancel_action->setIcon(QIcon(":/icons/close-circle-outline.svg"));
    cancel_action->setToolTip("Cancel running simulation");
    connect(cancel_action, &QAction::triggered, this, &QuickSimEditorToolBar::cancelPressed);
    addAction(cancel_action);
}

//! Setups actions to reset plot and access its settings.

void QuickSimEditorToolBar::setup_plot_elements() {
    auto reset_view = new QAction("Replot", this);
    reset_view->setToolTip("Set plot axes to default range");
    reset_view->setIcon(QIcon(":/icons/aspect-ratio.svg"));
    connect(reset_view, &QAction::triggered, this, &QuickSimEditorToolBar::resetViewRequest);
    addAction(reset_view);
}

} // namespace DaRefl
