//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      gui2/quicksimeditor/quicksimcontroller.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI2_QUICKSIMEDITOR_QUICKSIMCONTROLLER_H
#define BORNAGAIN_GUI2_QUICKSIMEDITOR_QUICKSIMCONTROLLER_H

#include "darefl_export.h"
#include "gui2/quicksimeditor/quicksim_types.h"
#include <QObject>
#include <memory>

namespace ModelView {
class ModelHasChangedController;
}

namespace gui2 {

class ApplicationModels;
class JobManager;
class JobModel;
class InstrumentModel;

//! Provides quick reflectometry simulations on any change of SampleModel and MaterialModel.
//! Listens for any change in SampleModel and MaterialModel, extracts the data needed for
//! the simulation, and then submit simulation request to JobManager. As soon as JobManager reports
//! about completed simulations, extract results from there and put them into JobModel.

class DAREFLCORE_EXPORT QuickSimController : public QObject {
    Q_OBJECT

public:
    QuickSimController(QObject* parent = nullptr);
    ~QuickSimController();

    void setModels(ApplicationModels* models);

signals:
    void progressChanged(int value);

public slots:
    void onInterruptRequest();
    void onRealTimeRequest(bool status);
    void onRunSimulationRequest();

private slots:
    void onMultiLayerChange();
    void onSimulationCompleted();

private:
    void process_multilayer(bool submit_simulation = false);
    void update_sld_profile(const multislice_t& multilayer);
    void submit_specular_simulation(const multislice_t& multislice);
    void setup_jobmanager_connections();

    JobModel* jobModel() const;
    InstrumentModel* instrumentModel() const;

    ApplicationModels* m_models{nullptr};
    JobManager* m_jobManager{nullptr};

    bool m_isRealTimeMode; //! Run simulation on every parameter change.

    std::unique_ptr<ModelView::ModelHasChangedController> m_materialChangedController;
    std::unique_ptr<ModelView::ModelHasChangedController> m_sampleChangedController;
    std::unique_ptr<ModelView::ModelHasChangedController> m_instrumentChangedController;
};

} // namespace gui2

#endif // BORNAGAIN_GUI2_QUICKSIMEDITOR_QUICKSIMCONTROLLER_H
