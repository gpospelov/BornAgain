#ifndef LAYERVIEW_H
#define LAYERVIEW_H

#include <QGraphicsWidget>
#include <QPainter>

//- -------------------------------------------------------------------
//! @class LayerView
//! @brief Graphics representation of Layer in SampleEditorScene
//- -------------------------------------------------------------------
class LayerView : public QGraphicsPolygonItem
{
public:
    explicit LayerView(QGraphicsItem *parent = 0);

private:
    QPolygonF m_polygon;
    QColor m_fillColor;
};

#endif // LAYERVIEW_H
