#include "ISampleView.h"
#include "DesignerHelper.h"
#include "qneport.h"

#include <QPainter>
#include <QStyleOptionGraphicsItem>


ISampleRectView::ISampleRectView(QGraphicsItem *parent, QRect rect)
    : ISampleView(parent)
    , m_rect(rect)
{
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
}


void ISampleRectView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    painter->setPen(Qt::black);
    if (option->state & (QStyle::State_Selected | QStyle::State_HasFocus)) {
        painter->setPen(Qt::DashLine);
    }

    painter->setBrush(DesignerHelper::getLayerGradient(Qt::gray, getRectangle() ) );
    painter->drawRect(getRectangle());
}


QNEPort* ISampleRectView::addPort(const QString &name, bool isOutput, int flags, int ptr)
{
    QNEPort *port = new QNEPort(this, name, isOutput);
    port->setNEBlock(this);

    Q_ASSERT(childItems().size());
    int hspace = getRectangle().height()*0.7;
    // vertical distance between ports
    int dy = hspace / (childItems().size() + 2);
    int ypos = getRectangle().height() - hspace + dy;

    int nOutPorts = getNumberOfOutputPorts();
    int nport(0);
    foreach(QGraphicsItem *port_, childItems()) {
        QNEPort *port = (QNEPort*) port_;
        if (port->isOutput()) {
            port->setPos(getRectangle().width(), ypos);
        }else{
            if(nport == nOutPorts) ypos +=dy; // additional margin between output and input ports
            port->setPos(0.0, ypos);
        }
        ypos += dy;
        nport++;
    }

    return port;
}


int ISampleRectView::getNumberOfOutputPorts()
{
    int result(0);
    foreach(QGraphicsItem *port_, childItems()) {
        QNEPort *port = (QNEPort*) port_;
        if (port->isOutput()) result++;
    }
    return result;
}

int ISampleRectView::getNumberOfInputPorts()
{
    return childItems().size() - getNumberOfOutputPorts();
}


//ISampleDefaultView::ISampleDefaultView(QGraphicsItem *parent)
//    : ISampleView(parent)
//    , m_rect(0, 0, DesignerHelper::getDefaultLayerWidth()/2, DesignerHelper::getDefaultLayerWidth()/2)
//{
//    setFlag(QGraphicsItem::ItemIsMovable, true);
//    setFlag(QGraphicsItem::ItemIsSelectable, true);
//    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
//}


//QRectF ISampleDefaultView::boundingRect() const
//{
//    return rect();
//}


//void ISampleDefaultView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
//{
//    Q_UNUSED(widget);

//    painter->setPen(Qt::black);
//    if (option->state & (QStyle::State_Selected | QStyle::State_HasFocus)) {
//        painter->setPen(Qt::DashLine);
//    }

//    painter->setBrush(DesignerHelper::getLayerGradient(Qt::gray, rect() ) );
//    painter->drawRect(rect());
//}

