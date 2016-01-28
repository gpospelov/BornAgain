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
#include "FitModel.h"
#include "FitParameterItems.h"
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
#include <QTableView>
#include <QItemSelection>
#include <QItemSelectionModel>



FitParameterWidget::FitParameterWidget(SampleModel *sampleModel, InstrumentModel *instrumentModel,
                                       FitModel *fitModel, QWidget *parent)
    : QWidget(parent)
    , m_treeview(new QTreeView())
    , m_fitpara(new QTreeView())
    , m_contextMenu(new QMenu)
    , m_parameter_count(1)
    , m_sampleModel(sampleModel)
    , m_instrumentModel(instrumentModel)
    , m_fitModel(fitModel)
    , m_selector(0)
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

    m_model = new FitParameterModel(m_fitModel, this);



    m_fitpara->setModel(m_model);
    m_fitpara->setColumnWidth(0, 300);
    m_fitpara->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(m_fitpara->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            this, SLOT(onSelectionChanged(QItemSelection,QItemSelection)));

    m_remove = m_contextMenu->addAction("Remove", this, SLOT(removeParameter()));
    m_add = m_contextMenu->addAction("Add Parameter", m_model, SLOT(addParameter()));

    connect(m_sampleModel, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),
            this, SLOT(updateParameters()));

    connect(m_model, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),
            this, SLOT(expandFitPara()));

    connect(m_fitpara, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(onCustomContextMenu(const QPoint &)));

    connect(m_model, SIGNAL(dataChanged(const QModelIndex &,const QModelIndex &,QVector<int>)),
            this, SLOT(onDataChanged(const QModelIndex &,const QModelIndex &)));
    connect(m_treeview->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
               this, SLOT(onSelectionChanged2(QItemSelection)));

    QSplitter *splitter = new QSplitter();
    splitter->addWidget(m_treeview);
    splitter->addWidget(m_fitpara);
    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->setMargin(0);
    vlayout->setSpacing(0);
    vlayout->addWidget(splitter);
    this->setLayout(vlayout);
    expandFitPara();
    updateParameters();
}

void FitParameterWidget::expandFitPara() {
    m_fitpara->expandAll();
    for (int i=0; i<m_model->rowCount(QModelIndex()); i++){
        int childRowCount = m_model->rowCount(m_model->index(i,0,QModelIndex()));
        if (childRowCount > 0){
            for (int j = 0; j < childRowCount; j++) {
                m_fitpara->setFirstColumnSpanned(j, m_model->index(i,0,QModelIndex()), true);
            }
        }
    }
}

void FitParameterWidget::updateParameters()
{
    // when data changed, we reconstruct it all
    buildSelectorModel();
    m_treeview->setModel(m_selector);
    m_treeview->expandAll();
    m_treeview->resizeColumnToContents(0);
    m_treeview->setColumnWidth(0, m_treeview->columnWidth(0) * 1.2);
}

FitSelectorModel *FitParameterWidget::buildSelectorModel() {

    m_selector = new FitSelectorModel();
    m_selector->setHorizontalHeaderItem(0, new QStandardItem("Property"));
    m_selector->setHorizontalHeaderItem(1, new QStandardItem("Value"));
    QStandardItem *root = m_selector->invisibleRootItem();

    ParameterizedItem *top = m_sampleModel->itemForIndex(QModelIndex());
    QStringList parameterTree = top->getParameterTreeList();

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
                    double value = top->getParameterValue(str);
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
}

void FitParameterWidget::onCustomContextMenu(const QPoint &point) {
    QModelIndex index = m_fitpara->indexAt(point);
    if (index.isValid()) {
        ParameterizedItem *cur = m_model->itemForIndex(index);
        if (cur->itemName().startsWith("FitParameter")) {
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
    else if (index.isValid()) {
        m_model->removeRow(index.row(), index.parent());
    }
}

void FitParameterWidget::onDataChanged(const QModelIndex &left,const QModelIndex &right) {

}

void FitParameterWidget::onSelectionChanged(const QItemSelection &se, const QItemSelection &)
{
    QModelIndex index = se.indexes().first();
    if (index.isValid() && index.parent().isValid()) {
        ParameterizedItem *val = m_fitModel->itemForIndex(index);
        QString string = val->getRegisteredProperty(FitParameterLinkItem::P_LINK).toString();
        QStringList parts = string.split("/");
        QStandardItem *t = m_selector->invisibleRootItem();
        for(int i = 0; i < parts.length(); i++) {
            for (int j = 0; j < t->rowCount(); j++) {
                if (t->child(j,0)->text() == parts[i]) {
                    t = t->child(j,0);
                    break;
                }
            }
        }
        disconnect(m_treeview->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
                   this, SLOT(onSelectionChanged2(QItemSelection)));
        m_treeview->selectionModel()->select(m_selector->indexFromItem(t),
                                             QItemSelectionModel::ClearAndSelect);
        connect(m_treeview->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
                   this, SLOT(onSelectionChanged2(QItemSelection)));
    }
}

void FitParameterWidget::onSelectionChanged2(const QItemSelection &se)
{
    QModelIndex index = se.indexes().first();
    index = index.sibling(index.row(), 0);
    if (index.isValid()) {
        QStringList namePath;
        QStandardItem *cur = m_selector->itemFromIndex(index);
        while (cur) {
            namePath << cur->text();
            cur = cur->parent();
        }
        std::reverse(namePath.begin(), namePath.end());
        QString name = namePath.join("/");
        for(int i = 0; i < m_model->rowCount(QModelIndex()); i++) {
            int rowcount = m_model->rowCount(m_model->index(i,0,QModelIndex()));
                for (int j = 0; j < rowcount; j++) {
                    QModelIndex index = m_model->index(j, 0, m_model->index(i,0,QModelIndex()));

                    QString value = m_model->itemForIndex(index)
                            ->getRegisteredProperty(FitParameterLinkItem::P_LINK).toString();
                    if (value == name) {

                        disconnect(m_fitpara->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
                                this, SLOT(onSelectionChanged(QItemSelection,QItemSelection)));
                        m_fitpara->selectionModel()->select(index, QItemSelectionModel::ClearAndSelect);

                        connect(m_fitpara->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
                                this, SLOT(onSelectionChanged(QItemSelection,QItemSelection)));

                        return;
                    }
                }
        }
    }
    disconnect(m_fitpara->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            this, SLOT(onSelectionChanged(QItemSelection,QItemSelection)));
    m_fitpara->selectionModel()->select(QModelIndex(), QItemSelectionModel::ClearAndSelect);

    connect(m_fitpara->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            this, SLOT(onSelectionChanged(QItemSelection,QItemSelection)));
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

// ---------------------------------

FitParameterModel::FitParameterModel(FitModel *fitmodel, QWidget *parent)
    : SessionModel("FitParameterModel", parent)
    , m_fitmodel(fitmodel)
{
    setRootItem(fitmodel->itemForIndex(QModelIndex())->
            getChildOfType(Constants::FitParameterContainerType));
    setMaxColumns(5);
}

void FitParameterModel::addParameter()
{
    insertNewItem(Constants::FitParameterType,
                              indexOfItem(itemForIndex(QModelIndex())
                              ->getChildOfType(Constants::FitParameterContainerType)));

}

Qt::ItemFlags FitParameterModel::flags(const QModelIndex & index) const
{
    if (index.isValid() && index.parent() == QModelIndex() && index.column() == 0)
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDropEnabled;
    else if (index.isValid() && index.parent() == QModelIndex() && index.column() > 0)
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QStringList FitParameterModel::mimeTypes() const
{
    QStringList types;
    types << "text/plain";
    return types;
}

bool FitParameterModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row,
                                     int column, const QModelIndex &parent)
{
    if (action == Qt::IgnoreAction)
        return true;



    auto link = m_fitmodel->insertNewItem(Constants::FitParameterLinkType, parent,
                              row);
    link->setRegisteredProperty(FitParameterLinkItem::P_LINK, data->text());

    emit dataChanged(parent, parent);
    return true;
}

QVariant FitParameterModel::data(const QModelIndex & index, int role) const
{
    // huge logic

    if ( !index.isValid() || index.column() < 0 || index.column() >= 5) {
        return QVariant();
    }
    if (ParameterizedItem *item = itemForIndex(index)) {

        if (role == Qt::DisplayRole || role == Qt::EditRole) {
            if (item->parent() != itemForIndex(QModelIndex()))
            {
                if (index.column() == 0)
                return item->getRegisteredProperty(FitParameterLinkItem::P_LINK);
            return QVariant();
            }
            switch (index.column()) {
            case 0:
                return item->itemName();
            case 1:
                return item->getRegisteredProperty(FitParameterItem::P_USE);
            case 2:
                return item->getRegisteredProperty(FitParameterItem::P_INIT);
            case 3:
                return item->getRegisteredProperty(FitParameterItem::P_MIN);
            case 4:
                return item->getRegisteredProperty(FitParameterItem::P_MAX);
            default:
                return QVariant();
            }
        }
    }
    return QVariant();
}

bool FitParameterModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;
    if (ParameterizedItem *item = itemForIndex(index)) {
        if (role == Qt::EditRole) {
            switch(index.column()) {
            case 0:
                return false;
            case 1:
                item->setRegisteredProperty(FitParameterItem::P_USE, value);
                break;
            case 2:
                item->setRegisteredProperty(FitParameterItem::P_INIT, value);
                break;
            case 3:
                item->setRegisteredProperty(FitParameterItem::P_MIN, value);
                break;
            case 4:
                item->setRegisteredProperty(FitParameterItem::P_MAX, value);
                break;

            }
        } else
            return false;
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

QVariant FitParameterModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole) {
        switch (section) {
        case 0:
            return "Name";
        case 1:
            return "Active";
        case 2:
            return "Init";
        case 3:
            return "Min";
        case 4:
            return "Max";
        default:
            return section;
        }
    }
    return QVariant();
}

bool FitParameterModel::canDropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column,
                         const QModelIndex &parent) const
{
    for (int i=0; i<rowCount(QModelIndex()); i++){
        int rowcount = rowCount(index(i,0,QModelIndex()));
            for (int j = 0; j < rowcount; j++) {
                QString value = itemForIndex(index(j,0,index(i,0,QModelIndex())))
                        ->getRegisteredProperty(FitParameterLinkItem::P_LINK).toString();
                if (value == data->text())
                    return false;
            }

    }
    return true;
}

Qt::DropActions FitParameterModel::supportedDropActions() const
{
    return Qt::CopyAction;
}

FitParameterModel::~FitParameterModel()
{
    setRootItem(0);
}
