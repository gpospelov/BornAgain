/* Copyright (c) 2012, STANISLAW ADASZEWSKI
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of STANISLAW ADASZEWSKI nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL STANISLAW ADASZEWSKI BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */

#include "qneport.h"

#include <QGraphicsScene>
#include <QFontMetrics>

#include <QPen>

#include "qneconnection.h"

#include "ISampleView.h"

//QNEPort::QNEPort(QGraphicsItem *parent, QGraphicsScene *scene)
////    : QGraphicsPathItem(parent, scene)
//    : QGraphicsPathItem(parent)
//{
//	label = new QGraphicsTextItem(this);

//	m_radius = 5;
//	margin = 2;

//	QPainterPath p;
//	p.addEllipse(-m_radius, -m_radius, 2*m_radius, 2*m_radius);
//	setPath(p);

//	setPen(QPen(Qt::darkRed));
//	setBrush(Qt::red);

//	setFlag(QGraphicsItem::ItemSendsScenePositionChanges);

//	m_portFlags = 0;
//    //scene->addItem(this);
//}


QNEPort::QNEPort(QGraphicsItem *parent, const QString &name, QNEPort::PortDirection direction, QNEPort::PortType port_type)
    : QGraphicsPathItem(parent)
    , m_name(name)
//    , m_isOutput(false)
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

    m_portFlags = 0;

    label = new QGraphicsTextItem(this);
    label->setPlainText(m_name);
    QFont serifFont("Monospace", 10, QFont::Normal);
    label->setFont(serifFont);

    if(isOutput()) {
        label->setPos(-m_radius - m_margin - label->boundingRect().width(), -label->boundingRect().height()/2);
    } else {
        label->setPos(m_radius + m_margin, -label->boundingRect().height()/2);
    }


}


//QNEPort::QNEPort(QGraphicsItem *parent, const QString &name, bool isOutput)
//    : QGraphicsPathItem(parent)
//    , m_name(name)
//    , m_isOutput(isOutput)
//    , m_color(Qt::green)
//    , m_radius(5)
//    , m_margin(2)
//{
//    QPainterPath p;
//    p.addEllipse(-m_radius, -m_radius, 2*m_radius, 2*m_radius);
//    setPath(p);

//    setPen(QPen(m_color.darker(180)));
//    setBrush(m_color);

//    setFlag(QGraphicsItem::ItemSendsScenePositionChanges);

//    m_portFlags = 0;

//    label = new QGraphicsTextItem(this);
//    label->setPlainText(m_name);
//    QFont serifFont("Monospace", 10, QFont::Normal);
//    label->setFont(serifFont);

//    if(m_isOutput) {
//        label->setPos(-m_radius - m_margin - label->boundingRect().width(), -label->boundingRect().height()/2);
//    } else {
//        label->setPos(m_radius + m_margin, -label->boundingRect().height()/2);
//    }

//}



QNEPort::~QNEPort()
{
	foreach(QNEConnection *conn, m_connections)
		delete conn;
}

//void QNEPort::setNEBlock(QNEBlock *b)
//{
//	m_block = b;
//}

void QNEPort::setNEBlock(ISampleView *b)
{
    m_block = b;
}

void QNEPort::setName(const QString &n)
{
    m_name = n;
	label->setPlainText(n);
}

#include <iostream>
void QNEPort::setIsOutput(bool o)
{
    std::cout << "PANIC " << std::endl;
    Q_ASSERT(0);
//    Q_ASSERT(scene());

//    m_isOutput = o;

//	QFontMetrics fm(scene()->font());
//	QRect r = fm.boundingRect(name);

//	if (isOutput_)
//		label->setPos(-radius_ - margin - label->boundingRect().width(), -label->boundingRect().height()/2);
//	else
//		label->setPos(radius_ + margin, -label->boundingRect().height()/2);

}

int QNEPort::radius()
{
    return m_radius;
}

bool QNEPort::isOutput()
{
//    return m_isOutput;
    return (m_direction == Output ? true : false);
}

QVector<QNEConnection*>& QNEPort::connections()
{
	return m_connections;
}

void QNEPort::setPortFlags(int f)
{
//    Q_ASSERT(scene());

	m_portFlags = f;

	if (m_portFlags & TypePort)
	{
//		QFont font(scene()->font());
//		font.setItalic(true);
//		label->setFont(font);
		setPath(QPainterPath());
	} else if (m_portFlags & NamePort)
	{
//		QFont font(scene()->font());
//		font.setBold(true);
//		label->setFont(font);
		setPath(QPainterPath());
	}
}

//QNEBlock* QNEPort::block() const
//{
//	return m_block;
//}

ISampleView* QNEPort::block() const
{
    return m_block;
}


//quint64 QNEPort::ptr()
//{
//	return m_ptr;
//}

//void QNEPort::setPtr(quint64 p)
//{
//	m_ptr = p;
//}

bool QNEPort::isConnected(QNEPort *other)
{
	foreach(QNEConnection *conn, m_connections)
		if (conn->port1() == other || conn->port2() == other)
			return true;

	return false;
}

QVariant QNEPort::itemChange(GraphicsItemChange change, const QVariant &value)
{
	if (change == ItemScenePositionHasChanged)
	{
		foreach(QNEConnection *conn, m_connections)
		{
			conn->updatePosFromPorts();
			conn->updatePath();
		}
	}
	return value;
}


QColor QNEPort::getPortTypeColor(QNEPort::PortType port_type)
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


