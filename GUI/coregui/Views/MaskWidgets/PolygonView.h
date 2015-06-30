#include <QWidget>
#include <QGraphicsProxyWidget>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include "DistributionEditor.h"
#include <QGraphicsView>
#include <QPainterPath>
#include <QBrush>
#include "IView.h"


#ifndef POLYGONVIEW_H
#define POLYGONVIEW_H
class PolygonItem;

class PolygonView : public IView
{
Q_OBJECT

public:

    enum {Type = UserType + 3};
    enum Color {INCLUDE, EXCLUDE};

    PolygonView();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    QRectF boundingRect() const;
    qreal calculateRotation(QGraphicsSceneMouseEvent *event);
    bool isCornerClicked(QGraphicsSceneMouseEvent *event);
    QRectF calculateBoundingRectangle() const;
    QRectF getFirstPoint() const;
    int type() const {return Type;}
    void setExclude();
    void setInclude();
    QRectF getTopLeftCorner();
    QRectF getTopRightCorner();
    QRectF getBottomLeftCorner();
    QRectF getBottomRightCorner();
    ParameterizedItem *getParameterizedItem();
    void setParameterizedItem(ParameterizedItem *item);
    QPointF getLastPoint() const;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    bool m_changeCornerMode;
    int m_indexOfCurrentSelectedPoint;
    ParameterizedItem *m_item;
};
#endif
