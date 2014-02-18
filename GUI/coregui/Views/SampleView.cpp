#include "SampleView.h"
#include "SampleViewComponents.h"
#include "SampleDesigner.h"
#include "SampleToolBar.h"
#include "MaterialBrowser.h"
#include "SessionModel.h"


#include <QDockWidget>
#include <QAbstractItemView>
//#include "widgetbox.h"
//#include "QToolBar"
#include <QToolBar>
#include <QAction>
#include <QToolButton>


#include <iostream>

#if QT_VERSION < 0x050000
#define QStringLiteral QString
#endif


SampleView::SampleView(QWidget *parent)
    : Manhattan::FancyMainWindow(parent)
    , m_materialBrowser(new MaterialBrowser(this))
    , m_sampleDesigner(new SampleDesigner(this))
    , m_toolBar(0)
{
    setObjectName(QLatin1String("SampleView"));

    setCentralWidget(m_sampleDesigner->getCentralWidget());

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

    initActions();

}


SampleView::~SampleView()
{
    delete m_sampleDesigner;
    delete m_materialBrowser;
}

//void SampleView::materialEditorCall()
//{
//    std::cout << "SampleView::materialEditorCall() ->" << std::endl;
//}


void SampleView::initSubWindows()
{
    qFill(m_subWindows, m_subWindows + NumberOfSubWindows, static_cast<QWidget*>(0));

    m_subWindows[WidgetBoxSubWindow] = SampleViewComponents::createWidgetBox(m_sampleDesigner, this);

    SessionModel *session_model = new SessionModel();
    // Temporary for testing
    QStandardItem *multilayer = session_model->insertNewItem("MultiLayer", QModelIndex());
    QStandardItem *layer = session_model->insertNewItem("Layer", QModelIndex());
    session_model->insertNewItem("Layer", multilayer->index());
    // END temporary
    m_subWindows[SampleTreeView] = SampleViewComponents::createTreeView(session_model, this);

    m_subWindows[PropertyEditorSubWindow] = SampleViewComponents::createPropertyEditor(m_sampleDesigner, this);

    SampleInfoStreamInterface *ae = SampleViewComponents::createInfoStream(this);
    ae->setWindowTitle(tr("Info Stream"));
    ae->setObjectName(QLatin1String("InfoStream"));
    m_subWindows[InfoSubWindow] = ae;
}


void SampleView::initActions()
{
    // toolBar should be initialized after MaterialBrowser
    m_toolBar = new SampleToolBar(this);
    connect(m_toolBar, SIGNAL(zoomOut()), m_sampleDesigner->getView(), SLOT(zoomOut()));
    connect(m_toolBar, SIGNAL(zoomIn()), m_sampleDesigner->getView(), SLOT(zoomIn()));
    connect(m_toolBar, SIGNAL(zoomFit()), m_sampleDesigner->getView(), SLOT(zoomFit()));
    connect(m_toolBar, SIGNAL(clearAll()), m_sampleDesigner->getView(), SLOT(clearAll()));
    connect(m_toolBar, SIGNAL(sceneToISample()), m_sampleDesigner, SLOT(sceneToISample()));

    addToolBar(m_toolBar);
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
    addDockWidget(Qt::RightDockWidgetArea, m_dockWidgets[SampleTreeView]);
    addDockWidget(Qt::RightDockWidgetArea, m_dockWidgets[PropertyEditorSubWindow]);
    addDockWidget(Qt::BottomDockWidgetArea, m_dockWidgets[InfoSubWindow]);

//    tabifyDockWidget(m_dockWidgets[SampleInspectorSubWindow],
//                     m_dockWidgets[PropertyEditorSubWindow]);

    foreach (QDockWidget *dockWidget, dockWidgetList)
        dockWidget->show();

    setTrackingEnabled(true);
}

