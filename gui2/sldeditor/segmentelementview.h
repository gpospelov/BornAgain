// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_SLDEDITOR_SEGMENTELEMENTVIEW_H
#define DAREFL_SLDEDITOR_SEGMENTELEMENTVIEW_H

#include "darefl_export.h"
#include "gui2/sldeditor/elementview.h"

#include <QBrush>
#include <QPen>
#include <QRectF>

namespace DaRefl {

class LayerElementController;

//! The segment QGraphicsViewItem on the Graphicsscene
class DAREFLCORE_EXPORT SegmentElementView : public ElementView {
public:
    SegmentElementView();
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    void setLayerElementController(LayerElementController* controller);
    void setRectangle(QRectF rectangle);
    void setBrush(QBrush brush);
    void setPen(QPen pen);
    QPointF getLastPos() const;

public:
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;

protected:
    LayerElementController* p_controller;
    QPointF m_pos;
    QRectF m_rectangle;
    QBrush m_brush;
    QPen m_pen;
};

} // namespace DaRefl

#endif // DAREFL_SLDEDITOR_SEGMENTELEMENTVIEW_H
