//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      gui2/settingsview/settingsview.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI2_SETTINGSVIEW_SETTINGSVIEW_H
#define BORNAGAIN_GUI2_SETTINGSVIEW_SETTINGSVIEW_H

#include "darefl_export.h"
#include <QWidget>

class QTabWidget;
class QStackedWidget;
class QListWidget;

namespace gui2 {

class ApplicationModels;

//! Main settings view, belongs directly to MainWindow.
//! For the moment contains QTabWidget with trees representating all application models.
//! In the future, might be extended to have any type of settings.

class DAREFLCORE_EXPORT SettingsView : public QWidget {
    Q_OBJECT

public:
    SettingsView(ApplicationModels* models, QWidget* parent = nullptr);

private:
    void init_list_selector();
    void init_model_settings();
    void init_other_settings();

    QListWidget* m_listWidget;                //!< selector for specific settings window on the left
    QStackedWidget* m_stackedWidget{nullptr}; //!< stack with settings widgets
    QTabWidget* m_tabWidget{nullptr};         //!< application model settings

    ApplicationModels* m_models{nullptr};
};

} // namespace gui2

#endif // BORNAGAIN_GUI2_SETTINGSVIEW_SETTINGSVIEW_H
