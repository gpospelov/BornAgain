#include "SampleViewComponents.h"
#include "widgetbox.h"
#include "SampleDesigner.h"


//SampleTreeInspector::SampleTreeInspector(QWidget *parent)
//    : QWidget(parent)
//{
//    setMinimumSize(128, 128);
//    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

//}



//SampleWidgetBoxInterface *SampleViewComponents::createWidgetBox(SampleDesignerInterface *core, QWidget *parent)
//{
//    QDesignerWidgetBoxInterface *result = new qdesigner_internal::WidgetBox(core, parent);
//    result->setFileName(QStringLiteral(":/widgetbox/widgetbox.xml"));
//    result->load();
//    result->setWindowTitle(QLatin1String("Widget Box"));
//    result->setObjectName(QLatin1String("WidgetBox"));
//    //m_sampleEditor->setWidgetBox(wb);
//    return result;
//}

SampleWidgetBox *SampleViewComponents::createWidgetBox(SampleDesignerInterface *core, QWidget *parent)
{
    return new SampleWidgetBox(core, parent);
}


//SamplePropertyEditorInterface *SampleViewComponents::createPropertyEditor(QWidget *parent)
SamplePropertyEditor *SampleViewComponents::createPropertyEditor(SampleDesignerInterface *core, QWidget *parent)
{
    //SamplePropertyEditorInterface *result = new SamplePropertyEditorInterface(parent);
//    SamplePropertyEditor *result = new SamplePropertyEditor(core, parent);
//    result->setWindowTitle(QLatin1String("Property Editor"));
//    result->setObjectName(QLatin1String("PropertyEditor"));
    return new SamplePropertyEditor(core, parent);
}

SampleTreeInspector *SampleViewComponents::createTreeInspector(QWidget *parent)
{
    return new SampleTreeInspector(parent);
}

SampleInfoStreamInterface *SampleViewComponents::createInfoStream(QWidget *parent)
{
    return new SampleInfoStreamInterface(parent);
}

