#ifndef DESIGNERVIEW_H
#define DESIGNERVIEW_H

#include <QWidget>

class QGraphicsView;
class QGraphicsScene;
class QDragEnterEvent;
class QWheelEvent;
class QKeyEvent;

class DesignerMimeData;

class DesignerView : public QWidget
{
public:

    explicit DesignerView(QWidget *parent = 0, QGraphicsScene *scene=0);
    virtual ~DesignerView(){}

public slots:
    void zoomIn();
    void zoomOut();
    void deleteItem();

protected:
//    virtual void dragEnterEvent(QDragEnterEvent *event);
//    virtual void dragMoveEvent(QDragMoveEvent *event);
//    virtual void dragLeaveEvent(QDragLeaveEvent *event);
//    virtual void dropEvent(QDropEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);

//    void wheelEvent(QWheelEvent *event);
    void scaleView(qreal scaleFactor);

    void keyPressEvent(QKeyEvent *event);

//    const DesignerMimeData *checkDragEvent(QDropEvent * event);

private:
    QGraphicsView *m_graphicsView;
};

#endif // DESIGNERVIEW_H
