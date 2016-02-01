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
#include "SampleModel.h"
#include "FitModel.h"
#include "FitParameterItems.h"
#include "InstrumentModel.h"
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

FitParameterWidget::FitParameterWidget(SampleModel *sampleModel, InstrumentModel *instrumentModel,
                                       FitModel *fitModel, QWidget *parent)
    : QWidget(parent)
    , m_fitModel(fitModel)
    , m_sampleModel(sampleModel)
    , m_instrumentModel(instrumentModel)
    , m_selectorTreeView(new QTreeView())
    , m_parameterTreeview(new QTreeView())
    , m_selectorModel(0)
    , m_parameterModel(0)
    , m_contextMenu(new QMenu())
    , m_splitter(new QSplitter())
    , m_keyboardFilter(new KeyboardFilter(this))
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
    m_parameterTreeview->setContextMenuPolicy(Qt::CustomContextMenu);
    m_parameterTreeview->installEventFilter(m_keyboardFilter);

    m_removeAction =  m_contextMenu->addAction("Remove", this, SLOT(onRemoveParameter()));
    m_addAction = m_contextMenu->addAction("Add Parameter", m_parameterModel, SLOT(addParameter()));

    m_splitter->addWidget(m_selectorTreeView);
    m_splitter->addWidget(m_parameterTreeview);
    int width = m_splitter->width();
    int left = width / 3;
    m_splitter->setSizes(QList<int>() << left << ( width - left));

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

    connectSelectorView();
    connectParameterView();

}

void FitParameterWidget::updateSelector()
{
    buildSelectorModel();

    m_selectorTreeView->setModel(m_selectorModel);
    m_selectorTreeView->expandAll();
    m_selectorTreeView->resizeColumnToContents(0);
    m_selectorTreeView->setColumnWidth(0, m_selectorTreeView->columnWidth(0) * 1.2);

    connect(m_selectorTreeView->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
               this, SLOT(onSelectorSelectionChanged(QItemSelection)));
}

ParameterizedItem *FitParameterWidget::getTopItemFromSelection(SessionModel *model,
                                                               const QString &itemType,
                                                               const QString &selectionType)
{
    QString selectedSample = m_fitModel->itemForIndex(QModelIndex())
            ->getChildOfType(Constants::FitSelectionType)
            ->getRegisteredProperty(selectionType).toString();

    if (selectedSample.isEmpty())
        return NULL;

    ParameterizedItem *top = 0;

    for (int i_row = 0; i_row < model->rowCount(QModelIndex()); ++i_row) {
        QModelIndex itemIndex = model->index(i_row, 0, QModelIndex());
        if (ParameterizedItem *item = model->itemForIndex(itemIndex)) {
            if (item->modelType()  == itemType) {
                if (item->displayName() == selectedSample)
                    top = item;
            }
        }
    }

    return top;
}

void FitParameterWidget::buildTree(QStandardItem *root, ParameterizedItem *top)
{
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

void FitParameterWidget::buildSelectorModel() {

    m_selectorModel = new FitSelectorModel();
    m_selectorModel->setHorizontalHeaderItem(0, new QStandardItem("Property"));
    m_selectorModel->setHorizontalHeaderItem(1, new QStandardItem("Value"));
    QStandardItem *root = m_selectorModel->invisibleRootItem();

    ParameterizedItem *topSample = getTopItemFromSelection(m_sampleModel, Constants::MultiLayerType,
                                                     FitSelectionItem::P_SAMPLE_INDEX);
    ParameterizedItem *topInst = getTopItemFromSelection(m_instrumentModel,
                                                         Constants::InstrumentType,
                                                         FitSelectionItem::P_INSTRUMENT_INDEX);
    if (topSample && topInst) {
        buildTree(root, topSample);
        buildTree(root, topInst);

        // check for consistency
        for (int i=0; i<m_parameterModel->rowCount(QModelIndex()); i++){
            int rowcount = m_parameterModel->rowCount(m_parameterModel->index(i,0,QModelIndex()));
            QModelIndex child = m_parameterModel->index(i,0,QModelIndex());
            for (int j = 0; j < rowcount; j++) {
                QModelIndex curIndex = m_parameterModel->index(j,0, child);
                QString value = m_parameterModel->itemForIndex(curIndex)
                        ->getRegisteredProperty(FitParameterLinkItem::P_LINK).toString();
                auto item = m_selectorModel->getItemFromPath(value);
                if (item == m_selectorModel->invisibleRootItem()) {
                    m_parameterModel->removeRow(j, child);
                    if (rowcount == 1) {
                        m_parameterModel->removeRow(i);
                        i--;
                    }
                    j--;
                    rowcount--;
                }
            }
        }

        spanParameters();
    }

}

void FitParameterWidget::spanParameters()
{
    m_parameterTreeview->expandAll();
    for (int i = 0; i < m_parameterModel->rowCount(QModelIndex()); i++){
        QModelIndex parameter = m_parameterModel->index(i,0,QModelIndex());
        int childRowCount = m_parameterModel->rowCount(parameter);
        if (childRowCount > 0){
            for (int j = 0; j < childRowCount; j++) {
                m_parameterTreeview->setFirstColumnSpanned(j, parameter, true);
            }
        }
    }
}

void FitParameterWidget::onCustomContextMenu(const QPoint &point) {
    m_removeAction->setVisible(false);
    QModelIndex index = m_parameterTreeview->indexAt(point);
    if (index.isValid()) {
        ParameterizedItem *cur = m_parameterModel->itemForIndex(index);
        if (cur->itemName().startsWith("FitParameter")) {
            m_parameterTreeview->setCurrentIndex(index);
            m_removeAction->setVisible(true);
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
        ParameterizedItem *val = m_fitModel->itemForIndex(index);
        QString link = val->getRegisteredProperty(FitParameterLinkItem::P_LINK).toString();
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

void FitParameterWidget::removeSelectedItem() {
    QModelIndex selection = m_parameterTreeview->currentIndex();
    if (selection.isValid()) {
        m_parameterModel->removeRow(selection.row(), selection.parent());
    }
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

// ---------------------------------------------------------

bool KeyboardFilter::eventFilter( QObject *dist, QEvent *event )
{
    Q_UNUSED(dist);
    if( event->type() == QEvent::KeyPress )
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>( event );
        if( keyEvent->key() == Qt::Key_Delete ) {
            emit removeItem();
        }
    }
    return false;
}

// ---------------------------------------------------------

QMimeData *FitSelectorModel::mimeData(const QModelIndexList &indexes) const
{
    QMimeData *mimeData = new QMimeData();
    QModelIndex index = indexes.first();
    if (index.isValid()) {
        QString path = getPathFromIndex(index);
        path = path.append("#%1").arg(itemFromIndex(index.sibling(index.row(), 1))
                                      ->data(Qt::EditRole).toDouble());
        mimeData->setData(FitParameterWidget::MIME_TYPE, path.toLatin1());
    }
    return mimeData;
}

QString FitSelectorModel::getPathFromIndex(const QModelIndex &index) const
{
    if (index.isValid()) {
        QStringList namePath;
        QStandardItem *cur = itemFromIndex(index);
        while (cur) {
            namePath << cur->text();
            cur = cur->parent();
        }
        std::reverse(namePath.begin(), namePath.end());
        return namePath.join("/");
    }
    return QString();
}

QStandardItem *FitSelectorModel::getItemFromPath(const QString &path)
{
    QStringList parts = path.split("/");
    QStandardItem *t = invisibleRootItem();
    for(int i = 0; i < parts.length(); i++) {
        for (int j = 0; j < t->rowCount(); j++) {
            if (t->child(j,0)->text() == parts[i]) {
                t = t->child(j,0);
                break;
            }
        }
    }
    return t;
}

// ---------------------------------

FitParameterModel::FitParameterModel(FitModel *fitmodel, QWidget *parent)
    : SessionModel("FitParameterModel", parent)
    , m_columnNames(new QMap<int, QString>())
{
    setRootItem(fitmodel->itemForIndex(QModelIndex())->
            getChildOfType(Constants::FitParameterContainerType));
    setMaxColumns(5);
    m_columnNames->insert(0, FitParameterItem::P_NAME);
    m_columnNames->insert(1, FitParameterItem::P_USE);
    m_columnNames->insert(2, FitParameterItem::P_MIN);
    m_columnNames->insert(3, FitParameterItem::P_INIT);
    m_columnNames->insert(4, FitParameterItem::P_MAX);
}

FitParameterModel::~FitParameterModel()
{
    setRootItem(0);
    delete m_columnNames;
}

ParameterizedItem *FitParameterModel::addParameter()
{
    return insertNewItem(Constants::FitParameterType, indexOfItem(itemForIndex(QModelIndex())));
}

QModelIndex FitParameterModel::itemForLink(const QString &link) const
{
    for (int i=0; i<rowCount(QModelIndex()); i++){
        int rowcount = rowCount(index(i,0,QModelIndex()));
        for (int j = 0; j < rowcount; j++) {
            QModelIndex curIndex = index(j,0,index(i,0,QModelIndex()));
            QString value = itemForIndex(curIndex)
                    ->getRegisteredProperty(FitParameterLinkItem::P_LINK).toString();
            if (value == link)
                return curIndex;
        }
    }
    return QModelIndex();
}

Qt::ItemFlags FitParameterModel::flags(const QModelIndex & index) const
{
    Qt::ItemFlags returnVal = Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    if (index.isValid() && index.parent() == QModelIndex()) {
        if (index.column() == 0)
            returnVal |= Qt::ItemIsDropEnabled;
        else
            returnVal |= Qt::ItemIsEditable;
    } else if (!index.isValid()) {
        returnVal |= Qt::ItemIsDropEnabled;
    }
    return returnVal;
}

QStringList FitParameterModel::mimeTypes() const
{
    QStringList types;
    types << FitParameterWidget::MIME_TYPE;
    return types;
}

bool FitParameterModel::canDropMimeData(const QMimeData *data, Qt::DropAction action,
                                        int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(action);
    Q_UNUSED(row);
    Q_UNUSED(parent);
    if (column > 0)
        return false;
    QString link = QString::fromLatin1(data->data(FitParameterWidget::MIME_TYPE)).split("#")[0];
    QModelIndex cur = itemForLink(link);
    return !cur.isValid();
}

Qt::DropActions FitParameterModel::supportedDropActions() const
{
    return Qt::CopyAction | Qt::MoveAction;
}

bool FitParameterModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row,
                                     int column, const QModelIndex &parent)
{
    if (action == Qt::IgnoreAction) return true;
    if (column > 0) return true;
    QStringList parts = QString::fromLatin1(data->data(FitParameterWidget::MIME_TYPE))
            .split("#");
    if (parts.size() != 2) return true;
    QModelIndex cur = parent;
    if (!parent.isValid()) {
        auto newlink = addParameter();
        double value = parts[1].toDouble();
        newlink->setRegisteredProperty(FitParameterItem::P_INIT, value);
        cur = indexOfItem(newlink);
    }
    auto link = insertNewItem(Constants::FitParameterLinkType, cur, row);
    if (link) link->setRegisteredProperty(FitParameterLinkItem::P_LINK, parts[0]);
    emit dataChanged(cur, cur);
    return true;
}

QVariant FitParameterModel::data(const QModelIndex & index, int role) const
{
    if ( !index.isValid() || index.column() < 0 || index.column() >= 5) {
        return QVariant();
    }
    if (ParameterizedItem *item = itemForIndex(index)) {
        if (role == Qt::DisplayRole || role == Qt::EditRole) {
            if (item->parent() != itemForIndex(QModelIndex()))
            {
                if (index.column() == 0)
                    return item->getRegisteredProperty(FitParameterLinkItem::P_LINK);
                else
                    return QVariant();
            }
            if (index.column() == 0)
                return item->itemName();
            else
                return item->getRegisteredProperty(m_columnNames->value(index.column()));
        }
    }
    return QVariant();
}

bool FitParameterModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;
    if (ParameterizedItem *item = itemForIndex(index)) {
        if (role == Qt::EditRole && index.column() > 0 && index.column() < 5) {
            item->setRegisteredProperty(m_columnNames->value(index.column()), value);
            emit dataChanged(index, index);
            return true;
        }
    }
    return false;
}

QVariant FitParameterModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        return m_columnNames->value(section);
    }
    return QVariant();
}
