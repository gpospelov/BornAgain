// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_MAINWINDOW_SIMULATIONVIEW_H
#define DAREFL_MAINWINDOW_SIMULATIONVIEW_H

#include <QMainWindow>
#include <darefl/darefl_export.h>
#include <memory>

namespace ModelView {
class CollapsibleListWidget;
}

namespace DaRefl {

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

} // namespace DaRefl

#endif // DAREFL_MAINWINDOW_SIMULATIONVIEW_H
