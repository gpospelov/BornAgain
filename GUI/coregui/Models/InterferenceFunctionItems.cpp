// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/InterferenceFunctionItems.cpp
//! @brief     Implements InterferenceFunctionItems's classes
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "InterferenceFunctionItems.h"
#include "Units.h"
#include "BornAgainNamespace.h"

#include <QDebug>

const QString InterferenceFunctionRadialParaCrystalItem::P_PEAK_DISTANCE =
        QString::fromStdString(BornAgain::PeakDistance);
const QString InterferenceFunctionRadialParaCrystalItem::P_DAMPING_LENGTH =
        QString::fromStdString(BornAgain::DampingLength);
const QString InterferenceFunctionRadialParaCrystalItem::P_DOMAIN_SIZE =
        QString::fromStdString(BornAgain::DomainSize);
const QString InterferenceFunctionRadialParaCrystalItem::P_KAPPA =
        QString::fromStdString(BornAgain::SizeSpaceCoupling);
const QString InterferenceFunctionRadialParaCrystalItem::P_PDF = "PDF";

const QString InterferenceFunction2DParaCrystalItem::P_ROTATION_ANGLE =
        QString::fromStdString(BornAgain::Xi);
const QString InterferenceFunction2DParaCrystalItem::P_DAMPING_LENGTH =
        QString::fromStdString(BornAgain::DampingLength);
const QString InterferenceFunction2DParaCrystalItem::P_DOMAIN_SIZE1 =
        QString::fromStdString(BornAgain::DomainSize1);
const QString InterferenceFunction2DParaCrystalItem::P_DOMAIN_SIZE2 =
        QString::fromStdString(BornAgain::DomainSize2);
const QString InterferenceFunction2DParaCrystalItem::P_XI_INTEGRATION = "Integration_over_xi";
const QString InterferenceFunction2DParaCrystalItem::P_PDF1 = "PDF #1";
const QString InterferenceFunction2DParaCrystalItem::P_PDF2 = "PDF #2";

const QString InterferenceFunction2DLatticeItem::P_LATTICE_TYPE = "Lattice_type";
const QString InterferenceFunction2DLatticeItem::P_ROTATION_ANGLE =
        QString::fromStdString(BornAgain::Xi);
const QString InterferenceFunction2DLatticeItem::P_PDF = "PDF";

const QString InterferenceFunction1DLatticeItem::P_LENGTH =
        QString::fromStdString(BornAgain::Length);
const QString InterferenceFunction1DLatticeItem::P_ROTATION_ANGLE =
        QString::fromStdString(BornAgain::Xi);
const QString InterferenceFunction1DLatticeItem::P_PDF = "PDF";


InterferenceFunctionRadialParaCrystalItem::InterferenceFunctionRadialParaCrystalItem(
        ParameterizedItem *parent)
    : ParameterizedGraphicsItem(Constants::InterferenceFunctionRadialParaCrystalType, parent)
{
    registerProperty(P_PEAK_DISTANCE, 20.0*Units::nanometer);
    registerProperty(P_DAMPING_LENGTH, 1000.0*Units::micrometer);
    registerProperty(P_DOMAIN_SIZE, 20.0*Units::micrometer);
    registerProperty(P_KAPPA, 0.0);
    registerGroupProperty(P_PDF, Constants::FTDistribution1DGroup);
}

InterferenceFunction2DParaCrystalItem::InterferenceFunction2DParaCrystalItem(
        ParameterizedItem *parent)
    : ParameterizedGraphicsItem(Constants::InterferenceFunction2DParaCrystalType, parent)
{
    registerGroupProperty(InterferenceFunction2DLatticeItem::P_LATTICE_TYPE,
                          Constants::LatticeGroup);
    registerProperty(P_DAMPING_LENGTH, 0.0);
    registerProperty(P_DOMAIN_SIZE1, 20.0*Units::micrometer);
    registerProperty(P_DOMAIN_SIZE2, 20.0*Units::micrometer);
    registerProperty(P_XI_INTEGRATION, true);
    registerProperty(P_ROTATION_ANGLE, 0.0).setDisabled();
    registerGroupProperty(P_PDF1, Constants::FTDistribution2DGroup);
    registerGroupProperty(P_PDF2, Constants::FTDistribution2DGroup);
}

void InterferenceFunction2DParaCrystalItem::onPropertyChange(const QString &name)
{
    if(name == P_XI_INTEGRATION && isRegisteredProperty(P_ROTATION_ANGLE)) {
        if(getRegisteredProperty(P_XI_INTEGRATION).toBool()) {
            getPropertyAttribute(P_ROTATION_ANGLE).setDisabled();
        } else {
            getPropertyAttribute(P_ROTATION_ANGLE).setVisible();
        }
        ParameterizedItem::onPropertyChange(P_ROTATION_ANGLE);
    }
    ParameterizedItem::onPropertyChange(name);
}

InterferenceFunction1DLatticeItem::InterferenceFunction1DLatticeItem(ParameterizedItem *parent)
    : ParameterizedGraphicsItem(Constants::InterferenceFunction1DLatticeType, parent)
{
    registerProperty(P_LENGTH, 20.0*Units::nanometer);
    registerProperty(P_ROTATION_ANGLE, 0.0);
    registerGroupProperty(P_PDF, Constants::FTDistribution1DGroup);
}

InterferenceFunction2DLatticeItem::InterferenceFunction2DLatticeItem(
        ParameterizedItem *parent)
    : ParameterizedGraphicsItem(Constants::InterferenceFunction2DLatticeType, parent)
{
    registerGroupProperty(P_LATTICE_TYPE, Constants::LatticeGroup);
    registerProperty(P_ROTATION_ANGLE, 0.0);
    registerGroupProperty(P_PDF, Constants::FTDistribution2DGroup);
}
