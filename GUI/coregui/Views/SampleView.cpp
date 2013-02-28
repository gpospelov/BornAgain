#include "SampleView.h"
#include "designercomponents.h"
//#include <QtWidgets>
#include "sampleeditor.h"

#include <QDockWidget>
#include <QAbstractItemView>

//#include <QDesignerFormEditorPluginInterface>

//#include <QDesignerComponents>
//#include <QDesignerWidgetBoxInterface>
//#include <QDesignerFormEditorInterface>
#include <QtDesigner/QDesignerComponents>
#include <QtDesigner/QDesignerWidgetBoxInterface>
#include <QtDesigner/QDesignerFormEditorInterface>
#include "widgetbox.h"


#if QT_VERSION < 0x050000
#define QStringLiteral QString
#endif


SampleView::SampleView(QWidget *parent)
    : Manhattan::FancyMainWindow(parent)
    , m_sampleEditor(0)
    , m_sampleEditorStack(0)
//    , m_formeditor(QDesignerComponents::createFormEditor(0))

{
    m_sampleEditor = new SampleEditor(parent);

    QWidget *widget = new QWidget(this);
    m_sampleEditorStack = new SampleEditorStack(this); // in Qt-creator it belongs to whole application
    m_sampleEditorStack->addWidget(widget);

    setObjectName(QLatin1String("EditorWidget"));
    setCentralWidget(m_sampleEditorStack);
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



void SampleView::initSubWindows()
{
    qFill(m_subWindows, m_subWindows + NumberOfSubWindows, static_cast<QWidget*>(0));

//    DesignerWidgetBoxInterface *wb = DesignerComponents::createWidgetBox(this);
//    wb->setWindowTitle(tr("Widget Box"));
//    wb->setObjectName(QLatin1String("WidgetBox"));
//    m_subWindows[WidgetBoxSubWindow] = wb;

//    QDesignerWidgetBoxInterface *wb = QDesignerComponents::createWidgetBox(m_sampleEditor, this);
    QDesignerWidgetBoxInterface *wb = new qdesigner_internal::WidgetBox(m_sampleEditor, this);
    wb->setFileName(QStringLiteral(":/widgetbox/widgetbox.xml"));
    wb->load();

    wb->setWindowTitle(tr("Widget Box"));
    wb->setObjectName(QLatin1String("WidgetBox"));
    //m_sampleEditor->setWidgetBox(wb);
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


void SampleView::resetToDefaultLayout()
{
    setTrackingEnabled(false);
    QList<QDockWidget *> dockWidgetList = dockWidgets();
    foreach (QDockWidget *dockWidget, dockWidgetList) {
        dockWidget->setFloating(false);
        removeDockWidget(dockWidget);
    }

    addDockWidget(Qt::LeftDockWidgetArea, m_dockWidgets[WidgetBoxSubWindow]);
    addDockWidget(Qt::RightDockWidgetArea, m_dockWidgets[SampleInspectorSubWindow]);
    addDockWidget(Qt::RightDockWidgetArea, m_dockWidgets[PropertyEditorSubWindow]);
    addDockWidget(Qt::BottomDockWidgetArea, m_dockWidgets[SampleWorkspaceSubWindow]);

//    tabifyDockWidget(m_dockWidgets[SampleInspectorSubWindow],
//                     m_dockWidgets[PropertyEditorSubWindow]);

    foreach (QDockWidget *dockWidget, dockWidgetList)
        dockWidget->show();

    setTrackingEnabled(true);
}

