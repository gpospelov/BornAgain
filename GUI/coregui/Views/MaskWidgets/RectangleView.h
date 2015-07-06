#ifndef RECTANGLEVIEW_H
#define RECTANGLEVIEW_H

#include "IView.h"

class QPainter;
class ParameterizedItem;
class QGraphicsSceneMouseEvent;

class RectangleView :public IView
{
Q_OBJECT

public:
    //! describes corner

    enum Corner { NONE, TOPLEFT, TOPRIGHT, BOTTOMLEFT, BOTTOMRIGHT };
    enum Mode { ROTATION, RESIZE };
    enum {Type = UserType + 1};

    //! create Rectangle
    //! @param posX x position in scene
    //! @param posY y position in scene
    //! @param width of rectangle
    //! @param heigth of rectangle
    RectangleView();

    //! bounding box of rectangle
    QRectF boundingRect() const;

    //! check if resize rules are correct
    //! @param event mouse event to check if resizes correct

    // FIXME Rename this. It is not a "check", it is an action
    void checkResizeRules(QGraphicsSceneMouseEvent *event);

    //! calculates resized rectangle
    //! @param event mouse event to set new coordinates
    void calculateResize(QGraphicsSceneMouseEvent *event);

    //! calculates rotated rectangle
    //! @param event mouse event to set new coordinates
    //! @return degree of rotation
    qreal getRotationAngle(QGraphicsSceneMouseEvent *event);

    int type() const {return Type;}
    void setInclude();
    void setExclude();
    QRectF getTopLeftCorner();
    QRectF getTopRightCorner();
    QRectF getBottomLeftCorner();
    QRectF getBottomRightCorner();
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


private:
    ParameterizedItem *m_item;
    Corner m_corner;                        //!< enum with all corners
    Mode m_mode;
    bool m_block_update;

    void setSelectedCorner(QGraphicsSceneMouseEvent *event);
    void showRotationArrows();
};
#endif

