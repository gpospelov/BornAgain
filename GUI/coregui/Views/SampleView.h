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

    SampleDesigner *m_sampleDesigner;
    QWidget *m_subWindows[NumberOfSubWindows];
    QDockWidget *m_dockWidgets[NumberOfSubWindows];
    SampleToolBar *m_toolBar;
    MaterialBrowser *m_materialBrowser;
};


#endif // SAMPLEMANAGER_H
