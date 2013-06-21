#ifndef ISAMPLEVIEW_H
#define ISAMPLEVIEW_H

#include "IView.h"
#include "NodeEditorPort.h"

class QPainter;
class QStyleOptionGraphicsItem;
class QWidget;

//! view of ISample's with rectangular shape and node functionality
class ConnectableView : public IView
{
public:
    enum { Type = DesignerHelper::ISampleRectType };
    ConnectableView(QGraphicsItem *parent = 0, QRect rect = QRect(0,0,50,50) );
    virtual ~ConnectableView(){}

    //! сalls the ISampleViewVisitor's visit method
    virtual void accept(ISampleViewVisitor *visitor) { visitor->visit(this); }

    int type() const { return Type; }

    virtual QRectF boundingRect() const { return getRectangle(); }
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    virtual NodeEditorPort* addPort(const QString &name, NodeEditorPort::PortDirection direction, NodeEditorPort::PortType port_type);

    //! connect input port of given view with appropriate output port(s) of other item, returns list of created connections
    virtual QList<QGraphicsItem *> connectInputPort(ConnectableView *other);

    //! returns list of items connected to all input ports
    virtual QList<ConnectableView *> getConnectedInputItems() const;

    virtual QString getName() const { return m_name; }
    virtual QColor getColor() const { return m_color; }
    virtual QRect getRectangle() const { return m_rect;}
    virtual void setRectangle(QRect rect) { m_rect = rect; }
    virtual QString getLabel() const { return m_label; }
    virtual void setLabel(const QString &name);

public slots:
    virtual void setName(const QString &name) { m_name = name; }
    virtual void setColor(const QColor &color) { m_color = color; }

protected:
    virtual void setPortCoordinates();
    virtual int getNumberOfPorts();
    virtual int getNumberOfOutputPorts();
    virtual int getNumberOfInputPorts();

    QString m_name;
    QColor m_color;
    QRect m_rect;
    int m_roundpar;
    double m_label_vspace; // vertical space occupied by the label
    QString m_label;
};


//! default view of unimplemented ISample's
class ISampleDefaultView : public ConnectableView
{
public:
    ISampleDefaultView(QGraphicsItem *parent = 0) : ConnectableView(parent){}
    //! сalls the ISampleViewVisitor's visit method
    virtual void accept(ISampleViewVisitor *visitor) { visitor->visit(this); }
};



#endif //  ISAMPLEVIEW_H
