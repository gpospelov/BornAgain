#ifndef ISAMPLEVIEW_H
#define ISAMPLEVIEW_H

#include <QGraphicsWidget>
#include <QPainter>


//! default view of some ISample item
class ISampleView : public QGraphicsPolygonItem
{
public:
    explicit ISampleView(QGraphicsItem *parent = 0);

private:
    QPolygonF m_polygon;
    QColor m_fillColor;
};

#endif //  ISAMPLEVIEW_H
