#include "designercomponents.h"




DesignerWidgetBoxInterface *DesignerComponents::createWidgetBox(QWidget *parent)
{
    return new DesignerWidgetBoxInterface(parent);
}

DesignerPropertyEditorInterface *DesignerComponents::createPropertyEditor(QWidget *parent)
{
    return new DesignerPropertyEditorInterface(parent);
}

DesignerSampleInspectorInterface *DesignerComponents::createSampleInspector(QWidget *parent)
{
    return new DesignerSampleInspectorInterface(parent);
}

DesignerSampleWorkspaceInterface *DesignerComponents::createSampleWorkspace(QWidget *parent)
{
    return new DesignerSampleWorkspaceInterface(parent);
}

