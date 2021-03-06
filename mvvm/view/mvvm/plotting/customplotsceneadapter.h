//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/view/mvvm/plotting/customplotsceneadapter.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_VIEW_MVVM_PLOTTING_CUSTOMPLOTSCENEADAPTER_H
#define BORNAGAIN_MVVM_VIEW_MVVM_PLOTTING_CUSTOMPLOTSCENEADAPTER_H

#include "mvvm/plotting/sceneadapterinterface.h"
#include <memory>

class QCustomPlot;

namespace ModelView {

//! Converts QGraphicsScene coordinates in the coordinates of local system of QCustomPlot
//! and vice versa.

class MVVM_VIEW_EXPORT CustomPlotSceneAdapter : public SceneAdapterInterface {
public:
    explicit CustomPlotSceneAdapter(QCustomPlot* custom_plot);
    ~CustomPlotSceneAdapter() override;

    double toSceneX(double customplot_x) const override;

    double toSceneY(double customplot_y) const override;

    double fromSceneX(double scene_x) const override;

    double fromSceneY(double scene_y) const override;

    QRectF viewportRectangle() const override;

private:
    struct CustomPlotSceneAdapterImpl;
    std::unique_ptr<CustomPlotSceneAdapterImpl> p_impl;
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_VIEW_MVVM_PLOTTING_CUSTOMPLOTSCENEADAPTER_H
