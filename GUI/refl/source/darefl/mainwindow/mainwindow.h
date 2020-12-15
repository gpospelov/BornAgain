// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_MAINWINDOW_MAINWINDOW_H
#define DAREFL_MAINWINDOW_MAINWINDOW_H

#include <QMainWindow>
#include <darefl/darefl_export.h>
#include <memory>

namespace DaRefl {

class WelcomeView;
class ImportDataView;
class SimulationView;
class MainBarWidget;
class ApplicationModels;
class ActionManager;
class SettingsView;

//! Application main window.

class DAREFLCORE_EXPORT MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent* event);

private:
    void init_application();
    void init_components();
    void init_connections();
    void write_settings();

    std::unique_ptr<ApplicationModels> m_models;
    ActionManager* m_actionManager{nullptr};
    WelcomeView* m_welcomeView{nullptr};
    ImportDataView* m_importDataView{nullptr};
    SimulationView* m_simView{nullptr};
    SettingsView* m_settingsView{nullptr};
    MainBarWidget* m_barWidget{nullptr};
};

} // namespace DaRefl

#endif // DAREFL_MAINWINDOW_MAINWINDOW_H
