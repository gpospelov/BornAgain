#ifndef SAMPLEEDITORVIEW_H
#define SAMPLEEDITORVIEW_H

#include <QWidget>

class QGraphicsView;
class QGraphicsScene;
class QDragEnterEvent;
class QWheelEvent;
class QKeyEvent;


class SampleEditorView : public QWidget
{
public:

    explicit SampleEditorView(QWidget *parent = 0, QGraphicsScene *scene=0);

    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);

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

#endif // SAMPLEEDITORVIEW_H
