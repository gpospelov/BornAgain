// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_SLDEDITOR_LAYERELEMENTCONTROLLER_H
#define DAREFL_SLDEDITOR_LAYERELEMENTCONTROLLER_H

#include "mvvm/plotting/sceneadapterinterface.h"
#include <QObject>
#include <QPainterPath>
#include <darefl/darefl_export.h>
#include <vector>

namespace DaRefl {

// The mvvm item associated to this layer
class LayerElementItem;
// The graphics scene to put the QGraphicsViewItem on
class GraphicsScene;
// The handle QGraphicsViewItem
class HandleElementView;
// The segment QGraphicsViewItem
class SegmentElementView;
// The roughness QGraphicsViewItem
class RoughnessElementView;

//! Manages the whole appearance of a layer on the graphicsscene
class DAREFLCORE_EXPORT LayerElementController : public QObject {
    Q_OBJECT

public:
    LayerElementController(LayerElementItem* layer_view_item);
    LayerElementItem* layerElementItem() const;
    void autoPopulate();
    void deleteViewItems();
    void connectToModel() const;
    void disconnectFormModel() const;

    // ##################################################################################
    // Scene management related
    void setScene(GraphicsScene* scene);
    GraphicsScene* scene() const;
    void unsetScene();

    // ##################################################################################
    // Sample id management related
    void setSampleItemId(std::string indentifier);
    std::string sampleItemId() const;
    void unsetSampleItemId();

    // ##################################################################################
    // Inter layer logic related
    void setLayerAbove(LayerElementController* layer_view_controller);
    void setLayerBelow(LayerElementController* layer_view_controller);
    LayerElementController* layerAbove() const;
    LayerElementController* layerBelow() const;
    void unsetLayerAbove(bool silent = true);
    void unsetLayerBelow(bool silent = true);

    // ##################################################################################
    // Segment related public methods
    void setSideSegment(SegmentElementView* segment_view);
    void setTopSegment(SegmentElementView* segment_view);
    SegmentElementView* sideSegment() const;
    SegmentElementView* topSegment() const;
    void unsetSideSegment();
    void unsetTopSegment();
    void segmentViewMoved(SegmentElementView* segment_view);

    // ##################################################################################
    // Handle related public methods
    void setSegmentHandles(HandleElementView* first_handle, HandleElementView* secondHandle);
    HandleElementView* firstSegmentHandle() const;
    HandleElementView* secondSegmentHandle() const;
    void unsetSegmentHandles();
    void handleViewMoved(HandleElementView* handle_view);

    // ##################################################################################
    // Roughness related
    void setRoughness(RoughnessElementView* roughness_view);
    void setRoughnessHandles(HandleElementView* first_handle_view,
                             HandleElementView* second_handle_view);
    RoughnessElementView* roughness() const;
    HandleElementView* leftRoughnessHandle() const;
    HandleElementView* rightRoughnessHandle() const;
    void unsetRoughness();
    void unsetRoughnessHandles();
    void updateRoughness() const;

signals:
    void heightChanged(std::string id, double value) const;
    void widthChanged(std::string id, double value) const;
    void roughnessChanged(std::string id, double value) const;

private:
    ModelView::SceneAdapterInterface* sceneAdapter() const;

protected:
    // ##################################################################################
    // Segment related protected methods
    void updateSideSegment() const;
    void updateTopSegment() const;
    QRectF sideSegmentRect() const;
    QRectF topSegmentRect() const;
    void putSegementsOnScene() const;
    void removeSegmentsFromScene() const;

    void sideSegmentMoved() const;
    void topSegmentMoved() const;

    // ##################################################################################
    // Handle related protected methods
    void updateSegmentHandles() const;
    QRectF firstSegmentHandleRect() const;
    QRectF secondSegmentHandleRect() const;
    void putSegmentHandlesOnScene() const;
    void removeSegmentHandlesFromScene() const;

    // ##################################################################################
    // Roughness related protected methods
    QPainterPath leftRoughnessPath() const;
    QPainterPath rightRoughnessPath() const;
    QRectF leftRoughnessHandleRect() const;
    QRectF rightRoughnessHandleRect() const;
    void putRoughnessOnScene() const;
    void putRoughnessHandlesOnScene() const;
    void removeRoughnessFromScene() const;
    void removeRoughnessHandlesFromScene() const;
    void setRoughnessInLimits(double roughness, bool active = true) const;

    void leftHandleMoved() const;
    void rightHandleMoved() const;

private:
    LayerElementItem* p_model_item;
    GraphicsScene* p_scene = nullptr;
    std::string m_sample_item_id;

    std::vector<SegmentElementView*> m_segment_views = {nullptr, nullptr};
    std::vector<HandleElementView*> m_handle_views = {nullptr, nullptr};
    std::vector<HandleElementView*> m_rough_handles_views = {nullptr, nullptr};
    RoughnessElementView* p_roughness_view = nullptr;

    LayerElementController* p_controller_above = nullptr;
    LayerElementController* p_controller_below = nullptr;
};

} // namespace DaRefl

#endif // DAREFL_SLDEDITOR_LAYERELEMENTCONTROLLER_H
