// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/InterferenceFunctionItems.cpp
//! @brief     Implements InterferenceFunctionItems's classes
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "InterferenceFunctionItems.h"
#include "BornAgainNamespace.h"
#include "ParameterTranslators.h"
#include "ModelPath.h"
#include "Units.h"

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

const QString InterferenceFunction1DLatticeItem::P_LENGTH =
        QString::fromStdString(BornAgain::Length);
const QString InterferenceFunction1DLatticeItem::P_ROTATION_ANGLE =
        QString::fromStdString(BornAgain::Xi);
const QString InterferenceFunction1DLatticeItem::P_DECAY_FUNCTION = "Decay Function";

const QString InterferenceFunction2DLatticeItem::P_LATTICE_TYPE = "Lattice_type";
const QString InterferenceFunction2DLatticeItem::P_ROTATION_ANGLE =
        QString::fromStdString(BornAgain::Xi);
const QString InterferenceFunction2DLatticeItem::P_DECAY_FUNCTION = "Decay Function";


InterferenceFunctionRadialParaCrystalItem::InterferenceFunctionRadialParaCrystalItem(
        )
    : SessionGraphicsItem(Constants::InterferenceFunctionRadialParaCrystalType)
{
    addProperty(P_PEAK_DISTANCE, 20.0*Units::nanometer);
    addProperty(P_DAMPING_LENGTH, 1000.0*Units::micrometer);
    addProperty(P_DOMAIN_SIZE, 20.0*Units::micrometer);
    addProperty(P_KAPPA, 0.0);
    addGroupProperty(P_PDF, Constants::FTDistribution1DGroup);
}

InterferenceFunction2DParaCrystalItem::InterferenceFunction2DParaCrystalItem(
        )
    : SessionGraphicsItem(Constants::InterferenceFunction2DParaCrystalType)
{
    addGroupProperty(InterferenceFunction2DLatticeItem::P_LATTICE_TYPE,
                          Constants::LatticeGroup);
    addProperty(P_DAMPING_LENGTH, 0.0);
    addProperty(P_DOMAIN_SIZE1, 20.0*Units::micrometer);
    addProperty(P_DOMAIN_SIZE2, 20.0*Units::micrometer);
    addProperty(P_XI_INTEGRATION, true);
    addProperty(P_ROTATION_ANGLE, 0.0);
    getItem(P_ROTATION_ANGLE)->setEnabled(false);
    addGroupProperty(P_PDF1, Constants::FTDistribution2DGroup);
    addGroupProperty(P_PDF2, Constants::FTDistribution2DGroup);

    LatticeTypeTranslator lattice_translator;
    ModelPath::addParameterTranslator(lattice_translator);

    mapper()->setOnPropertyChange(
        [this](const QString &name) {
            if(name == P_XI_INTEGRATION && isTag(P_ROTATION_ANGLE)) {
                if(getItemValue(P_XI_INTEGRATION).toBool()) {
                    getItem(P_ROTATION_ANGLE)->setEnabled(false);
                } else {
                    getItem(P_ROTATION_ANGLE)->setEnabled(true);
                }
            }
    });
}

InterferenceFunction1DLatticeItem::InterferenceFunction1DLatticeItem()
    : SessionGraphicsItem(Constants::InterferenceFunction1DLatticeType)
{
    addProperty(P_LENGTH, 20.0*Units::nanometer);
    addProperty(P_ROTATION_ANGLE, 0.0);
    addGroupProperty(P_DECAY_FUNCTION, Constants::FTDecayFunction1DGroup);
}

InterferenceFunction2DLatticeItem::InterferenceFunction2DLatticeItem(
        )
    : SessionGraphicsItem(Constants::InterferenceFunction2DLatticeType)
{
    addGroupProperty(P_LATTICE_TYPE, Constants::LatticeGroup);
    addProperty(P_ROTATION_ANGLE, 0.0);
    addGroupProperty(P_DECAY_FUNCTION, Constants::FTDecayFunction2DGroup);
    LatticeTypeTranslator lattice_translator;
    ModelPath::addParameterTranslator(lattice_translator);
}
