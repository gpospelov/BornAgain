// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_QUICKSIMEDITOR_QUICKSIMEDITORTOOLBAR_H
#define DAREFL_QUICKSIMEDITOR_QUICKSIMEDITORTOOLBAR_H

#include <QToolBar>
#include <darefl/darefl_export.h>

class QProgressBar;
class QCheckBox;

namespace DaRefl {

//! Toolbar for QuickSimEditor.
//! Contains live simulation button, cancel button, simulation progress bar and settings buttons.

class DAREFLCORE_EXPORT QuickSimEditorToolBar : public QToolBar {
    Q_OBJECT

public:
    explicit QuickSimEditorToolBar(QWidget* parent = nullptr);

signals:
    void realTimeRequest(bool);
    void runSimulationRequest();
    void cancelPressed();
    void instrumentSettingsRequest();
    void resetViewRequest();
    void plotSettingsRequest();

public slots:
    void onProgressChanged(int value);

private:
    void add_wide_separator();
    void setup_simulation_elements();
    void setup_plot_elements();

    QCheckBox* m_liveCheckbox{nullptr};
    QProgressBar* m_progressBar{nullptr}; //! Simulation progressbar.
};

} // namespace DaRefl

#endif // DAREFL_QUICKSIMEDITOR_QUICKSIMEDITORTOOLBAR_H
