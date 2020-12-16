// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_MODEL_APPLICATIONMODELS_H
#define DAREFL_MODEL_APPLICATIONMODELS_H

#include <darefl/darefl_export.h>
#include <memory>
#include "mvvm/interfaces/applicationmodelsinterface.h"

namespace ModelView {
class SessionModel;
}

namespace DaRefl {

class MaterialModel;
class SampleModel;
class SLDElementModel;
class SLDElementController;
class JobModel;
class ExperimentalDataModel;
class InstrumentModel;

//!  Main class to holds all models of GUI session.

class DAREFLCORE_EXPORT ApplicationModels : public ModelView::ApplicationModelsInterface {
public:
    ApplicationModels();
    ~ApplicationModels();

    MaterialModel* materialModel();
    SampleModel* sampleModel();
    SLDElementModel* sldViewModel();
    JobModel* jobModel();
    ExperimentalDataModel* experimentalDataModel();
    InstrumentModel* instrumentModel();

    std::vector<ModelView::SessionModel*> persistent_models() const override;

    std::vector<ModelView::SessionModel*> application_models() const;

private:
    struct ApplicationModelsImpl;
    std::unique_ptr<ApplicationModelsImpl> p_impl;
};

} // namespace DaRefl

#endif // DAREFL_MODEL_APPLICATIONMODELS_H
