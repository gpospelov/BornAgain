// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/NodeEditorConnection.cpp
//! @brief     Implements class NodeEditorConnection
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "NodeEditorConnection.h"
#include "NodeEditorPort.h"
#include "ConnectableView.h"
#include <QBrush>
#include <QPen>
#include <QGraphicsScene>
#include <QPainter>
#include <QDebug>

NodeEditorConnection::NodeEditorConnection(QGraphicsItem *parent, QGraphicsScene *scene)
    : QGraphicsPathItem(parent)
    , m_port1(0)
    , m_port2(0)
{
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setPen(QPen(Qt::darkGray, 2));
    setBrush(Qt::NoBrush);
    setZValue(-1);
    if(scene) scene->addItem(this);
}


NodeEditorConnection::~NodeEditorConnection()
{
    qDebug() << "NodeEditorConnection::~NodeEditorConnection()" << this;
    if (m_port1) {
        qDebug() << " NodeEditorConnection removeAll from " << m_port1;
        m_port1->connections().removeAll(this);
    }
    if (m_port2) {
        qDebug() << " NodeEditorConnection removeAll from " << m_port2;
        m_port2->connections().removeAll(this);
    }
}

void NodeEditorConnection::setPos1(const QPointF &p)
{
    pos1 = p;
}


void NodeEditorConnection::setPos2(const QPointF &p)
{
    pos2 = p;
}


void NodeEditorConnection::setPort1(NodeEditorPort *p)
{
    m_port1 = p;
    m_port1->connections().append(this);
    setPos1(p->scenePos());
}

void NodeEditorConnection::setPort2(NodeEditorPort *p)
{
    m_port2 = p;
    m_port2->connections().append(this);
    setPos2(p->scenePos());
}

void NodeEditorConnection::updatePosFromPorts()
{
    pos1 = m_port1->scenePos();
    pos2 = m_port2->scenePos();
}


void NodeEditorConnection::updatePath()
{
    QPainterPath p;
    p.moveTo(pos1);
    qreal dx = pos2.x() - pos1.x();
    dx = qMax(dx, 200.);
    QPointF ctr1(pos1.x() + dx * 0.25, pos1.y() );
    QPointF ctr2(pos2.x() - dx * 0.25, pos2.y() );
    p.cubicTo(ctr1, ctr2, pos2);
    setPath(p);
}


NodeEditorPort* NodeEditorConnection::port1() const
{
    return m_port1;
}


NodeEditorPort* NodeEditorConnection::port2() const
{
    return m_port2;
}


NodeEditorPort *NodeEditorConnection::getInputPort()
{
    Q_ASSERT(m_port1 && m_port2);
    return (m_port1->isInput() ? m_port1 : m_port2);
}


NodeEditorPort *NodeEditorConnection::getOutputPort()
{
    Q_ASSERT(m_port1 && m_port2);
    return (m_port1->isOutput() ? m_port1 : m_port2);
}


void NodeEditorConnection::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->setPen(QPen(Qt::darkGray, 2));
    painter->setBrush(Qt::NoBrush);

    if (isSelected()) {
        painter->setPen(Qt::DashLine);
    }

    painter->drawPath(path());
}

ConnectableView *NodeEditorConnection::getParentView()
{
    Q_ASSERT(getInputPort() != getOutputPort());
    ConnectableView *result = dynamic_cast<ConnectableView *>(getInputPort()->parentItem());
    Q_ASSERT(result);
    return result;
}

ConnectableView *NodeEditorConnection::getChildView()
{
    Q_ASSERT(getInputPort() != getOutputPort());
    ConnectableView *result = dynamic_cast<ConnectableView *>(getOutputPort()->parentItem());
    Q_ASSERT(result);
    return result;
}

