#ifndef SAMPLEWIDGETBOX_H
#define SAMPLEWIDGETBOX_H

#include <QWidget>

class QDesignerWidgetBoxInterface;
class SampleDesignerInterface;

//! widget box and tool window on the left side of SampleView
class SampleWidgetBox : public QWidget
{
public:
    explicit SampleWidgetBox(SampleDesignerInterface *core, QWidget *parent);

private:
    SampleDesignerInterface *m_core;
    QDesignerWidgetBoxInterface *m_widgetBox;
};

#endif // SAMPLEWIDGETBOX_H
