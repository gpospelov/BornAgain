// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/FTDecayFunctionItems.cpp
//! @brief     Implements FTDecayFunction1DItem classes
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FTDecayFunctionItems.h"
#include "item_constants.h"
#include "Units.h"

const QString FTDecayFunction1DItem::P_DECAY_LENGTH = "Decay Length";
const QString FTDecayFunction1DVoigtItem::P_ETA = "Eta";

const QString FTDecayFunction2DItem::P_DECAY_LENGTH_X = "Decay Length X";
const QString FTDecayFunction2DItem::P_DECAY_LENGTH_Y = "Decay Length Y";
const QString FTDecayFunction2DItem::P_GAMMA = "Gamma";
const QString FTDecayFunction2DVoigtItem::P_ETA = "Eta";

using namespace Constants;

//===============1D======================

// Cauchy
FTDecayFunction1DCauchyItem::FTDecayFunction1DCauchyItem(ParameterizedItem *parent)
    : FTDecayFunction1DItem(FTDecayFunction1DCauchyType, parent)
{
    registerProperty(P_DECAY_LENGTH, 1000.0);
}

IFTDecayFunction1D *FTDecayFunction1DCauchyItem::createFTDecayFunction() const
{
    return new FTDecayFunction1DCauchy(
                getRegisteredProperty(P_DECAY_LENGTH).toDouble() );
}

// Gauss
FTDecayFunction1DGaussItem::FTDecayFunction1DGaussItem(ParameterizedItem *parent)
    : FTDecayFunction1DItem(FTDecayFunction1DGaussType, parent)
{
    registerProperty(P_DECAY_LENGTH, 1000.0);
}

IFTDecayFunction1D *FTDecayFunction1DGaussItem::createFTDecayFunction() const
{
    return new FTDecayFunction1DGauss(
                getRegisteredProperty(P_DECAY_LENGTH).toDouble() );
}

// Triangle
FTDecayFunction1DTriangleItem::FTDecayFunction1DTriangleItem(ParameterizedItem *parent)
    : FTDecayFunction1DItem(FTDecayFunction1DTriangleType, parent)
{
    registerProperty(P_DECAY_LENGTH, 1000.0);
}

IFTDecayFunction1D *FTDecayFunction1DTriangleItem::createFTDecayFunction() const
{
    return new FTDecayFunction1DTriangle(
                getRegisteredProperty(P_DECAY_LENGTH).toDouble() );
}

// Voigt
FTDecayFunction1DVoigtItem::FTDecayFunction1DVoigtItem(ParameterizedItem *parent)
    : FTDecayFunction1DItem(FTDecayFunction1DVoigtType, parent)
{
    registerProperty(P_DECAY_LENGTH, 1000.0);
    registerProperty(P_ETA, 0.5, PropertyAttribute(AttLimits::limited(0.0, 1.0)));
}

IFTDecayFunction1D *FTDecayFunction1DVoigtItem::createFTDecayFunction() const
{
    return new FTDecayFunction1DVoigt(
                getRegisteredProperty(P_DECAY_LENGTH).toDouble(),
                getRegisteredProperty(P_ETA).toDouble() );
}

FTDecayFunction2DCauchyItem::FTDecayFunction2DCauchyItem(ParameterizedItem *parent)
    : FTDecayFunction2DItem(FTDecayFunction2DCauchyType, parent)
{
    registerProperty(P_DECAY_LENGTH_X, 1000.0);
    registerProperty(P_DECAY_LENGTH_Y, 1000.0);
}

IFTDecayFunction2D *FTDecayFunction2DCauchyItem::createFTDecayFunction() const
{
    auto *p_result
        = new FTDecayFunction2DCauchy(getRegisteredProperty(P_DECAY_LENGTH_X).toDouble(),
                                      getRegisteredProperty(P_DECAY_LENGTH_Y).toDouble());
    double gamma = Units::deg2rad(getRegisteredProperty(P_GAMMA).toDouble());
    p_result->setGamma(gamma);
    return p_result;
}

FTDecayFunction2DGaussItem::FTDecayFunction2DGaussItem(ParameterizedItem *parent)
    : FTDecayFunction2DItem(FTDecayFunction2DGaussType, parent)
{
    registerProperty(P_DECAY_LENGTH_X, 1000.0);
    registerProperty(P_DECAY_LENGTH_Y, 1000.0);
}

IFTDecayFunction2D *FTDecayFunction2DGaussItem::createFTDecayFunction() const
{
    auto *p_result
        = new FTDecayFunction2DGauss(getRegisteredProperty(P_DECAY_LENGTH_X).toDouble(),
                                     getRegisteredProperty(P_DECAY_LENGTH_Y).toDouble());
    double gamma = Units::deg2rad(getRegisteredProperty(P_GAMMA).toDouble());
    p_result->setGamma(gamma);
    return p_result;
}

FTDecayFunction2DVoigtItem::FTDecayFunction2DVoigtItem(ParameterizedItem *parent)
    : FTDecayFunction2DItem(FTDecayFunction2DVoigtType, parent)
{
    registerProperty(P_DECAY_LENGTH_X, 1000.0);
    registerProperty(P_DECAY_LENGTH_Y, 1000.0);
    registerProperty(P_ETA, 0.5, PropertyAttribute(AttLimits::limited(0.0, 1.0)));
}

IFTDecayFunction2D *FTDecayFunction2DVoigtItem::createFTDecayFunction() const
{
    auto *p_result
        = new FTDecayFunction2DVoigt(getRegisteredProperty(P_DECAY_LENGTH_X).toDouble(),
                                     getRegisteredProperty(P_DECAY_LENGTH_Y).toDouble(),
                                     getRegisteredProperty(P_ETA).toDouble());
    double gamma = Units::deg2rad(getRegisteredProperty(P_GAMMA).toDouble());
    p_result->setGamma(gamma);
    return p_result;
}
