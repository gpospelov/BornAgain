//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/view/mvvm/plotting/data2dplotcontroller.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_VIEW_MVVM_PLOTTING_DATA2DPLOTCONTROLLER_H
#define BORNAGAIN_MVVM_VIEW_MVVM_PLOTTING_DATA2DPLOTCONTROLLER_H

#include "mvvm/signals/itemlistener.h"
#include "mvvm/view_export.h"
#include <memory>

class QCPColorMap;

namespace ModelView {

class Data2DItem;

//! Establish communication between QCPColorMap and Data2DItem.
//! Provide update of data points on QCPColorMap when Graph2DItem is changed.

class MVVM_VIEW_EXPORT Data2DPlotController : public ItemListener<Data2DItem> {
public:
    explicit Data2DPlotController(QCPColorMap* color_map);
    ~Data2DPlotController() override;

protected:
    void subscribe() override;
    void unsubscribe() override;

private:
    struct Data2DPlotControllerImpl;
    std::unique_ptr<Data2DPlotControllerImpl> p_impl;
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_VIEW_MVVM_PLOTTING_DATA2DPLOTCONTROLLER_H
