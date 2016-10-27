// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/DetectorMaskDelegate.cpp
//! @brief     Implements class DetectorMaskDelegate
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "DetectorMaskDelegate.h"
#include "AxesItems.h"
#include "ComboProperty.h"
#include "DetectorItems.h"
#include "GUIHelpers.h"
#include "InstrumentModel.h"
#include "IntensityDataItem.h"
#include "MaskEditor.h"
#include "MaskItems.h"
#include "MaskModel.h"
#include "OutputData.h"
#include <QDebug>

DetectorMaskDelegate::DetectorMaskDelegate(QObject *parent)
    : QObject(parent)
    , m_tempIntensityDataModel(new SessionModel("TempIntensityDataModel", this))
    , m_instrumentModel(0)
    , m_detectorItem(0)
    , m_intensityItem(0)
{
}

void DetectorMaskDelegate::initMaskEditorContext(
    MaskEditor *maskEditor, InstrumentModel *instrumentModel,
    DetectorItem *detectorItem)
{
    m_instrumentModel = instrumentModel;
    m_detectorItem = detectorItem;

    Q_ASSERT(m_instrumentModel);
    Q_ASSERT(m_detectorItem);

    createIntensityDataItem();
    createMaskContainer();

    Q_ASSERT(m_detectorItem->maskContainerItem());

    maskEditor->setMaskContext(
        m_instrumentModel,
        m_instrumentModel->indexOfItem(m_detectorItem->maskContainerItem()),
        m_intensityItem);
}

//! Creates IntensityDataItem from DetectorItem for later usage in MaskEditor.
//! As amplitude, value 1.0 is set for each bin.
//! The object additionally tuned to appear nicely on ColorMap plot.
void DetectorMaskDelegate::createIntensityDataItem()
{
    m_tempIntensityDataModel->clear();

    m_intensityItem = dynamic_cast<IntensityDataItem *>(
        m_tempIntensityDataModel->insertNewItem(Constants::IntensityDataType));
    Q_ASSERT(m_intensityItem);

    m_intensityItem->getItem(IntensityDataItem::P_PROJECTIONS_FLAG)->setEnabled(false);
    m_intensityItem->setItemValue(IntensityDataItem::P_IS_INTERPOLATED,
                                           false);

//    ComboProperty gradient
//        = m_intensityItem->getRegisteredProperty(IntensityDataItem::P_GRADIENT)
//              .value<ComboProperty>();
//    gradient.setValue(Constants::GRADIENT_GRAYSCALE);
//    m_intensityItem->setRegisteredProperty(IntensityDataItem::P_GRADIENT,
//                                           gradient.getVariant());

    AmplitudeAxisItem *zAxisItem = dynamic_cast<AmplitudeAxisItem *>(
        m_intensityItem->getItem(IntensityDataItem::P_ZAXIS));

    zAxisItem->setItemValue(BasicAxisItem::P_IS_VISIBLE, false);
    zAxisItem->setItemValue(BasicAxisItem::P_MIN, 0.0);
    zAxisItem->setItemValue(BasicAxisItem::P_MAX, 2.0);
    zAxisItem->setItemValue(AmplitudeAxisItem::P_IS_LOGSCALE, false);
    zAxisItem->setItemValue(AmplitudeAxisItem::P_LOCK_MIN_MAX, true);

    m_intensityItem->setOutputData(createOutputData(m_detectorItem));
}

//! Creates MaskContainer in DetectorItem
void DetectorMaskDelegate::createMaskContainer()
{
    Q_ASSERT(m_detectorItem);
    if (!m_detectorItem->maskContainerItem()) {
        m_instrumentModel->insertNewItem(
            Constants::MaskContainerType,
            m_instrumentModel->indexOfItem(m_detectorItem));
    }
}

//! Creates OutputData from DetectorItem's axes for later initialization of
//! IntensityDataItem
OutputData<double> *
DetectorMaskDelegate::createOutputData(DetectorItem *detectorItem)
{
    Q_ASSERT(detectorItem);
    OutputData<double> *result = new OutputData<double>;

    auto subDetector = detectorItem->getGroupItem(DetectorItem::P_DETECTOR);
    Q_ASSERT(subDetector);

    if (subDetector->modelType() == Constants::SphericalDetectorType) {

        auto x_axis = dynamic_cast<BasicAxisItem *>(
            subDetector->getItem(SphericalDetectorItem::P_PHI_AXIS));
        Q_ASSERT(x_axis);
        int n_x = x_axis->getItemValue(BasicAxisItem::P_NBINS).toInt();
        double x_min
            = x_axis->getItemValue(BasicAxisItem::P_MIN).toDouble();
        double x_max
            = x_axis->getItemValue(BasicAxisItem::P_MAX).toDouble();

        auto y_axis = dynamic_cast<BasicAxisItem *>(
            subDetector->getItem(SphericalDetectorItem::P_ALPHA_AXIS));
        Q_ASSERT(y_axis);
        int n_y = y_axis->getItemValue(BasicAxisItem::P_NBINS).toInt();
        double y_min
            = y_axis->getItemValue(BasicAxisItem::P_MIN).toDouble();
        double y_max
            = y_axis->getItemValue(BasicAxisItem::P_MAX).toDouble();

        result->addAxis("x", n_x, x_min, x_max);
        result->addAxis("y", n_y, y_min, y_max);

    }

    else if (subDetector->modelType() == Constants::RectangularDetectorType) {
        auto x_axis = dynamic_cast<BasicAxisItem *>(
            subDetector->getItem(RectangularDetectorItem::P_X_AXIS));
        Q_ASSERT(x_axis);
        int n_x = x_axis->getItemValue(BasicAxisItem::P_NBINS).toInt();
        double x_min = x_axis->getItemValue(BasicAxisItem::P_MIN).toDouble();
        double x_max = x_axis->getItemValue(BasicAxisItem::P_MAX).toDouble();

        auto y_axis = dynamic_cast<BasicAxisItem *>(
            subDetector->getItem(RectangularDetectorItem::P_Y_AXIS));
        Q_ASSERT(y_axis);
        int n_y = y_axis->getItemValue(BasicAxisItem::P_NBINS).toInt();
        double y_min
            = y_axis->getItemValue(BasicAxisItem::P_MIN).toDouble();
        double y_max
            = y_axis->getItemValue(BasicAxisItem::P_MAX).toDouble();

        result->addAxis("x", n_x, x_min, x_max);
        result->addAxis("y", n_y, y_min, y_max);

    }

    else {
        throw GUIHelpers::Error(
            "DetectorMaskDelegate::createOutputData() -> Error. "
            " Unknown detector type");
    }

    result->setAllTo(1.0);
//    (*result)[0] = 10;

//    const IAxis *axis0 = result->getAxis(0);
//    const IAxis *axis1 = result->getAxis(1);

//    for(int ix=0; ix<(int)axis0.size(); ix+=2) {
//        for(int iy=0; iy<(int)axis1.size(); iy+=2) {
//            std::vector<int> indices = {ix, iy};
//            int index = result->toGlobalIndex(indices);
//            (*result)[index] = 10;
//        }
//    }

    return result;
}
