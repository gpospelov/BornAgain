//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/view/mvvm/plotting/viewportaxisplotcontroller.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_VIEW_MVVM_PLOTTING_VIEWPORTAXISPLOTCONTROLLER_H
#define BORNAGAIN_MVVM_VIEW_MVVM_PLOTTING_VIEWPORTAXISPLOTCONTROLLER_H

#include "mvvm/signals/itemlistener.h"
#include "mvvm/view_export.h"
#include <memory>

class QCPAxis;

namespace ModelView {

class ViewportAxisItem;

//! Establishes communication between QCPAxis and ViewportAxisItem.
//! Provide mutual update of axis parameters (min, max, title) for two axes representations.

class MVVM_VIEW_EXPORT ViewportAxisPlotController : public ItemListener<ViewportAxisItem> {
public:
    explicit ViewportAxisPlotController(QCPAxis* axis);
    ~ViewportAxisPlotController() override;

protected:
    void subscribe() override;
    void unsubscribe() override;

public:
    struct AxesPlotControllerImpl;
    std::unique_ptr<AxesPlotControllerImpl> p_impl;
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_VIEW_MVVM_PLOTTING_VIEWPORTAXISPLOTCONTROLLER_H
