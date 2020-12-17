//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      gui2/quicksimeditor/quicksimeditortoolbar.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI2_QUICKSIMEDITOR_QUICKSIMEDITORTOOLBAR_H
#define BORNAGAIN_GUI2_QUICKSIMEDITOR_QUICKSIMEDITORTOOLBAR_H

#include "darefl_export.h"
#include <QToolBar>

class QProgressBar;
class QCheckBox;

namespace gui2 {

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

} // namespace gui2

#endif // BORNAGAIN_GUI2_QUICKSIMEDITOR_QUICKSIMEDITORTOOLBAR_H
