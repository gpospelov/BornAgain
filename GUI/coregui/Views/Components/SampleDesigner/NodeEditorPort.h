#ifndef NODEEDITORPORT_H
#define NODEEDITORPORT_H

/*
 * Node editor: original code is taken from
 * http://algoholic.eu/qnodeseditor-qt-nodesports-based-data-processing-flow-editor/
 * Copyright (c) 2012, STANISLAW ADASZEWSKI
 */

#include <QGraphicsPathItem>
#include <QString>
#include "DesignerHelper.h"

class QNEBlock;
class NodeEditorConnection;
class ISampleView;

class NodeEditorPort : public QGraphicsPathItem
//class NodeEditorPort : public QGraphicsItem
{
public:
    enum { Type = DesignerHelper::NodeEditorPortType };

    //! type of ports, same type can be connected together
    enum PortType
    {
        Default,
        Interference,
        ParticleFactory,
        FormFactor,
        GeometryTransformation
    };

    //! port direction
    enum PortDirection
    {
        Input,
        Output
    };

    NodeEditorPort(QGraphicsItem *parent = 0, const QString &name=QString("unnamed"), PortDirection direction = Input, PortType port_type = Default);

//    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
//    virtual QRectF boundingRect() const;

    ~NodeEditorPort();

    bool isOutput();
    bool isInput();

    QVector<NodeEditorConnection*>& connections();

    const QString& portName() const { return m_name; }

	int type() const { return Type; }

    ISampleView* block() const;

    bool isConnected(NodeEditorPort*);

    PortType getPortType() const { return m_port_type; }

    static QColor getPortTypeColor(NodeEditorPort::PortType port_type);

protected:
	QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
    QString m_name;
    PortDirection m_direction;
    PortType m_port_type;
    QColor m_color;
    int m_radius;
    int m_margin;
    QVector<NodeEditorConnection*> m_connections;
//    QRect m_rect;
};


#endif // NODEEDITORPORT_H
