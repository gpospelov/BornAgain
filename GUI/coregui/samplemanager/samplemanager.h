#ifndef SAMPLEMANAGER_H
#define SAMPLEMANAGER_H

#include "fancymainwindow.h"
#include <QWidget>
#include <QMainWindow>
#include <QDockWidget>
//namespace SampleManager {

class SampleManager : public Manhattan::FancyMainWindow
{
public:

    enum SubWindows
    {
        WidgetBoxSubWindow,
        SampleInspectorSubWindow,
        PropertyEditorSubWindow,
        SampleWorkspaceSubWindow,
        NumberOfSubWindows
    };


    SampleManager(QWidget *parent = 0);


public slots:
    void resetToDefaultLayout();


private:
    void initSubWindows();
//    QDockWidget *addDockForWidget(QWidget *w);


    //FormEditorStack *m_stack;

    QWidget *m_subWindows[NumberOfSubWindows];


    QDockWidget *m_dockWidgets[NumberOfSubWindows];

};

//}

#endif // SAMPLEMANAGER_H
