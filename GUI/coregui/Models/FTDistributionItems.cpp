// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/FTDistributionItems.cpp
//! @brief     Implements FTDistribution1DItem's classes
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "FTDistributionItems.h"
#include "Units.h"
#include "BornAgainNamespace.h"
#include "GUIHelpers.h"

const QString FTDistribution1DItem::P_CORR_LENGTH = "Corr_length";

FTDistribution1DItem::FTDistribution1DItem(const QString& name)
    : SessionItem(name)
{

}

// --------------------------------------------------------------------------------------------- //

FTDistribution1DCauchyItem::FTDistribution1DCauchyItem()
    : FTDistribution1DItem(Constants::FTDistribution1DCauchyType)
{
    addProperty(P_CORR_LENGTH, 1.0);
}

std::unique_ptr<IFTDistribution1D> FTDistribution1DCauchyItem::createFTDistribution() const
{
    return GUIHelpers::make_unique<FTDistribution1DCauchy>(getItemValue(P_CORR_LENGTH).toDouble());
}

// --------------------------------------------------------------------------------------------- //

FTDistribution1DGaussItem::FTDistribution1DGaussItem()
    : FTDistribution1DItem(Constants::FTDistribution1DGaussType)
{
    addProperty(P_CORR_LENGTH, 1.0);
}

std::unique_ptr<IFTDistribution1D> FTDistribution1DGaussItem::createFTDistribution() const
{
    return GUIHelpers::make_unique<FTDistribution1DGauss>(getItemValue(P_CORR_LENGTH).toDouble());
}

// --------------------------------------------------------------------------------------------- //

FTDistribution1DGateItem::FTDistribution1DGateItem()
    : FTDistribution1DItem(Constants::FTDistribution1DGateType)
{
    addProperty(P_CORR_LENGTH, 1.0);
}

std::unique_ptr<IFTDistribution1D> FTDistribution1DGateItem::createFTDistribution() const
{
    return GUIHelpers::make_unique<FTDistribution1DGate>(getItemValue(P_CORR_LENGTH).toDouble());
}

// --------------------------------------------------------------------------------------------- //

FTDistribution1DTriangleItem::FTDistribution1DTriangleItem()
    : FTDistribution1DItem(Constants::FTDistribution1DTriangleType)
{
    addProperty(P_CORR_LENGTH, 1.0);
}

std::unique_ptr<IFTDistribution1D> FTDistribution1DTriangleItem::createFTDistribution() const
{
    return GUIHelpers::make_unique<FTDistribution1DTriangle>(
                getItemValue(P_CORR_LENGTH).toDouble());
}

// --------------------------------------------------------------------------------------------- //

FTDistribution1DCosineItem::FTDistribution1DCosineItem()
    : FTDistribution1DItem(Constants::FTDistribution1DCosineType)
{
    addProperty(P_CORR_LENGTH, 1.0);
}

std::unique_ptr<IFTDistribution1D> FTDistribution1DCosineItem::createFTDistribution() const
{
    return GUIHelpers::make_unique<FTDistribution1DCosine>(getItemValue(P_CORR_LENGTH).toDouble());
}

// --------------------------------------------------------------------------------------------- //

const QString FTDistribution1DVoigtItem::P_ETA = "Eta";

FTDistribution1DVoigtItem::FTDistribution1DVoigtItem()
    : FTDistribution1DItem(Constants::FTDistribution1DVoigtType)
{
    addProperty(P_CORR_LENGTH, 1.0);
    addProperty(P_ETA, 0.5)->setLimits(RealLimits::limited(0.0, 1.0));
}

std::unique_ptr<IFTDistribution1D> FTDistribution1DVoigtItem::createFTDistribution() const
{
    return GUIHelpers::make_unique<FTDistribution1DVoigt>(getItemValue(P_CORR_LENGTH).toDouble(),
                                                          getItemValue(P_ETA).toDouble());
}

// --------------------------------------------------------------------------------------------- //

const QString FTDistribution2DItem::P_COHER_LENGTH_X =
        QString::fromStdString(BornAgain::CoherenceLengthX);
const QString FTDistribution2DItem::P_COHER_LENGTH_Y =
    QString::fromStdString(BornAgain::CoherenceLengthY);
const QString FTDistribution2DItem::P_GAMMA =
        QString::fromStdString(BornAgain::Gamma);

FTDistribution2DItem::FTDistribution2DItem(const QString& name)
    : SessionItem(name) {
    addProperty(P_GAMMA, 0.0);
}

// --------------------------------------------------------------------------------------------- //

FTDistribution2DCauchyItem::FTDistribution2DCauchyItem()
    : FTDistribution2DItem(Constants::FTDistribution2DCauchyType)
{
    addProperty(P_COHER_LENGTH_X, 1.0);
    addProperty(P_COHER_LENGTH_Y, 1.0);
}

std::unique_ptr<IFTDistribution2D> FTDistribution2DCauchyItem::createFTDistribution() const
{
    auto result = GUIHelpers::make_unique<FTDistribution2DCauchy>(
                getItemValue(P_COHER_LENGTH_X).toDouble(),
                getItemValue(P_COHER_LENGTH_Y).toDouble()
                );
    result->setGamma(Units::deg2rad(getItemValue(P_GAMMA).toDouble()));
    return std::move(result);
}

// --------------------------------------------------------------------------------------------- //

FTDistribution2DGaussItem::FTDistribution2DGaussItem()
    : FTDistribution2DItem(Constants::FTDistribution2DGaussType)
{
    addProperty(P_COHER_LENGTH_X, 1.0);
    addProperty(P_COHER_LENGTH_Y, 1.0);
}

std::unique_ptr<IFTDistribution2D> FTDistribution2DGaussItem::createFTDistribution() const
{
    auto result = GUIHelpers::make_unique<FTDistribution2DGauss>(
        getItemValue(P_COHER_LENGTH_X).toDouble(), getItemValue(P_COHER_LENGTH_Y).toDouble());
    result->setGamma(Units::deg2rad(getItemValue(P_GAMMA).toDouble()));
    return std::move(result);
}

// --------------------------------------------------------------------------------------------- //

FTDistribution2DGateItem::FTDistribution2DGateItem()
    : FTDistribution2DItem(Constants::FTDistribution2DGateType)
{
    addProperty(P_COHER_LENGTH_X, 1.0);
    addProperty(P_COHER_LENGTH_Y, 1.0);
}

std::unique_ptr<IFTDistribution2D> FTDistribution2DGateItem::createFTDistribution() const
{
    auto result = GUIHelpers::make_unique<FTDistribution2DGate>(
        getItemValue(P_COHER_LENGTH_X).toDouble(), getItemValue(P_COHER_LENGTH_Y).toDouble());
    result->setGamma(Units::deg2rad(getItemValue(P_GAMMA).toDouble()));
    return std::move(result);
}

// --------------------------------------------------------------------------------------------- //

FTDistribution2DConeItem::FTDistribution2DConeItem()
    : FTDistribution2DItem(Constants::FTDistribution2DConeType)
{
    addProperty(P_COHER_LENGTH_X, 1.0);
    addProperty(P_COHER_LENGTH_Y, 1.0);
}

std::unique_ptr<IFTDistribution2D> FTDistribution2DConeItem::createFTDistribution() const
{
    auto result = GUIHelpers::make_unique<FTDistribution2DCone>(
        getItemValue(P_COHER_LENGTH_X).toDouble(), getItemValue(P_COHER_LENGTH_Y).toDouble());
    result->setGamma(Units::deg2rad(getItemValue(P_GAMMA).toDouble()));
    return std::move(result);
}

// --------------------------------------------------------------------------------------------- //

const QString FTDistribution2DVoigtItem::P_ETA = "Eta";

FTDistribution2DVoigtItem::FTDistribution2DVoigtItem()
    : FTDistribution2DItem(Constants::FTDistribution2DVoigtType)
{
    addProperty(P_COHER_LENGTH_X, 1.0);
    addProperty(P_COHER_LENGTH_Y, 1.0);
    addProperty(P_ETA, 0.5)->setLimits(RealLimits::limited(0.0, 1.0));
}

std::unique_ptr<IFTDistribution2D> FTDistribution2DVoigtItem::createFTDistribution() const
{
    auto result = GUIHelpers::make_unique<FTDistribution2DVoigt>(
        getItemValue(P_COHER_LENGTH_X).toDouble(), getItemValue(P_COHER_LENGTH_Y).toDouble(),
        getItemValue(P_ETA).toDouble());
    result->setGamma(Units::deg2rad(getItemValue(P_GAMMA).toDouble()));
    return std::move(result);
}
