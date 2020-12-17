//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/view/mvvm/plotting/colormapcanvas.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_VIEW_MVVM_PLOTTING_COLORMAPCANVAS_H
#define BORNAGAIN_MVVM_VIEW_MVVM_PLOTTING_COLORMAPCANVAS_H

#include "mvvm/view_export.h"
#include <QWidget>
#include <memory>

namespace ModelView {

class ColorMapViewportItem;
class SceneAdapterInterface;

//! Widget to show 2D data as color map.
//! Contains embedded QCustomPlot widget, shows content of ColorMapViewportItem.

class MVVM_VIEW_EXPORT ColorMapCanvas : public QWidget {
    Q_OBJECT

public:
    explicit ColorMapCanvas(QWidget* parent = nullptr);
    ~ColorMapCanvas() override;

    void setItem(ColorMapViewportItem* viewport_item);

    std::unique_ptr<SceneAdapterInterface> createSceneAdapter() const;

private:
    struct ColorMapCanvasImpl;
    std::unique_ptr<ColorMapCanvasImpl> p_impl;
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_VIEW_MVVM_PLOTTING_COLORMAPCANVAS_H
