#ifndef ELLIPSEVIEW_H
#define ELLIPSEVIEW_H

#include "IView.h"

class EllipseItem;
class QGraphicsSceneMouseEvent;
class QPainter;
class QPointF;

class EllipseView :public IView
{
Q_OBJECT

public:
    //! describes corner
    enum Corner { NONE, TOPLEFT, TOPRIGHT, BOTTOMLEFT, BOTTOMRIGHT };
    enum Mode { ROTATION, RESIZE };
    enum {Type = UserType + 1};

    EllipseView();
    QRectF boundingRect() const;
    int type() const {return Type;}
    void setInclude();
    void setExclude();
    void setParameterizedItem(ParameterizedItem *item);

public slots:
    void onChangedX();
    void onChangedY();
    void onPropertyChange(const QString &propertyName);

protected:
    //! paintEvent paints Rectangle and corners
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);

private:
    ParameterizedItem *m_item;
    Corner m_corner;
    Mode m_mode;
    bool m_block_mode;
    QPointF *m_diagonalOpposedPoint;

    qreal getRotationAngle(QGraphicsSceneMouseEvent *event);
    void calculateResize(QGraphicsSceneMouseEvent *event);
    void updateRotationArrows();
    void initializeArrow();
    void setSelectedCorner(QPointF currentMousePosition);
    void setDiagonalOpposedPoint();
    QRectF getTopLeftCorner();
    QRectF getTopRightCorner();
    QRectF getBottomLeftCorner();
    QRectF getBottomRightCorner();
    ParameterizedItem *getParameterizedItem();
};
#endif
