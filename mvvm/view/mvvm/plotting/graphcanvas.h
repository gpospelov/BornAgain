//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/view/mvvm/plotting/graphcanvas.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_VIEW_MVVM_PLOTTING_GRAPHCANVAS_H
#define BORNAGAIN_MVVM_VIEW_MVVM_PLOTTING_GRAPHCANVAS_H

#include "mvvm/view_export.h"
#include <QWidget>
#include <memory>

namespace ModelView {

class GraphViewportItem;
class SceneAdapterInterface;

//! Widget to show scientific figure with multiple 1D graphs.
//! Contains embedded QCustomPlot widget, shows content of GraphViewportItem.

class MVVM_VIEW_EXPORT GraphCanvas : public QWidget {
    Q_OBJECT

public:
    explicit GraphCanvas(QWidget* parent = nullptr);
    ~GraphCanvas() override;

    void setItem(GraphViewportItem* viewport_item);

    std::unique_ptr<SceneAdapterInterface> createSceneAdapter() const;

    void setViewportToContent(double left, double top, double right, double bottom);

    void setViewportToContent();

    void setAxisMargins(int left, int top, int right, int bottom);

signals:
    void axisMarginsChanged(int left, int top, int right, int bottom);

private:
    struct GraphCanvasImpl;
    std::unique_ptr<GraphCanvasImpl> p_impl;
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_VIEW_MVVM_PLOTTING_GRAPHCANVAS_H
