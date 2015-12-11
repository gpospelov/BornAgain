// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/InstrumentWidgets/DetectorMaskDelegate.cpp
//! @brief     Implements class DetectorMaskDelegate
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "DetectorMaskDelegate.h"
#include "InstrumentModel.h"
#include "MaskModel.h"
#include "DetectorItems.h"
#include "IntensityDataItem.h"
#include "OutputData.h"
#include "AxesItems.h"
#include "MaskEditor.h"
#include "MaskItems.h"
#include <QDebug>

DetectorMaskDelegate::DetectorMaskDelegate(QObject *parent)
    : QObject(parent)
    , m_instrumentModel(0)
    , m_detectorItem(0)
    , m_intensityItem(0)
{

}

void DetectorMaskDelegate::setDetectorContext(InstrumentModel *instrumentModel,
                                              DetectorItem *detectorItem)
{
    m_instrumentModel = instrumentModel;
    m_detectorItem = detectorItem;
    createIntensityDataItem();
    createMaskContainer();
}

void DetectorMaskDelegate::initMaskEditor(MaskEditor *maskEditor)
{
    Q_ASSERT(m_instrumentModel);
    Q_ASSERT(m_detectorItem);
    Q_ASSERT(m_intensityItem);
    Q_ASSERT(m_detectorItem->getMaskContainerItem());
    maskEditor->setMaskContext(
        m_instrumentModel,
        m_instrumentModel->indexOfItem(m_detectorItem->getMaskContainerItem()),
        m_intensityItem);

}


//! Creates IntensityDataItem from DetectorItem for later usage in MaskEditor.
//! As amplitude, value 1.0 is set for each bin.
//! The object additionally tuned to appear nicely on ColorMap plot.
void DetectorMaskDelegate::createIntensityDataItem()
{
    delete m_intensityItem;
    m_intensityItem = new IntensityDataItem();
    m_intensityItem->setPropertyAppearance(IntensityDataItem::P_PROJECTIONS_FLAG,
                                           PropertyAttribute::DISABLED);

    AmplitudeAxisItem *zAxisItem = dynamic_cast<AmplitudeAxisItem *>(
        m_intensityItem->getSubItems()[IntensityDataItem::P_ZAXIS]);

    zAxisItem->setRegisteredProperty(BasicAxisItem::P_IS_VISIBLE, false);
    zAxisItem->setRegisteredProperty(BasicAxisItem::P_MIN, 0.0);
    zAxisItem->setRegisteredProperty(BasicAxisItem::P_MAX, 2.0);
    zAxisItem->setRegisteredProperty(AmplitudeAxisItem::P_IS_LOGSCALE, false);
    zAxisItem->setRegisteredProperty(AmplitudeAxisItem::P_LOCK_MIN_MAX, true);

    m_intensityItem->setOutputData(createOutputData(m_detectorItem));
}

//! Creates MaskContainer in DetectorItem
void DetectorMaskDelegate::createMaskContainer()
{
    Q_ASSERT(m_detectorItem);
    if(!m_detectorItem->getMaskContainerItem()) {
        m_instrumentModel->insertNewItem(Constants::MaskContainerType,
                                         m_instrumentModel->indexOfItem(m_detectorItem));
    }
}

//! Creates OutputData from DetectorItem's axes for later initialization of IntensityDataItem
OutputData<double> *DetectorMaskDelegate::createOutputData(DetectorItem *detectorItem)
{
    Q_ASSERT(detectorItem);
    OutputData<double> *result = new OutputData<double>;


    auto subDetector = detectorItem->getSubItems()[DetectorItem::P_DETECTOR];
    Q_ASSERT(subDetector);


    Q_ASSERT(subDetector->modelType() == Constants::SphericalDetectorType);

    auto x_axis = dynamic_cast<BasicAxisItem *>(
         subDetector->getSubItems()[PhiAlphaDetectorItem::P_PHI_AXIS]);
    Q_ASSERT(x_axis);
    int n_x = x_axis->getRegisteredProperty(BasicAxisItem::P_NBINS).toInt();
    double x_min
        = Units::deg2rad(x_axis->getRegisteredProperty(BasicAxisItem::P_MIN).toDouble());
    double x_max
        = Units::deg2rad(x_axis->getRegisteredProperty(BasicAxisItem::P_MAX).toDouble());

    auto y_axis = dynamic_cast<BasicAxisItem *>(
        subDetector->getSubItems()[PhiAlphaDetectorItem::P_ALPHA_AXIS]);
    Q_ASSERT(y_axis);
    int n_y = y_axis->getRegisteredProperty(BasicAxisItem::P_NBINS).toInt();
    double y_min
        = Units::deg2rad(y_axis->getRegisteredProperty(BasicAxisItem::P_MIN).toDouble());
    double y_max
        = Units::deg2rad(y_axis->getRegisteredProperty(BasicAxisItem::P_MAX).toDouble());


    result->addAxis("x", n_x, x_min, x_max);
    result->addAxis("y", n_y, y_min, y_max);

    result->setAllTo(1.0);

    return result;

}

//! Copies masks from the detector to IntensityData objects
void DetectorMaskDelegate::copyMasksFromDetector()
{
//    Q_ASSERT(m_detectorItem);
//    auto subDetector = m_detectorItem->getSubItems()[DetectorItem::P_DETECTOR];
//    Q_ASSERT(subDetector);

//    foreach(ParameterizedItem *item, )

}
