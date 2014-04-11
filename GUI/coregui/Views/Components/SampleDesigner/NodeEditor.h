#ifndef NODEEDITOR_H
#define NODEEDITOR_H

/*
 * Node editor: original code is taken from
 * http://algoholic.eu/qnodeseditor-qt-nodesports-based-data-processing-flow-editor/
 * Copyright (c) 2012, STANISLAW ADASZEWSKI
 */

#include <QObject>

class QGraphicsScene;
class NodeEditorConnection;
class QGraphicsItem;
class QPointF;

//! The NodeEditor class implement for QGraphicsScene an editable schematic
//! of the dependency graph, displaying nodes and the connections between their
//! attributes
class NodeEditor : public QObject
{
	Q_OBJECT

public:
    explicit NodeEditor(QObject *parent = 0);

	void install(QGraphicsScene *scene);

	bool eventFilter(QObject *, QEvent *);

signals:
    void connectionIsEstablished(NodeEditorConnection *);

private:
	QGraphicsItem *itemAt(const QPointF&);

private:
	QGraphicsScene *scene;
    NodeEditorConnection *conn;
};

#endif // NODEEDITOR_H
