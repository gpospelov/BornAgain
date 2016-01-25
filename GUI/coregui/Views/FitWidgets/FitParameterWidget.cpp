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
#include "DomainObjectBuilder.h"
#include "MultiLayer.h"
#include "ParameterizedItem.h"
#include "ParameterPool.h"
#include "RealParameterWrapper.h"
#include "ParameterModelBuilder.h"
#include <QDebug>
#include <QVBoxLayout>
#include <QTreeView>
#include <QPlainTextEdit>
#include <QSplitter>
#include <QStringList>
#include <QStandardItemModel>
#include <QStandardItem>



FitParameterWidget::FitParameterWidget(MainWindow *main, QWidget *parent)
    : QWidget(parent)
    , m_textedit(new DebugTextEdit())
    , m_treeview(new QTreeView())
    , m_fitpara(new QTreeView())
    , m_main(main)
{

    QColor bgColor(255,255,255,255);
    QPalette palette;
    palette.setColor(QPalette::Background, bgColor);
    setAutoFillBackground(true);
    setPalette(palette);

    QSplitter *splitter = new QSplitter();
    splitter->addWidget(m_treeview);
    splitter->addWidget(m_fitpara);


    m_treeview->setStyleSheet(
        "QTreeView::branch {background: palette(base);}QTreeView::branch:has-siblings:!adjoins-item "
        "{border-image: url(:/images/treeview-vline.png) 0;}QTreeView::branch:has-siblings:"
        "adjoins-item {border-image: url(:/images/treeview-branch-more.png) 0;}QTreeView::branch:"
        "!has-children:!has-siblings:adjoins-item {border-image: "
        "url(:/images/treeview-branch-end.png) 0;}QTreeView::branch:has-children:!has-siblings:closed"
        ",QTreeView::branch:closed:has-children:has-siblings {border-image: none;image: "
        "url(:/images/treeview-branch-closed.png);}QTreeView::branch:open:has-children:!has-siblings,"
        "QTreeView::branch:open:has-children:has-siblings  {border-image: none;image: "
        "url(:/images/treeview-branch-open.png);}");


    m_treeview->setDragEnabled(true);
    m_treeview->setDragDropMode(QAbstractItemView::DragOnly);

    m_fitpara->setAcceptDrops(true);
    m_fitpara->setDragDropMode(QAbstractItemView::DropOnly);

    m_model = new FitParameterModel();
    QStandardItem *root = m_model->invisibleRootItem();
    auto par1 = new QStandardItem("Parameter1");
    par1->setDropEnabled(true);
    auto set1 = new QStandardItem("use");
    set1->setCheckable(true);
    set1->setEditable(false);
    set1->setDropEnabled(false);
    auto set2 = new QStandardItem("0.0");
    set2->setDropEnabled(false);
    auto set3 = new QStandardItem("5.0");
    set3->setDropEnabled(false);
    root->appendRow(QList<QStandardItem *>() << par1 << set1 << set2 << set3);
    root->appendRow(QList<QStandardItem *>() << new QStandardItem("Parameter2") << set1 << set2 << set3);
    root->appendRow(QList<QStandardItem *>() << new QStandardItem("Parameter3") << set1 << set2 << set3);

    m_fitpara->setModel(m_model);

    connect(m_main->getSampleModel(), SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),
            this, SLOT(updateParameters()));

    connect(m_model, SIGNAL(dropFinished()),
            this, SLOT(expandRightTree()));

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->setMargin(0);
    vlayout->setSpacing(0);
    vlayout->addWidget(splitter);
    this->setLayout(vlayout);
    updateParameters();
}


// FIXME_DAVID Pretty impressive that you have managed to build a tree without recursive calls
// Anyway, if it works and looks compact, no reason to rewrite it to use recursion
// - Just isolate model creation into separate call, to not to mix inside updateParameters() two
//   various activities: building the model, and initializing m_textEdit and m_treeView
//

void FitParameterWidget::expandRightTree() {
    m_fitpara->expandAll();
    QModelIndex idx = m_model->invisibleRootItem()->index();
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
    QStringList parameterTree = m_main->getSampleModel()->getTopItem()->getParameterTreeList();

    // show our parameters
    m_textedit->clear();
    foreach (const QString &str, parameterTree) {
        m_textedit->appendPlainText(str);
    }

    // !!!! rough proto

    FitParameterSelectionModel *model = new FitParameterSelectionModel();
    model->setHorizontalHeaderItem(0, new QStandardItem("Property"));
    model->setHorizontalHeaderItem(1, new QStandardItem("Value"));
    QStandardItem *root = model->invisibleRootItem();

    // build a QStandardItemModel from it, hehe :p
    foreach (const QString &str, parameterTree) {
        // populate model, traverse path on the way ...

        QStringList parts = str.split("/");
        QStandardItem *cur = root;
        for (int i = 0; i < parts.size(); i++) {
            bool needFillin = true;
            for (int j = 0; j < cur->rowCount(); j++) {
                QString debugname = cur->child(j,0)->text();
                if (debugname == parts[i]) {
                    cur = cur->child(j,0);
                    needFillin = false;
                    break;
                }
            }
            if (needFillin) {
                QStandardItem *item = new QStandardItem(parts[i]);
                item->setDragEnabled(true);
                item->setEditable(false);
                if (i == parts.size() - 1) {
                    double value = m_main->getSampleModel()->getTopItem()->getParameterValue(str);
                    QStandardItem *data = new QStandardItem("data");
                    data->setData(QVariant(value), Qt::EditRole);
                    data->setEditable(false);
                    data->setDragEnabled(false);
                    cur->appendRow(QList<QStandardItem *>() << item << data);
                } else {

                    item->setDragEnabled(false);
                    cur->appendRow(item);
                    cur = item;
                }

            }
        }
    }

    m_treeview->setModel(model);
    m_treeview->expandAll();
    m_treeview->resizeColumnToContents(0);
    m_treeview->setColumnWidth(0, (double)m_treeview->columnWidth(0) * 1.2);
}

bool FitParameterModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column,
                                const QModelIndex &parent)
{
    if (action == Qt::IgnoreAction)
        return true;
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

Qt::ItemFlags FitParameterModel::flags(const QModelIndex &index) const {
    if (index.isValid())
         return itemFromIndex(index)->flags();
    else return Qt::ItemIsEnabled;
}

Qt::DropActions FitParameterModel::supportedDropActions() const {
    return Qt::CopyAction;
}

QStringList FitParameterModel::mimeTypes() const
 {
     QStringList types;
     types << "text/plain";
     return types;
 }
