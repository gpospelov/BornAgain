// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/ImportDataWidgets/ImportDataToolBar.cpp
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
#include "ImportDataToolBar.h"
#include "ComboProperty.h"
#include "DetectorItems.h"
#include "IDetector2D.h"
#include "IDetector2D.h"
#include "ImportDataAssistant.h"
#include "InstrumentItem.h"
#include "InstrumentModel.h"
#include "IntensityDataItem.h"
#include "JobItemHelper.h"
#include "RealDataItem.h"
#include "RealDataModel.h"
#include "RectangularDetectorItem.h"
#include "SessionItem.h"
#include "SphericalDetectorItem.h"
#include <QAction>
#include <QDebug>
#include <QItemSelectionModel>

ImportDataToolBar::ImportDataToolBar(QWidget *parent)
    : StyledToolBar(parent)
    , m_importDataAction(0)
//    , m_cloneDataAction(0)
    , m_removeDataAction(0)
    , m_realDataModel(0)
    , m_instrumentModel(0)
    , m_selectionModel(0)
{
    setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    m_importDataAction = new QAction(QStringLiteral("Import"), parent);
    m_importDataAction->setIcon(QIcon(":/images/toolbar16light_newitem.svg"));
    m_importDataAction->setToolTip(QStringLiteral("Import data"));
    connect(m_importDataAction, SIGNAL(triggered()), this,
            SLOT(onImportDataAction()));
    addAction(m_importDataAction);

//    m_cloneDataAction = new QAction(QStringLiteral("Clone"), parent);
//    m_cloneDataAction->setIcon(
//        QIcon(":/images/toolbar16light_cloneitem.svg"));
//    m_cloneDataAction->setToolTip(QStringLiteral("Clone selected data"));
//    connect(m_cloneDataAction, SIGNAL(triggered()), this,
//            SLOT(onCloneDataAction()));
//    addAction(m_cloneDataAction);

    m_removeDataAction = new QAction(QStringLiteral("Remove"), parent);
    m_removeDataAction->setIcon(QIcon(":/images/toolbar16light_recycle.svg"));
    m_removeDataAction->setToolTip(QStringLiteral("Remove selected data"));
    connect(m_removeDataAction, SIGNAL(triggered()), this,
            SLOT(onRemoveDataAction()));
    addAction(m_removeDataAction);

}

void ImportDataToolBar::setRealDataModel(RealDataModel *model)
{
    m_realDataModel = model;
}

void ImportDataToolBar::setInstrumentModel(InstrumentModel *model)
{
    m_instrumentModel = model;
}

void ImportDataToolBar::setSelectionModel(QItemSelectionModel *selectionModel)
{
    m_selectionModel = selectionModel;
}

//! Sets action to toolbar, preserving own toolbar's actions.

void ImportDataToolBar::setActionList(const QList<QAction *> &actionList)
{
    clear();

    addAction(m_importDataAction);
    addAction(m_removeDataAction);

    addStyledSeparator();

    foreach(QAction *action, actionList) {
        addAction(action);
    }

}

void ImportDataToolBar::onImportDataAction()
{
    qDebug() << "ImportDataToolBar::onImportDataAction()";
    Q_ASSERT(m_realDataModel);
    ImportDataAssistant assistant;
    QString baseNameOfImportedFile;


    std::unique_ptr<OutputData<double>> data(assistant.importData(baseNameOfImportedFile));
    if(data) {
        RealDataItem *realDataItem = dynamic_cast<RealDataItem *>(
            m_realDataModel->insertNewItem(Constants::RealDataType));
        realDataItem->setItemName(baseNameOfImportedFile);
        realDataItem->setOutputData(data.release());


//        IntensityDataItem *intensityDataItem = dynamic_cast<IntensityDataItem *>(
//            m_realDataModel->insertNewItem(Constants::IntensityDataType, realDataItem->index()));
//        intensityDataItem->setOutputData(data.release());
//        ComboProperty combo;
//        combo << Constants::UnitsNbins;
//        intensityDataItem->setItemValue(IntensityDataItem::P_AXES_UNITS, combo.getVariant());
//        intensityDataItem->getItem(IntensityDataItem::P_AXES_UNITS)->setVisible(true);

        m_selectionModel->clearSelection();
        m_selectionModel->select(realDataItem->index(), QItemSelectionModel::Select);
    }


//    if(OutputData<double> *data = assistant.importData(baseNameOfImportedFile)) {
//        RealDataItem *realDataItem = dynamic_cast<RealDataItem *>(
//                    m_realDataModel->insertNewItem(Constants::RealDataType));
//        realDataItem->setItemName(baseNameOfImportedFile);
//        IntensityDataItem *intensityDataItem = dynamic_cast<IntensityDataItem *>(
//                    m_realDataModel->insertNewItem(Constants::IntensityDataType, realDataItem->index()));
//        intensityDataItem->setOutputData(data);
//        m_selectionModel->clearSelection();
//        m_selectionModel->select(realDataItem->index(), QItemSelectionModel::Select);
//        qDebug() << "baseNameOfImportedFile" << baseNameOfImportedFile;

//        //matchAxesToInstrument(realDataItem);
//    }

}

void ImportDataToolBar::onCloneDataAction()
{
    qDebug() << "ImportDataToolBar::onCloneDataAction()";

}

void ImportDataToolBar::onRemoveDataAction()
{
    qDebug() << "ImportDataToolBar::onRemoveDataAction()";
    Q_ASSERT(m_realDataModel);
    Q_ASSERT(m_selectionModel);

    QModelIndex currentIndex = m_selectionModel->currentIndex();
    qDebug() << "InstrumentView::onRemoveInstrument()" <<  currentIndex;
    if(currentIndex.isValid())
        m_realDataModel->removeRows(currentIndex.row(), 1, currentIndex.parent());

//    QModelIndexList indexes = m_selectionModel->selectedIndexes();
//    while (indexes.size()) {
//        m_model->removeRows(indexes.back().row(), 1, indexes.back().parent());
//        indexes = m_selectionModel->selectedIndexes();
    //    }
}


//! FIXME refactor this after refactoring of DetectorItem

//! When we import new real data, we perform scan of existing instruments, and if
//! the  axes dimensions in the detectorItem is the same as in RealDataItem, we silently set axes
//! of RealDataItem to match  the axes of existing detector.

//! TODO this is a temporary hack, later it will be replaced with special widget to match
//! axes of RealDataItem with existing instruments.
//! Combine with JobItemHelper::updateDataAxes to avoid duplication.

void ImportDataToolBar::matchAxesToInstrument(RealDataItem *realDataItem)
{

    std::unique_ptr<OutputData<double>> detectorMap;

    foreach(SessionItem *item, m_instrumentModel->topItems()) {
        InstrumentItem *instrumentItem = dynamic_cast<InstrumentItem *>(item);
        detectorMap.reset(JobItemHelper::createDefaultDetectorMap(instrumentItem));

        OutputData<double> *realData = realDataItem->intensityDataItem()->getOutputData();
        if(realData->hasSameDimensions(*detectorMap.get())) {
            detectorMap->setRawDataVector(realData->getRawDataVector());
            IntensityDataItem *intensityItem = realDataItem->intensityDataItem();
            intensityItem->setOutputData(detectorMap.release());
            intensityItem->setAxesRangeToData();
            ComboProperty combo;
            combo << Constants::UnitsNbins;
            intensityItem->setItemValue(IntensityDataItem::P_AXES_UNITS, combo.getVariant());
            intensityItem->getItem(IntensityDataItem::P_AXES_UNITS)->setVisible(true);

            break;
        }



//        DetectorItem *detectorItem = instrumentItem->getDetectorItem();

//        auto subDetector = detectorItem->getGroupItem(DetectorItem::P_DETECTOR);
//        Q_ASSERT(subDetector);

//        if(auto sphericalDetector = dynamic_cast<SphericalDetectorItem *>(subDetector)) {
//            auto detector = sphericalDetector->createDetector();
//            detectorMap.reset(detector->createDetectorMap(IDetector2D::DEGREES));
//        }

//        else if(auto rectangularDetector = dynamic_cast<RectangularDetectorItem *>(subDetector)) {
//            auto detector = rectangularDetector->createDetector();
//            detectorMap.reset(detector->createDetectorMap(IDetector2D::DEGREES));
//        }

    }

}
