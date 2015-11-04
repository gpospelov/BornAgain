#ifndef OBSOLETEPOLYGONVIEW_H
#define OBSOLETEPOLYGONVIEW_H

#include "IView.h"

class ObsoletePolygonItem;
class QPainter;
class QGraphicsSceneMouseEvent;

class ObsoletePolygonView : public IView
{
    Q_OBJECT

public:
    ObsoletePolygonView();

    //! Type of this item
    enum { Type = UserType + 3 };

    //! boundingbox of this item
    QRectF boundingRect() const;

    //! returns the type of this item
    //! @return number of type
    int type() const
    {
        return Type;
    }

    //! polygon including an area and it's color is changing to red
    void setExclude();

    //! polygon is excluding an area and it's color is changing to  blue
    void setInclude();

    //! get current polygon item
    //! @return polygon item as parameterized item
    ParameterizedItem *getParameterizedItem();

    //! get current polygon item
    //! @return polygon item as parameterized item
    void setParameterizedItem(ParameterizedItem *item);

protected:
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
    bool m_changeCornerMode; //!< shows if someone is going to change the points from polygon
    int m_indexOfCurrentSelectedPoint; //!< index from current current selected point
    bool m_mouseIsOverFirstPoint;      //!<  shows if mouse is over the first point
    ParameterizedItem *m_item;         //!< polygon item

    //! first point as rectangle
    //! @return first point
    QRectF getFirstPoint() const;

    //! last point from polygon
    //! @return last added point
    QPointF getLastPoint() const;

    //! verifies if any of the points from polygon is clicked
    //! @return true if a point is selected else false
    bool isCornerClicked(QGraphicsSceneMouseEvent *event);

    //! calculates the bounding box of the polygon by looking for the smallest and biggest values.
    QRectF calculateBoundingRectangle() const;

    //! paints polygon
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
};
#endif
