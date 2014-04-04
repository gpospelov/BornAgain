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

    QGraphicsTextItem *label = new QGraphicsTextItem(this);
    label->setPlainText(m_name);
    QFont serifFont("Monospace", 10, QFont::Normal);
    label->setFont(serifFont);

    if(isOutput()) {
        label->setPos(-m_radius - m_margin - label->boundingRect().width(), -label->boundingRect().height()/2);
    } else {
        label->setPos(m_radius + m_margin, -label->boundingRect().height()/2);
    }

//    QFont serifFont("Monospace", 10, QFont::Normal);
//    QFontMetrics fm(serifFont);
//    QRect text_rect = fm.boundingRect(m_name);
//    qreal height = qMax(fm.height(), 2*m_radius);
//    if(isOutput()) {
//        m_rect = QRect(-m_radius-m_margin-text_rect.width(), -text_rect.height()/2., 2*m_radius+m_margin+text_rect.width(), text_rect.height());
//    }else {
//        m_rect = QRect(-m_radius, -height/2., 2*m_radius+m_margin+text_rect.width(), height);
//    }
}

NodeEditorPort::~NodeEditorPort()
{
    foreach(NodeEditorConnection *conn, m_connections)
		delete conn;
}


void NodeEditorPort::deleteAllConnections()
{
    foreach(NodeEditorConnection *conn, m_connections)
        delete conn;
    m_connections.clear();
}


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
    case ParticleFactory:
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


//QRectF NodeEditorPort::boundingRect() const
//{
//    return m_rect;
//}


//void NodeEditorPort::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
//{
//    Q_UNUSED(widget);
//    painter->setPen(m_color.darker(180) );
//    painter->setBrush(m_color);
//    painter->drawEllipse(-m_radius, -m_radius, 2*m_radius, 2*m_radius);
//    painter->setPen(Qt::black);
//    QFont serifFont("Monospace", 10, QFont::Normal);
//    QFontMetrics fm(serifFont);
//    QRect rect = fm.boundingRect(m_name);
//    painter->setFont(serifFont);
//    if(isOutput()) {
//        painter->drawText(-m_radius - m_margin - m_rect.width(), rect.height()/2, m_name);
//    } else {
//        painter->drawText(m_radius + m_margin, rect.height()/2, m_name);
//    }
//}
