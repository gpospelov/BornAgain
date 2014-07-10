#ifndef DESIGNERVIEW_H
#define DESIGNERVIEW_H

#include<QGraphicsView>

class QGraphicsView;
class QGraphicsScene;
class QDragEnterEvent;
class QWheelEvent;
class QKeyEvent;

//! The DesignerView class provides widget for displaying the contents of DesignerScene
//!
//! Belongs to SampleDesigner
//! Currently contains logic for zooming, deleting objects
class DesignerView : public QGraphicsView
{
    Q_OBJECT

public:

    explicit DesignerView(QGraphicsScene *scene, QWidget *parent = 0);
    virtual ~DesignerView(){}

    enum SelectionModes { SimpleSelectionMode, RubberSelectionMode, HandDragMode};
    int getSelectionMode() const;

signals:
    void selectionModeChanged(int);

public slots:
    void onSelectionMode(int);

    void zoomIn();
    void zoomOut();
    void zoomFit();
    void deleteSelectedItems();
    void onSceneScaleChanged(const QString &);


protected:
//    void wheelEvent(QWheelEvent *event);
    void scaleView(qreal scaleFactor);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void mouseMoveEvent(QMouseEvent * event);


};

#endif // DESIGNERVIEW_H
