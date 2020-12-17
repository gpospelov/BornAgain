//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      gui2/model/applicationmodels.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI2_MODEL_APPLICATIONMODELS_H
#define BORNAGAIN_GUI2_MODEL_APPLICATIONMODELS_H

#include "darefl_export.h"
#include "mvvm/interfaces/applicationmodelsinterface.h"
#include <memory>

namespace ModelView {
class SessionModel;
}

namespace gui2 {

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

} // namespace gui2

#endif // BORNAGAIN_GUI2_MODEL_APPLICATIONMODELS_H
