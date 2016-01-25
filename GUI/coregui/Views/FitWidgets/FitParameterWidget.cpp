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
    , m_main(main)
{

    QColor bgColor(255,255,255,255);
    QPalette palette;
    palette.setColor(QPalette::Background, bgColor);
    setAutoFillBackground(true);
    setPalette(palette);

    QSplitter *splitter = new QSplitter();
    splitter->addWidget(m_treeview);
    splitter->addWidget(m_textedit);

    m_treeview->setModel(m_main->getSampleModel());
    m_treeview->expandAll();
    m_treeview->setColumnWidth(0, 300);
    m_treeview->setDragEnabled(true);
    m_treeview->setDragDropMode(QAbstractItemView::DragOnly);

    m_textedit->setAcceptDrops(true);

    connect(m_main->getSampleModel(), SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),
            this, SLOT(updateParameters()));

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
    QStandardItem *root = model->invisibleRootItem();

    // build a QStandardItemModel from it, hehe :p
    foreach (const QString &str, parameterTree) {
        // populate model, traverse path on the way ...

        QStringList parts = str.split("/");
        QStandardItem *cur = root;
        foreach (const QString &name, parts) {
            bool needFillin = true;
            for (int i = 0; i < cur->rowCount(); i++) {
                QString debugname = cur->child(i,0)->text();
                if (debugname == name) {
                    cur = cur->child(i,0);
                    needFillin = false;
                    break;
                }
            }
            if (needFillin) {
                QStandardItem *item = new QStandardItem(name);
                item->setDragEnabled(false);
                cur->appendRow(item);
                cur = item;
            }
        }
        // now we can add the value to it

        // FIXME_DAVID Can you add value to the same row as property name, to have them in one line?

        QStandardItem *data = new QStandardItem();
        double value = m_main->getSampleModel()->getTopItem()->getParameterValue(str);
        data->setData(QVariant(value), Qt::EditRole);
        auto list = new QList<QStandardItem*>;
        list->append(data);
        cur->appendRow(data);
    }

    m_treeview->setModel(model);
    m_treeview->expandAll();
}
