// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI2_QUICKSIMEDITOR_SIMPLOTCONTROLLER_H
#define BORNAGAIN_GUI2_QUICKSIMEDITOR_SIMPLOTCONTROLLER_H

#include "darefl_export.h"
#include <QObject>
#include <memory>

namespace ModelView {
class ModelHasChangedController;
}

namespace gui2 {

class ApplicationModels;

//! Updates reference curve in JobItem when BeamItem is changed.

class DAREFLCORE_EXPORT SimPlotController : public QObject {
    Q_OBJECT

public:
    SimPlotController(QObject* parent = nullptr);
    ~SimPlotController();

    void setModels(ApplicationModels* models);

private:
    void onInstrumentChange();

    ApplicationModels* m_models{nullptr};
    std::unique_ptr<ModelView::ModelHasChangedController> m_instrumentChangedController;
};

} // namespace gui2

#endif // BORNAGAIN_GUI2_QUICKSIMEDITOR_SIMPLOTCONTROLLER_H
