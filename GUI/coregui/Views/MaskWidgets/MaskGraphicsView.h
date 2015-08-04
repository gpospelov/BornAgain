#ifndef MASKGRAPHICSVIEW_H
#define MASKGRAPHICSVIEW_H

#include <QGraphicsView>

class MaskGraphicsView : public QGraphicsView
{
Q_OBJECT
public:
//    GraphicsView();
    void deleteSelectedItems();

protected:
    void wheelEvent(QWheelEvent* event);
    void zoom(qreal factor, QPointF centerPoint);
    void keyPressEvent(QKeyEvent *event);   
    void keyReleaseEvent(QKeyEvent *event);

private:
    bool controlButtonIsPressed(QWheelEvent *event);
    bool eventPosIsOnColorMap(QWheelEvent *event);

signals:
    void panMode(bool active);

};
#endif
