// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "gui2/model/applicationmodels.h"
#include "gui2/model/experimentaldatacontroller.h"
#include "gui2/model/experimentaldatamodel.h"
#include "gui2/model/instrumentmodel.h"
#include "gui2/model/jobmodel.h"
#include "gui2/model/materialmodel.h"
#include "gui2/model/materialpropertycontroller.h"
#include "gui2/model/sampleitems.h"
#include "gui2/model/samplemodel.h"
#include "gui2/sldeditor/sldelementmodel.h"
#include "mvvm/model/externalproperty.h"
#include "mvvm/model/itempool.h"
#include "mvvm/model/modelutils.h"
#include "mvvm/model/sessionitem.h"

namespace gui2 {

using namespace ModelView;

struct ApplicationModels::ApplicationModelsImpl {
    std::unique_ptr<MaterialModel> m_material_model;
    std::unique_ptr<SampleModel> m_sample_model;
    std::unique_ptr<SLDElementModel> m_sld_view_model;
    std::unique_ptr<JobModel> m_job_model;
    std::unique_ptr<ExperimentalDataModel> m_experimental_model;
    std::unique_ptr<InstrumentModel> m_instrument_model;
    std::unique_ptr<MaterialPropertyController> m_material_controller;
    std::unique_ptr<ExperimentalDataController> m_data_controller;
    std::shared_ptr<ItemPool> item_pool;

    ApplicationModelsImpl() {
        item_pool = std::make_shared<ItemPool>();
        m_material_model = std::make_unique<MaterialModel>(item_pool);
        m_sample_model = std::make_unique<SampleModel>(item_pool);
        m_sld_view_model = std::make_unique<SLDElementModel>();
        m_job_model = std::make_unique<JobModel>(item_pool);
        m_experimental_model = std::make_unique<ExperimentalDataModel>(item_pool);
        m_instrument_model = std::make_unique<InstrumentModel>(item_pool);
        m_material_controller = std::make_unique<MaterialPropertyController>(m_material_model.get(),
                                                                             m_sample_model.get());
        m_data_controller = std::make_unique<ExperimentalDataController>(m_experimental_model.get(),
                                                                         m_instrument_model.get());
        m_sample_model->create_default_multilayer();
        update_material_properties();
    }

    //! Runs through all layers and assign materials.
    //! Expecting 3 materials existing by default (air, default, Si) to assign to our 3 layers.

    void update_material_properties() {
        auto multilayer = Utils::TopItem<MultiLayerItem>(m_sample_model.get());
        auto layers = multilayer->items<LayerItem>(MultiLayerItem::T_LAYERS);
        size_t index(0);
        for (const auto& material_property : m_material_model->material_data()) {
            if (index < layers.size())
                layers[index]->setProperty(LayerItem::P_MATERIAL, material_property);
            ++index;
        }
    }

    //! Models intended for saving.
    std::vector<SessionModel*> persistent_models() const {
        return {m_material_model.get(), m_sample_model.get(), m_instrument_model.get(),
                m_experimental_model.get()};
    }

    //! All application models.
    std::vector<SessionModel*> application_models() const {
        return {m_material_model.get(), m_sample_model.get(), m_instrument_model.get(),
                m_sld_view_model.get(), m_job_model.get(),    m_experimental_model.get()};
    }
};

ApplicationModels::ApplicationModels() : p_impl(std::make_unique<ApplicationModelsImpl>()) {}

ApplicationModels::~ApplicationModels() = default;

MaterialModel* ApplicationModels::materialModel() {
    return p_impl->m_material_model.get();
}

SampleModel* ApplicationModels::sampleModel() {
    return p_impl->m_sample_model.get();
}

SLDElementModel* ApplicationModels::sldViewModel() {
    return p_impl->m_sld_view_model.get();
}

JobModel* ApplicationModels::jobModel() {
    return p_impl->m_job_model.get();
}

ExperimentalDataModel* ApplicationModels::experimentalDataModel() {
    return p_impl->m_experimental_model.get();
}

InstrumentModel* ApplicationModels::instrumentModel() {
    return p_impl->m_instrument_model.get();
}

std::vector<SessionModel*> ApplicationModels::persistent_models() const {
    return p_impl->persistent_models();
}

//! Return vector of all models of our application.

std::vector<SessionModel*> ApplicationModels::application_models() const {
    return p_impl->application_models();
}

} // namespace gui2
