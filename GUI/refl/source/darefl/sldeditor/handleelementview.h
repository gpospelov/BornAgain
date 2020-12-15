// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_SLDEDITOR_HANDLEELEMENTVIEW_H
#define DAREFL_SLDEDITOR_HANDLEELEMENTVIEW_H

#include <darefl/darefl_export.h>
#include <darefl/sldeditor/elementview.h>

#include <QBrush>
#include <QPen>
#include <QRectF>

namespace DaRefl
{

class LayerElementController;

//! The handle QGraphicsViewItem on GraphicsScene
class DAREFLCORE_EXPORT HandleElementView : public ElementView
{
public:
    HandleElementView();
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

#endif // DAREFL_SLDEDITOR_HANDLEELEMENTVIEW_H
