#ifndef MASKGRAPHICSVIEW_H
#define MASKGRAPHICSVIEW_H

#include <QGraphicsView>

class MaskGraphicsView : public QGraphicsView
{
Q_OBJECT
public:
//    GraphicsView();

protected:
    void wheelEvent(QWheelEvent* event);
    void zoom(qreal factor, QPointF centerPoint);

private:
    bool controlButtonIsPressed(QWheelEvent *event);
    bool eventPosIsOnColorMap(QWheelEvent *event);

signals:
    void panMode(bool active);

};
#endif
