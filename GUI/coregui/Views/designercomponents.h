#ifndef DESIGNERCOMPONENTS_H
#define DESIGNERCOMPONENTS_H

#include <QWidget>


class DesignerWidgetBoxInterface : public QWidget
{
public:
    explicit DesignerWidgetBoxInterface(QWidget *parent = 0) : QWidget(parent) {}
};

class DesignerPropertyEditorInterface : public QWidget
{
public:
    explicit DesignerPropertyEditorInterface(QWidget *parent = 0) : QWidget(parent) {}
};

class DesignerSampleInspectorInterface : public QWidget
{
public:
    explicit DesignerSampleInspectorInterface(QWidget *parent = 0) : QWidget(parent) {}
};

class DesignerSampleWorkspaceInterface : public QWidget
{
public:
    explicit DesignerSampleWorkspaceInterface(QWidget *parent = 0) : QWidget(parent) {}
};

class DesignerComponents
{
public:

    static DesignerWidgetBoxInterface *createWidgetBox(QWidget *parent);
    static DesignerPropertyEditorInterface *createPropertyEditor(QWidget *parent);
    static DesignerSampleInspectorInterface *createSampleInspector(QWidget *parent);
    static DesignerSampleWorkspaceInterface *createSampleWorkspace(QWidget *parent);

};

#endif // DESIGNERCOMPONENTS_H
