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
    setWindowTitle("Material Editor");
    setMinimumSize(128, 128);
    resize(512, 256);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_tableView = new QTableView;
    m_tableView->setModel( m_tableModel );
    m_tableView->horizontalHeader()->setStretchLastSection(true);
    m_tableView->horizontalHeader()->resizeSection(0, 140);

    m_toolBar = new QToolBar;
    m_toolBar->setFixedHeight(28);
    m_toolBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    const int size = style()->pixelMetric(QStyle::PM_SmallIconSize);
    m_toolBar->setIconSize(QSize(size, size));
    m_toolBar->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    m_statusBar = new QStatusBar;
    connect(m_tableModel, SIGNAL(SetDataMessage(QString)), this, SLOT(showMessage(QString)));

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_toolBar);
    layout->addWidget(m_tableView);

    QPushButton *closeButton = new QPushButton(tr("Close"));
    connect(closeButton, SIGNAL(clicked()), this, SLOT(closeButtonClicked()));

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addStretch(1);
    buttonsLayout->addWidget(closeButton);
    buttonsLayout->setMargin(0);
    buttonsLayout->setSpacing(0);
    layout->addLayout(buttonsLayout);

    layout->addWidget(m_statusBar);

    setLayout(layout);

    SetupActions();
}


MaterialBrowserView::~MaterialBrowserView()
{
    std::cout << "MaterialBrowserView::~MaterialBrowserView() ->" << std::endl;
}


void MaterialBrowserView::closeButtonClicked()
{
    std::cout << "MaterialBrowserView::close() -> 1.1" << std::endl;
    Q_ASSERT(m_tableModel);
    if( !m_tableModel->hasSelection() && isModal() ) {
        showMessage("Please select material with checkbox");
        return;
    }
    std::cout << "MaterialBrowserView::close() -> 1.2" << std::endl;
//    setResult(QDialog::Accepted);
    accept();
    std::cout << "MaterialBrowserView::close() -> 1.3" << std::endl;
    close();
    std::cout << "MaterialBrowserView::close() -> 1.4" << std::endl;
//    return QDialog::close();
}


void MaterialBrowserView::close()
{
    Q_ASSERT(m_tableModel);
    if( !m_tableModel->hasSelection() && isModal() ) {
        showMessage("Please select material with checkbox");
        return;
    }
    QDialog::close();
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
    MaterialManager::instance().getHomogeneousMaterial(name.toStdString(), 0.0, 0.0);
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
}


//void MaterialBrowserView::closeEvent(QCloseEvent *event)
//{
//    std::cout << "MaterialBrowserView::closeEvent() ->" << std::endl;
//    emit WindowClosed();
//    event->accept();
//}


