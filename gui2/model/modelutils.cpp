//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      gui2/model/modelutils.cpp
//! @brief     Implements class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "gui2/model/modelutils.h"
#include "gui2/model/experimentaldatamodel.h"
#include "mvvm/model/externalproperty.h"
#include "mvvm/model/modelutils.h"
#include "mvvm/standarditems/axisitems.h"
#include "mvvm/standarditems/data1ditem.h"
#include "mvvm/standarditems/graphitem.h"

namespace gui2 {

ModelView::ExternalProperty Utils::CreateProperty(const ModelView::GraphItem* graph) {
    std::string name = graph->parent()->displayName() + "/" + graph->displayName();
    auto colorName = QString::fromStdString(graph->colorName());
    return ModelView::ExternalProperty(name, QColor(colorName), graph->identifier());
}

std::vector<ModelView::ExternalProperty>
Utils::CreateGraphProperties(ExperimentalDataModel* model) {
    std::vector<ModelView::ExternalProperty> result;
    for (auto graph : ModelView::Utils::FindItems<ModelView::GraphItem>(model))
        result.push_back(Utils::CreateProperty(graph));
    return result;
}

// FIXME unit tests
ModelView::ExternalProperty
Utils::FindProperty(const std::vector<ModelView::ExternalProperty>& properties,
                    const std::string& id) {
    for (const auto& prop : properties)
        if (prop.identifier() == id)
            return prop;

    return ModelView::ExternalProperty::undefined();
}

std::vector<double> Utils::CreateDiffVector(const std::vector<double>& a,
                                            const std::vector<double>& b) {
    size_t length = std::min(a.size(), b.size());
    std::vector<double> result(length, 0.0);
    for (size_t i = 0; i < length; ++i) {
        double denom = a[i] + b[i];
        result[i] = denom != 0.0 ? 2 * (a[i] - b[i]) / (a[i] + b[i]) : 0.0;
    }
    return result;
}

void Utils::SetDifference(const ModelView::Data1DItem* data1, const ModelView::Data1DItem* data2,
                          ModelView::Data1DItem* target) {
    // it is expected that difference graph has proper axis
    target->setValues(CreateDiffVector(data1->binValues(), data2->binValues()));
}

} // namespace gui2
