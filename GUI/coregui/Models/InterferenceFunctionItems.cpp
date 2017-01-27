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
#include "Lattice2DItems.h"
#include "ModelPath.h"
#include "GUIHelpers.h"
#include "Units.h"
#include "FTDecayFunctionItems.h"
#include "FTDecayFunctions.h"
#include "FTDistributionItems.h"
#include "FTDistributions2D.h"
#include "InterferenceFunction2DLattice.h"
#include "InterferenceFunction2DParaCrystal.h"
#include "InterferenceFunctionRadialParaCrystal.h"
#include "InterferenceFunction1DLattice.h"

InterferenceFunctionItem::InterferenceFunctionItem(const QString& modelType)
    : SessionGraphicsItem(modelType)
{

}

InterferenceFunctionItem::~InterferenceFunctionItem(){}

// --------------------------------------------------------------------------------------------- //

const QString InterferenceFunctionRadialParaCrystalItem::P_PEAK_DISTANCE =
        QString::fromStdString(BornAgain::PeakDistance);
const QString InterferenceFunctionRadialParaCrystalItem::P_DAMPING_LENGTH =
        QString::fromStdString(BornAgain::DampingLength);
const QString InterferenceFunctionRadialParaCrystalItem::P_DOMAIN_SIZE =
        QString::fromStdString(BornAgain::DomainSize);
const QString InterferenceFunctionRadialParaCrystalItem::P_KAPPA =
        QString::fromStdString(BornAgain::SizeSpaceCoupling);
const QString InterferenceFunctionRadialParaCrystalItem::P_PDF = "PDF";

InterferenceFunctionRadialParaCrystalItem::InterferenceFunctionRadialParaCrystalItem()
    : InterferenceFunctionItem(Constants::InterferenceFunctionRadialParaCrystalType)
{
    addProperty(P_PEAK_DISTANCE, 20.0*Units::nanometer);
    addProperty(P_DAMPING_LENGTH, 1000.0*Units::micrometer);
    addProperty(P_DOMAIN_SIZE, 20.0*Units::micrometer);
    addProperty(P_KAPPA, 0.0);
    addGroupProperty(P_PDF, Constants::FTDistribution1DGroup);
}

std::unique_ptr<IInterferenceFunction>
InterferenceFunctionRadialParaCrystalItem::createInterferenceFunction() const
{
    auto result = GUIHelpers::make_unique<InterferenceFunctionRadialParaCrystal>(
        getItemValue(P_PEAK_DISTANCE).toDouble(), getItemValue(P_DAMPING_LENGTH).toDouble());
    result->setDomainSize(getItemValue(P_DOMAIN_SIZE).toDouble());
    result->setKappa(getItemValue(P_KAPPA).toDouble());

    auto pdfItem = dynamic_cast<FTDistribution1DItem*>(getGroupItem(P_PDF));
    std::unique_ptr<IFTDistribution1D> P_pdf(pdfItem->createFTDistribution());
    result->setProbabilityDistribution(*P_pdf);
    return std::move(result);
}

// --------------------------------------------------------------------------------------------- //

const QString InterferenceFunction2DParaCrystalItem::P_DAMPING_LENGTH =
        QString::fromStdString(BornAgain::DampingLength);
const QString InterferenceFunction2DParaCrystalItem::P_DOMAIN_SIZE1 =
        QString::fromStdString(BornAgain::DomainSize1);
const QString InterferenceFunction2DParaCrystalItem::P_DOMAIN_SIZE2 =
        QString::fromStdString(BornAgain::DomainSize2);
const QString InterferenceFunction2DParaCrystalItem::P_XI_INTEGRATION = "Integration_over_xi";
const QString InterferenceFunction2DParaCrystalItem::P_PDF1 = "PDF #1";
const QString InterferenceFunction2DParaCrystalItem::P_PDF2 = "PDF #2";

InterferenceFunction2DParaCrystalItem::InterferenceFunction2DParaCrystalItem()
    : InterferenceFunctionItem(Constants::InterferenceFunction2DParaCrystalType)
{
    addGroupProperty(InterferenceFunction2DLatticeItem::P_LATTICE_TYPE, Constants::LatticeGroup);
    getGroupItem(InterferenceFunction2DLatticeItem::P_LATTICE_TYPE)
        ->getItem(Lattice2DItem::P_LATTICE_ROTATION_ANGLE)->setEnabled(false);
    addProperty(P_XI_INTEGRATION, true);

    addProperty(P_DAMPING_LENGTH, 0.0);
    addProperty(P_DOMAIN_SIZE1, 20.0 * Units::micrometer);
    addProperty(P_DOMAIN_SIZE2, 20.0 * Units::micrometer);
    addGroupProperty(P_PDF1, Constants::FTDistribution2DGroup);
    addGroupProperty(P_PDF2, Constants::FTDistribution2DGroup);

    mapper()->setOnPropertyChange([this](const QString& name) {
        if (name == P_XI_INTEGRATION && isTag(InterferenceFunction2DLatticeItem::P_LATTICE_TYPE)) {
            update_rotation_availability();
        }
    });

    mapper()->setOnChildPropertyChange([this](SessionItem* item, const QString&) {
        if (item->modelType() == Constants::GroupItemType) {
            update_rotation_availability();
        }
    });
}

std::unique_ptr<IInterferenceFunction>
InterferenceFunction2DParaCrystalItem::createInterferenceFunction() const
{
    auto latticeItem = dynamic_cast<Lattice2DItem*>(
        getGroupItem(InterferenceFunction2DLatticeItem::P_LATTICE_TYPE));

    std::unique_ptr<InterferenceFunction2DParaCrystal> result(
        new InterferenceFunction2DParaCrystal(*latticeItem->createLattice()));

    result->setDampingLength(getItemValue(P_DAMPING_LENGTH).toDouble());
    result->setDomainSizes(getItemValue(P_DOMAIN_SIZE1).toDouble(),
                           getItemValue(P_DOMAIN_SIZE2).toDouble());
    result->setIntegrationOverXi(getItemValue(P_XI_INTEGRATION).toBool());

    auto pdf1Item = dynamic_cast<FTDistribution2DItem*>(
        getGroupItem(InterferenceFunction2DParaCrystalItem::P_PDF1));
    auto pdf2Item = dynamic_cast<FTDistribution2DItem*>(
        getGroupItem(InterferenceFunction2DParaCrystalItem::P_PDF2));
    result->setProbabilityDistributions(*pdf1Item->createFTDistribution(),
                                        *pdf2Item->createFTDistribution());

    return std::move(result);
}

//! Sets rotation property of the lattice enabled/disabled depending on integration flag.

void InterferenceFunction2DParaCrystalItem::update_rotation_availability()
{
    SessionItem *angleItem = getGroupItem(InterferenceFunction2DLatticeItem::P_LATTICE_TYPE)
            ->getItem(Lattice2DItem::P_LATTICE_ROTATION_ANGLE);

    angleItem->setEnabled(!getItemValue(P_XI_INTEGRATION).toBool());
}

// --------------------------------------------------------------------------------------------- //

const QString InterferenceFunction1DLatticeItem::P_LENGTH =
        QString::fromStdString(BornAgain::Length);
const QString InterferenceFunction1DLatticeItem::P_ROTATION_ANGLE =
        QString::fromStdString(BornAgain::Xi);
const QString InterferenceFunction1DLatticeItem::P_DECAY_FUNCTION = "Decay Function";

InterferenceFunction1DLatticeItem::InterferenceFunction1DLatticeItem()
    : InterferenceFunctionItem(Constants::InterferenceFunction1DLatticeType)
{
    addProperty(P_LENGTH, 20.0 * Units::nanometer);
    addProperty(P_ROTATION_ANGLE, 0.0);
    addGroupProperty(P_DECAY_FUNCTION, Constants::FTDecayFunction1DGroup);
}

std::unique_ptr<IInterferenceFunction>
InterferenceFunction1DLatticeItem::createInterferenceFunction() const
{
    auto result = GUIHelpers::make_unique<InterferenceFunction1DLattice>(
        getItemValue(P_LENGTH).toDouble(),
        Units::deg2rad(getItemValue(P_ROTATION_ANGLE).toDouble()));
    auto pdfItem = dynamic_cast<FTDecayFunction1DItem*>(
        getGroupItem(InterferenceFunction1DLatticeItem::P_DECAY_FUNCTION));
    result->setDecayFunction(*pdfItem->createFTDecayFunction());
    return std::move(result);
}

// --------------------------------------------------------------------------------------------- //

const QString InterferenceFunction2DLatticeItem::P_LATTICE_TYPE = "LatticeType";
const QString InterferenceFunction2DLatticeItem::P_DECAY_FUNCTION = "DecayFunction";

InterferenceFunction2DLatticeItem::InterferenceFunction2DLatticeItem()
    : InterferenceFunctionItem(Constants::InterferenceFunction2DLatticeType)
{
    addGroupProperty(P_LATTICE_TYPE, Constants::LatticeGroup);
    addGroupProperty(P_DECAY_FUNCTION, Constants::FTDecayFunction2DGroup);
}

std::unique_ptr<IInterferenceFunction>
InterferenceFunction2DLatticeItem::createInterferenceFunction() const
{
    auto latticeItem = dynamic_cast<Lattice2DItem*>(getGroupItem(P_LATTICE_TYPE));
    std::unique_ptr<InterferenceFunction2DLattice> result(
        new InterferenceFunction2DLattice(*latticeItem->createLattice()));

    auto pdfItem = dynamic_cast<FTDecayFunction2DItem*>(getGroupItem(P_DECAY_FUNCTION));
    result->setDecayFunction(*pdfItem->createFTDecayFunction());

    return std::move(result);
}
