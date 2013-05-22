#ifndef SAMPLEVIEWCOMPONENTS_H
#define SAMPLEVIEWCOMPONENTS_H

#include <QWidget>
#include "widgetbox.h"
#include "SamplePropertyEditor.h"

//class SampleWidgetBoxInterface : public QWidget
//{
//public:
//    explicit SampleWidgetBoxInterface(QWidget *parent = 0) : QWidget(parent)
//    {
//        setMinimumSize(128, 128);
//        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//    }
//};

class SampleDesignerInterface;

typedef QDesignerWidgetBoxInterface SampleWidgetBoxInterface;


//class SamplePropertyEditorInterface : public QWidget
//{
//public:
//    explicit SamplePropertyEditorInterface(QWidget *parent = 0);
//};

class SampleTreeInspectorInterface : public QWidget
{
public:
    explicit SampleTreeInspectorInterface(QWidget *parent = 0) : QWidget(parent)
    {
        setMinimumSize(128, 128);
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    }
};

class SampleInfoStreamInterface : public QWidget
{
public:
    explicit SampleInfoStreamInterface(QWidget *parent = 0) : QWidget(parent)
    {
        setMinimumSize(128, 128);
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    }
};


class SampleViewComponents
{
public:
    static SampleWidgetBoxInterface *createWidgetBox(SampleDesignerInterface *core, QWidget *parent);
//    static SamplePropertyEditorInterface *createPropertyEditor(QWidget *parent);
    static SamplePropertyEditor *createPropertyEditor(SampleDesignerInterface *core,QWidget *parent);
    static SampleTreeInspectorInterface *createTreeInspector(QWidget *parent);
    static SampleInfoStreamInterface *createInfoStream(QWidget *parent);
};

#endif // SAMPLEVIEWCOMPONENTS_H
