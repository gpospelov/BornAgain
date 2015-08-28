#ifndef MASKGRAPHICSVIEW_H
#define MASKGRAPHICSVIEW_H

#include <QGraphicsView>

class MaskGraphicsView : public QGraphicsView
{
Q_OBJECT
public:
    MaskGraphicsView(QGraphicsScene *scene, QWidget *parent = 0);

protected:
    //! manages mouse wheel events
    //! @param event contain current mouse wheel event
    void wheelEvent(QWheelEvent* event);

    //! zoom to a specific position
    //! @param factor to be zoomed in or out
    //! @param centerPoint the point where to zoom in or out
    void zoom(qreal factor, QPointF centerPoint);

    //! manages key release events
    //! @param event contains current release button
    void keyReleaseEvent(QKeyEvent *event);

    //! manages key press events
    //! @param event contains current clicked button
    void keyPressEvent(QKeyEvent *event);

private:
    //! check if control button is pressed to zoom on view
    //! @param event contains current pressed button
    //! @returns true if controll button pressed else false
    bool controlButtonIsPressed(QWheelEvent *event);

    //! check if color map is clicked to zoom on the color map
    //! @param event contains current pressed button
    //! @returns true if position of the event is about color map else false
    bool eventPosIsOnColorMap(QWheelEvent *event);

signals:

    //! emitted if space button is pressed
    void panMode(bool active);

    //! emitted if delete button is pressed
    void deleteSelectedItems();

};
#endif
