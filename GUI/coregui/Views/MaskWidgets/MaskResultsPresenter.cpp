// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaskWidgets/MaskResultsPresenter.cpp
//! @brief     Implements class MaskResultsPresenter
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MaskResultsPresenter.h"
#include "ColorMapPlot.h"
#include "SessionModel.h"
#include "IntensityDataItem.h"
#include "OutputData.h"
#include "MaskItems.h"
#include "IShape2D.h"
#include "DetectorMask.h"
#include <boost/scoped_ptr.hpp>
#include <QVBoxLayout>
#include <QDebug>

MaskResultsPresenter::MaskResultsPresenter(QWidget *parent)
    : QObject(parent)
{

}

void MaskResultsPresenter::setModel(SessionModel *maskModel, const QModelIndex &rootIndex)
{
    m_maskModel = maskModel;
    m_rootIndex = rootIndex;
}

void MaskResultsPresenter::updatePresenter(MaskEditorFlags::PresentationType presentationType)
{
    Q_ASSERT(m_maskModel);
    Q_ASSERT(m_rootIndex.isValid());

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
    qDebug() << "MaskResultsPresenter::setShowMaskMode()";

    if (OutputData<double> *maskedData = createMaskPresentation()) {
        backup_data();
        IntensityDataItem *origItem
            = dynamic_cast<IntensityDataItem *>(m_maskModel->itemForIndex(m_rootIndex));
        origItem->setOutputData(maskedData);
        qDebug() << m_dataBackup->totalSum() << maskedData->totalSum();
        origItem->setRegisteredProperty(IntensityDataItem::P_IS_INTERPOLATED, false);
    } else {
        m_dataBackup.reset();
    }
}

//! Restores original state of IntensityDataItem
void MaskResultsPresenter::setOriginalMode()
{
    if (m_dataBackup) {
        IntensityDataItem *origItem
            = dynamic_cast<IntensityDataItem *>(m_maskModel->itemForIndex(m_rootIndex));
        origItem->setOutputData(m_dataBackup->clone());
        origItem->setRegisteredProperty(IntensityDataItem::P_IS_INTERPOLATED,
                                        m_interpolation_flag_backup);
    }
}

void MaskResultsPresenter::backup_data()
{
    IntensityDataItem *origItem
        = dynamic_cast<IntensityDataItem *>(m_maskModel->itemForIndex(m_rootIndex));
    Q_ASSERT(origItem);
    m_interpolation_flag_backup
        = origItem->getRegisteredProperty(IntensityDataItem::P_IS_INTERPOLATED).toBool();
    m_dataBackup.reset(origItem->getOutputData()->clone());
}

//! Constructs OutputData which contains original intensity data except masked areas,
//! where bin content is set to zero.
OutputData<double> *MaskResultsPresenter::createMaskPresentation() const
{
    qDebug() << "MaskResultsPresenter::createMaskPresentation()";

    // Requesting mask information
    DetectorMask detectorMask;
    for (int i_row = m_maskModel->rowCount(m_rootIndex); i_row > 0; --i_row) {
        QModelIndex itemIndex = m_maskModel->index(i_row - 1, 0, m_rootIndex);
        if (MaskItem *item = dynamic_cast<MaskItem *>(m_maskModel->itemForIndex(itemIndex))) {
            Geometry::IShape2D *shape = item->createShape();
            if (shape) {
                detectorMask.addMask(*shape,
                                     item->getRegisteredProperty(MaskItem::P_MASK_VALUE).toBool());
            }
            delete shape;
        }
    }

    if (!detectorMask.hasMasks())
        return 0;

    // modifying IntensityData
    IntensityDataItem *origItem
        = dynamic_cast<IntensityDataItem *>(m_maskModel->itemForIndex(m_rootIndex));
    Q_ASSERT(origItem);

    OutputData<double> *result = origItem->getOutputData()->clone();

    detectorMask.initMaskData(*result);

    qDebug() << "BBB 1.4" << detectorMask.getNumberOfMaskedChannels();
    for (size_t i = 0; i < detectorMask.getMaskData()->getAllocatedSize(); ++i) {
        bool mask_value = (*detectorMask.getMaskData())[i];
        if (mask_value == true)
            (*result)[i] = 0.0;
    }

    return result;
}
