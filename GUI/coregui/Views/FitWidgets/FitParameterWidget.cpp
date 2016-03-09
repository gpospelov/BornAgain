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
#include "FitModel.h"
#include "FitParameterItems.h"
#include "FitParameterModel.h"
#include "FitSelectorModel.h"
#include "DeleteEventFilter.h"
#include "MinimizerSettingsWidget.h"
#include "minisplitter.h"
#include "ModelPath.h"
#include <QVBoxLayout>
#include <QTreeView>
#include <QSplitter>
#include <QStringList>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QModelIndex>
#include <QMenu>
#include <QAction>
#include <QItemSelection>
#include <QItemSelectionModel>

#include <QMimeData>
#include <QDragEnterEvent>

const QString FitParameterWidget::MIME_TYPE = "application/org.bornagainproject.fittinglink";

FitParameterWidget::FitParameterWidget(FitModel *fitModel, QWidget *parent)
    : QWidget(parent)
    , m_fitModel(fitModel)
    , m_selectorTreeView(new QTreeView())
    , m_parameterTreeview(new QTreeView())
    , m_selectorModel(nullptr)
    , m_parameterModel(nullptr)
    , m_contextMenu(new QMenu())
    , m_splitter(new Manhattan::MiniSplitter(this))
    , m_keyboardFilter(new DeleteEventFilter(this))
{

    m_parameterModel = new FitParameterModel(m_fitModel, this);

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

    m_selectorTreeView->setStyleSheet(style);
    m_selectorTreeView->setDragEnabled(true);
    m_selectorTreeView->setDragDropMode(QAbstractItemView::DragOnly);

    m_parameterTreeview->setStyleSheet(style);
    m_parameterTreeview->setAcceptDrops(true);
    m_parameterTreeview->setDragDropMode(QAbstractItemView::DropOnly);
    m_parameterTreeview->setModel(m_parameterModel);
    m_parameterTreeview->setColumnWidth(0, 300);
    m_parameterTreeview->setColumnWidth(2, 120);
    m_parameterTreeview->setContextMenuPolicy(Qt::CustomContextMenu);
    m_parameterTreeview->installEventFilter(m_keyboardFilter);

    m_removeAction =  m_contextMenu->addAction("Remove", this, SLOT(onRemoveParameter()));
    m_addAction = m_contextMenu->addAction("Add Parameter", m_parameterModel, SLOT(addParameter()));

    /*QSplitter *rightWindow = new QSplitter;
    rightWindow->setOrientation(Qt::Vertical);
    rightWindow->addWidget(m_parameterTreeview);
    m_parameterTreeview->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    auto *minimizersettings = new MinimizerSettingsWidget(m_fitModel, this);
    rightWindow->addWidget(minimizersettings);
    rightWindow->setSizes(QList<int>() << 3000 << 1000);*/

    m_splitter->addWidget(m_selectorTreeView);
    m_splitter->addWidget(m_parameterTreeview);
    m_splitter->setSizes(QList<int>() << 10000 << 20000);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->setMargin(0);
    vlayout->setSpacing(0);
    vlayout->addWidget(m_splitter);
    this->setLayout(vlayout);

    // update selector when sample model changes - more jobs to be done here
    //connect(m_sampleModel, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),
    //        this, SLOT(updateSelector()));

    connect(m_parameterModel, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),
            m_fitModel, SLOT(dataChangedProxy(QModelIndex,QModelIndex,QVector<int>)));

    // setup firstcolumnspanning
    connect(m_parameterModel, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),
            this, SLOT(spanParameters()));

    // make context menu availabe
    connect(m_parameterTreeview, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(onCustomContextMenu(const QPoint &)));

    // event from keyeventfilter
    connect(m_keyboardFilter, SIGNAL(removeItem()), this, SLOT(removeSelectedItem()));

    // select by doubleclick
    connect(m_selectorTreeView, SIGNAL(doubleClicked(QModelIndex)),
            this, SLOT(onDoubleclick(QModelIndex)));


    connectParameterView();

}

void FitParameterWidget::updateSelector()
{
    m_parameterModel = new FitParameterModel(m_fitModel, this);
    m_parameterTreeview->setModel(m_parameterModel);
    connect(m_parameterModel, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),
            m_fitModel, SLOT(dataChangedProxy(QModelIndex,QModelIndex,QVector<int>)));

    // setup firstcolumnspanning
    connect(m_parameterModel, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),
            this, SLOT(spanParameters()));
    spanParameters();
    buildSelectorModel();

    m_selectorTreeView->setModel(m_selectorModel);
    m_selectorTreeView->expandAll();
    m_selectorTreeView->resizeColumnToContents(0);
    m_selectorTreeView->setColumnWidth(0, m_selectorTreeView->columnWidth(0) * 1.2);

    connectSelectorView();
}

void FitParameterWidget::clearParameter() {
    while (m_parameterModel->rowCount(QModelIndex())) {
        m_parameterModel->removeRow(0, QModelIndex());
    }
}

void FitParameterWidget::buildTree(QStandardItem *root, SessionItem *top)
{
    QStringList parameterTree = ModelPath::getParameterTreeList(top);

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
                    double value = ModelPath::getParameterValue(top, str);
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

void FitParameterWidget::buildSelectorModel() {

    m_selectorModel = new FitSelectorModel();
    m_selectorModel->setHorizontalHeaderItem(0, new QStandardItem("Property"));
    m_selectorModel->setHorizontalHeaderItem(1, new QStandardItem("Value"));
    QStandardItem *root = m_selectorModel->invisibleRootItem();

    SessionItem *topSample = m_fitModel->getSelectedMultiLayerItem();
    SessionItem *topInst = m_fitModel->getSelectedInstrumentItem();
    if (topSample && topInst) {
        QStandardItem *multilayer = new QStandardItem("MultiLayer");
        root->appendRow(multilayer);
        buildTree(multilayer, topSample);
        QStandardItem *instrument = new QStandardItem("Instrument");
        root->appendRow(instrument);
        buildTree(instrument, topInst);
        spanParameters();
    }
}

void FitParameterWidget::spanParameters()
{
    m_parameterTreeview->expandAll();
    for (int i = 0; i < m_parameterModel->rowCount(QModelIndex()); i++){
        QModelIndex parameter = m_parameterModel->index(i,0,QModelIndex());
        if (!parameter.isValid())
            break;
        int childRowCount = m_parameterModel->rowCount(parameter);
        if (childRowCount > 0){
            for (int j = 0; j < childRowCount; j++) {
                m_parameterTreeview->setFirstColumnSpanned(j, parameter, true);
            }
        }
    }
}

void FitParameterWidget::onCustomContextMenu(const QPoint &point) {
    m_removeAction->setEnabled(false);
    QModelIndex index = m_parameterTreeview->indexAt(point);
    if (index.isValid()) {
        SessionItem *cur = m_parameterModel->itemForIndex(index);
        if (cur->itemName().startsWith("FitParameter")) {
            m_parameterTreeview->setCurrentIndex(index);
            m_removeAction->setEnabled(true);
        }
    }
    m_contextMenu->exec(m_parameterTreeview->mapToGlobal(point + QPoint(2, 22)));
}

void FitParameterWidget::onRemoveParameter() {
    QModelIndex index = m_parameterTreeview->currentIndex();
    if (index.isValid()) {
        m_parameterModel->removeRow(index.row(), index.parent());
    }
}

void FitParameterWidget::onParameterSelectionChanged(const QItemSelection &selection)
{
    if (selection.indexes().isEmpty())
        return;
    QModelIndex index = selection.indexes().first();
    QModelIndex newSelection = QModelIndex();
    if (index.isValid() && index.parent().isValid()) {
        SessionItem *val = m_fitModel->itemForIndex(index);
        QString link = val->getChildValue(FitParameterLinkItem::P_LINK).toString();
        QStandardItem *t = m_selectorModel->getItemFromPath(link);
        newSelection = m_selectorModel->indexFromItem(t);
    }
    connectSelectorView(false);
    m_selectorTreeView->selectionModel()
            ->select(newSelection, QItemSelectionModel::ClearAndSelect);
    if (newSelection.isValid()) {
        newSelection = newSelection.sibling(newSelection.row(), 1);
        m_selectorTreeView->selectionModel()
                ->select(newSelection, QItemSelectionModel::Select);
    }
    connectSelectorView();
}

void FitParameterWidget::onSelectorSelectionChanged(const QItemSelection &selection)
{
    if (selection.indexes().isEmpty())
        return;
    QModelIndex index = selection.indexes().first();
    index = index.sibling(index.row(), 0);
    QModelIndex newSelection = QModelIndex();
    if (index.isValid()) {
        QString link = m_selectorModel->getPathFromIndex(index);
        newSelection = m_parameterModel->itemForLink(link);
    }
    connectParameterView(false);
    m_parameterTreeview->selectionModel()->
            select(newSelection, QItemSelectionModel::ClearAndSelect);
    connectParameterView();
}

void FitParameterWidget::connectSelectorView(bool active) {
    if (active) {
        connect(m_selectorTreeView->selectionModel(),
                SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
                this, SLOT(onSelectorSelectionChanged(QItemSelection)));
    } else {
        disconnect(m_selectorTreeView->selectionModel(),
                   SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
                   this, SLOT(onSelectorSelectionChanged(QItemSelection)));
    }
}

void FitParameterWidget::connectParameterView(bool active) {
    if (active) {
        connect(m_parameterTreeview->selectionModel(),
                SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
                this, SLOT(onParameterSelectionChanged(QItemSelection)));
    } else {
        disconnect(m_parameterTreeview->selectionModel(),
                   SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
                   this, SLOT(onParameterSelectionChanged(QItemSelection)));
    }
}

void FitParameterWidget::removeEmptyParameter() {
    bool finished = false;
    while (!finished) {
        int rowCount = m_parameterModel->rowCount(QModelIndex());
        if (rowCount == 0)
            break;
        for (int i=0; i<rowCount; i++) {
            QModelIndex child = m_parameterModel->index(i,0,QModelIndex());
            if (child.isValid() && m_parameterModel->rowCount(child) == 0) {
                m_parameterModel->removeRow(i, QModelIndex());
                break;
            }
            if (i + 1 == rowCount) {
                finished = true;
            }
        }
    }
}

void FitParameterWidget::removeSelectedItem() {
    QModelIndex selection = m_parameterTreeview->currentIndex();
    if (selection.isValid()) {
        m_parameterModel->removeRow(selection.row(), selection.parent());
    }
    removeEmptyParameter();
}

void FitParameterWidget::onDoubleclick(const QModelIndex index) {
    QModelIndex entryIndex = index.sibling(index.row(), 0);
    if (m_selectorModel->itemFromIndex(entryIndex)->isDragEnabled()) {
        QMimeData *data = m_selectorModel->mimeData(QModelIndexList() << entryIndex);
        if (m_parameterModel->canDropMimeData(data,Qt::CopyAction,0,0,QModelIndex())) {
            m_parameterModel->dropMimeData(data,Qt::CopyAction,-1,-1,QModelIndex());
        }
        data->deleteLater();
    }
}
