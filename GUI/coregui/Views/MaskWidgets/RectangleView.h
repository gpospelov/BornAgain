#ifndef RECTANGLEVIEW_H
#define RECTANGLEVIEW_H

#include "IView.h"

class QPainter;
class ParameterizedItem;
class QGraphicsSceneMouseEvent;
class QPointF;

class RectangleView :public IView
{
Q_OBJECT

public:
    //! describes corner

    enum Corner { NONE, TOPLEFT, TOPRIGHT, BOTTOMLEFT, BOTTOMRIGHT };
    enum Mode { ROTATION, RESIZE };
    enum {Type = UserType + 1};

    RectangleView();
    QRectF boundingRect() const;
    int type() const {return Type;}
    void setInclude();
    void setExclude();
    ParameterizedItem *getParameterizedItem();
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
    Corner m_corner;                        //!< enum with all corners
    Mode m_mode;
    bool m_block_mode;
    QPointF *m_diagonalOpposedPoint;

    void setDiagonalOpposedPoint();
    QPointF getDiagonalOpposedPoint();
    void calculateResize(QGraphicsSceneMouseEvent *event);
    qreal getRotationAngle(QGraphicsSceneMouseEvent *event);
    void setSelectedCorner(QPointF currentMousePosition);
    void updateRotationArrows();
    void initializeArrow();
    QRectF getTopLeftCorner();
    QRectF getTopRightCorner();
    QRectF getBottomLeftCorner();
    QRectF getBottomRightCorner();
};
#endif

