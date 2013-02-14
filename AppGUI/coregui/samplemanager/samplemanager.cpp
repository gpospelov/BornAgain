#include "samplemanager.h"
#include "designercomponents.h"
#include <QtWidgets>
#include <QDockWidget>
#include <QAbstractItemView>


SampleManager::SampleManager(QWidget *parent)
    : QMainWindow(parent)
{

    setObjectName(QLatin1String("SampleManager"));
    setDocumentMode(true);
    setTabPosition(Qt::AllDockWidgetAreas, QTabWidget::South);
    setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
    setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);

    initSubWindows();

    for (int i = 0; i < NumberOfSubWindows; i++) {
        QWidget *subWindow = m_subWindows[i];
        //subWindow->setWindowTitle(subs[i]->windowTitle());
        m_dockWidgets[i] = addDockForWidget(subWindow);

        // Since we have 1-pixel splitters, we generally want to remove
        // frames around item views. So we apply this hack for now.
        QList<QAbstractItemView*> frames = subWindow->findChildren<QAbstractItemView*>();
        for (int i = 0 ; i< frames.count(); ++i)
            frames[i]->setFrameStyle(QFrame::NoFrame);

    }
    resetToDefaultLayout();


}

QDockWidget *SampleManager::addDockForWidget(QWidget *w)
{
    QDockWidget *dock = new QDockWidget(tr("Customers"), this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    dock->setWidget(w);
//    addDockWidget(Qt::RightDockWidgetArea, dock);
    return dock;
}


void SampleManager::initSubWindows()
{
    qFill(m_subWindows, m_subWindows + NumberOfSubWindows, static_cast<QWidget*>(0));

    DesignerWidgetBoxInterface *wb = DesignerComponents::createWidgetBox(this);
    wb->setWindowTitle(tr("Widget Box"));
    wb->setObjectName(QLatin1String("WidgetBox"));
    m_subWindows[WidgetBoxSubWindow] = wb;

    DesignerSampleInspectorInterface *oi = DesignerComponents::createSampleInspector(this);
    oi->setWindowTitle(tr("Object Inspector"));
    oi->setObjectName(QLatin1String("ObjectInspector"));
    m_subWindows[SampleInspectorSubWindow] = oi;

    DesignerPropertyEditorInterface *pe = DesignerComponents::createPropertyEditor(this);
    pe->setWindowTitle(tr("Property Editor"));
    pe->setObjectName(QLatin1String("PropertyEditor"));
    m_subWindows[PropertyEditorSubWindow] = pe;

    DesignerSampleWorkspaceInterface *ae = DesignerComponents::createSampleWorkspace(this);
    ae->setWindowTitle(tr("Action Editor"));
    ae->setObjectName(QLatin1String("Workspace"));
    m_subWindows[SampleWorkspaceSubWindow] = ae;
}


void SampleManager::resetToDefaultLayout()
{
//    setTrackingEnabled(false);
//    QList<QDockWidget *> dockWidgetList = dockWidgets();
//    return qFindChildren<QDockWidget *>(this);

//    QList<QDockWidget *> dockWidgetList = findChildren<QDockWidget *>(this);
//    foreach (QDockWidget *dockWidget, dockWidgetList) {
//        dockWidget->setFloating(false);
//        removeDockWidget(dockWidget);
//    }

    addDockWidget(Qt::LeftDockWidgetArea, m_dockWidgets[WidgetBoxSubWindow]);
    addDockWidget(Qt::RightDockWidgetArea, m_dockWidgets[SampleInspectorSubWindow]);
    addDockWidget(Qt::RightDockWidgetArea, m_dockWidgets[PropertyEditorSubWindow]);
    addDockWidget(Qt::BottomDockWidgetArea, m_dockWidgets[SampleWorkspaceSubWindow]);

//    tabifyDockWidget(m_dockWidgets[ActionEditorSubWindow],
//                     m_dockWidgets[SignalSlotEditorSubWindow]);

//    foreach (QDockWidget *dockWidget, dockWidgetList)
//        dockWidget->show();

//    setTrackingEnabled(true);
}


