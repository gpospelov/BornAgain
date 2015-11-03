#ifndef OBSOLETERECTANGLEVIEW_H
#define OBSOLETERECTANGLEVIEW_H

#include "IView.h"

class QPainter;
class ParameterizedItem;
class QGraphicsSceneMouseEvent;
class QPointF;

class ObsoleteRectangleView : public IView
{
    Q_OBJECT

public:
    ObsoleteRectangleView();

    //! describes the corners
    enum Corner { NONE, TOPLEFT, TOPRIGHT, BOTTOMLEFT, BOTTOMRIGHT };

    //! current active mode
    enum Mode { ROTATION, RESIZE };

    //! Type of this item
    enum { Type = UserType + 1 };

    //! boundingbox of this item
    QRectF boundingRect() const;

    //! returns the type of this item
    //! @return number of type
    int type() const
    {
        return Type;
    }

    //! rectangle is including an area and it's color is changing to red
    void setInclude();

    //! rectangle is excluding an area and it's color is changing to  blue
    void setExclude();

    //! get current rectangle item
    //! @return rectangle item as parameterized item
    ParameterizedItem *getParameterizedItem();

    //! set rectangle item
    //! @param rectangle item to be drawn
    void setParameterizedItem(ParameterizedItem *item);

public slots:
    //! called when x-value changed
    void onChangedX();

    //! called when x-value changed
    void onChangedY();

    //! called when property of rectangle changed
    void onPropertyChange(const QString &propertyName);

protected:
    //! paintEvent paints Rectangle and corners
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

    //! manages mouse press events
    //! @param event from scene
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    //! manages mouse move events
    //! @param event from scene
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

    //! manages mouse release events
    //! @param event from scene
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    //! manages hover events
    //! @param event from scene
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);

private:
    ParameterizedItem *m_item;       //!< rectangle item
    Corner m_corner;                 //!< enum with all corners
    Mode m_mode;                     //!< current active mode
    bool m_block_mode;               //!< blocking modes from changing
    QPointF *m_diagonalOpposedPoint; //!< diagonally opposite point from current selected corner

    //! set diagonally opposite point from current selected corner
    void setDiagonalOpposedPoint();

    //! @return diagonally opposite point from current selected corner
    QPointF getDiagonalOpposedPoint();

    //! calculates resized rectangle
    //! @param event to receive current mouse position
    void calculateResize(QGraphicsSceneMouseEvent *event);

    //! calculates angle for rotation
    //! @return angle between selected corner and mouse
    //! @param event to receive current mouse position
    qreal getRotationAngle(QGraphicsSceneMouseEvent *event);

    //! verfies clicked corner
    //! @param current mouse position
    void setSelectedCorner(QPointF currentMousePosition);

    //! updates all arrows;
    void updateArrows();

    //! initialize all arrows
    void initializeArrows();

    //! returns corner of rectangle
    //! @return top left corner
    QRectF getTopLeftCorner();

    //! returns corner of rectangle
    //! @return top right corner
    QRectF getTopRightCorner();

    //! returns corner of rectangle
    //! @return bottom left corner
    QRectF getBottomLeftCorner();

    //! returns corner of rectangle
    //! @return bottom right corner
    QRectF getBottomRightCorner();
};
#endif
