// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/ImportDataWidgets/ImportDataToolBar.cpp
//! @brief     Implements class ImportDataToolBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ImportDataToolBar.h"
#include "SessionModel.h"
#include "ImportDataAssistant.h"
#include "ImportDataToolBar.h"
#include "IntensityDataItem.h"
#include <QItemSelectionModel>
#include <QAction>
#include <QDebug>

ImportDataToolBar::ImportDataToolBar(QWidget *parent)
    : StyledToolBar(parent)
    , m_importDataAction(0)
    , m_cloneDataAction(0)
    , m_removeDataAction(0)
    , m_model(0)
    , m_selectionModel(0)
{
    setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    m_importDataAction = new QAction(QStringLiteral("Import"), parent);
    m_importDataAction->setIcon(QIcon(":/images/toolbar16light_newitem.svg"));
    m_importDataAction->setToolTip(QStringLiteral("Import data"));
    connect(m_importDataAction, SIGNAL(triggered()), this,
            SLOT(onImportDataAction()));
    addAction(m_importDataAction);

    m_cloneDataAction = new QAction(QStringLiteral("Clone"), parent);
    m_cloneDataAction->setIcon(
        QIcon(":/images/toolbar16light_cloneitem.svg"));
    m_cloneDataAction->setToolTip(QStringLiteral("Clone selected data"));
    connect(m_cloneDataAction, SIGNAL(triggered()), this,
            SLOT(onCloneDataAction()));
    addAction(m_cloneDataAction);

    m_removeDataAction = new QAction(QStringLiteral("Remove"), parent);
    m_removeDataAction->setIcon(QIcon(":/images/toolbar16light_recycle.svg"));
    m_removeDataAction->setToolTip(QStringLiteral("Remove selected data"));
    connect(m_removeDataAction, SIGNAL(triggered()), this,
            SLOT(onRemoveDataAction()));
    addAction(m_removeDataAction);

}

void ImportDataToolBar::setModel(SessionModel *model)
{
    m_model = model;
}

void ImportDataToolBar::setSelectionModel(QItemSelectionModel *selectionModel)
{
    m_selectionModel = selectionModel;
}

void ImportDataToolBar::onImportDataAction()
{
    qDebug() << "ImportDataToolBar::onImportDataAction()";
    Q_ASSERT(m_model);
    ImportDataAssistant assistant;
    if(OutputData<double> *data = assistant.importData()) {
        SessionItem *realDataItem = m_model->insertNewItem(Constants::RealDataType);
        IntensityDataItem *intensityDataItem = dynamic_cast<IntensityDataItem *>(m_model->insertNewItem(Constants::IntensityDataType, realDataItem->index()));
        intensityDataItem->setOutputData(data);
        m_selectionModel->clearSelection();
        m_selectionModel->select(realDataItem->index(), QItemSelectionModel::Select);
    }

}

void ImportDataToolBar::onCloneDataAction()
{
    qDebug() << "ImportDataToolBar::onCloneDataAction()";

}

void ImportDataToolBar::onRemoveDataAction()
{
    qDebug() << "ImportDataToolBar::onRemoveDataAction()";
    Q_ASSERT(m_model);
    Q_ASSERT(m_selectionModel);

    QModelIndex currentIndex = m_selectionModel->currentIndex();
    qDebug() << "InstrumentView::onRemoveInstrument()" <<  currentIndex;
    if(currentIndex.isValid())
        m_model->removeRows(currentIndex.row(), 1, currentIndex.parent());

//    QModelIndexList indexes = m_selectionModel->selectedIndexes();
//    while (indexes.size()) {
//        m_model->removeRows(indexes.back().row(), 1, indexes.back().parent());
//        indexes = m_selectionModel->selectedIndexes();
//    }
}
