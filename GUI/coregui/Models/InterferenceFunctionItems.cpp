#include "InterferenceFunctionItems.h"
#include "Units.h"
#include <QDebug>

const QString InterferenceFunctionRadialParaCrystalItem::P_PEAK_DISTANCE =
        "Peak_distance";
const QString InterferenceFunctionRadialParaCrystalItem::P_DAMPING_LENGTH =
        "Damping_length";
const QString InterferenceFunctionRadialParaCrystalItem::P_DOMAIN_SIZE =
        "Domain_size";
const QString InterferenceFunctionRadialParaCrystalItem::P_KAPPA =
        "Size_space_coupling";
const QString InterferenceFunctionRadialParaCrystalItem::P_PDF = "PDF";

const QString InterferenceFunction2DParaCrystalItem::P_LATTICE_TYPE =
        "Lattice_type";
const QString InterferenceFunction2DParaCrystalItem::P_ROTATION_ANGLE =
        "Rotation_angle";
const QString InterferenceFunction2DParaCrystalItem::P_DAMPING_LENGTH =
        "Damping_length";
const QString InterferenceFunction2DParaCrystalItem::P_DOMAIN_SIZE1 =
        "Domain_size_1";
const QString InterferenceFunction2DParaCrystalItem::P_DOMAIN_SIZE2 =
        "Domain_size_2";
const QString InterferenceFunction2DParaCrystalItem::P_XI_INTEGRATION =
        "Integration_over_xi";
const QString InterferenceFunction2DParaCrystalItem::P_PDF1 = "PDF #1";
const QString InterferenceFunction2DParaCrystalItem::P_PDF2 = "PDF #2";

const QString InterferenceFunction2DLatticeItem::P_LATTICE_TYPE =
        "Lattice_type";
const QString InterferenceFunction2DLatticeItem::P_ROTATION_ANGLE =
        "Rotation_angle";
const QString InterferenceFunction2DLatticeItem::P_PDF = "PDF";

InterferenceFunctionRadialParaCrystalItem::InterferenceFunctionRadialParaCrystalItem(
        ParameterizedItem *parent)
    : ParameterizedGraphicsItem(Constants::InterferenceFunctionRadialParaCrystalType,
                                parent)
{
    setItemName(Constants::InterferenceFunctionRadialParaCrystalType);
    setItemPort(ParameterizedItem::PortInfo::PORT_1);
    registerProperty(P_PEAK_DISTANCE, 20.0*Units::nanometer);
    registerProperty(P_DAMPING_LENGTH, 1000.0*Units::micrometer);
    registerProperty(P_DOMAIN_SIZE, 20.0*Units::micrometer);
    registerProperty(P_KAPPA, 0.0);
    registerGroupProperty(P_PDF, Constants::FTDistribution1DGroup);
}


InterferenceFunction2DParaCrystalItem::InterferenceFunction2DParaCrystalItem(
        ParameterizedItem *parent)
    : ParameterizedGraphicsItem(Constants::InterferenceFunction2DParaCrystalType,
                                parent)
{
    setItemName(Constants::InterferenceFunction2DParaCrystalType);
    setItemPort(ParameterizedItem::PortInfo::PORT_1);
    registerGroupProperty(P_LATTICE_TYPE, Constants::LatticeGroup);

    registerProperty(P_DAMPING_LENGTH, 0.0);
    registerProperty(P_DOMAIN_SIZE1, 20.0*Units::micrometer);
    registerProperty(P_DOMAIN_SIZE2, 20.0*Units::micrometer);
    registerProperty(P_XI_INTEGRATION, true);
    registerProperty(P_ROTATION_ANGLE, 0.0, PropertyAttribute(PropertyAttribute::DISABLED));
    registerGroupProperty(P_PDF1, Constants::FTDistribution2DGroup);
    registerGroupProperty(P_PDF2, Constants::FTDistribution2DGroup);
}

void InterferenceFunction2DParaCrystalItem::onPropertyChange(const QString &name)
{
    if(name == P_XI_INTEGRATION && isRegisteredProperty(P_ROTATION_ANGLE)) {
        if(getRegisteredProperty(P_XI_INTEGRATION).toBool()) {
            setPropertyAppearance(P_ROTATION_ANGLE, PropertyAttribute::DISABLED);
        } else {
            setPropertyAppearance(P_ROTATION_ANGLE, PropertyAttribute::VISIBLE);
        }
        ParameterizedItem::onPropertyChange(P_ROTATION_ANGLE);
    }
    ParameterizedItem::onPropertyChange(name);

}


InterferenceFunction2DLatticeItem::InterferenceFunction2DLatticeItem(
        ParameterizedItem *parent)
    : ParameterizedGraphicsItem(Constants::InterferenceFunction2DLatticeType,
                                parent)
{
    setItemName(Constants::InterferenceFunction2DLatticeType);
    setItemPort(ParameterizedItem::PortInfo::PORT_1);
    registerGroupProperty(P_LATTICE_TYPE, Constants::LatticeGroup);

    registerProperty(P_ROTATION_ANGLE, 0.0);
    registerGroupProperty(P_PDF, Constants::FTDistribution2DGroup);
}
