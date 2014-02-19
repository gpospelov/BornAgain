#include "SampleView.h"
#include "SampleViewComponents.h"
#include "SampleDesigner.h"
#include "SampleToolBar.h"
#include "MaterialBrowser.h"
#include "GUIHelpers.h"
#include <ItemFactory.h>


#include <QDockWidget>
#include <QAbstractItemView>
#include <QToolBar>
#include <QAction>
#include <QToolButton>
#include <QMenu>


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
    setObjectName(tr("SampleView"));

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

    createActions();



    connectSignals();

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

    m_session = new SessionModel();
    // Temporary for testing
    QStandardItem *multilayer = m_session->insertNewItem("MultiLayer", QModelIndex());
    QStandardItem *layer = m_session->insertNewItem("Layer", multilayer->index());
    m_session->insertNewItem("ParticleDecoration", layer->index());
    m_session->insertNewItem("Layer", QModelIndex());
    // END temporary
    m_tree_view = SampleViewComponents::createTreeView(m_session, this);
    m_subWindows[SampleTreeView] = m_tree_view;

    m_subWindows[PropertyEditorSubWindow] = SampleViewComponents::createPropertyEditor(m_sampleDesigner, this);

    SampleInfoStreamInterface *ae = SampleViewComponents::createInfoStream(this);
    ae->setWindowTitle(tr("Info Stream"));
    ae->setObjectName(tr("InfoStream"));
    m_subWindows[InfoSubWindow] = ae;
}

void SampleView::createActions()
{
    m_add_item_mapper = new QSignalMapper(this);
    connect(m_add_item_mapper, SIGNAL(mapped(const QString &)),
            this, SLOT(addItem(const QString &)));

    m_delete_item_action = new QAction(tr("Delete"), this);
    m_delete_item_action->setStatusTip(tr("Delete current object"));
    connect(m_delete_item_action, SIGNAL(triggered()), this, SLOT(deleteItem()));
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

void SampleView::addItem(const QString &item_name)
{
    QModelIndex currentIndex = getTreeView()->currentIndex();
    getSessionModel()->insertNewItem(item_name, currentIndex);
    setDirty();
    updateUi();
}


void SampleView::deleteItem()
{
    QModelIndex currentIndex = getTreeView()->currentIndex();
    if (currentIndex.isValid()) {
        QStandardItem *item = getSessionModel()->itemFromIndex(currentIndex);
        QString name = item->text();
        int rows = item->rowCount();
        QString message;
        if (rows == 0)
            message = tr("<p>Delete '%1'").arg(name);
        else if (rows == 1)
            message = tr("<p>Delete '%1' and its child (and "
                         "grandchildren etc.)").arg(name);
        else if (rows > 1)
            message = tr("<p>Delete '%1' and its %2 children (and "
                         "grandchildren etc.)").arg(name).arg(rows);
        if (!GUIHelpers::okToDelete(this, tr("Delete"), message)) return;
        getSessionModel()->removeRow(currentIndex.row(), currentIndex.parent());
        setDirty();
        updateUi();
    }
}

void SampleView::showContextMenu(const QPoint &pnt)
{
    QMenu menu;
    QMenu add_menu(QString("Add"));
    QList<QString> addItemNames;
    QModelIndex parent_index = getTreeView()->indexAt(pnt);
    getTreeView()->setCurrentIndex(parent_index);
    if (!parent_index.isValid()) {
        addItemNames = ItemFactory::getAllItemNames();
    } else {
        QStandardItem *parent = getSessionModel()->itemFromIndex(parent_index);
        ParameterizedItem *parent_par = static_cast<ParameterizedItem *>(parent);
        addItemNames = parent_par->getAcceptableChildren();
    }
    if (addItemNames.size() > 0) {
        foreach (QString item_name, addItemNames) {
            QAction *add_action = 0;
            if (m_add_action_map.contains(item_name)) {
                add_action = m_add_action_map[item_name];
            }
            else {
                add_action = new QAction(item_name, this);
                m_add_action_map[item_name] = add_action;
                connect(add_action, SIGNAL(triggered()),
                        m_add_item_mapper, SLOT(map()));
                m_add_item_mapper->setMapping(add_action, item_name);
            }
            add_menu.addAction(add_action);
        }
        menu.addMenu(&add_menu);
    }
    if (parent_index.isValid()) {
        menu.addAction(m_delete_item_action);
    }
    if (!menu.isEmpty()) {
        menu.exec(getTreeView()->mapToGlobal(pnt));
    }
}

void SampleView::updateUi()
{
}


void SampleView::connectSignals()
{
    // toolBar should be initialized after MaterialBrowser
    m_toolBar = new SampleToolBar(this);
    connect(m_toolBar, SIGNAL(zoomOut()), m_sampleDesigner->getView(), SLOT(zoomOut()));
    connect(m_toolBar, SIGNAL(zoomIn()), m_sampleDesigner->getView(), SLOT(zoomIn()));
    connect(m_toolBar, SIGNAL(zoomFit()), m_sampleDesigner->getView(), SLOT(zoomFit()));
    connect(m_toolBar, SIGNAL(clearAll()), m_sampleDesigner->getView(), SLOT(clearAll()));
    connect(m_toolBar, SIGNAL(sceneToISample()), m_sampleDesigner, SLOT(sceneToISample()));

    // connect context menu for tree view
    QTreeView *tree_view = static_cast<QTreeView *>(m_subWindows[SampleTreeView]);
    connect(tree_view, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(showContextMenu(const QPoint &)));

    addToolBar(m_toolBar);
}

SessionModel *SampleView::getSessionModel()
{
    return m_session;
}

QTreeView *SampleView::getTreeView()
{
    return m_tree_view;
}


