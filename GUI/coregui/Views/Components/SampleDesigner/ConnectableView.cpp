#include "ConnectableView.h"
#include "DesignerHelper.h"
#include "NodeEditorPort.h"
#include "NodeEditorConnection.h"

#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QObject>
#include <iostream>

ConnectableView::ConnectableView(QGraphicsItem *parent, QRect rect)
    : IView(parent)
    , m_name("Unnamed")
    , m_color(Qt::gray)
    , m_rect(rect)
    , m_roundpar(3)
    , m_label_vspace(35)
{
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
}


void ConnectableView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    painter->setPen(Qt::gray);
    if (option->state & (QStyle::State_Selected | QStyle::State_HasFocus)) {
        painter->setPen(Qt::DashLine);
    }

    painter->setBrush(DesignerHelper::getDecorationGradient(m_color, getRectangle() ) );
    painter->drawRoundedRect(getRectangle(), m_roundpar, m_roundpar);

    if ( m_label.isEmpty() ) return;

    painter->setPen(Qt::black);
    double width = getRectangle().width()*0.9;
    double yoffset = 5; // space above the label
    double height = m_label_vspace - yoffset;
    QFont serifFont("Monospace", 12, QFont::Normal);
    painter->setFont(serifFont);
    QRect textRect( getRectangle().x() + (getRectangle().width()-width)/2., getRectangle().y() + yoffset, width, height );
    painter->drawText(textRect, Qt::AlignCenter, m_label);
}


// adding port to the sample
NodeEditorPort* ConnectableView::addPort(const QString &name, NodeEditorPort::PortDirection direction, NodeEditorPort::PortType port_type)
{
    NodeEditorPort *port = new NodeEditorPort(this, name, direction, port_type);
    setPortCoordinates();
    return port;
}


// calculation of y-pos for ports
void ConnectableView::setPortCoordinates()
{
    if(!getNumberOfPorts()) return;

    // without main label ports can be placed over all rectangle vertical space
    int hspace = getRectangle().height();
    if( !getLabel().isEmpty() ) hspace -= m_label_vspace;

    int nintervals = getNumberOfPorts() + 2; // one spare interval for margin between input/output ports

    int dy = hspace / double(nintervals);
    int ypos = getRectangle().height() - hspace + dy;

    if(getNumberOfPorts() == 1) {
        // if total number of ports is 1, place it in the middle
        ypos = getRectangle().height() - hspace + hspace/2;
    }

    int nOutPorts = getNumberOfOutputPorts();
    int nport(0);
    foreach(QGraphicsItem *item, childItems()) {
        NodeEditorPort *port = dynamic_cast<NodeEditorPort *>(item);
        if( !port ) continue;
        if (port->isOutput()) {
            port->setPos(getRectangle().width(), ypos);
        }else{
            if(nport == nOutPorts && nOutPorts!=0) ypos +=dy; // additional margin between output and input ports
            port->setPos(0.0, ypos);
        }
        ypos += dy;
        nport++;
    }
}


void ConnectableView::setLabel(const QString &name)
{
    m_label = name;
    setPortCoordinates();
}


int ConnectableView::getNumberOfPorts()
{
    int result(0);
    foreach(QGraphicsItem *item, childItems()) {
        NodeEditorPort *port = dynamic_cast<NodeEditorPort *>(item);
        if (port) result++;
    }
    return result;
}


int ConnectableView::getNumberOfOutputPorts()
{
    int result(0);
    foreach(QGraphicsItem *item, childItems()) {
        NodeEditorPort *port = dynamic_cast<NodeEditorPort *>(item);
        if (port && port->isOutput()) result++;
    }
    return result;
}


int ConnectableView::getNumberOfInputPorts()
{
    return getNumberOfPorts()-getNumberOfOutputPorts();
}


// connect input port of given view with appropriate output port(s) of other item
// returns list of created connection
QList<QGraphicsItem *> ConnectableView::connectInputPort(ConnectableView *other)
{
    Q_ASSERT(other);
    QList<QGraphicsItem *> result;
    foreach(QGraphicsItem *item, childItems()) {
        NodeEditorPort *port = dynamic_cast<NodeEditorPort *>(item);
        if (port && port->isInput() && !port->isConnected()) {
            foreach(QGraphicsItem *other_item, other->childItems()) {
                NodeEditorPort *other_port= dynamic_cast<NodeEditorPort *>(other_item);
                if(other_port && port->getPortType() == other_port->getPortType()) {
                    NodeEditorConnection *conn = new NodeEditorConnection(0, scene());
                    conn->setPort2(port);
                    conn->setPort1(other_port);
                    conn->setPos2(port->scenePos());
                    conn->setPos1(other_port->scenePos());
                    conn->updatePath();
                    result.append(conn);
                }
            }
        }
    }
    return result;
}


//! returns list of items connected to all input ports
QList<ConnectableView *> ConnectableView::getConnectedInputItems() const
{
    QList<ConnectableView *> result;
    foreach(QGraphicsItem *item, childItems()) {
        NodeEditorPort *port = dynamic_cast<NodeEditorPort *>(item);
        if (port && port->isInput()) {
            for(int i=0; i<port->connections().size(); ++i) {
                Q_ASSERT(port->connections().at(i)->port1()->parentItem());
                ConnectableView *connected = dynamic_cast<ConnectableView *>(port->connections().at(i)->port1()->parentItem());
                if(connected) {
                    result.append(connected);
                }
            }
        }
    }
    return result;
}


