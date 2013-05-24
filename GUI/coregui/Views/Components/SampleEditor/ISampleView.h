#ifndef ISAMPLEVIEW_H
#define ISAMPLEVIEW_H

#include <QGraphicsObject>

class QPainter;
class QStyleOptionGraphicsItem;
class QWidget;
class QNEPort;


//! parent class for graphic representation of all ISample's
class ISampleView : public QGraphicsObject
{
public:
    ISampleView(QGraphicsItem *parent = 0) : QGraphicsObject(parent) {}
    virtual ~ISampleView(){}

};


//! view of ISample's with rectangular shape and node functionality
class ISampleRectView : public ISampleView
{
public:
    ISampleRectView(QGraphicsItem *parent = 0, QRect rect = QRect(0,0,50,50) );
    virtual ~ISampleRectView(){}

    virtual QRectF boundingRect() const { return getRectangle(); }
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    virtual QNEPort* addPort(const QString &name, bool isOutput, int flags = 0, int ptr = 0);
    virtual void setRectangle(QRect rect) { m_rect = rect; }

protected:
    virtual int getNumberOfOutputPorts();
    virtual int getNumberOfInputPorts();
    virtual QRect getRectangle() const { return m_rect;}

    QRect m_rect;
};


//! default view of unimplemented ISample's
class ISampleDefaultView : public ISampleRectView
{
public:
    ISampleDefaultView(QGraphicsItem *parent = 0) : ISampleRectView(parent){}
};



#endif //  ISAMPLEVIEW_H
