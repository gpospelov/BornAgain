#ifndef SAMPLEMANAGER_H
#define SAMPLEMANAGER_H

#include "fancymainwindow.h"
#include <QWidget>
#include <QMainWindow>
#include <QDockWidget>


class SampleDesignerInterface;
class SampleDesigner;

class SampleView : public Manhattan::FancyMainWindow
{
public:

    enum SubWindows
    {
        WidgetBoxSubWindow,
        SampleInspectorSubWindow,
        PropertyEditorSubWindow,
        InfoSubWindow,
        NumberOfSubWindows
    };

    SampleView(QWidget *parent = 0);

public slots:
    void resetToDefaultLayout();


private:
    void initSubWindows();

    SampleDesigner *m_sampleEditor;
    QWidget *m_subWindows[NumberOfSubWindows];
    QDockWidget *m_dockWidgets[NumberOfSubWindows];

};


#endif // SAMPLEMANAGER_H
