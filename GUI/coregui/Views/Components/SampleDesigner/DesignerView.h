#ifndef DESIGNERVIEW_H
#define DESIGNERVIEW_H

#include <QWidget>

class QGraphicsView;
class QGraphicsScene;
class QDragEnterEvent;
class QWheelEvent;
class QKeyEvent;

//! The DesignerView class provides widget for displaying the contents of DesignerScene
//!
//! Belongs to SampleDesigner
//! Currently contains logic for zooming, deleting objects
class DesignerView : public QWidget
{
    Q_OBJECT

public:

    explicit DesignerView(QWidget *parent = 0, QGraphicsScene *scene=0);
    virtual ~DesignerView(){}

public slots:
    void zoomIn();
    void zoomOut();
    void zoomFit();
    void deleteSelectedItems();
    void clearAll();


protected:
//    void wheelEvent(QWheelEvent *event);
    void scaleView(qreal scaleFactor);
    void keyPressEvent(QKeyEvent *event);

private:
    QGraphicsView *m_graphicsView;
};

#endif // DESIGNERVIEW_H
