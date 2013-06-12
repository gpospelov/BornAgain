#ifndef SAMPLEMANAGER_H
#define SAMPLEMANAGER_H

#include "fancymainwindow.h"
#include <QWidget>
#include <QMainWindow>
#include <QDockWidget>


class SampleDesignerInterface;
class SampleDesigner;
class SampleToolBar;
class MaterialBrowser;


class SampleView : public Manhattan::FancyMainWindow
{
    Q_OBJECT

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
    virtual ~SampleView();


public slots:
    void resetToDefaultLayout();
    void materialEditorCall();

private:
    void initSubWindows();

    MaterialBrowser *m_materialBrowser;
    SampleDesigner *m_sampleDesigner;
    SampleToolBar *m_toolBar;
    QWidget *m_subWindows[NumberOfSubWindows];
    QDockWidget *m_dockWidgets[NumberOfSubWindows];
};


#endif // SAMPLEMANAGER_H
