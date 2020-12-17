//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      gui2/sldeditor/handleelementview.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI2_SLDEDITOR_HANDLEELEMENTVIEW_H
#define BORNAGAIN_GUI2_SLDEDITOR_HANDLEELEMENTVIEW_H

#include "darefl_export.h"
#include "gui2/sldeditor/elementview.h"

#include <QBrush>
#include <QPen>
#include <QRectF>

namespace gui2 {

class LayerElementController;

//! The handle QGraphicsViewItem on GraphicsScene
class DAREFLCORE_EXPORT HandleElementView : public ElementView {
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

} // namespace gui2

#endif // BORNAGAIN_GUI2_SLDEDITOR_HANDLEELEMENTVIEW_H
