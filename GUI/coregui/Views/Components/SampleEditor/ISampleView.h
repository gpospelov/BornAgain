#ifndef ISAMPLEVIEW_H
#define ISAMPLEVIEW_H

#include <QGraphicsObject>

class QPainter;
class QStyleOptionGraphicsItem;
class QWidget;


class ISampleView : public QGraphicsObject
{
public:
    ISampleView(QGraphicsItem *parent = 0) : QGraphicsObject(parent) {}
    virtual ~ISampleView(){}
};


class ISampleDefaultView : public ISampleView
{
public:
    ISampleDefaultView(QGraphicsItem *parent = 0);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    QRect rect() const { return m_rect;}
    QRect m_rect;
};


#endif //  ISAMPLEVIEW_H
