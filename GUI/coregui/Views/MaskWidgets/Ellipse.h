#include <QWidget>
#include <QGraphicsProxyWidget>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include "DistributionEditor.h"
#include <QGraphicsView>
#include <QPainterPath>

#ifndef ELLIPSE_H
#define ELLIPSE_H

class Ellipse : public QGraphicsItem
{

public:
    enum {Type = UserType + 2};
    enum Color {INCLUDE, EXCLUDE};
    enum Corner { NONE, TOPLEFT, TOPRIGHT, BOTTOMLEFT, BOTTOMRIGHT };

    Ellipse(qreal posX, qreal poxY, qreal width, qreal heigth);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    QRectF boundingRect() const;
    void checkResizeRules(QGraphicsSceneMouseEvent *event);
    void calculateResize(QGraphicsSceneMouseEvent *event);
    qreal calculateRotation(QGraphicsSceneMouseEvent *event);
    int type() const {return Type;}
    void setWidth(qreal width);
    void setHeigth(qreal heigth);

    void setExclude();
    void setInclude();
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

private:
    qreal m_posX;
    qreal m_posY;
    qreal m_width;
    qreal m_heigth;
    QRectF m_topLeftCorner;
    QRectF m_bottomLeftCorner;
    QRectF m_topRightCorner;
    QRectF m_bottomRightCorner;
    bool m_resizeMode;
    bool m_rotationMode;
    Corner m_corner;
    Color m_color;
};
#endif
