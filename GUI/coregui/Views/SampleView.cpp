#include "SampleView.h"
#include "SampleViewComponents.h"
#include "SampleEditor.h"

#include <QDockWidget>
#include <QAbstractItemView>
#include "widgetbox.h"


#if QT_VERSION < 0x050000
#define QStringLiteral QString
#endif


SampleView::SampleView(QWidget *parent)
    : Manhattan::FancyMainWindow(parent)
    , m_sampleEditor(0)
{
    m_sampleEditor = new SampleEditor(parent);

    setObjectName(QLatin1String("SampleView"));

    setCentralWidget(m_sampleEditor->getCentralWidget());

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

    QDesignerWidgetBoxInterface *wb = new qdesigner_internal::WidgetBox(m_sampleEditor, this);
    wb->setFileName(QStringLiteral(":/widgetbox/widgetbox.xml"));
    wb->load();
    wb->setWindowTitle(tr("Widget Box"));
    wb->setObjectName(QLatin1String("WidgetBox"));
    //m_sampleEditor->setWidgetBox(wb);
    m_subWindows[WidgetBoxSubWindow] = wb;

    SampleTreeInspectorInterface *oi = SampleViewComponents::createTreeInspector(this);
    oi->setWindowTitle(tr("Object Inspector"));
    oi->setObjectName(QLatin1String("ObjectInspector"));
    m_subWindows[SampleInspectorSubWindow] = oi;

    SamplePropertyEditorInterface *pe = SampleViewComponents::createPropertyEditor(this);
    pe->setWindowTitle(tr("Property Editor"));
    pe->setObjectName(QLatin1String("PropertyEditor"));
    m_subWindows[PropertyEditorSubWindow] = pe;

    SampleInfoStreamInterface *ae = SampleViewComponents::createInfoStream(this);
    ae->setWindowTitle(tr("Info Stream"));
    ae->setObjectName(QLatin1String("InfoStream"));
    m_subWindows[InfoSubWindow] = ae;
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
    addDockWidget(Qt::BottomDockWidgetArea, m_dockWidgets[InfoSubWindow]);

//    tabifyDockWidget(m_dockWidgets[SampleInspectorSubWindow],
//                     m_dockWidgets[PropertyEditorSubWindow]);

    foreach (QDockWidget *dockWidget, dockWidgetList)
        dockWidget->show();

    setTrackingEnabled(true);
}

