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
#include <QDebug>

DetectorMaskDelegate::DetectorMaskDelegate(QObject *parent)
    : QObject(parent)
    , m_maskModel(0)
    , m_detectorItem(0)
{

}

void DetectorMaskDelegate::setDetectorItem(DetectorItem *detectorItem)
{
    m_detectorItem = detectorItem;
    init_mask_model();
}


MaskModel *DetectorMaskDelegate::getMaskModel()
{
    return m_maskModel;
}


void DetectorMaskDelegate::init_mask_model()
{
    delete m_maskModel;
    m_maskModel = new MaskModel(this);

    IntensityDataItem *intensityItem = dynamic_cast<IntensityDataItem *>(
        m_maskModel->insertNewItem(Constants::IntensityDataType));
    Q_ASSERT(intensityItem);

    intensityItem->setOutputData(createOutputData(m_detectorItem));
}

OutputData<double> *DetectorMaskDelegate::createOutputData(DetectorItem *detectorItem)
{
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


    return result;

}
