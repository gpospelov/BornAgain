// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaskWidgets/MaskUnitsConverter.cpp
//! @brief     Implements class MaskUnitsConverter
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "MaskUnitsConverter.h"
#include "IntensityDataItem.h"
#include "MaskItems.h"
#include "BornAgainNamespace.h"
#include <QDebug>

void MaskUnitsConverter::convertToNbins(IntensityDataItem *intensityData)
{
    if(!intensityData || !intensityData->getOutputData() || !intensityData->maskContainerItem())
        return;

    foreach(SessionItem *maskItem, intensityData->maskContainerItem()->getItems())
        convertMaskToNbins(maskItem, intensityData->getOutputData());
}

void MaskUnitsConverter::convertFromNbins(IntensityDataItem *intensityData)
{
    if(!intensityData || !intensityData->getOutputData() || !intensityData->maskContainerItem())
        return;

    foreach(SessionItem *maskItem, intensityData->maskContainerItem()->getItems())
        convertMaskFromNbins(maskItem, intensityData->getOutputData());

}

void MaskUnitsConverter::convertMaskToNbins(SessionItem *maskItem, const OutputData<double> *data)
{
    qDebug() << "TTT" << maskItem->modelType();

    if(maskItem->modelType() == Constants::RectangleMaskType) {
        double x = maskItem->getItemValue(RectangleItem::P_XLOW).toDouble();
        double y = maskItem->getItemValue(RectangleItem::P_YLOW).toDouble();

        pointToBins(x, y, data);
        maskItem->setItemValue(RectangleItem::P_XLOW, x);
        maskItem->setItemValue(RectangleItem::P_YLOW, y);

        x = maskItem->getItemValue(RectangleItem::P_XUP).toDouble();
        y = maskItem->getItemValue(RectangleItem::P_YUP).toDouble();
        pointToBins(x, y, data);
        maskItem->setItemValue(RectangleItem::P_XUP, x);
        maskItem->setItemValue(RectangleItem::P_YUP, y);
    }
}

void MaskUnitsConverter::convertMaskFromNbins(SessionItem *maskItem, const OutputData<double> *data)
{
    if(maskItem->modelType() == Constants::RectangleMaskType) {
        double x = maskItem->getItemValue(RectangleItem::P_XLOW).toDouble();
        double y = maskItem->getItemValue(RectangleItem::P_YLOW).toDouble();

        pointFromBins(x, y, data);
        maskItem->setItemValue(RectangleItem::P_XLOW, x);
        maskItem->setItemValue(RectangleItem::P_YLOW, y);

        x = maskItem->getItemValue(RectangleItem::P_XUP).toDouble();
        y = maskItem->getItemValue(RectangleItem::P_YUP).toDouble();
        pointFromBins(x, y, data);
        maskItem->setItemValue(RectangleItem::P_XUP, x);
        maskItem->setItemValue(RectangleItem::P_YUP, y);
    }

}

void MaskUnitsConverter::pointToBins(double &x, double &y, const OutputData<double> *data)
{
    x = pointToBins(x, data->getAxis(BornAgain::X_AXIS_INDEX));
    y = pointToBins(y, data->getAxis(BornAgain::Y_AXIS_INDEX));
}

void MaskUnitsConverter::pointFromBins(double &x, double &y, const OutputData<double> *data)
{
    x = pointFromBins(x, data->getAxis(BornAgain::X_AXIS_INDEX));
    y = pointFromBins(y, data->getAxis(BornAgain::Y_AXIS_INDEX));

}

double MaskUnitsConverter::pointToBins(double value, const IAxis *axis)
{
    int index = axis->findClosestIndex(value);

    Bin1D bin = axis->getBin(index);

    double f = (value - bin.m_lower)/bin.getBinSize();

    return double(index) + f;
}

double MaskUnitsConverter::pointFromBins(double value, const IAxis *axis)
{
    int index = static_cast<int>(value);
    Bin1D bin = axis->getBin(index);

    double f = value - static_cast<double>(index);

    return bin.m_lower + f*bin.getBinSize();
}


