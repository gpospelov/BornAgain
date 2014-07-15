#include "DetectorItems.h"
#include "GroupProperty.h"
#include "ComboProperty.h"
#include <QDebug>

const QString DetectorItem::P_DETECTOR_TYPE = "Detector type";
const QString DetectorItem::P_AXES_UNITS = "Units";
const QString DetectorItem::P_BINNING = "Binning";

const QString XYDetectorItem::P_MODEL_TYPE = "X, Y plane";

const QString ThetaPhiDetectorItem::P_MODEL_TYPE = "Theta, Phi plane";
const QString ThetaPhiDetectorItem::P_NPHI = "Phi, nbins";
const QString ThetaPhiDetectorItem::P_PHI_MIN = "Phi, min";
const QString ThetaPhiDetectorItem::P_PHI_MAX = "Phi, max";
const QString ThetaPhiDetectorItem::P_NALPHA = "Alpha, nbins";
const QString ThetaPhiDetectorItem::P_ALPHA_MIN = "Alpha, min";
const QString ThetaPhiDetectorItem::P_ALPHA_MAX = "Alpha, max";

DetectorItem::DetectorItem(ParameterizedItem *parent)
    : ParameterizedItem(Constants::DetectorType, parent)
{
    setItemName(Constants::DetectorType);
    registerGroupProperty(P_DETECTOR_TYPE, ThetaPhiDetectorItem::P_MODEL_TYPE);

//    registerProperty(P_NBINX, 100);
//    registerProperty(P_NBINY, 100);
}


XYDetectorItem::XYDetectorItem(ParameterizedItem *parent)
    : ParameterizedItem(QString(P_MODEL_TYPE), parent)
{
    setItemName("XYDetector");

    ComboProperty units;
    units << "Millimeters";
    registerProperty(DetectorItem::P_AXES_UNITS, units.getVariant());

    ComboProperty binning;
    binning << "Flat";
    registerProperty(DetectorItem::P_BINNING, binning.getVariant());

//    registerProperty(DetectorItem::P_XMIN, 0.0);
//    registerProperty(DetectorItem::P_XMAX, 0.0);

}


ThetaPhiDetectorItem::ThetaPhiDetectorItem(ParameterizedItem *parent)
    : ParameterizedItem(QString(P_MODEL_TYPE), parent)
{
    setItemName("ThetaPhiDetector");

    ComboProperty units;
    units << "Degrees" << "Radians";
    registerProperty(DetectorItem::P_AXES_UNITS, units.getVariant());

    ComboProperty binning;
    binning << "Flat" << "Flat in sin";
    registerProperty(DetectorItem::P_BINNING, binning.getVariant());

    registerProperty(P_NPHI, 100);
    registerProperty(P_PHI_MIN, -1.0);
    registerProperty(P_PHI_MAX,  1.0);
    registerProperty(P_NALPHA, 100);
    registerProperty(P_ALPHA_MIN, 0.0);
    registerProperty(P_ALPHA_MAX,  2.0);
}


void ThetaPhiDetectorItem::onPropertyChange(const QString &name)
{
//    if(name == DetectorItem::P_AXES_UNITS) {

//    }
//    qDebug() << "ThetaPhiDetectorItem::onPropertyChange() -> before emit";
    ParameterizedItem::onPropertyChange(name);
}

