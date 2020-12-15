// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_MODEL_JOBITEM_H
#define DAREFL_MODEL_JOBITEM_H

#include <darefl/darefl_export.h>
#include <mvvm/model/compounditem.h>
#include <mvvm/standarditems/graphviewportitem.h>

namespace ModelView
{
class Data1DItem;
class GraphViewportItem;
class GraphItem;
} // namespace ModelView

namespace DaRefl
{

class CanvasItem;

//! Viewport intended for showing SLD profile.
//! Provides custom y-axis range.

class DAREFLCORE_EXPORT SLDCanvasItem : public ModelView::GraphViewportItem
{
public:
    SLDCanvasItem();

protected:
    std::pair<double, double> data_yaxis_range() const override;
};

//! Represents state of QuickSimEditor.
//! Holds results of realtime simulation, SLD profiles and difference plot.

class DAREFLCORE_EXPORT JobItem : public ModelView::CompoundItem
{
public:
    static inline const std::string P_SLD_DATA = "P_SLD_DATA";
    static inline const std::string P_SLD_VIEWPORT = "P_SLD_VIEWPORT";
    static inline const std::string P_SPECULAR_DATA = "P_SPECULAR_DATA";
    static inline const std::string P_SPECULAR_VIEWPORT = "P_SPECULAR_VIEWPORT";
    static inline const std::string P_DIFF_DATA = "P_DIFF_DATA";
    static inline const std::string P_DIFF_VIEWPORT = "P_DIFF_VIEWPORT";

    JobItem();

    ModelView::Data1DItem* sldData() const;
    SLDCanvasItem* sldViewport() const;

    ModelView::Data1DItem* specularData() const;
    CanvasItem* specularViewport() const;

    ModelView::GraphViewportItem* diffViewport() const;

    void updateReferenceGraph(const ModelView::GraphItem* graph);

    void updateDifferenceData();

private:
    ModelView::Data1DItem* differenceData() const;
    ModelView::GraphItem* specularGraph() const;
    ModelView::GraphItem* referenceGraph() const;
    ModelView::GraphItem* differenceGraph() const;

    void setupReferenceGraphFrom(const ModelView::GraphItem* graph);
    void setupDifferenceGraphFrom(const ModelView::GraphItem* graph);
    void removeReferenceGraph();
    void removeDifferenceGraph();

    void setup_sld_viewport();
    void setup_specular_viewport();
    void setup_diff_viewport();
};

} // namespace DaRefl

#endif // DAREFL_MODEL_JOBITEM_H
