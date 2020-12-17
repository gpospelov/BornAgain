//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      gui2/mainwindow/mainwindow.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI2_MAINWINDOW_MAINWINDOW_H
#define BORNAGAIN_GUI2_MAINWINDOW_MAINWINDOW_H

#include "darefl_export.h"
#include <QMainWindow>
#include <memory>

namespace gui2 {

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

} // namespace gui2

#endif // BORNAGAIN_GUI2_MAINWINDOW_MAINWINDOW_H
