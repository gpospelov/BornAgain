#include "InstrumentSelectorWidget.h"
#include "SessionModel.h"
#include "ParameterizedItem.h"
#include <QListView>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMenu>
#include <QAction>
#include <QDebug>

InstrumentSelectorWidget::InstrumentSelectorWidget(SessionModel *model, QWidget *parent)
    : QWidget(parent)
    , m_instrumentModel(0)
    , m_listView(0)
{
    setMinimumSize(128, 600);
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);

//    m_listWidget = new QListWidget;
    m_listView = new QListView;
    m_listView->setViewMode(QListView::IconMode);
    m_listView->setIconSize(QSize(96, 84));
    m_listView->setMovement(QListView::Static);
    m_listView->setMaximumWidth(200);
    m_listView->setSpacing(12);
    //m_listView->setModel(m_instrumentModel);

    m_listView->setObjectName("listView");
    m_listView->setStyleSheet(QString::fromUtf8("QListView#listView\n"
    "{\n"
    "   selection-background-color : rgb(98,100,105); \n"
    "   selection-color: rgb(255,255,255);\n"
    "   border: 1px solid rgb(98,100,105);\n"
    "}\n"
    ""));






//    QMenu *addInstrumentMenu = new QMenu();
//    m_addDefaultGisasAction = new QAction(tr("Default GISAS instrument"), this);
//    m_addDefaultGisasAction->setStatusTip(tr("Add default GISAS instrument"));
//    connect(m_addDefaultGisasAction, SIGNAL(triggered()), this, SLOT(onAddDefaultGISAS()) );
//    addInstrumentMenu->addAction(m_addDefaultGisasAction);

//    QPushButton *addInstrumentButton = new QPushButton("Add new instrument");
//    addInstrumentButton->setMinimumHeight(30);
//    addInstrumentButton->setMenu(addInstrumentMenu);


    QVBoxLayout *verticaLayout = new QVBoxLayout;
    verticaLayout->setMargin(10);
    verticaLayout->setSpacing(10);
    verticaLayout->addWidget(m_listView, 3);
//    verticaLayout->addWidget(addInstrumentButton);

    setLayout(verticaLayout);

    setInstrumentModel(model);
}


//void InstrumentSelectorWidget::onAddDefaultGISAS()
//{
//    qDebug() << "InstrumentSelectorWidget::onAddDefaultGISAS() ";
//}



void InstrumentSelectorWidget::setInstrumentModel(SessionModel *model)
{
    Q_ASSERT(model);
    Q_ASSERT(m_listView);

    if(model != m_instrumentModel) {
        if(m_instrumentModel) {
            disconnect(m_instrumentModel, SIGNAL(rowsInserted(const QModelIndex &, int, int)), this, SLOT(onRowsInserted(const QModelIndex &,int,int)));
        }
        m_instrumentModel = model;
        m_listView->setModel(model);

        connect(m_listView->selectionModel(),
            SIGNAL( selectionChanged(const QItemSelection&, const QItemSelection&) ),
            this,
            SIGNAL( selectionChanged(const QItemSelection&, const QItemSelection&) )
        );

//        connect(m_instrumentModel, SIGNAL(rowsInserted(const QModelIndex &, int, int)), this, SLOT(onRowsInserted(const QModelIndex &,int,int)));
    }
}

QItemSelectionModel *InstrumentSelectorWidget::getSelectionModel()
{
    return m_listView->selectionModel();
}

//void InstrumentSelectorWidget::onRowsInserted(const QModelIndex &parent, int first, int /* last */)
//{
//    QModelIndex indexToSelect = m_instrumentModel->index(first, 0, parent);
//    qDebug() << "InstrumentSelectorWidget::onRowsInserted()" << indexToSelect;
//    m_listView->selectionModel()->select(indexToSelect, QItemSelectionModel::Select);
//}


