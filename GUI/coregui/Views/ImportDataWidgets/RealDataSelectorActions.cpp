// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/ImportDataWidgets/RealDataSelectorActions.cpp
//! @brief     Implements class RealDataSelectorActions
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "RealDataSelectorActions.h"
#include "GUIHelpers.h"
#include "ImportDataInfo.h"
#include "ImportDataUtils.h"
#include "IntensityDataFunctions.h"
#include "IntensityDataItem.h"
#include "MaskItems.h"
#include "OutputData.h"
#include "ProjectionItems.h"
#include "RealDataItem.h"
#include "RealDataModel.h"
#include <QAction>
#include <QApplication>
#include <QItemSelectionModel>
#include <QMenu>

namespace {
bool openRotateWarningDialog(QWidget* parent) {
    const QString title("Rotate data");

    const QString message("Rotation will break the link between the data and the instrument. "
                          "Detector masks or profiles, if they exist, will be removed.");

    return GUIHelpers::question(parent, title, message, "Do you wish to rotate the data?",
        "Yes, please rotate", "No, cancel data rotation");
}

//! Returns true, if rotation will affect linked instrument or mask presence.

bool rotationAffectsSetup(IntensityDataItem& intensityItem) {
    if (intensityItem.parent()->getItemValue(RealDataItem::P_INSTRUMENT_ID).toBool())
        return true;

    if (intensityItem.maskContainerItem() && intensityItem.maskContainerItem()->hasChildren())
        return true;

    if (intensityItem.projectionContainerItem()
        && intensityItem.projectionContainerItem()->hasChildren())
        return true;

    return false;
}

//! Resets linked instruments and masks.

void resetSetup(IntensityDataItem& intensityItem) {

    auto data_parent = intensityItem.parent();
    if (data_parent->getItemValue(RealDataItem::P_INSTRUMENT_ID).toBool())
        data_parent->setItemValue(RealDataItem::P_INSTRUMENT_ID, QString());

    if (auto maskContainer = intensityItem.maskContainerItem())
        maskContainer->model()->removeRows(0, maskContainer->numberOfChildren(), maskContainer->index());

    if (auto projectionsContainer = intensityItem.projectionContainerItem())
        projectionsContainer->model()->removeRows(0, projectionsContainer->numberOfChildren(),
                                                  projectionsContainer->index());
}

}


RealDataSelectorActions::RealDataSelectorActions(QObject* parent)
    : QObject(parent)
    , m_importBornAgainDataAction(nullptr)
    , m_importAsciiDataAction(nullptr)
    , m_removeDataAction(nullptr)
    , m_rotateDataAction(new QAction(this))
    , m_realDataModel(nullptr)
    , m_selectionModel(nullptr)
{
    m_importBornAgainDataAction = new QAction(QStringLiteral("Import 2D data"), parent);
    m_importBornAgainDataAction->setIcon(QIcon(":/images/toolbar16dark_newitem.svg"));
    m_importBornAgainDataAction->setToolTip(QStringLiteral("Import 2D data"));
    connect(m_importBornAgainDataAction, &QAction::triggered,
            this, &RealDataSelectorActions::onImportBornAgainDataAction);

    m_importAsciiDataAction = new QAction(QStringLiteral("Import Ascii data"), parent);
    m_importAsciiDataAction->setIcon(QIcon(":/images/toolbar16dark_newitem.svg"));
    m_importAsciiDataAction->setToolTip(QStringLiteral("Import Bornagain data"));
    connect(m_importAsciiDataAction, &QAction::triggered,
            this, &RealDataSelectorActions::onImportAsciiDataAction);

    m_removeDataAction = new QAction(QStringLiteral("Remove this data"), parent);
    m_removeDataAction->setIcon(QIcon(":/images/toolbar16dark_recycle.svg"));
    m_removeDataAction->setToolTip(QStringLiteral("Remove selected data"));
    connect(m_removeDataAction, &QAction::triggered,
            this, &RealDataSelectorActions::onRemoveDataAction);

    m_rotateDataAction->setText("Rotate this data");
    m_rotateDataAction->setIcon(QIcon(":/images/toolbar16light_rotate.svg"));
    m_rotateDataAction->setToolTip("Rotate intensity data by 90 deg counterclockwise");
    connect(m_rotateDataAction, &QAction::triggered,
            this, &RealDataSelectorActions::onRotateDataRequest);
}

void RealDataSelectorActions::setRealDataModel(RealDataModel* model)
{
    m_realDataModel = model;
}

void RealDataSelectorActions::setSelectionModel(QItemSelectionModel* selectionModel)
{
    m_selectionModel = selectionModel;

}

void RealDataSelectorActions::onImportBornAgainDataAction()
{
    Q_ASSERT(m_realDataModel);
    Q_ASSERT(m_selectionModel);
    QString baseNameOfImportedFile;

    std::unique_ptr<OutputData<double>> data = ImportDataUtils::ImportBornAgainData(baseNameOfImportedFile);
    if (data) {
        RealDataItem* realDataItem
            = dynamic_cast<RealDataItem*>(m_realDataModel->insertNewItem(Constants::RealDataType));
        realDataItem->setItemName(baseNameOfImportedFile);
        realDataItem->setOutputData(data.release());
        m_selectionModel->clearSelection();
        m_selectionModel->select(realDataItem->index(), QItemSelectionModel::Select);
    }
}

void RealDataSelectorActions::onImportAsciiDataAction()
{
    Q_ASSERT(m_realDataModel);
    Q_ASSERT(m_selectionModel);
    QString baseNameOfImportedFile;

    auto data = ImportDataUtils::ImportAsciiData(baseNameOfImportedFile);
    if (data) {
        RealDataItem* realDataItem
            = dynamic_cast<RealDataItem*>(m_realDataModel->insertNewItem(Constants::RealDataType));
        realDataItem->setItemName(baseNameOfImportedFile);
        realDataItem->setImportData(std::move(data));
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

void RealDataSelectorActions::onRotateDataRequest()
{
    QModelIndex currentIndex = m_selectionModel->currentIndex();
    if (!currentIndex.isValid())
        return;

    RealDataItem* dataItem = dynamic_cast<RealDataItem*>(m_realDataModel->itemForIndex(currentIndex));
    Q_ASSERT(dataItem);
    auto intensityItem = dataItem->intensityDataItem();
    Q_ASSERT(intensityItem);

    if (rotationAffectsSetup(*intensityItem)) {
        if (!openRotateWarningDialog(nullptr))
            return;

        m_selectionModel->select(currentIndex, QItemSelectionModel::Clear);
        resetSetup(*intensityItem);
    }

    QApplication::setOverrideCursor(Qt::WaitCursor);
    const auto input = intensityItem->getOutputData();
    intensityItem->setOutputData(
        IntensityDataFunctions::createRearrangedDataSet(*input, 1).release());
    intensityItem->setAxesRangeToData();

    m_selectionModel->select(currentIndex, QItemSelectionModel::Select);
    QApplication::restoreOverrideCursor();
}

void RealDataSelectorActions::onContextMenuRequest(const QPoint& point,
                                                   const QModelIndex& indexAtPoint)
{
    QMenu menu;
    menu.setToolTipsVisible(true);

    setAllActionsEnabled(indexAtPoint.isValid());

    m_importBornAgainDataAction->setEnabled(true);
    m_importAsciiDataAction->setEnabled(true);

    menu.addAction(m_removeDataAction);
    menu.addAction(m_rotateDataAction);
    menu.addSeparator();
    menu.addAction(m_importBornAgainDataAction);
    menu.addAction(m_importAsciiDataAction);
    menu.exec(point);
}

void RealDataSelectorActions::setAllActionsEnabled(bool value)
{
    m_importBornAgainDataAction->setEnabled(value);
    m_importAsciiDataAction->setEnabled(value);
    m_rotateDataAction->setEnabled(value);
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
