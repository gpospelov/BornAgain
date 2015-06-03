#include <QWidget>
#include <QGraphicsProxyWidget>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include "DistributionEditor.h"
#include <QGraphicsView>
#include <QPainterPath>

#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle : public QGraphicsItem
{

public:
    //! describes corner
    enum Corner { NONE, TOPLEFT, TOPRIGHT, BOTTOMLEFT, BOTTOMRIGHT };

    //! create Rectangle
    //! @param posX x position in scene
    //! @param posY y position in scene
    //! @param width of rectangle
    //! @param heigth of rectangle
    Rectangle(qreal posX, qreal poxY, qreal width, qreal heigth);

    //! bounding box of rectangle
    QRectF boundingRect() const;

    //! check if resize rules are correct
    //! @param event mouse event to check if resizes correct
    void checkResizeRules(QGraphicsSceneMouseEvent *event);

    //! calculates resized rectangle
    //! @param event mouse event to set new coordinates
    void calculateResize(QGraphicsSceneMouseEvent *event);

    //! calculates rotated rectangle
    //! @param event mouse event to set new coordinates
    //! @return degree of rotation
    qreal calculateRotation(QGraphicsSceneMouseEvent *event);

protected:
    //! paintEvent paints Rectangle and corners
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

private:
    qreal m_posX;                           //!< x position of rectangle
    qreal m_posY;                           //!< y position of rectangle
    qreal m_width;                          //!< width of rectangle
    qreal m_heigth;                         //!< height of rectangle
    QGraphicsRectItem *m_topLeftCorner;     //!< rectangle in the top left corner
    QGraphicsRectItem *m_bottomLeftCorner;  //!< rectangle in the bottom left corner
    QGraphicsRectItem *m_topRightCorner;    //!< rectangle in the top right corner
    QGraphicsRectItem *m_bottomRightCorner; //!< rectangle in the bottom right corner
    bool m_resizeMode;                      //!< activates resize mode
    bool m_rotationMode;                    //!< activiates rotation mode
    Corner m_corner;                        //!< enum with all corners
};
#endif
