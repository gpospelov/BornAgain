//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/view/mvvm/plotting/colormapplotcontroller.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_VIEW_MVVM_PLOTTING_COLORMAPPLOTCONTROLLER_H
#define BORNAGAIN_MVVM_VIEW_MVVM_PLOTTING_COLORMAPPLOTCONTROLLER_H

#include "mvvm/signals/itemlistener.h"
#include "mvvm/view_export.h"
#include <memory>

class QCustomPlot;
class QCPColorScale;

namespace ModelView {

class ColorMapItem;

//! Establish communication between QCPColorMap and ColorMapItem.
//! Provide update on QCPColorMap when ColorMapItem is changed. QCPColorMap is added to
//! QCustomPlot plottables, when controller is created, and removed from plottables, when controller
//! is destroyed.

class MVVM_VIEW_EXPORT ColorMapPlotController : public ItemListener<ColorMapItem> {
public:
    explicit ColorMapPlotController(QCustomPlot* plot, QCPColorScale* color_scale = nullptr);
    ~ColorMapPlotController() override;

protected:
    void subscribe() override;
    void unsubscribe() override;

private:
    struct ColorMapPlotControllerImpl;
    std::unique_ptr<ColorMapPlotControllerImpl> p_impl;
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_VIEW_MVVM_PLOTTING_COLORMAPPLOTCONTROLLER_H
