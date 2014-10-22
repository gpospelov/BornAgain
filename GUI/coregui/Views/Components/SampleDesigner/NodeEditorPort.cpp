#include "NodeEditorPort.h"
#include "NodeEditorConnection.h"
//#include "ISampleView.h"

#include <QGraphicsScene>
#include <QFontMetrics>
#include <QPen>
#include <QPainter>
#include <iostream>


NodeEditorPort::NodeEditorPort(QGraphicsItem *parent, const QString &name, NodeEditorPort::PortDirection direction, NodeEditorPort::PortType port_type)
    : QGraphicsPathItem(parent)
//    : QGraphicsItem(parent)
    , m_name(name)
    , m_direction(direction)
    , m_port_type(port_type)
    , m_radius(5)
    , m_margin(2)
{
    m_color = getPortTypeColor(port_type);

    QPainterPath p;
    p.addEllipse(-m_radius, -m_radius, 2*m_radius, 2*m_radius);
    setPath(p);

    setPen(QPen(m_color.darker(180)));
    setBrush(m_color);

    setFlag(QGraphicsItem::ItemSendsScenePositionChanges);

    if(!m_name.isEmpty()) {
        QGraphicsTextItem *label = new QGraphicsTextItem(this);
        label->setPlainText(m_name);
        QFont serifFont("Monospace", DesignerHelper::getPortFontSize(), QFont::Normal);
        label->setFont(serifFont);

        if(isOutput()) {
            label->setPos(-m_radius - m_margin - label->boundingRect().width(), -label->boundingRect().height()/2);
        } else {
            label->setPos(m_radius + m_margin, -label->boundingRect().height()/2);
        }
    }
}


NodeEditorPort::~NodeEditorPort()
{
    foreach(NodeEditorConnection *conn, m_connections) {
        conn->setSelected(false);
		delete conn;
    }
}


//void NodeEditorPort::deleteAllConnections()
//{
//    foreach(NodeEditorConnection *conn, m_connections)
//        delete conn;
//    m_connections.clear();
//}


bool NodeEditorPort::isOutput()
{
    return (m_direction == Output ? true : false);
}

bool NodeEditorPort::isInput()
{
    return !isOutput();
}


QVector<NodeEditorConnection*>& NodeEditorPort::connections()
{
	return m_connections;
}


bool NodeEditorPort::isConnected(NodeEditorPort *other)
{
    foreach(NodeEditorConnection *conn, m_connections)
		if (conn->port1() == other || conn->port2() == other)
			return true;

	return false;
}


QVariant NodeEditorPort::itemChange(GraphicsItemChange change, const QVariant &value)
{
	if (change == ItemScenePositionHasChanged)
	{
        foreach(NodeEditorConnection *conn, m_connections)
		{
			conn->updatePosFromPorts();
			conn->updatePath();
		}
	}
	return value;
}


QColor NodeEditorPort::getPortTypeColor(NodeEditorPort::PortType port_type)
{
    switch(port_type)
    {
    case Default:
       return QColor(Qt::gray);
       break;
    case Interference:
       return QColor(Qt::yellow);
       break;
    case ParticleLayout:
       return QColor(Qt::green);
       break;
    case FormFactor:
       return QColor(Qt::blue);
       break;
    case GeometryTransformation:
       return QColor(Qt::magenta);
       break;
    default:
        return QColor(Qt::red);
        break;
    }
}

