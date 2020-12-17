//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/view/mvvm/plotting/graphviewportplotcontroller.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_VIEW_MVVM_PLOTTING_GRAPHVIEWPORTPLOTCONTROLLER_H
#define BORNAGAIN_MVVM_VIEW_MVVM_PLOTTING_GRAPHVIEWPORTPLOTCONTROLLER_H

#include "mvvm/signals/itemlistener.h"
#include "mvvm/view_export.h"
#include <memory>

class QCustomPlot;

namespace ModelView {

class GraphViewportItem;

//! Establishes communications and mutual updates for GraphViewportItem and QCutomPlot.
//! Populates custom plot with all graphs found in GraphViewportItem.

class MVVM_VIEW_EXPORT GraphViewportPlotController : public ItemListener<GraphViewportItem> {
public:
    explicit GraphViewportPlotController(QCustomPlot* plot);
    ~GraphViewportPlotController() override;

protected:
    void subscribe() override;

private:
    struct GraphViewportPlotControllerImpl;
    std::unique_ptr<GraphViewportPlotControllerImpl> p_impl;
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_VIEW_MVVM_PLOTTING_GRAPHVIEWPORTPLOTCONTROLLER_H
