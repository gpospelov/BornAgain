// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_SETTINGSVIEW_SETTINGSVIEW_H
#define DAREFL_SETTINGSVIEW_SETTINGSVIEW_H

#include <QWidget>
#include <darefl/darefl_export.h>

class QTabWidget;
class QStackedWidget;
class QListWidget;

namespace DaRefl {

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

} // namespace DaRefl

#endif // DAREFL_SETTINGSVIEW_SETTINGSVIEW_H
