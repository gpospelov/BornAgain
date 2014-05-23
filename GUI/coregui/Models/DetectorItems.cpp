#include "DetectorItems.h"
#include "GroupProperty.h"
#include "ComboProperty.h"
#include <QDebug>

const QString DetectorItem::P_DETECTOR_TYPE = "Detector type";
const QString DetectorItem::P_AXES_UNITS = "Units";
const QString DetectorItem::P_BINNING = "Binning";

const QString XYDetectorItem::P_MODEL_TYPE = "X, Y plane";
const QString ThetaPhiDetectorItem::P_MODEL_TYPE = "Theta, Phi plane";

DetectorItem::DetectorItem(ParameterizedItem *parent)
    : ParameterizedItem(QString("Detector"), parent)
{
    setItemName("Detector");
    registerGroupProperty(P_DETECTOR_TYPE, ThetaPhiDetectorItem::P_MODEL_TYPE);
}


XYDetectorItem::XYDetectorItem(ParameterizedItem *parent)
    : ParameterizedItem(QString(P_MODEL_TYPE), parent)
{
    setItemName("XYDetector");

    ComboProperty units;
    units << "millimeters";
    registerProperty(DetectorItem::P_AXES_UNITS, units.getVariant());

}


ThetaPhiDetectorItem::ThetaPhiDetectorItem(ParameterizedItem *parent)
    : ParameterizedItem(QString(P_MODEL_TYPE), parent)
{
    setItemName("ThetaPhiDetector");

    ComboProperty units;
    units << "degrees" << "radians";
    registerProperty(DetectorItem::P_AXES_UNITS, units.getVariant());
}
