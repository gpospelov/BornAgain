//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/model/mvvm/standarditems/graphviewportitem.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_MODEL_MVVM_STANDARDITEMS_GRAPHVIEWPORTITEM_H
#define BORNAGAIN_MVVM_MODEL_MVVM_STANDARDITEMS_GRAPHVIEWPORTITEM_H

#include "mvvm/standarditems/viewportitem.h"

namespace ModelView {

class GraphItem;

//! 2D viewport specialized for showing multiple GraphItem's.
//! Provides calculation of viewport's x-axis and y-axis range basing on GraphItem data.
//! Provides functionality to hide selected graphs.

class MVVM_MODEL_EXPORT GraphViewportItem : public ViewportItem {
public:
    GraphViewportItem(const std::string& model_type = Constants::GraphViewportItemType);

    std::vector<GraphItem*> graphItems() const;

    std::vector<GraphItem*> visibleGraphItems() const;

    void setVisible(const std::vector<GraphItem*>& visible_graph_items);

    void setAllVisible();

protected:
    std::pair<double, double> data_xaxis_range() const override;
    std::pair<double, double> data_yaxis_range() const override;
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_MODEL_MVVM_STANDARDITEMS_GRAPHVIEWPORTITEM_H
