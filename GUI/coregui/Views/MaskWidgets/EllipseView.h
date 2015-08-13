#ifndef ELLIPSEVIEW_H
#define ELLIPSEVIEW_H

#include "IView.h"

class EllipseItem;
class QGraphicsSceneMouseEvent;
class QPainter;
class QPointF;

class EllipseView : public IView
{
    Q_OBJECT

public:
    EllipseView();

    //! describes the corners
    enum Corner { NONE, TOPLEFT, TOPRIGHT, BOTTOMLEFT, BOTTOMRIGHT };

    //! current active mode
    enum Mode { ROTATION, RESIZE };

    //! Type of this item
    enum { Type = UserType + 2 };

    //! boundingbox of this item
    QRectF boundingRect() const;

    //! returns the type of this item
    //! @return number of type
    int type() const
    {
        return Type;
    }

    //! ellipse including an area and it's color is changing to red
    void setInclude();

    //! ellipse is excluding an area and it's color is changing to  blue
    void setExclude();

    //! get current ellipse item
    //! @return ellipse item as parameterized item
    void setParameterizedItem(ParameterizedItem *item);

    //! get current ellipse item
    //! @return ellipse item as parameterized item
    ParameterizedItem *getParameterizedItem();

public slots:
    //! called when x-value changed
    void onChangedX();

    //! called when x-value changed
    void onChangedY();

    //! called when property of ellipse changed
    void onPropertyChange(const QString &propertyName);

protected:
    //! paintEvent paints ellipse and corners
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

    //! manages mouse press events
    //! @param event from scene
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    //! manages mouse move events
    //! @param event from scene
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

    //! manages hover events
    //! @param event from scene
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    //! manages hover events
    //! @param event from scene
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);

private:
    ParameterizedItem *m_item;       //!< ellipse item
    Corner m_corner;                 //!< enum with all corners
    Mode m_mode;                     //!< current active mode
    bool m_block_mode;               //!< blocking modes
    QPointF *m_diagonalOpposedPoint; //!< diagonally opposite point from current selected corner

    //! calculates angle for rotation
    //! @return angle between selected corner and mouse
    //! @param event to receive current mouse position
    qreal getRotationAngle(QGraphicsSceneMouseEvent *event);

    //! calculates resized ellipse
    //! @param event to receive current mouse position
    void calculateResize(QGraphicsSceneMouseEvent *event);

    //! updates all arrows;
    void updateArrows();

    //! initialize all arrows
    void initializeArrows();

    //! verfies clicked corner
    //! @param current mouse position
    void setSelectedCorner(QPointF currentMousePosition);

    //! set diagonally opposite point from current selected corner
    void setDiagonalOpposedPoint();

    //! returns corner of rectangle
    //! @return top left corner
    QRectF getTopLeftCorner();

    //! returns corner of rectangle
    //! @return top left corner
    QRectF getTopRightCorner();

    //! returns corner of rectangle
    //! @return top left corner
    QRectF getBottomLeftCorner();

    //! returns corner of rectangle
    //! @return top left corner
    QRectF getBottomRightCorner();
};
#endif
