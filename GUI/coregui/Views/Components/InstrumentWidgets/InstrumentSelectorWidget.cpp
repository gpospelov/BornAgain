#include "InstrumentSelectorWidget.h"
#include "SessionModel.h"
#include "ParameterizedItem.h"
#include <QListView>
#include <QListWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMenu>
#include <QAction>
#include <QDebug>

InstrumentSelectorWidget::InstrumentSelectorWidget(SessionModel *model, QWidget *parent)
    : QWidget(parent)
    , m_instrumentModel(0)
{
    setMinimumSize(128, 600);
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);

    m_listWidget = new QListWidget;
    m_listWidget->setViewMode(QListView::IconMode);
    m_listWidget->setIconSize(QSize(96, 84));
    m_listWidget->setMovement(QListView::Static);
    m_listWidget->setMaximumWidth(200);
    m_listWidget->setSpacing(12);
    //m_listView->setModel(m_instrumentModel);

    QMenu *addInstrumentMenu = new QMenu();
    m_addDefaultGisasAction = new QAction(tr("Default GISAS instrument"), this);
    m_addDefaultGisasAction->setStatusTip(tr("Add default GISAS instrument"));
    connect(m_addDefaultGisasAction, SIGNAL(triggered()), this, SLOT(onAddDefaultGISAS()) );
    addInstrumentMenu->addAction(m_addDefaultGisasAction);

    QPushButton *addInstrumentButton = new QPushButton("Add new instrument");
    addInstrumentButton->setMinimumHeight(30);
    addInstrumentButton->setMenu(addInstrumentMenu);


    QVBoxLayout *verticaLayout = new QVBoxLayout;
    verticaLayout->setMargin(10);
    verticaLayout->setSpacing(10);
    verticaLayout->addWidget(addInstrumentButton);
    verticaLayout->addWidget(m_listWidget, 3);

    setLayout(verticaLayout);

    setInstrumentModel(model);
}


void InstrumentSelectorWidget::onAddDefaultGISAS()
{
    qDebug() << "InstrumentSelectorWidget::onAddDefaultGISAS() ";
}



void InstrumentSelectorWidget::setInstrumentModel(SessionModel *model)
{
    Q_ASSERT(model);
    if(model != m_instrumentModel) {
        m_instrumentModel = model;
        //m_listView->setModel(model);
        initFromModel();

    }
}


void InstrumentSelectorWidget::initFromModel()
{
    Q_ASSERT(m_listWidget);

    m_listWidget->clear();

    QModelIndex parentIndex = QModelIndex();
    for(int i_row=0; i_row<m_instrumentModel->rowCount(parentIndex); ++i_row) {
        qDebug() << "InstrumentSelectorWidget::initFromModel()";

        QModelIndex itemIndex = m_instrumentModel->index( i_row, 0, parentIndex );

        if (ParameterizedItem *item = m_instrumentModel->itemForIndex(itemIndex)){

            QListWidgetItem *configButton = new QListWidgetItem(m_listWidget);
            configButton->setIcon(QIcon(":/images/config.png"));
            configButton->setText(item->itemName());
            configButton->setTextAlignment(Qt::AlignHCenter);
            configButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        }
    }

    m_listWidget->setCurrentRow(0);

}


