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
//    enum Drawing { NONE, RECTANGLE, ELLIPSE, POLYGON };
//    void setDrawing(Drawing drawing);

protected:
//    void mousePressEvent(QMouseEvent *event);
//    void mouseMoveEvent(QMouseEvent *event);
//    void mouseReleaseEvent(QMouseEvent *event);
//    void drawForeground(QPainter *painter, const QRectF &);
    void wheelEvent(QWheelEvent* event);


private:
//    Drawing m_drawing;
//    Rectangle *m_rectangle;
//    Ellipse *m_ellipse;
//    Polygon *m_polygon;
//    bool isFinished;
//    QPointF m_currentMousePosition;
//    QPointF m_lastAddedPoint;
};
#endif
