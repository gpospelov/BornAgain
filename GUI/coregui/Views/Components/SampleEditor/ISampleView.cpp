#include "ISampleView.h"
#include "DesignerHelper.h"
#include "qneport.h"

#include <QPainter>
#include <QStyleOptionGraphicsItem>


ISampleRectView::ISampleRectView(QGraphicsItem *parent, QRect rect)
    : ISampleView(parent)
    , m_name("Unnamed")
    , m_color(Qt::gray)
    , m_rect(rect)
    , m_label_vspace(30)
{
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    //    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
    //    effect->setBlurRadius(8);
    //    effect->setOffset(2,2);
    //    setGraphicsEffect(effect);
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


// adding port to the sample
QNEPort* ISampleRectView::addPort(const QString &name, QNEPort::PortDirection direction, QNEPort::PortType port_type)
{
    QNEPort *port = new QNEPort(this, name, direction, port_type);
    port->setNEBlock(this);
    setPortCoordinates();
    return port;

}


// calculation right y-pos for ports
void ISampleRectView::setPortCoordinates()
{
    Q_ASSERT(childItems().size());
    int hspace = getRectangle().height();
    if( !getLabel().isEmpty() ) hspace -= m_label_vspace;

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
}


void ISampleRectView::setLabel(const QString &name)
{
    m_label = name;
    setPortCoordinates();
}



//QNEPort* ISampleRectView::addPort(const QString &name, bool isOutput, int flags, int ptr)
//{
//    QNEPort *port = new QNEPort(this, name, isOutput);
//    port->setNEBlock(this);

//    Q_ASSERT(childItems().size());
//    //int hspace = getRectangle().height()*m_ports_vspace;
//    int hspace = getRectangle().height() - m_label_vspace;
//    // vertical distance between ports
//    int dy = hspace / (childItems().size() + 2);
//    int ypos = getRectangle().height() - hspace + dy;

//    int nOutPorts = getNumberOfOutputPorts();
//    int nport(0);
//    foreach(QGraphicsItem *port_, childItems()) {
//        QNEPort *port = (QNEPort*) port_;
//        if (port->isOutput()) {
//            port->setPos(getRectangle().width(), ypos);
//        }else{
//            if(nport == nOutPorts) ypos +=dy; // additional margin between output and input ports
//            port->setPos(0.0, ypos);
//        }
//        ypos += dy;
//        nport++;
//    }

//    return port;
//}


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
