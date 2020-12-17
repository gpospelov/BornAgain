//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      gui2/model/modelutils.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI2_MODEL_MODELUTILS_H
#define BORNAGAIN_GUI2_MODEL_MODELUTILS_H

#include "darefl_export.h"
#include <string>
#include <vector>

namespace ModelView {
class GraphItem;
class Data1DItem;
class ExternalProperty;
} // namespace ModelView

namespace gui2 {

class ExperimentalDataModel;

namespace Utils {

//! Returns property representing given graph.
//! Used to link with the graph from various editors.
DAREFLCORE_EXPORT ModelView::ExternalProperty CreateProperty(const ModelView::GraphItem* graph);

//! Returns vector of properties representing GraphItem content of the model.
DAREFLCORE_EXPORT std::vector<ModelView::ExternalProperty>
CreateGraphProperties(ExperimentalDataModel* model);

//! Finds the property with the same `id` in given vector and returns it.
DAREFLCORE_EXPORT ModelView::ExternalProperty
FindProperty(const std::vector<ModelView::ExternalProperty>& properties, const std::string& id);

//! Returns vector representing elementwise 2*(a-b)/(a+b) difference over two vectors.
//! Resulting vector will have size equal to min(a.size(), b.size())
DAREFLCORE_EXPORT std::vector<double> CreateDiffVector(const std::vector<double>& a,
                                                       const std::vector<double>& b);

//! Make target item represent difference of two Data1DItems. Target will get an axis as in data1.
DAREFLCORE_EXPORT void SetDifference(const ModelView::Data1DItem* data1,
                                     const ModelView::Data1DItem* data2,
                                     ModelView::Data1DItem* target);
} // namespace Utils

} // namespace gui2

#endif // BORNAGAIN_GUI2_MODEL_MODELUTILS_H
