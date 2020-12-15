// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_QUICKSIMEDITOR_QUICKSIMEDITOR_H
#define DAREFL_QUICKSIMEDITOR_QUICKSIMEDITOR_H

#include <QWidget>
#include <darefl/darefl_export.h>

namespace DaRefl {

class JobModel;
class ApplicationModels;
class QuickSimController;
class QuickSimEditorToolBar;
class SimPlotController;
class SimPlotWidget;

//! Quick reflectivity simulations.

class DAREFLCORE_EXPORT QuickSimEditor : public QWidget {
    Q_OBJECT

public:
    QuickSimEditor(QWidget* parent = nullptr);
    ~QuickSimEditor();

    void setModels(ApplicationModels* models);

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

private:
    void setup_toolbar_connections();
    void setup_controller_connections();

    ApplicationModels* m_appModels{nullptr};
    QuickSimController* m_simController{nullptr};
    SimPlotController* m_plotController{nullptr};
    SimPlotWidget* m_plotWidget{nullptr};
    QuickSimEditorToolBar* m_toolBar{nullptr};
};

} // namespace DaRefl

#endif // DAREFL_QUICKSIMEDITOR_QUICKSIMEDITOR_H
