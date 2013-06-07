#include "MaterialBrowserView.h"
#include "MaterialBrowserModel.h"
#include "MaterialManager.h"
#include <styledbar.h>
#include <manhattanstyle.h>

#include <QTableView>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QCloseEvent>
#include <QStatusBar>
#include <QToolBar>
#include <QtGlobal>
#include <QApplication>
#include <QAction>
#include <QPushButton>
#include <iostream>

int MaterialBrowserView::m_IndexOfUnnamed = 0;

MaterialBrowserView::MaterialBrowserView(MaterialBrowserModel *tableModel, QWidget *parent)
    : QDialog(parent)
    , m_tableView(0)
    , m_tableModel(tableModel)
    , m_statusBar(0)
    , m_toolBar(0)
{
    setWindowTitle("Material Browser");
    std::cout << "MaterialEditorView::MaterialEditorView() ->  " << std::endl;
    setMinimumSize(128, 128);
    resize(512, 256);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //setStyleSheet("background-color:white;");

    m_tableView = new MyTableView(this);
    std::cout << "XXX " << m_tableModel << std::endl;
    m_tableView->setModel( m_tableModel );
    m_tableView->horizontalHeader()->setStretchLastSection(true);
    m_tableView->horizontalHeader()->resizeSection(0, 140);

    m_toolBar = new QToolBar(this);
    m_toolBar->setFixedHeight(28);
    m_toolBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    const int size = style()->pixelMetric(QStyle::PM_SmallIconSize);
    m_toolBar->setIconSize(QSize(size, size));
    m_toolBar->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    m_statusBar = new QStatusBar(this);
    connect(m_tableModel, SIGNAL(SetDataMessage(QString)), this, SLOT(showMessage(QString)));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_toolBar);
    layout->addWidget(m_tableView);

    QPushButton *closeButton = new QPushButton(tr("Close"));
    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addStretch(1);
    buttonsLayout->addWidget(closeButton);
    buttonsLayout->setMargin(0);
    buttonsLayout->setSpacing(0);
    layout->addLayout(buttonsLayout);

    layout->addWidget(m_statusBar);

    setLayout(layout);

    SetupActions();

//    show();
}


MaterialBrowserView::~MaterialBrowserView()
{
    std::cout << "MaterialBrowserView::~MaterialBrowserView() ->" << std::endl;
}


bool MaterialBrowserView::close()
{
    std::cout << "MaterialBrowserView::close() ->" << std::endl;
    Q_ASSERT(m_tableModel);
    if( !m_tableModel->hasSelection() && isModal() ) {
        showMessage("Please select material with checkbox");
        return false;
    }
    accepted();
    return QDialog::close();
}


void MaterialBrowserView::showMessage(const QString &message)
{
    m_statusBar->showMessage(message, 4000);
}


void MaterialBrowserView::SetupActions()
{
    QAction *addMaterialAction = new QAction(QIcon(":/SampleDesigner/images/card--plus.png"), tr("Add material"), this);
    connect(addMaterialAction, SIGNAL(triggered()), this, SLOT(addMaterial()));
    m_toolBar->addAction(addMaterialAction);

    QAction *removeMaterialAction = new QAction(QIcon(":/SampleDesigner/images/card--minus.png"), tr("Remove selected material"), this);
    connect(removeMaterialAction, SIGNAL(triggered()), this, SLOT(removeMaterial()));
    m_toolBar->addAction(removeMaterialAction);
}


void MaterialBrowserView::addMaterial()
{
    QString name = QString("unnamed%1").arg(m_IndexOfUnnamed);
    std::cout << "MaterialBrowserView::addMaterial() -> " << name.toStdString() << std::endl;
    MaterialManager::instance().getHomogeneousMaterial(name.toStdString(), 1.0, 0.0);
    m_tableModel->UpdateMaterials();
    m_tableView->scrollToBottom();

    m_IndexOfUnnamed++;
}


void MaterialBrowserView::removeMaterial()
{
    std::cout << "MaterialBrowserView::removeMaterial() -> " << std::endl;
    QModelIndexList selectedList = m_tableView->selectionModel()->selectedRows();
    if( !selectedList.size() ) {
        showMessage("Select one or more rows to delete materials");
    }
    m_tableModel->RemoveMaterials(selectedList);

//    for(int i=0; i<selectedList.size(); ++i) {
//        m_tableModel->RemoveMaterial(selectedList[i].row());
//        std::cout << "XXX " << i << " " << selectedList[i].row()<< std::endl;
//    }
}


void MaterialBrowserView::closeEvent(QCloseEvent *event)
{
    std::cout << "MaterialBrowserView::closeEvent() ->" << std::endl;
    emit WindowClosed();
    event->accept();
}


