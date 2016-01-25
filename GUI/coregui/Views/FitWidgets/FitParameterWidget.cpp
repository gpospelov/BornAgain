// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/FitWidgets/FitParameterWidget.cpp
//! @brief     Implements class FitParameterWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FitParameterWidget.h"
#include "mainwindow.h"
#include "SampleModel.h"
#include <QVBoxLayout>
#include <QTreeView>
#include <QSplitter>
#include <QStringList>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QMimeData>
#include <QDragEnterEvent>
#include <QModelIndex>
#include <QMenu>
#include <QAction>



FitParameterWidget::FitParameterWidget(MainWindow *main, QWidget *parent)
    : QWidget(parent)
    , m_treeview(new QTreeView())
    , m_fitpara(new QTreeView())
    , m_main(main)
    , m_contextMenu(new QMenu)
    , m_parameter_count(1)
{
    QString style(
    "QTreeView::branch {background: palette(base);}QTreeView::branch:has-siblings:!adjoins-item "
    "{border-image: url(:/images/treeview-vline.png) 0;}QTreeView::branch:has-siblings:"
    "adjoins-item {border-image: url(:/images/treeview-branch-more.png) 0;}QTreeView::branch:"
    "!has-children:!has-siblings:adjoins-item {border-image: "
    "url(:/images/treeview-branch-end.png) 0;}QTreeView::branch:has-children:!has-siblings:closed"
    ",QTreeView::branch:closed:has-children:has-siblings {border-image: none;image: "
    "url(:/images/treeview-branch-closed.png);}QTreeView::branch:open:has-children:!has-siblings,"
    "QTreeView::branch:open:has-children:has-siblings  {border-image: none;image: "
    "url(:/images/treeview-branch-open.png);}");

    m_treeview->setStyleSheet(style);
    m_fitpara->setStyleSheet(style);

    m_treeview->setDragEnabled(true);
    m_treeview->setDragDropMode(QAbstractItemView::DragOnly);

    m_fitpara->setAcceptDrops(true);
    m_fitpara->setDragDropMode(QAbstractItemView::DropOnly);

    m_model = new FitParameterModel();
    addParameter();
    addParameter();
    addParameter();
    m_model->setHorizontalHeaderItem(0, new QStandardItem("Name"));
    m_model->setHorizontalHeaderItem(1, new QStandardItem("Status"));
    m_model->setHorizontalHeaderItem(2, new QStandardItem("Init Value"));
    m_model->setHorizontalHeaderItem(3, new QStandardItem("Min"));
    m_model->setHorizontalHeaderItem(4, new QStandardItem("Max"));

    m_fitpara->setModel(m_model);
    m_fitpara->setColumnWidth(0, 300);
    m_fitpara->setContextMenuPolicy(Qt::CustomContextMenu);

    m_remove = m_contextMenu->addAction("Remove", this, SLOT(removeParameter()));
    m_add = m_contextMenu->addAction("Add Parameter", this, SLOT(onAddParameter()));

    connect(m_main->getSampleModel(), SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),
            this, SLOT(updateParameters()));

    connect(m_model, SIGNAL(dropFinished()),
            this, SLOT(expandFitPara()));

    connect(m_fitpara, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(onCustomContextMenu(const QPoint &)));

    QSplitter *splitter = new QSplitter();
    splitter->addWidget(m_treeview);
    splitter->addWidget(m_fitpara);
    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->setMargin(0);
    vlayout->setSpacing(0);
    vlayout->addWidget(splitter);
    this->setLayout(vlayout);
    updateParameters();
}

void FitParameterWidget::addParameter() {
    auto item = m_model->invisibleRootItem();
    QString name = QString("Parameter %1").arg(m_parameter_count++);
    auto par1 = new QStandardItem(name);
    par1->setEditable(false);
    par1->setDropEnabled(true);
    auto set1 = new QStandardItem("use");
    set1->setCheckable(true);
    set1->setEditable(false);
    set1->setDropEnabled(false);
    auto set2 = new QStandardItem();
    set2->setData(QVariant(5.0), Qt::EditRole);
    set2->setDropEnabled(false);
    auto set3 = new QStandardItem();
    set3->setData(QVariant(0.0), Qt::EditRole);
    set3->setDropEnabled(false);
    auto set4 = new QStandardItem();
    set4->setData(QVariant(10.0), Qt::EditRole);
    set4->setDropEnabled(false);
    item->appendRow(QList<QStandardItem *>() << par1 << set1 << set2 << set3 << set4);
}

void FitParameterWidget::expandFitPara() {
    m_fitpara->expandAll();
    for (int i=0; i<m_model->rowCount(); i++){
        if (m_model->item(i,0)->hasChildren()){
            for (int j = 0; j < m_model->item(i,0)->rowCount(); j++) {
                m_fitpara->setFirstColumnSpanned(j, m_model->item(i,0)->index(), true);
            }
        }
    }
}

void FitParameterWidget::updateParameters()
{
    // when data changed, we reconstruct it all
    FitSelectorModel *model = getSelectorModel();
    m_treeview->setModel(model);
    m_treeview->expandAll();
    m_treeview->resizeColumnToContents(0);
    m_treeview->setColumnWidth(0, m_treeview->columnWidth(0) * 1.2);
}

FitSelectorModel *FitParameterWidget::getSelectorModel() {

    FitSelectorModel *model = new FitSelectorModel();
    model->setHorizontalHeaderItem(0, new QStandardItem("Property"));
    model->setHorizontalHeaderItem(1, new QStandardItem("Value"));
    QStandardItem *root = model->invisibleRootItem();

    QStringList parameterTree = m_main->getSampleModel()->getTopItem()->getParameterTreeList();

    foreach (const QString &str, parameterTree) {
        QStringList parts = str.split("/");
        QStandardItem *cur = root;
        for (int partIndex = 0; partIndex < parts.size(); partIndex++) {
            bool insertItem = true;

            // search for existing child
            for (int childIndex = 0; childIndex < cur->rowCount(); childIndex++) {
                if (cur->child(childIndex, 0)->text() == parts[partIndex]) {
                    cur = cur->child(childIndex, 0);
                    insertItem = false;
                    break;
                }
            }
            if (insertItem) {
                QStandardItem *item = new QStandardItem(parts[partIndex]);
                QStandardItem *data = new QStandardItem();
                item->setEditable(false);
                data->setEditable(false);
                if (partIndex == parts.size() - 1) { // arrived at the end
                    double value = m_main->getSampleModel()->getTopItem()->getParameterValue(str);
                    data->setData(QVariant(value), Qt::EditRole);
                } else {
                    item->setDragEnabled(false);
                    data->setDragEnabled(false);
                }
                cur->appendRow(QList<QStandardItem *>() << item << data);
                cur = item;
            }
        }
    }
    return model;
}

void FitParameterWidget::onCustomContextMenu(const QPoint &point) {
    QModelIndex index = m_fitpara->indexAt(point);
    if (index.isValid()) {
        QStandardItem *cur = m_model->itemFromIndex(index);
        if (cur->text().startsWith("Parameter ")) {
            m_fitpara->setCurrentIndex(index);
            m_remove->setVisible(true);
            m_contextMenu->exec(m_fitpara->mapToGlobal(point+QPoint(0,22)));
        }
    } else {
        m_remove->setVisible(false);
        m_contextMenu->exec(m_fitpara->mapToGlobal(point+QPoint(0,22)));
    }
}

void FitParameterWidget::removeParameter() {
    QModelIndex index = m_fitpara->currentIndex();
    if (index.isValid() && !index.parent().isValid()) {
        m_model->removeRow(index.row());
    }
}

void FitParameterWidget::onAddParameter() {
    addParameter();
}


// ---------------------------------------------------------

QMimeData *FitSelectorModel::mimeData(const QModelIndexList &indexes) const
{
    QMimeData *mimeData = new QMimeData();
    QModelIndex index = indexes.first();
    if (index.isValid()) {
        QStringList namePath;
        QStandardItem *cur = itemFromIndex(index);
        while (cur) {
            namePath << cur->text();
            cur = cur->parent();
        }
        std::reverse(namePath.begin(), namePath.end());
        mimeData->setText(namePath.join("/"));
    }
    return mimeData;
}



// ------------------------------------

bool FitParameterModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row,
                                     int column, const QModelIndex &parent)
{
    if (action == Qt::IgnoreAction)
        return true;

    for (int i=0; i<rowCount(); i++){
        if (item(i,0)->hasChildren()){
            for (int j = 0; j < item(i,0)->rowCount(); j++) {
                QString value = item(i,0)->child(j,0)->text();
                if (value == data->text())
                    return false;
            }
        }
    }

    QStandardItem *item = new QStandardItem(data->text());
    item->setDropEnabled(false);
    item->setEditable(false);
    if (row == -1)
        itemFromIndex(parent)->appendRow(item);
    else
        itemFromIndex(parent)->insertRow(row, item);
    emit dropFinished();
    return true;
}

Qt::ItemFlags FitParameterModel::flags(const QModelIndex &index) const
{
    if (index.isValid())
         return itemFromIndex(index)->flags();
    else return Qt::ItemIsEnabled;
}

QStringList FitParameterModel::mimeTypes() const
{
    QStringList types;
    types << "text/plain";
    return types;
}

