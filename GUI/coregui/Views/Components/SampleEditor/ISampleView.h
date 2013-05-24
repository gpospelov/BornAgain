#ifndef ISAMPLEVIEW_H
#define ISAMPLEVIEW_H

#include <QGraphicsObject>

class QPainter;
class QStyleOptionGraphicsItem;
class QWidget;


#include "qneport.h"

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
//    virtual QNEPort* addPort(const QString &name, bool isOutput, int flags = 0, int ptr = 0);

    virtual QNEPort* addPort(const QString &name, QNEPort::PortDirection direction, QNEPort::PortType port_type);


    QString getName() const { return m_name; }
    void setName(const QString &name) { m_name = name; }
    QColor getColor() const { return m_color; }
    void setColor(const QColor &color) { m_color = color; }
    QRect getRectangle() const { return m_rect;}
    void setRectangle(QRect rect) { m_rect = rect; }

protected:
    virtual int getNumberOfOutputPorts();
    virtual int getNumberOfInputPorts();

    QString m_name;
    QColor m_color;
    QRect m_rect;
    double m_label_vspace; // vertical space occupied by the label
//    double m_ports_vspace; // vertical space occupied by ports
};


//! default view of unimplemented ISample's
class ISampleDefaultView : public ISampleRectView
{
public:
    ISampleDefaultView(QGraphicsItem *parent = 0) : ISampleRectView(parent){}
};



#endif //  ISAMPLEVIEW_H
