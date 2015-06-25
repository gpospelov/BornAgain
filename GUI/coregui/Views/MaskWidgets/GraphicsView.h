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
//    GraphicsView();
    void deleteSelectedItems();
protected:
    void wheelEvent(QWheelEvent* event);
    void zoom(qreal factor, QPointF centerPoint);
    void resizeEvent(QResizeEvent *event);
    void keyPressEvent(QKeyEvent *event);
};
#endif
