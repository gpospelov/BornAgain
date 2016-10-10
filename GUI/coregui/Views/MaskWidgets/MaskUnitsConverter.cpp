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
#include "IntensityDataFunctions.h"
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
    if(maskItem->modelType() == Constants::RectangleMaskType ||
            maskItem->modelType() == Constants::RegionOfInterestType) {
        convertToBinf(maskItem, RectangleItem::P_XLOW, RectangleItem::P_YLOW, data);
        convertToBinf(maskItem, RectangleItem::P_XUP, RectangleItem::P_YUP, data);
    }

    else if(maskItem->modelType() == Constants::PolygonMaskType) {
        foreach (SessionItem *pointItem, maskItem->getChildrenOfType(Constants::PolygonPointType))
            convertToBinf(pointItem, PolygonPointItem::P_POSX, PolygonPointItem::P_POSY, data);
    }

    else if(maskItem->modelType() == Constants::VerticalLineMaskType) {
        convertToBinf(maskItem, VerticalLineItem::P_POSX, QString(), data);

    }

    else if(maskItem->modelType() == Constants::HorizontalLineMaskType) {
        convertToBinf(maskItem, QString(), HorizontalLineItem::P_POSY, data);

    }

    else if(maskItem->modelType() == Constants::EllipseMaskType) {
        double xc = maskItem->getItemValue(EllipseItem::P_XCENTER).toDouble();
        double yc = maskItem->getItemValue(EllipseItem::P_YCENTER).toDouble();
        double xR = maskItem->getItemValue(EllipseItem::P_XRADIUS).toDouble();
        double yR = maskItem->getItemValue(EllipseItem::P_YRADIUS).toDouble();

        double x2 = xc + xR;
        double y2 = yc + yR;

        IntensityDataFunctions::coordinateToBinf(xc, yc, data);
        IntensityDataFunctions::coordinateToBinf(x2, y2, data);

        maskItem->setItemValue(EllipseItem::P_XCENTER, xc);
        maskItem->setItemValue(EllipseItem::P_YCENTER, yc);
        maskItem->setItemValue(EllipseItem::P_XRADIUS, x2 - xc);
        maskItem->setItemValue(EllipseItem::P_YRADIUS, y2 - yc);

//        convertToBinf(maskItem, EllipseItem::P_XCENTER, EllipseItem::P_YCENTER, data);
//        convertToBinf(maskItem, EllipseItem::P_XRADIUS, EllipseItem::P_YRADIUS, data);
    }

}

void MaskUnitsConverter::convertMaskFromNbins(SessionItem *maskItem, const OutputData<double> *data)
{
    if(maskItem->modelType() == Constants::RectangleMaskType ||
            maskItem->modelType() == Constants::RegionOfInterestType) {
        convertFromBinf(maskItem, RectangleItem::P_XLOW, RectangleItem::P_YLOW, data);
        convertFromBinf(maskItem, RectangleItem::P_XUP, RectangleItem::P_YUP, data);
    }

    else if(maskItem->modelType() == Constants::PolygonMaskType) {
        foreach (SessionItem *pointItem, maskItem->getChildrenOfType(Constants::PolygonPointType))
            convertFromBinf(pointItem, PolygonPointItem::P_POSX, PolygonPointItem::P_POSY, data);
    }

    else if(maskItem->modelType() == Constants::VerticalLineMaskType) {
        convertFromBinf(maskItem, VerticalLineItem::P_POSX, QString(), data);

    }

    else if(maskItem->modelType() == Constants::HorizontalLineMaskType) {
        convertFromBinf(maskItem, QString(), HorizontalLineItem::P_POSY, data);

    }

    else if(maskItem->modelType() == Constants::EllipseMaskType) {
        double xc = maskItem->getItemValue(EllipseItem::P_XCENTER).toDouble();
        double yc = maskItem->getItemValue(EllipseItem::P_YCENTER).toDouble();
        double xR = maskItem->getItemValue(EllipseItem::P_XRADIUS).toDouble();
        double yR = maskItem->getItemValue(EllipseItem::P_YRADIUS).toDouble();

        double x2 = xc + xR;
        double y2 = yc + yR;

        IntensityDataFunctions::coordinateFromBinf(xc, yc, data);
        IntensityDataFunctions::coordinateFromBinf(x2, y2, data);

        maskItem->setItemValue(EllipseItem::P_XCENTER, xc);
        maskItem->setItemValue(EllipseItem::P_YCENTER, yc);
        maskItem->setItemValue(EllipseItem::P_XRADIUS, x2 - xc);
        maskItem->setItemValue(EllipseItem::P_YRADIUS, y2 - yc);



//        convertFromBinf(maskItem, EllipseItem::P_XCENTER, EllipseItem::P_YCENTER, data);
//        convertFromBinf(maskItem, EllipseItem::P_XRADIUS, EllipseItem::P_YRADIUS, data);
    }



}

void MaskUnitsConverter::convertToBinf(SessionItem *maskItem, const QString &xname,
                                       const QString &yname, const OutputData<double> *data)
{
    if(maskItem->isTag(xname)) {
        double x = maskItem->getItemValue(xname).toDouble();
        x = IntensityDataFunctions::coordinateToBinf(x, data->getAxis(BornAgain::X_AXIS_INDEX));
        maskItem->setItemValue(xname, x);
    }

    if(maskItem->isTag(yname)) {
        double y = maskItem->getItemValue(yname).toDouble();
        y = IntensityDataFunctions::coordinateToBinf(y, data->getAxis(BornAgain::Y_AXIS_INDEX));
        maskItem->setItemValue(yname, y);
    }
}

void MaskUnitsConverter::convertFromBinf(SessionItem *maskItem, const QString &xname,
                                         const QString &yname, const OutputData<double> *data)
{
    if(maskItem->isTag(xname)) {
        double x = maskItem->getItemValue(xname).toDouble();
        x = IntensityDataFunctions::coordinateFromBinf(x, data->getAxis(BornAgain::X_AXIS_INDEX));
        maskItem->setItemValue(xname, x);
    }

    if(maskItem->isTag(yname)) {
        double y = maskItem->getItemValue(yname).toDouble();
        y = IntensityDataFunctions::coordinateFromBinf(y, data->getAxis(BornAgain::Y_AXIS_INDEX));
        maskItem->setItemValue(yname, y);
    }


//    double x = maskItem->getItemValue(xname).toDouble();
//    double y = maskItem->getItemValue(yname).toDouble();
//    IntensityDataFunctions::coordinateFromBinf(x, y, data);
//    maskItem->setItemValue(xname, x);
//    maskItem->setItemValue(yname, y);
}
