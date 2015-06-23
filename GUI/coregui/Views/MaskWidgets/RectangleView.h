#include <QWidget>
#include <QGraphicsProxyWidget>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include "DistributionEditor.h"
#include <QGraphicsView>
#include <QPainterPath>

#ifndef RECTANGLEVIEW_H
#define RECTANGLEVIEW_H

class RectangleItem;

class RectangleView :public QGraphicsObject
{
Q_OBJECT

public:
    //! describes corner
    enum Corner { NONE, TOPLEFT, TOPRIGHT, BOTTOMLEFT, BOTTOMRIGHT };
    enum Point { X, Y};
    enum {Type = UserType + 1};
//    enum Color {INCLUDE = 0, EXCLUDE = 1};

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
    void checkResizeRules(QGraphicsSceneMouseEvent *event);

    //! calculates resized rectangle
    //! @param event mouse event to set new coordinates
    void calculateResize(QGraphicsSceneMouseEvent *event);

    //! calculates rotated rectangle
    //! @param event mouse event to set new coordinates
    //! @return degree of rotation
    qreal calculateRotation(QGraphicsSceneMouseEvent *event);

    int type() const {return Type;}
    void setInclude();
    void setExclude();
    QRectF getTopLeftCorner();
    QRectF getTopRightCorner();
    QRectF getBottomLeftCorner();
    QRectF getBottomRightCorner();
    void setItem(ParameterizedItem *item);
    void setPosition(qreal x, qreal y);
    qreal getXValue() const;
    qreal getYValue() const;
public slots:
    void onXValueChanged();
    void onYValueChanged();
//    void onPropertyChange(const QString &propertyName);
protected:
    //! paintEvent paints Rectangle and corners
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
//    QVariant itemChange(GraphicsItemChange change, const QVariant &value);


private:
    RectangleItem *m_item;
    Corner m_corner;                        //!< enum with all corners
    bool m_block_update;
    int degree;
};
#endif

