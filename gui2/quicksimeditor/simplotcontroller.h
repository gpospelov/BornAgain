// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_QUICKSIMEDITOR_SIMPLOTCONTROLLER_H
#define DAREFL_QUICKSIMEDITOR_SIMPLOTCONTROLLER_H

#include <QObject>
#include "darefl_export.h"
#include <memory>

namespace ModelView {
class ModelHasChangedController;
}

namespace DaRefl {

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

} // namespace DaRefl

#endif // DAREFL_QUICKSIMEDITOR_SIMPLOTCONTROLLER_H
