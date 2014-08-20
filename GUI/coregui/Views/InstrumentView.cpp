#include "InstrumentView.h"
#include "InstrumentModel.h"
#include "InstrumentSelectorWidget.h"
#include "InstrumentEditorWidget.h"
#include "styledbar.h"
#include "minisplitter.h"
#include <QBoxLayout>
#include <QListView>
#include <QStackedWidget>
#include <QPushButton>
#include <QToolButton>
#include <QMenu>
#include <QAction>
#include <QDebug>
#include <QComboBox>
#include <QToolBar>


InstrumentView::InstrumentView(InstrumentModel *model, QWidget *parent)
    : QWidget(parent)
    , m_instrumentModel(model)
    , m_toolBar(new QToolBar(this))
    , m_instrumentSelector(new InstrumentSelectorWidget(m_instrumentModel, this))
    , m_stackWidget(new QStackedWidget)
    , m_addInstrumentAction(0)
    , m_removeInstrumentAction(0)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    QHBoxLayout *horizontalLayout = new QHBoxLayout;
    horizontalLayout->addWidget(m_instrumentSelector);
    horizontalLayout->addWidget(m_stackWidget, 1);

    mainLayout->addWidget(m_toolBar);
    mainLayout->addLayout(horizontalLayout);
    setLayout(mainLayout);

    connect(m_instrumentSelector,
        SIGNAL( selectionChanged(const QItemSelection&, const QItemSelection&) ),
        this,
        SLOT( onSelectionChanged(const QItemSelection&, const QItemSelection&) )
        );

    connect(m_instrumentModel, SIGNAL(modelAboutToBeReset()), this, SLOT(resetView()));
    connect(m_instrumentModel, SIGNAL(rowsAboutToBeRemoved(QModelIndex, int,int)), this, SLOT(onRowsAboutToBeRemoved(QModelIndex,int,int)));

    createActions();
    updateView();
}

void InstrumentView::updateView()
{
    qDebug() << "InstrumentView::updateView()";
    m_instrumentSelector->updateSelection();
}


void InstrumentView::resetView()
{
    qDebug() << "InstrumentView::resetView()";

    QMap<ParameterizedItem *, InstrumentEditorWidget *>::iterator it = m_instrumentToEditor.begin();
    while(it!=m_instrumentToEditor.end()) {
        m_stackWidget->removeWidget(it.value());
        delete it.value();
        ++it;
    }
    m_instrumentToEditor.clear();
}


void InstrumentView::onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected )
{
    qDebug() << "InstrumentView::onSelectionChanged()" << selected << deselected;
    if(selected.indexes().isEmpty()) {
        qDebug() << "       InstrumentView::onSelectionChanged() -> no selected" << selected << deselected;
        return;
    }

    ParameterizedItem *instrument = m_instrumentModel->itemForIndex(selected.indexes().back());
    qDebug() << "InstrumentView::onSelectionChanged()" << instrument->itemName();

    InstrumentEditorWidget *widget = m_instrumentToEditor[instrument];

    if( !widget) {
        widget = new InstrumentEditorWidget();
        widget->setInstrumentItem(instrument);
        m_stackWidget->addWidget(widget);
        m_instrumentToEditor[instrument] = widget;
    }
    m_stackWidget->setCurrentWidget(widget);

}


void InstrumentView::onAddInstrument()
{
    qDebug() << "InstrumentView::onAddInstrument()";
    ParameterizedItem *instrument = m_instrumentModel->insertNewItem(Constants::InstrumentType);
    instrument->setItemName("Default GISAS");
    m_instrumentModel->insertNewItem(Constants::DetectorType, m_instrumentModel->indexOfItem(instrument));
    m_instrumentModel->insertNewItem(Constants::BeamType, m_instrumentModel->indexOfItem(instrument));    
    QModelIndex itemIndex = m_instrumentModel->indexOfItem(instrument);
    qDebug() << "       InstrumentView::onAddInstrument() -> clearing selection";
    m_instrumentSelector->getSelectionModel()->clearSelection();
    qDebug() << "       InstrumentView::onAddInstrument() -> clearing selection -> done.";
    m_instrumentSelector->getSelectionModel()->select(itemIndex, QItemSelectionModel::Select);
}


void InstrumentView::onRemoveInstrument()
{
    qDebug() << "InstrumentView::onRemoveInstrument()";
    QModelIndex currentIndex = m_instrumentSelector->getSelectionModel()->currentIndex();
    qDebug() << "InstrumentView::onRemoveInstrument()" <<  currentIndex;
    m_instrumentModel->removeRows(currentIndex.row(), 1, QModelIndex());

}


void InstrumentView::onRowsAboutToBeRemoved(QModelIndex parent, int first, int /* last */)
{
    qDebug() << "InstrumentView::onRowsAboutToBeRemoved()";
    ParameterizedItem *item = m_instrumentModel->itemForIndex(m_instrumentModel->index(first,0, parent));
    Q_ASSERT(item);
    InstrumentEditorWidget *widget = m_instrumentToEditor[item];
    Q_ASSERT(widget);

    QMap<ParameterizedItem *, InstrumentEditorWidget *>::iterator it = m_instrumentToEditor.begin();
    while(it!=m_instrumentToEditor.end()) {
        if(it.value() == widget) {
            it = m_instrumentToEditor.erase(it);
        } else {
            ++it;
        }
    }

    m_stackWidget->removeWidget(widget);
    delete widget;
}


void InstrumentView::createActions()
{
    m_addInstrumentAction = new QAction(QIcon(":/images/append.png"), tr("Add new instrument"), this);
    connect(m_addInstrumentAction, SIGNAL(triggered()), this, SLOT(onAddInstrument()));
    m_toolBar->addAction(m_addInstrumentAction);

    m_removeInstrumentAction = new QAction(QIcon(":/images/remove.png"), tr("Remove currently selected instrument"), this);
    connect(m_removeInstrumentAction, SIGNAL(triggered()), this, SLOT(onRemoveInstrument()));
    m_toolBar->addAction(m_removeInstrumentAction);

    Q_ASSERT(m_instrumentSelector->getListView());
    m_instrumentSelector->getListView()->setContextMenuPolicy(Qt::ActionsContextMenu);
    m_instrumentSelector->getListView()->addAction(m_addInstrumentAction);
    m_instrumentSelector->getListView()->addAction(m_removeInstrumentAction);
}

