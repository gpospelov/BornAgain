#include "SampleViewComponents.h"


SampleWidgetBoxInterface *SampleViewComponents::createWidgetBox(QWidget *parent)
{
    return new SampleWidgetBoxInterface(parent);
}

SamplePropertyEditorInterface *SampleViewComponents::createPropertyEditor(QWidget *parent)
{
    return new SamplePropertyEditorInterface(parent);
}

SampleTreeInspectorInterface *SampleViewComponents::createTreeInspector(QWidget *parent)
{
    return new SampleTreeInspectorInterface(parent);
}

SampleInfoStreamInterface *SampleViewComponents::createInfoStream(QWidget *parent)
{
    return new SampleInfoStreamInterface(parent);
}

