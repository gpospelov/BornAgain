// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleView.cpp
//! @brief     Implements class SampleView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "SampleView.h"
#include "SampleViewDocks.h"
#include "FilterPropertyProxy.h"
#include "InfoWidget.h"
#include "ItemFactory.h"
#include "SampleDesigner.h"
#include "SamplePropertyWidget.h"
#include "SampleToolBar.h"
#include "mainwindow.h"
#include "ApplicationModels.h"
#include "SampleWidgetBox.h"
#include "ItemTreeView.h"
#include "SampleTreeWidget.h"
#include <QDockWidget>
#include <QMenu>
#include <QTimer>


SampleView::SampleView(MainWindow *mainWindow)
    : Manhattan::FancyMainWindow(mainWindow)
    , m_docks(new SampleViewDocks(this))
    , m_sampleDesigner(new SampleDesigner(this))
    , m_toolBar(nullptr)
    , m_models(mainWindow->models())
{
    setObjectName("SampleView");

    setCentralWidget(sampleDesigner()->getCentralWidget());

    setDocumentMode(true);
    setTabPosition(Qt::AllDockWidgetAreas, QTabWidget::South);
    setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
    setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);

    initSubWindows();

    for (int i = 0; i < NUMBER_OF_SUB_WINDOWS; i++) {
        QWidget *subWindow = m_subWindows[i];
        //subWindow->setWindowTitle(subs[i]->windowTitle());
        m_dockWidgets[i] = addDockForWidget(subWindow);
        m_widget_to_dock[subWindow] = m_dockWidgets[i];
        m_dock_to_widget[m_dockWidgets[i]] = subWindow;

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
}

void SampleView::initSubWindows()
{
    qFill(m_subWindows, m_subWindows + NUMBER_OF_SUB_WINDOWS,
          static_cast<QWidget*>(nullptr));

    m_subWindows[WIDGET_BOX] = new SampleWidgetBox(sampleDesigner(), this);

    m_tree_view = new SampleTreeWidget(this, m_models->sampleModel());
    m_subWindows[SAMPLE_TREE] = getTreeView();
    getTreeView()->expandAll();
    connect(getTreeView()->model(), SIGNAL(rowsInserted(QModelIndex,int,int)),
            getTreeView(), SLOT(expandAll()));

    m_subWindows[PROPERTY_EDITOR] = new SamplePropertyWidget(selectionModel(), this);

    InfoWidget *infoWidget = new InfoWidget(this);
    connect(infoWidget, SIGNAL(widgetHeightRequest(int)), this, SLOT(setDockHeightForWidget(int)));
    connect(infoWidget, SIGNAL(widgetCloseRequest()), this, SLOT(onWidgetCloseRequest()));
    infoWidget->setSampleModel(m_models->sampleModel());
    infoWidget->setInstrumentModel(m_models->instrumentModel());
    m_subWindows[INFO] = infoWidget;

    sampleDesigner()->setModels(m_models);
    sampleDesigner()->setSelectionModel(selectionModel(), dynamic_cast<FilterPropertyProxy*>(const_cast<QAbstractItemModel*>(getTreeView()->model())));
}

void SampleView::createActions()
{
    m_delete_item_action = new QAction("Delete", this);
    m_delete_item_action->setStatusTip("Delete current object");
    connect(m_delete_item_action, SIGNAL(triggered()),
            this, SLOT(deleteItem()));
}

void SampleView::resetToDefaultLayout()
{
    setTrackingEnabled(false);
    QList<QDockWidget *> dockWidgetList = dockWidgets();
    for(QDockWidget *dockWidget : dockWidgetList) {
        dockWidget->setFloating(false);
        removeDockWidget(dockWidget);
    }
    addDockWidget(Qt::LeftDockWidgetArea,
                  m_dockWidgets[WIDGET_BOX]);
    addDockWidget(Qt::RightDockWidgetArea,
                  m_dockWidgets[SAMPLE_TREE]);
    addDockWidget(Qt::RightDockWidgetArea,
                  m_dockWidgets[PROPERTY_EDITOR]);
    addDockWidget(Qt::BottomDockWidgetArea,
                  m_dockWidgets[INFO]);

    for(QDockWidget *dockWidget : dockWidgetList)
        dockWidget->show();

    setTrackingEnabled(true);
}

void SampleView::addItem(const QString &item_name)
{
    QModelIndex currentIndex = FilterPropertyProxy::toSourceIndex(getTreeView()->currentIndex());

    QModelIndex currentIndexAtColumnZero = getIndexAtColumnZero(currentIndex);
    SessionItem *new_item
        = getSampleModel()->insertNewItem(item_name, currentIndexAtColumnZero);
    if (new_item) {
        QModelIndex new_index = getSampleModel()->indexOfItem(new_item);
        scrollToIndex(new_index);
    }
}

void SampleView::deleteItem()
{
    QModelIndex currentIndex = FilterPropertyProxy::toSourceIndex(getTreeView()->currentIndex());

    if (!currentIndex.isValid()) return;
    QModelIndex parent_index = getSampleModel()->parent(currentIndex);
    int row = currentIndex.row();
    if (currentIndex.isValid()) {
        getSampleModel()->removeRows(row, 1, parent_index);
    }
}

//! A hack to request update of QDockWidget size if its child (e.g. InfoWidget) wants it.
//! The problem bypassed here is that there is no direct method to QMainWindow to recalculate
//! position of splitters surrounding given QDockWidget. So our child QWidget requests here
//! the change of Min/Max size of QDockWidget, this will trigger recalculation of QDockWidget
//! layout and will force QDockWidget to respect sizeHints provided by ChildWidget. Later (in one
//! single timer shot) we return min/max sizes of QDockWidget back to re-enable splitters
//! functionality.
void SampleView::setDockHeightForWidget(int height)
{
    QWidget *widget = qobject_cast<QWidget *>(sender());
    Q_ASSERT(widget);
    QDockWidget *dock = m_widget_to_dock[widget];
    Q_ASSERT(dock);

    m_dock_info.m_dock = dock;
    m_dock_info.m_min_size = dock->minimumSize();
    m_dock_info.m_max_size = dock->maximumSize();

    if(height >0) {
        if(dock->height() < height) {
            dock->setMinimumHeight(height);
        } else {
            dock->setMaximumHeight(height);
        }
    }

    QTimer::singleShot(1, this, SLOT(dockToMinMaxSizes()));
}

void SampleView::onWidgetCloseRequest()
{
    QWidget *widget = qobject_cast<QWidget *>(sender());
    Q_ASSERT(widget);
    QDockWidget *dock = m_widget_to_dock[widget];
    Q_ASSERT(dock);

    dock->toggleViewAction()->trigger();
}

void SampleView::showContextMenu(const QPoint &pnt)
{
    QMenu menu;
    QMenu add_menu(QString("Add"));
    QVector<QString> addItemNames;
    QModelIndex parent_index = FilterPropertyProxy::toSourceIndex(getTreeView()->indexAt(pnt));
    getTreeView()->setCurrentIndex(parent_index);
    if (!parent_index.isValid()) {
        addItemNames = ItemFactory::ValidTopItemTypes().toVector();
    } else {
        addItemNames = getSampleModel()->acceptableDefaultItemTypes(parent_index);
    }
    if (addItemNames.size() > 0) {
        for(QString item_name : addItemNames) {
            QAction *add_action = nullptr;
            if (m_add_action_map.contains(item_name)) {
                add_action = m_add_action_map[item_name];
            }
            else {
                add_action = new QAction(item_name, this);
                m_add_action_map[item_name] = add_action;
                connect(add_action, &QAction::triggered, [=] { addItem(item_name); });
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

void SampleView::dockToMinMaxSizes()
{
    Q_ASSERT(m_dock_info.m_dock);
    m_dock_info.m_dock->setMinimumSize(m_dock_info.m_min_size);
    m_dock_info.m_dock->setMaximumSize(m_dock_info.m_max_size);
    m_dock_info.m_dock = nullptr;
}

void SampleView::onDockVisibilityChangeV2(bool status)
{
    QDockWidget *dock = qobject_cast<QDockWidget *>(sender());
    Q_ASSERT(dock);

    InfoWidget *infoWidget = dynamic_cast<InfoWidget *>(m_dock_to_widget[dock]);
    Q_ASSERT(infoWidget);

    infoWidget->onDockVisibilityChange(status);
}

void SampleView::connectSignals()
{

    connect(this, SIGNAL(resetLayout()), this, SLOT(resetToDefaultLayout()));

    // toolBar should be initialized after MaterialBrowser
    m_toolBar = new SampleToolBar(getSampleModel(), selectionModel(), this);
    connect(m_toolBar, SIGNAL(deleteItems()),
            sampleDesigner()->getView(), SLOT(deleteSelectedItems()));
    connect(m_toolBar, SIGNAL(selectionMode(int)), sampleDesigner()->getView(), SLOT(onSelectionMode(int)));
    connect(sampleDesigner()->getView(), SIGNAL(selectionModeChanged(int)),m_toolBar, SLOT(onViewSelectionMode(int)));
    connect(m_toolBar, SIGNAL(centerView()), sampleDesigner()->getView(), SLOT(onCenterView()));
    connect(m_toolBar, SIGNAL(smartAlign()), sampleDesigner(), SLOT(onSmartAlign()));
    connect(m_toolBar, SIGNAL(changeScale(double)),
            sampleDesigner()->getView(), SLOT(onChangeScale(double)));

    connect(m_toolBar, SIGNAL(zoomOut()),
            sampleDesigner()->getView(), SLOT(zoomOut()));
    connect(m_toolBar, SIGNAL(zoomIn()),
            sampleDesigner()->getView(), SLOT(zoomIn()));

    connect(sampleDesigner()->getScene(), SIGNAL(selectionModeChangeRequest(int)),
            sampleDesigner()->getView(), SLOT(onSelectionMode(int)));

    // connect context menu for tree view
    connect(getTreeView(), SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(showContextMenu(const QPoint &)));

    addToolBar(m_toolBar);

    for (int i = 0; i < NUMBER_OF_SUB_WINDOWS; i++) {
        if(i == INFO) {
            connect(m_dockWidgets[i], SIGNAL(visibilityChanged(bool)),
                    this, SLOT(onDockVisibilityChangeV2(bool)));

        }
    }

}

void SampleView::scrollToIndex(const QModelIndex &index)
{
    if (index.isValid()) {
        getTreeView()->scrollTo(index);
    }
}

QModelIndex SampleView::getIndexAtColumnZero(const QModelIndex &index)
{
    if (index==QModelIndex() || index.column()==0) return index;
    QModelIndex parent_index = getSampleModel()->parent(index);
    return getSampleModel()->index(index.row(), 0, parent_index);
}

SampleModel *SampleView::getSampleModel()
{
    return m_models->sampleModel();
}

QTreeView *SampleView::getTreeView()
{
    return m_tree_view->treeView();
}

QItemSelectionModel* SampleView::selectionModel()
{
    return getTreeView()->selectionModel();
}

SampleDesigner* SampleView::sampleDesigner()
{
    return m_sampleDesigner;
}


