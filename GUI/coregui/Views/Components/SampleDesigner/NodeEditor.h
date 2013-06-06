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

class NodeEditor : public QObject
{
	Q_OBJECT
public:
    explicit NodeEditor(QObject *parent = 0);

	void install(QGraphicsScene *scene);

	bool eventFilter(QObject *, QEvent *);

private:
	QGraphicsItem *itemAt(const QPointF&);

private:
	QGraphicsScene *scene;
    NodeEditorConnection *conn;
};

#endif // NODEEDITOR_H
