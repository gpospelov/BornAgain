#include "InstrumentView2.h"
#include "SessionModel.h"
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


InstrumentView2::InstrumentView2(SessionModel *model, QWidget *parent)
    : QWidget(parent)
    , m_instrumentModel(model)
    , m_toolBar(new QToolBar(this))
//    , m_toolBar(new Manhattan::StyledBar(this))
//    , m_splitter(new Manhattan::MiniSplitter(this))
    , m_instrumentSelector(new InstrumentSelectorWidget(m_instrumentModel, this))
//    , m_instrumentEditor(new InstrumentEditorWidget(m_instrumentModel, this))
    , m_addInstrumentAction(0)
    , m_removeInstrumentAction(0)
{
//    setInstrumentModel(model);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    //Manhattan::StyledBar *bar = new Manhattan::StyledBar;

//    const int size = style()->pixelMetric(QStyle::PM_SmallIconSize);
//    m_toolBar->setIconSize(QSize(size, size));
//    m_toolBar->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    m_stackWidget = new QStackedWidget;

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

    connect(m_instrumentModel, SIGNAL(rowsAboutToBeRemoved(QModelIndex, int,int)), this, SLOT(onRowsAboutToBeRemoved(QModelIndex,int,int)));

    QModelIndex itemIndex = m_instrumentModel->index(0,0,QModelIndex());
    m_instrumentSelector->getSelectionModel()->select(itemIndex, QItemSelectionModel::Select);

    createActions();
}


void InstrumentView2::onSelectionChanged(const QItemSelection &selected, const QItemSelection & /* deselected */)
{
    qDebug() << "InstrumentView2::onSelectionChanged()" << selected;
    if(selected.indexes().isEmpty()) return;

    ParameterizedItem *instrument = m_instrumentModel->itemForIndex(selected.indexes().back());
    qDebug() << "InstrumentView2::onSelectionChanged()" << instrument->itemName();

    InstrumentEditorWidget *widget = m_instrumentToEditor[instrument];

    if( !widget) {
        widget = new InstrumentEditorWidget();
        widget->setInstrumentItem(instrument);
        m_stackWidget->addWidget(widget);
        m_instrumentToEditor[instrument] = widget;
    }
    m_stackWidget->setCurrentWidget(widget);

}


void InstrumentView2::onAddInstrument()
{
    qDebug() << "InstrumentView2::onAddInstrument()";

    ParameterizedItem *instrument = m_instrumentModel->insertNewItem("Instrument");
    instrument->setItemName("Default GISAS");
    m_instrumentModel->insertNewItem("Detector", m_instrumentModel->indexOfItem(instrument));
    m_instrumentModel->insertNewItem("Beam", m_instrumentModel->indexOfItem(instrument));

}

void InstrumentView2::onRemoveInstrument()
{
    qDebug() << "InstrumentView2::onRemoveInstrument()";
    QModelIndex currentIndex = m_instrumentSelector->getSelectionModel()->currentIndex();
    qDebug() << "InstrumentView2::onRemoveInstrument()" <<  currentIndex;
    m_instrumentModel->removeRows(currentIndex.row(), 1, QModelIndex());

}

void InstrumentView2::onRowsAboutToBeRemoved(QModelIndex parent, int first, int /* last */)
{
    qDebug() << "InstrumentView2::onRowsAboutToBeRemoved()";
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

void InstrumentView2::createActions()
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

