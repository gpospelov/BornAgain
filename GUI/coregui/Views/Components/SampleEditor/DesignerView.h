#ifndef DESIGNERVIEW_H
#define DESIGNERVIEW_H

#include <QWidget>

class QGraphicsView;
class QGraphicsScene;
class QDragEnterEvent;
class QWheelEvent;
class QKeyEvent;


class DesignerView : public QWidget
{
public:

    explicit DesignerView(QWidget *parent = 0, QGraphicsScene *scene=0);


public slots:
    void zoomIn();
    void zoomOut();
    void deleteItem();

protected:
//    void wheelEvent(QWheelEvent *event);
    void scaleView(qreal scaleFactor);

    void keyPressEvent(QKeyEvent *event);

private:
    QGraphicsView *m_graphicsView;
    QGraphicsScene *m_graphicsScene;
};

#endif // DESIGNERVIEW_H
