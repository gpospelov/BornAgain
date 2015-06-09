#include <QWidget>
#include <QGraphicsProxyWidget>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include "DistributionEditor.h"
#include <QGraphicsView>
#include <QPainterPath>
#include <QBrush>

#ifndef POLYGON_H
#define POLYGON_H

class Polygon : public QGraphicsItem
{

public:
    enum Corner { NONE, TOPLEFT, TOPRIGHT, BOTTOMLEFT, BOTTOMRIGHT };

    Polygon(qreal posX, qreal poxY, qreal width, qreal heigth);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    QRectF boundingRect() const;
    void checkResizeRules(QGraphicsSceneMouseEvent *event);
    void calculateResize(QGraphicsSceneMouseEvent *event);
    qreal calculateRotation(QGraphicsSceneMouseEvent *event);
    bool checkCornerClicked(QGraphicsSceneMouseEvent *event);
    void calculateBoundingRectangle();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

private:
    qreal m_posX;
    qreal m_posY;
    qreal m_width;
    qreal m_heigth;
    QGraphicsRectItem *m_topLeftCorner;
    QGraphicsRectItem *m_bottomLeftCorner;
    QGraphicsRectItem *m_topRightCorner;
    QGraphicsRectItem *m_bottomRightCorner;
    QGraphicsRectItem *m_firstPoint;
    bool m_resizeMode;
    bool m_rotationMode;
    bool m_drawingMode;
    bool m_changeCornerMode;
    Corner m_corner;
    QPolygon m_polygon;
    int m_currentPoint1;
    int m_currentPoint2;
};
#endif
