//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      gui2/model/jobmodel.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI2_MODEL_JOBMODEL_H
#define BORNAGAIN_GUI2_MODEL_JOBMODEL_H

#include "darefl_export.h"
#include "mvvm/model/sessionmodel.h"

namespace ModelView {
class GraphViewportItem;
class GraphItem;
} // namespace ModelView

namespace gui2 {

class JobItem;
class CanvasItem;
struct SimulationResult;
struct SLDProfile;

//! The model to store results of (possibly) multiple reflectometry simulation, and all
//! viewports, representing various graphs in QuickSimEditor widgets.

class DAREFLCORE_EXPORT JobModel : public ModelView::SessionModel {
public:
    JobModel(std::shared_ptr<ModelView::ItemPool> pool = {});

    ModelView::GraphViewportItem* sldViewport() const;

    CanvasItem* specularViewport() const;

    ModelView::GraphViewportItem* diffViewport() const;

    void updateReferenceGraph(const ModelView::GraphItem* graph);

    void updateSpecularData(const SimulationResult& data);

    void updateSLDProfile(const SLDProfile& data);

private:
    JobItem* jobItem() const;
};

} // namespace gui2

#endif // BORNAGAIN_GUI2_MODEL_JOBMODEL_H
