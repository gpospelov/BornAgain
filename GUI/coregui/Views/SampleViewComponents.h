#ifndef SAMPLEVIEWCOMPONENTS_H
#define SAMPLEVIEWCOMPONENTS_H

#include <QWidget>


class SampleWidgetBoxInterface : public QWidget
{
public:
    explicit SampleWidgetBoxInterface(QWidget *parent = 0) : QWidget(parent)
    {
        setMinimumSize(128, 128);
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    }
};

class SamplePropertyEditorInterface : public QWidget
{
public:
    explicit SamplePropertyEditorInterface(QWidget *parent = 0) : QWidget(parent)
    {
        setMinimumSize(128, 128);
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    }
};

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
    static SampleWidgetBoxInterface *createWidgetBox(QWidget *parent);
    static SamplePropertyEditorInterface *createPropertyEditor(QWidget *parent);
    static SampleTreeInspectorInterface *createTreeInspector(QWidget *parent);
    static SampleInfoStreamInterface *createInfoStream(QWidget *parent);
};

#endif // SAMPLEVIEWCOMPONENTS_H
