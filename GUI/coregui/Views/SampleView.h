#ifndef SAMPLEMANAGER_H
#define SAMPLEMANAGER_H

#include "fancymainwindow.h"
#include <QWidget>
#include <QMainWindow>
#include <QDockWidget>
#include <QTreeView>
#include <QAction>

#include "SessionModel.h"


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
        WidgetBoxSubWindow,         // drag & drop items
        SampleTreeView,             // a tree view
        PropertyEditorSubWindow,    // property editor
        InfoSubWindow,              // status/info display
        NumberOfSubWindows
    };

    SampleView(QWidget *parent = 0);
    virtual ~SampleView();


public slots:
    void resetToDefaultLayout();
    void addItem();
    void deleteItem();
//    void materialEditorCall();

protected slots:
    void showContextMenu(const QPoint &pnt);
    void setDirty(bool dirty=true) { setWindowModified(dirty); }
    void updateUi();

private:
    void initSubWindows();
    void createActions();
    void connectSignals();

    SessionModel *getSessionModel();
    QTreeView *getTreeView();

    MaterialBrowser *m_materialBrowser;  // material editor
    SampleDesigner *m_sampleDesigner;    // main sample view
    SampleToolBar *m_toolBar;            // toolbar
    QWidget *m_subWindows[NumberOfSubWindows];
    QDockWidget *m_dockWidgets[NumberOfSubWindows];

    QAction *addAct;
    QAction *delAct;

    SessionModel *m_session;
    QTreeView *m_tree_view;
};


#endif // SAMPLEMANAGER_H
