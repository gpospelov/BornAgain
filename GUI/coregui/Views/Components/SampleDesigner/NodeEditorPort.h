// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/Components/SampleDesigner/NodeEditorPort.h
//! @brief     Defines class NodeEditorPort
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

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
class IView;

class BA_CORE_API_ NodeEditorPort : public QGraphicsPathItem
{
public:
    enum { TYPE = DesignerHelper::NODE_EDITOR_PORT };

    //! type of ports, same type can be connected together
    enum EPortType
    {
        DEFAULT,
        INTERFERENCE,
        PARTICLE_LAYOUT,
        FORM_FACTOR,
        TRANSFORMATION
    };

    //! port direction
    enum EPortDirection
    {
        INPUT,
        OUTPUT
    };

    NodeEditorPort(QGraphicsItem *parent = 0, const QString &name=QString("unnamed"), EPortDirection direction = INPUT, EPortType port_type = DEFAULT);

//    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
//    virtual QRectF boundingRect() const;

    ~NodeEditorPort();

    bool isOutput();
    bool isInput();

    QVector<NodeEditorConnection*>& connections();

    const QString& portName() const { return m_name; }

    int type() const { return TYPE; }

    IView* block() const;

    bool isConnected(NodeEditorPort*);

    bool isConnected() { return m_connections.size(); }

    EPortType getPortType() const { return m_port_type; }

    static QColor getPortTypeColor(NodeEditorPort::EPortType port_type);

//    void deleteAllConnections();

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
    QString m_name;
    EPortDirection m_direction;
    EPortType m_port_type;
    QColor m_color;
    int m_radius;
    int m_margin;
    QVector<NodeEditorConnection*> m_connections;
//    QRect m_rect;
};


#endif // NODEEDITORPORT_H
