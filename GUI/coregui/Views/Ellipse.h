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
    enum Corner { TOPLEFT, TOPRIGHT, BOTTOMLEFT, BOTTOMRIGHT };

    Ellipse(qreal posX, qreal poxY, qreal width, qreal heigth);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    QRectF boundingRect() const;
    void checkResizeRules(QGraphicsSceneMouseEvent *event);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    qreal m_posX;
    qreal m_posY;
    qreal m_width;
    qreal m_heigth;
    QGraphicsRectItem *m_topLeftCorner;
    QGraphicsRectItem *m_bottomLeftCorner;
    QGraphicsRectItem *m_topRightCorner;
    QGraphicsRectItem *m_bottomRightCorner;
    bool m_resizeMode;
    Corner m_corner;
};
#endif
