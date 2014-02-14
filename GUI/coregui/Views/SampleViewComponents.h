#ifndef SAMPLEVIEWCOMPONENTS_H
#define SAMPLEVIEWCOMPONENTS_H

#include <QWidget>
#include <QTreeView>
#include "widgetbox.h"

#include "SamplePropertyEditor.h"
#include "SampleTreeInspector.h"
#include "SampleWidgetBox.h"
#include "SessionModel.h"

//class SampleWidgetBoxInterface : public QWidget
//{
//public:
//    explicit SampleWidgetBoxInterface(QWidget *parent = 0) : QWidget(parent)
//    {
//        setMinimumSize(128, 128);
//        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//    }
//};

//class SampleDesignerInterface;

//typedef QDesignerWidgetBoxInterface SampleWidgetBoxInterface;



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
    static SampleWidgetBox *createWidgetBox(SampleDesignerInterface *core, QWidget *parent);
    static SamplePropertyEditor *createPropertyEditor(SampleDesignerInterface *core,QWidget *parent);
    static QTreeView *createTreeView(SessionModel *session_model, QWidget *parent);
    static SampleInfoStreamInterface *createInfoStream(QWidget *parent);
};

#endif // SAMPLEVIEWCOMPONENTS_H
