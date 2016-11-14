// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/FTDecayFunctionItems.cpp
//! @brief     Implements FTDecayFunction1DItem classes
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "FTDecayFunctionItems.h"
#include "Units.h"
#include "BornAgainNamespace.h"

const QString FTDecayFunction1DItem::P_DECAY_LENGTH
    = QString::fromStdString(BornAgain::DecayLengthX);
const QString FTDecayFunction1DVoigtItem::P_ETA
    = QString::fromStdString(BornAgain::Eta);
const QString FTDecayFunction2DItem::P_DECAY_LENGTH_X
    = QString::fromStdString(BornAgain::DecayLengthX);
const QString FTDecayFunction2DItem::P_DECAY_LENGTH_Y
    = QString::fromStdString(BornAgain::DecayLengthY);
const QString FTDecayFunction2DItem::P_GAMMA
    = QString::fromStdString(BornAgain::Gamma);
const QString FTDecayFunction2DVoigtItem::P_ETA
    = QString::fromStdString(BornAgain::Eta);

using namespace Constants;

//===============1D======================

// Cauchy
FTDecayFunction1DCauchyItem::FTDecayFunction1DCauchyItem()
    : FTDecayFunction1DItem(FTDecayFunction1DCauchyType)
{
    addProperty(P_DECAY_LENGTH, 1000.0);
}

IFTDecayFunction1D* FTDecayFunction1DCauchyItem::createFTDecayFunction() const
{
    return new FTDecayFunction1DCauchy(getItemValue(P_DECAY_LENGTH).toDouble() );
}

// Gauss
FTDecayFunction1DGaussItem::FTDecayFunction1DGaussItem()
    : FTDecayFunction1DItem(FTDecayFunction1DGaussType)
{
    addProperty(P_DECAY_LENGTH, 1000.0);
}

IFTDecayFunction1D* FTDecayFunction1DGaussItem::createFTDecayFunction() const
{
    return new FTDecayFunction1DGauss(getItemValue(P_DECAY_LENGTH).toDouble() );
}

// Triangle
FTDecayFunction1DTriangleItem::FTDecayFunction1DTriangleItem()
    : FTDecayFunction1DItem(FTDecayFunction1DTriangleType)
{
    addProperty(P_DECAY_LENGTH, 1000.0);
}

IFTDecayFunction1D* FTDecayFunction1DTriangleItem::createFTDecayFunction() const
{
    return new FTDecayFunction1DTriangle(getItemValue(P_DECAY_LENGTH).toDouble() );
}

// Voigt
FTDecayFunction1DVoigtItem::FTDecayFunction1DVoigtItem()
    : FTDecayFunction1DItem(FTDecayFunction1DVoigtType)
{
    addProperty(P_DECAY_LENGTH, 1000.0);
    addProperty(P_ETA, 0.5)->setLimits(RealLimits::limited(0.0, 1.0));
}

IFTDecayFunction1D* FTDecayFunction1DVoigtItem::createFTDecayFunction() const
{
    return new FTDecayFunction1DVoigt(
                getItemValue(P_DECAY_LENGTH).toDouble(),
                getItemValue(P_ETA).toDouble() );
}

FTDecayFunction2DCauchyItem::FTDecayFunction2DCauchyItem()
    : FTDecayFunction2DItem(FTDecayFunction2DCauchyType)
{
    addProperty(P_DECAY_LENGTH_X, 1000.0);
    addProperty(P_DECAY_LENGTH_Y, 1000.0);
}

IFTDecayFunction2D* FTDecayFunction2DCauchyItem::createFTDecayFunction() const
{
    auto* p_result
        = new FTDecayFunction2DCauchy(getItemValue(P_DECAY_LENGTH_X).toDouble(),
                                      getItemValue(P_DECAY_LENGTH_Y).toDouble());
    double gamma = Units::deg2rad(getItemValue(P_GAMMA).toDouble());
    p_result->setGamma(gamma);
    return p_result;
}

FTDecayFunction2DGaussItem::FTDecayFunction2DGaussItem()
    : FTDecayFunction2DItem(FTDecayFunction2DGaussType)
{
    addProperty(P_DECAY_LENGTH_X, 1000.0);
    addProperty(P_DECAY_LENGTH_Y, 1000.0);
}

IFTDecayFunction2D* FTDecayFunction2DGaussItem::createFTDecayFunction() const
{
    auto* p_result
        = new FTDecayFunction2DGauss(getItemValue(P_DECAY_LENGTH_X).toDouble(),
                                     getItemValue(P_DECAY_LENGTH_Y).toDouble());
    double gamma = Units::deg2rad(getItemValue(P_GAMMA).toDouble());
    p_result->setGamma(gamma);
    return p_result;
}

FTDecayFunction2DVoigtItem::FTDecayFunction2DVoigtItem()
    : FTDecayFunction2DItem(FTDecayFunction2DVoigtType)
{
    addProperty(P_DECAY_LENGTH_X, 1000.0);
    addProperty(P_DECAY_LENGTH_Y, 1000.0);
    addProperty(P_ETA, 0.5)->setLimits(RealLimits::limited(0.0, 1.0));
}

IFTDecayFunction2D* FTDecayFunction2DVoigtItem::createFTDecayFunction() const
{
    auto* p_result
        = new FTDecayFunction2DVoigt(getItemValue(P_DECAY_LENGTH_X).toDouble(),
                                     getItemValue(P_DECAY_LENGTH_Y).toDouble(),
                                     getItemValue(P_ETA).toDouble());
    double gamma = Units::deg2rad(getItemValue(P_GAMMA).toDouble());
    p_result->setGamma(gamma);
    return p_result;
}
