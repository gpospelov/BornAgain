// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleView.h
//! @brief     Defines class SampleView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef SAMPLEVIEW_H
#define SAMPLEVIEW_H

#include "WinDllMacros.h"
#include "fancymainwindow.h"
#include <QAction>
#include <QTreeView>

class MainWindow;
class SampleViewDocks;
class SampleDesigner;
class SampleToolBar;
class ApplicationModels;
class SampleModel;
class SampleTreeWidget;

class BA_CORE_API_ SampleView : public Manhattan::FancyMainWindow
{
    Q_OBJECT

public:
    enum ESubWindows
    {
        WIDGET_BOX,         // drag & drop items
        SAMPLE_TREE,             // a tree view
        PROPERTY_EDITOR,    // property editor
        INFO,              // status/info display
        NUMBER_OF_SUB_WINDOWS
    };

    SampleView(MainWindow *mainWindow);
    virtual ~SampleView();

public slots:
    void resetToDefaultLayout();
    void setDockHeightForWidget(int height);
    void onWidgetCloseRequest();

    SampleModel *getSampleModel();

protected slots:
    void dockToMinMaxSizes();
    void onDockVisibilityChangeV2(bool status);


private:
    //! Stores sizes of dock widget
    struct DockSizeInfo {
        DockSizeInfo():m_dock(nullptr){}
        QDockWidget *m_dock;
        QSize m_min_size;
        QSize m_max_size;
    };

    void initSubWindows();
    void connectSignals();
    void scrollToIndex(const QModelIndex &index);
    QModelIndex getIndexAtColumnZero(const QModelIndex &index);

    QTreeView *getTreeView();
    QItemSelectionModel* selectionModel();

    ApplicationModels* m_models;

    SampleViewDocks* m_docks;

    SampleDesigner* sampleDesigner();

    SampleToolBar *m_toolBar;            // toolbar
    QWidget *m_subWindows[NUMBER_OF_SUB_WINDOWS];
    QDockWidget *m_dockWidgets[NUMBER_OF_SUB_WINDOWS];

    QMap<QWidget *, QDockWidget *> m_widget_to_dock;
    QMap<QDockWidget *, QWidget *> m_dock_to_widget;


    DockSizeInfo m_dock_info;
};


#endif // SAMPLEVIEW_H
