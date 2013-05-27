#ifndef NODEEDITORCONNECTION_H
#define NODEEDITORCONNECTION_H

/*
 * Node editor: original code is taken from
 * http://algoholic.eu/qnodeseditor-qt-nodesports-based-data-processing-flow-editor/
 * Copyright (c) 2012, STANISLAW ADASZEWSKI
 */

#include <QGraphicsPathItem>
#include "DesignerHelper.h"

class NodeEditorPort;

class NodeEditorConnection : public QGraphicsPathItem
{
public:
    enum { Type = DesignerHelper::NodeEditorConnectionType };

    NodeEditorConnection(QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);
    virtual ~NodeEditorConnection();

	void setPos1(const QPointF &p);
	void setPos2(const QPointF &p);
	void setPort1(NodeEditorPort *p);
	void setPort2(NodeEditorPort *p);
	void updatePosFromPorts();
	void updatePath();
	NodeEditorPort* port1() const;
	NodeEditorPort* port2() const;

	int type() const { return Type; }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
	QPointF pos1;
	QPointF pos2;
	NodeEditorPort *m_port1;
	NodeEditorPort *m_port2;
};

#endif // NODEEDITORCONNECTION_H
