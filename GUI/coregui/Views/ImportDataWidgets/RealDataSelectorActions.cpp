// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/ImportDataWidgets/RealDataSelectorActions.cpp
//! @brief     Implements class RealDataSelectorActions
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "RealDataSelectorActions.h"
#include "ImportDataAssistant.h"
#include "RealDataItem.h"
#include "RealDataModel.h"
#include "OutputData.h"
#include <QAction>
#include <QItemSelectionModel>
#include <QMenu>

RealDataSelectorActions::RealDataSelectorActions(QObject* parent)
    : QObject(parent)
    , m_importDataAction(nullptr)
    , m_removeDataAction(nullptr)
    , m_realDataModel(nullptr)
    , m_selectionModel(nullptr)
{
    m_importDataAction = new QAction(QStringLiteral("Import data"), parent);
    m_importDataAction->setIcon(QIcon(":/images/toolbar16dark_newitem.svg"));
    m_importDataAction->setToolTip(QStringLiteral("Import data"));
    connect(m_importDataAction, &QAction::triggered,
            this, &RealDataSelectorActions::onImportDataAction);

    m_removeDataAction = new QAction(QStringLiteral("Remove this data"), parent);
    m_removeDataAction->setIcon(QIcon(":/images/toolbar16dark_recycle.svg"));
    m_removeDataAction->setToolTip(QStringLiteral("Remove selected data"));
    connect(m_removeDataAction, &QAction::triggered,
            this, &RealDataSelectorActions::onRemoveDataAction);
}

void RealDataSelectorActions::setRealDataModel(RealDataModel* model)
{
    m_realDataModel = model;
}

void RealDataSelectorActions::setSelectionModel(QItemSelectionModel* selectionModel)
{
    m_selectionModel = selectionModel;

}

void RealDataSelectorActions::onImportDataAction()
{
    Q_ASSERT(m_realDataModel);
    Q_ASSERT(m_selectionModel);
    ImportDataAssistant assistant;
    QString baseNameOfImportedFile;

    std::unique_ptr<OutputData<double>> data(assistant.importData(baseNameOfImportedFile));
    if (data) {
        RealDataItem* realDataItem
            = dynamic_cast<RealDataItem*>(m_realDataModel->insertNewItem(Constants::RealDataType));
        realDataItem->setItemName(baseNameOfImportedFile);
        realDataItem->setOutputData(data.release());
        m_selectionModel->clearSelection();
        m_selectionModel->select(realDataItem->index(), QItemSelectionModel::Select);
    }
}

void RealDataSelectorActions::onRemoveDataAction()
{
    QModelIndex currentIndex = m_selectionModel->currentIndex();
    if (currentIndex.isValid())
        m_realDataModel->removeRows(currentIndex.row(), 1, QModelIndex());

    updateSelection();
}

void RealDataSelectorActions::onContextMenuRequest(const QPoint& point,
                                                   const QModelIndex& indexAtPoint)
{
    QMenu menu;

    setAllActionsEnabled(indexAtPoint.isValid());

    m_importDataAction->setEnabled(true);

    menu.addAction(m_removeDataAction);
    menu.addSeparator();
    menu.addAction(m_importDataAction);
    menu.exec(point);
}

void RealDataSelectorActions::setAllActionsEnabled(bool value)
{
    m_importDataAction->setEnabled(value);
    m_removeDataAction->setEnabled(value);
}

void RealDataSelectorActions::updateSelection()
{
    if (!m_selectionModel->hasSelection()) {
        // select last item
        QModelIndex itemIndex
            = m_realDataModel->index(m_realDataModel->rowCount(QModelIndex()) - 1, 0, QModelIndex());
        m_selectionModel->select(itemIndex, QItemSelectionModel::ClearAndSelect);
    }
}
