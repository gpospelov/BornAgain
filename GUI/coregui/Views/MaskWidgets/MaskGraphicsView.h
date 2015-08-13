#ifndef MASKGRAPHICSVIEW_H
#define MASKGRAPHICSVIEW_H

#include <QGraphicsView>

class MaskGraphicsView : public QGraphicsView
{
Q_OBJECT
public:
    MaskGraphicsView(QGraphicsScene *scene, QWidget *parent = 0);

protected:
    void wheelEvent(QWheelEvent* event);
    void zoom(qreal factor, QPointF centerPoint);

    void keyReleaseEvent(QKeyEvent *event);
    void keyPressEvent(QKeyEvent *event);
private:
    bool controlButtonIsPressed(QWheelEvent *event);
    bool eventPosIsOnColorMap(QWheelEvent *event);

signals:
    void panMode(bool active);
    void deleteSelectedItems();

};
#endif
