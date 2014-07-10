#include "SampleView.h"
#include "SampleViewComponents.h"
#include "SampleDesigner.h"
#include "SampleToolBar.h"
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


SampleView::SampleView(SessionModel *sampleModel, SessionModel *instrumentModel, QWidget *parent)
    : Manhattan::FancyMainWindow(parent)
//    , m_materialBrowser(MaterialBrowser::instance())
    , m_sampleDesigner(new SampleDesigner(this))
    , m_toolBar(0)
    , m_sampleModel(sampleModel)
    , m_instrumentModel(instrumentModel)
{
    setObjectName(tr("SampleView"));

//    m_materialBrowser->setParent(this);

    setCentralWidget(m_sampleDesigner->getCentralWidget());

    setDocumentMode(true);
    setTabPosition(Qt::AllDockWidgetAreas, QTabWidget::South);
    setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
    setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);

    initSubWindows();
    initSelectionModel();

    for (int i = 0; i < NumberOfSubWindows; i++) {
        QWidget *subWindow = m_subWindows[i];
        //subWindow->setWindowTitle(subs[i]->windowTitle());
        m_dockWidgets[i] = addDockForWidget(subWindow);

        // Since we have 1-pixel splitters, we generally want to remove
        // frames around item views. So we apply this hack for now.
        QList<QAbstractItemView*> frames =
                subWindow->findChildren<QAbstractItemView*>();
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
//    delete m_materialBrowser;
}

//void SampleView::materialEditorCall()
//{
//    std::cout << "SampleView::materialEditorCall() ->" << std::endl;
//}


void SampleView::initSubWindows()
{
    qFill(m_subWindows, m_subWindows + NumberOfSubWindows,
          static_cast<QWidget*>(0));

    m_subWindows[WidgetBoxSubWindow] =
            SampleViewComponents::createWidgetBox(m_sampleDesigner, this);

    m_tree_view = SampleViewComponents::createTreeView(m_sampleModel, this);
    m_subWindows[SampleTreeView] = m_tree_view;

    m_subWindows[PropertyEditorSubWindow] =
            SampleViewComponents::createPropertyEditor(
                m_tree_view->selectionModel(), this);

    SampleInfoStreamInterface *ae =
            SampleViewComponents::createInfoStream(this);
    ae->setWindowTitle(tr("Info Stream"));
    ae->setObjectName(tr("InfoStream"));
    m_subWindows[InfoSubWindow] = ae;

    m_sampleDesigner->setSampleModel(m_sampleModel);
    m_sampleDesigner->setInstrumentModel(m_instrumentModel);
    m_sampleDesigner->setSelectionModel(m_tree_view->selectionModel());
}

void SampleView::initSelectionModel()
{
    m_selection_model = m_tree_view->selectionModel();
}

void SampleView::createActions()
{
    m_add_item_mapper = new QSignalMapper(this);
    connect(m_add_item_mapper, SIGNAL(mapped(const QString &)),
            this, SLOT(addItem(const QString &)));

    m_delete_item_action = new QAction(tr("Delete"), this);
    m_delete_item_action->setStatusTip(tr("Delete current object"));
    connect(m_delete_item_action, SIGNAL(triggered()),
            this, SLOT(deleteItem()));
}

void SampleView::resetToDefaultLayout()
{
    setTrackingEnabled(false);
    QList<QDockWidget *> dockWidgetList = dockWidgets();
    foreach (QDockWidget *dockWidget, dockWidgetList) {
        dockWidget->setFloating(false);
        removeDockWidget(dockWidget);
    }

    addDockWidget(Qt::LeftDockWidgetArea,
                  m_dockWidgets[WidgetBoxSubWindow]);
    addDockWidget(Qt::RightDockWidgetArea,
                  m_dockWidgets[SampleTreeView]);
    addDockWidget(Qt::RightDockWidgetArea,
                  m_dockWidgets[PropertyEditorSubWindow]);
    addDockWidget(Qt::BottomDockWidgetArea,
                  m_dockWidgets[InfoSubWindow]);

//    tabifyDockWidget(m_dockWidgets[SampleInspectorSubWindow],
//                     m_dockWidgets[PropertyEditorSubWindow]);

    foreach (QDockWidget *dockWidget, dockWidgetList)
        dockWidget->show();

    setTrackingEnabled(true);
}

void SampleView::addItem(const QString &item_name)
{
    QModelIndex currentIndex = getTreeView()->currentIndex();
    ParameterizedItem * new_item = getSampleModel()->insertNewItem(
                item_name, currentIndex);
    if (new_item) setCurrentIndex(getSampleModel()->indexOfItem(new_item));
    setDirty();
    updateUi();
}

void SampleView::deleteItem()
{
    QModelIndex currentIndex = getTreeView()->currentIndex();
    if (!currentIndex.isValid()) return;
    QModelIndex parent_index = getSampleModel()->parent(currentIndex);
    int row = currentIndex.row();
    if (currentIndex.isValid()) {
        getSampleModel()->removeRows(row, 1, parent_index);
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
        addItemNames = getSampleModel()->getAcceptableChildItems(parent_index);
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
    connect(m_toolBar, SIGNAL(deleteItems()),
            m_sampleDesigner->getView(), SLOT(deleteSelectedItems()));
    connect(m_toolBar, SIGNAL(selectionMode(int)), m_sampleDesigner->getView(), SLOT(onSelectionMode(int)));
    connect(m_sampleDesigner->getView(), SIGNAL(selectionModeChanged(int)),m_toolBar, SLOT(onViewSelectionMode(int)));

//    connect(m_toolBar, SIGNAL(zoomOut()),
//            m_sampleDesigner->getView(), SLOT(zoomOut()));
//    connect(m_toolBar, SIGNAL(zoomIn()),
//            m_sampleDesigner->getView(), SLOT(zoomIn()));
//    connect(m_toolBar, SIGNAL(zoomFit()),
//            m_sampleDesigner->getView(), SLOT(zoomFit()));
//    connect(m_toolBar, SIGNAL(clearAll()),
//            m_sampleDesigner->getView(), SLOT(clearAll()));
//    connect(m_toolBar, SIGNAL(smartAlign()),
//            m_sampleDesigner, SLOT(onSmartAlign()));

//    connect(m_toolBar, SIGNAL(sceneScaleChanged(QString)),
//            m_sampleDesigner->getView(), SLOT(onSceneScaleChanged(QString)));


    // connect context menu for tree view
    connect(m_tree_view, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(showContextMenu(const QPoint &)));

    addToolBar(m_toolBar);
}

void SampleView::setCurrentIndex(const QModelIndex &index)
{
    if (index.isValid()) {
        m_tree_view->scrollTo(index);
        m_tree_view->setCurrentIndex(index);
    }
}

SessionModel *SampleView::getSampleModel()
{
    return m_sampleModel;
}

QTreeView *SampleView::getTreeView()
{
    return m_tree_view;
}


