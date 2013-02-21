#ifndef DESIGNERCOMPONENTS_H
#define DESIGNERCOMPONENTS_H

#include <QWidget>


class DesignerWidgetBoxInterface : public QWidget
{
public:
    explicit DesignerWidgetBoxInterface(QWidget *parent = 0) : QWidget(parent)
    {
        setMinimumSize(128, 128);
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    }
};

class DesignerPropertyEditorInterface : public QWidget
{
public:
    explicit DesignerPropertyEditorInterface(QWidget *parent = 0) : QWidget(parent)
    {
        setMinimumSize(128, 128);
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    }
};

class DesignerSampleInspectorInterface : public QWidget
{
public:
    explicit DesignerSampleInspectorInterface(QWidget *parent = 0) : QWidget(parent)
    {
        setMinimumSize(128, 128);
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    }
};

class DesignerSampleWorkspaceInterface : public QWidget
{
public:
    explicit DesignerSampleWorkspaceInterface(QWidget *parent = 0) : QWidget(parent)
    {
        setMinimumSize(128, 128);
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    }
};

//class QDesignerWidgetBoxInterface;
//class QDesignerFormEditorInterface;

class DesignerComponents
{
public:

    static DesignerWidgetBoxInterface *createWidgetBox(QWidget *parent);
    static DesignerPropertyEditorInterface *createPropertyEditor(QWidget *parent);
    static DesignerSampleInspectorInterface *createSampleInspector(QWidget *parent);
    static DesignerSampleWorkspaceInterface *createSampleWorkspace(QWidget *parent);
//    static QDesignerWidgetBoxInterface *createDesignerWidgetBox(QDesignerFormEditorInterface *core, QWidget *parent);

};

#endif // DESIGNERCOMPONENTS_H
