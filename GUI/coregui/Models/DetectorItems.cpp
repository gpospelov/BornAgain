#include "DetectorItems.h"
#include "ComboProperty.h"
#include "AngleProperty.h"
#include <QDebug>

const QString DetectorItem::P_DETECTOR = "Detector";

DetectorItem::DetectorItem(ParameterizedItem *parent)
    : ParameterizedItem(Constants::DetectorType, parent)
{
    setItemName(Constants::DetectorType);
    registerGroupProperty(P_DETECTOR, Constants::DetectorGroup);
}


const QString PhiAlphaDetectorItem::P_AXES_UNITS = "Axes Units";
const QString PhiAlphaDetectorItem::P_BINNING = "Binning";
const QString PhiAlphaDetectorItem::P_NPHI = "Phi, nbins";
const QString PhiAlphaDetectorItem::P_PHI_MIN = "Phi, min";
const QString PhiAlphaDetectorItem::P_PHI_MAX = "Phi, max";
const QString PhiAlphaDetectorItem::P_NALPHA = "Alpha, nbins";
const QString PhiAlphaDetectorItem::P_ALPHA_MIN = "Alpha, min";
const QString PhiAlphaDetectorItem::P_ALPHA_MAX = "Alpha, max";

PhiAlphaDetectorItem::PhiAlphaDetectorItem(ParameterizedItem *parent)
    : ParameterizedItem(Constants::PhiAlphaDetectorType, parent)
{
    setItemName(Constants::PhiAlphaDetectorType);

    ComboProperty binning;
    binning << "Const KBin" << "Fixed";
    registerProperty(P_BINNING, binning.getVariant());

    registerProperty(P_NPHI, 100);
    registerProperty(P_PHI_MIN, AngleProperty::Degrees(-1.0));
    registerProperty(P_PHI_MAX,  AngleProperty::Degrees(1.0));
    registerProperty(P_NALPHA, 100);
    registerProperty(P_ALPHA_MIN, AngleProperty::Degrees(0.0));
    registerProperty(P_ALPHA_MAX,  AngleProperty::Degrees(2.0));

    registerProperty(P_AXES_UNITS, AngleProperty::Degrees());
}


void PhiAlphaDetectorItem::onPropertyChange(const QString &name)
{

    if(name == P_AXES_UNITS) {
        qDebug() << "PhiAlphaDetectorItem::onPropertyChange()" << name;
        AngleProperty axes_units = getRegisteredProperty(P_AXES_UNITS).value<AngleProperty>();

        AngleProperty phi_min_property = getRegisteredProperty(PhiAlphaDetectorItem::P_PHI_MIN).value<AngleProperty>();
        phi_min_property.setUnits(axes_units.getUnits());
        setRegisteredProperty(P_PHI_MIN, phi_min_property.getVariant());

        AngleProperty phi_max_property = getRegisteredProperty(PhiAlphaDetectorItem::P_PHI_MAX).value<AngleProperty>();
        phi_max_property.setUnits(axes_units.getUnits());
        setRegisteredProperty(P_PHI_MAX, phi_max_property.getVariant());

        AngleProperty alpha_min_property = getRegisteredProperty(PhiAlphaDetectorItem::P_ALPHA_MIN).value<AngleProperty>();
        alpha_min_property.setUnits(axes_units.getUnits());
        setRegisteredProperty(P_ALPHA_MIN, alpha_min_property.getVariant());

        AngleProperty alpha_max_property = getRegisteredProperty(PhiAlphaDetectorItem::P_ALPHA_MAX).value<AngleProperty>();
        alpha_max_property.setUnits(axes_units.getUnits());
        setRegisteredProperty(P_ALPHA_MAX, alpha_max_property.getVariant());

    }
    ParameterizedItem::onPropertyChange(name);
}

