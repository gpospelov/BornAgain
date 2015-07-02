#ifndef MASKGRAPHICSVIEW_H
#define MASKGRAPHICSVIEW_H

#include <QGraphicsView>

class MaskGraphicsView : public QGraphicsView
{

public:
//    GraphicsView();
    void deleteSelectedItems();
protected:
    void wheelEvent(QWheelEvent* event);
    void zoom(qreal factor, QPointF centerPoint);
    void resizeEvent(QResizeEvent *event);
    void keyPressEvent(QKeyEvent *event);
private:
    bool controlButtonIsPressed(QWheelEvent *event);
    bool eventPosIsOnColorMap(QWheelEvent *event);
};
#endif
