#include <QWidget>
#include <QGraphicsView>


#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

class Rectangle;
class Ellipse;
class Polygon;

class GraphicsView : public QGraphicsView
{


public:
    GraphicsView();
    enum Drawing { NONE, RECTANGLE, ELLIPSE, POLYGON };
    void setDrawing(Drawing drawing);
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
//    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
//    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
//    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
//    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

private:
    Drawing m_drawing;
    Rectangle *m_rectangle;
    Ellipse *m_ellipse;
    Polygon *m_polygon;
};
#endif
