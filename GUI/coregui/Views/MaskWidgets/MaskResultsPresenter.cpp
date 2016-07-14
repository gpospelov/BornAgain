// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaskWidgets/MaskResultsPresenter.cpp
//! @brief     Implements class MaskResultsPresenter
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include <QDebug>
#include <QVBoxLayout>
#include "ColorMapPlot.h"
#include "DetectorMask.h"
#include "IShape2D.h"
#include "IntensityDataItem.h"
#include "MaskItems.h"
#include "OutputData.h"
#include "SessionModel.h"
#include "MaskResultsPresenter.h"

MaskResultsPresenter::MaskResultsPresenter(QWidget *parent)
    : QObject(parent)
    , m_interpolation_flag_backup(false)
{

}

void MaskResultsPresenter::setMaskContext(SessionModel *maskModel,
                                          const QModelIndex &maskContainerIndex,
                                          IntensityDataItem *intensityItem)
{
    m_maskModel = maskModel;
    m_maskContainerIndex = maskContainerIndex;
    m_intensityDataItem = intensityItem;

}


void MaskResultsPresenter::updatePresenter(MaskEditorFlags::PresentationType presentationType)
{
    if(!m_maskContainerIndex.isValid()) return;

    if(presentationType == MaskEditorFlags::MASK_PRESENTER) {
        setShowMaskMode();
    } else if(presentationType == MaskEditorFlags::MASK_EDITOR) {
        setOriginalMode();
    }
}

//! Update IntensityDataItem in SessionModel to represent masked areas. Corresponding
//! bins of OutputData will be put to zero.
void MaskResultsPresenter::setShowMaskMode()
{
    if (OutputData<double> *maskedData = createMaskPresentation()) {
        backup_data();
        m_intensityDataItem->setOutputData(maskedData);
        m_intensityDataItem->setItemValue(IntensityDataItem::P_IS_INTERPOLATED, false);
    } else {
        m_dataBackup.reset();
    }
}

//! Restores original state of IntensityDataItem
void MaskResultsPresenter::setOriginalMode()
{
    if (m_dataBackup) {
        m_intensityDataItem->setOutputData(m_dataBackup->clone());
        m_intensityDataItem->setItemValue(IntensityDataItem::P_IS_INTERPOLATED,
                                        m_interpolation_flag_backup);
    }
}

void MaskResultsPresenter::backup_data()
{
    m_interpolation_flag_backup
        = m_intensityDataItem->getItemValue(IntensityDataItem::P_IS_INTERPOLATED).toBool();
    m_dataBackup.reset(m_intensityDataItem->getOutputData()->clone());
}

//! Constructs OutputData which contains original intensity data except masked areas,
//! where bin content is set to zero.
OutputData<double> *MaskResultsPresenter::createMaskPresentation() const
{
    qDebug() << "MaskResultsPresenter::createMaskPresentation()";

    // Requesting mask information
    DetectorMask detectorMask;
    for (int i_row = m_maskModel->rowCount(m_maskContainerIndex); i_row > 0; --i_row) {
        QModelIndex itemIndex = m_maskModel->index(i_row - 1, 0, m_maskContainerIndex);
        if (MaskItem *item = dynamic_cast<MaskItem *>(m_maskModel->itemForIndex(itemIndex))) {
            if (item && (item->modelType() == Constants::GroupItemType || item->modelType() == Constants::PropertyType)) {
                continue;
            }

            std::unique_ptr<Geometry::IShape2D> shape = item->createShape();
            if (shape) {
                detectorMask.addMask(*shape.get(),
                                     item->getItemValue(MaskItem::P_MASK_VALUE).toBool());
            }
        }
    }

    if (!detectorMask.hasMasks())
        return 0;

    // modifying IntensityData
    Q_ASSERT(m_intensityDataItem->getOutputData());

    OutputData<double> *result = m_intensityDataItem->getOutputData()->clone();

    detectorMask.initMaskData(*result);

    for (size_t i = 0; i < detectorMask.getMaskData()->getAllocatedSize(); ++i) {
        bool mask_value = (*detectorMask.getMaskData())[i];
        if (mask_value == true)
            (*result)[i] = 0.0;
    }

    return result;
}
