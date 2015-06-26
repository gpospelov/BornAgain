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

public:

    enum {Type = UserType + 3};
    enum Color {INCLUDE, EXCLUDE};
    enum Corner { NONE, TOPLEFT, TOPRIGHT, BOTTOMLEFT, BOTTOMRIGHT };

    PolygonView();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    QRectF boundingRect() const;
    void checkResizeRules(QGraphicsSceneMouseEvent *event);
    void calculateResize(QGraphicsSceneMouseEvent *event);
    qreal calculateRotation(QGraphicsSceneMouseEvent *event);
    bool checkCornerClicked(QGraphicsSceneMouseEvent *event);
    void calculateBoundingRectangle();
    void setWidth(qreal width);
    void setHeigth(qreal heigth);
    void setDrawingMode(QPointF firstPoint);
    bool getDrawingMode() const;
    void setMouseIsOverFirstPoint(bool mouseIsOverFirstPoint);
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

public slots:
    void onPropertyChange(const QString &propertyName);
    void onSubItemPropertyChanged(QString, QString);
    void onSubItemChanged(QString);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    qreal m_width;
    qreal m_heigth;
    QRectF m_firstPoint;
    bool m_drawingMode;
    bool m_changeCornerMode;
    Corner m_corner;
    QPolygon m_polygon;
    int m_currentPoint1;
    int m_currentPoint2;
    bool m_mouseIsOverFirstPoint;
    Color m_color;

    ParameterizedItem*m_item;
    bool m_block_update;
};
#endif
