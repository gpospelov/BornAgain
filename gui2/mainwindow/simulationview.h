//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      gui2/mainwindow/simulationview.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI2_MAINWINDOW_SIMULATIONVIEW_H
#define BORNAGAIN_GUI2_MAINWINDOW_SIMULATIONVIEW_H

#include "darefl_export.h"
#include <QMainWindow>
#include <memory>

namespace ModelView {
class CollapsibleListWidget;
}

namespace gui2 {

class ApplicationModels;
class QuickSimEditor;

//! Main simulation window with all components for quick sample editing and simulations.

class DAREFLCORE_EXPORT SimulationView : public QMainWindow {
    Q_OBJECT

public:
    SimulationView(ApplicationModels* models, QWidget* parent = nullptr);

private:
    void initEditorList();

    ModelView::CollapsibleListWidget* m_editorList{nullptr};
    QuickSimEditor* m_simEditor{nullptr};
    ApplicationModels* m_models{nullptr};
};

} // namespace gui2

#endif // BORNAGAIN_GUI2_MAINWINDOW_SIMULATIONVIEW_H
