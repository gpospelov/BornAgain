// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/FTDistributionItems.cpp
//! @brief     Implements FTDistribution1DItem's classes
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FTDistributionItems.h"
#include "item_constants.h"
#include "Units.h"

using namespace Constants;

const QString FTDistribution1DItem::P_CORR_LENGTH = "Corr_length";
const QString FTDistribution1DVoigtItem::P_ETA = "Eta";

const QString FTDistribution2DItem::P_CORR_LENGTH_X = "Corr_length_x";
const QString FTDistribution2DItem::P_CORR_LENGTH_Y = "Corr_length_y";
const QString FTDistribution2DItem::P_GAMMA = "Gamma";
const QString FTDistribution2DVoigtItem::P_ETA = "Eta";


//===============1D======================

// Cauchy
FTDistribution1DCauchyItem::FTDistribution1DCauchyItem()
    : FTDistribution1DItem(FTDistribution1DCauchyType)
{
    registerProperty(P_CORR_LENGTH, 1.0);
}

IFTDistribution1D *FTDistribution1DCauchyItem::createFTDistribution() const
{
    return new FTDistribution1DCauchy(
                getRegisteredProperty(P_CORR_LENGTH).toDouble() );
}

// Gauss
FTDistribution1DGaussItem::FTDistribution1DGaussItem()
    : FTDistribution1DItem(FTDistribution1DGaussType)
{
    registerProperty(P_CORR_LENGTH, 1.0);
}

IFTDistribution1D *FTDistribution1DGaussItem::createFTDistribution() const
{
    return new FTDistribution1DGauss(
                getRegisteredProperty(P_CORR_LENGTH).toDouble() );
}

// Gate
FTDistribution1DGateItem::FTDistribution1DGateItem()
    : FTDistribution1DItem(FTDistribution1DGateType)
{
    registerProperty(P_CORR_LENGTH, 1.0);
}

IFTDistribution1D *FTDistribution1DGateItem::createFTDistribution() const
{
    return new FTDistribution1DGate(
                getRegisteredProperty(P_CORR_LENGTH).toDouble() );
}

// Triangle
FTDistribution1DTriangleItem::FTDistribution1DTriangleItem()
    : FTDistribution1DItem(FTDistribution1DTriangleType)
{
    registerProperty(P_CORR_LENGTH, 1.0);
}

IFTDistribution1D *FTDistribution1DTriangleItem::createFTDistribution() const
{
    return new FTDistribution1DTriangle(
                getRegisteredProperty(P_CORR_LENGTH).toDouble() );
}

// Cosine
FTDistribution1DCosineItem::FTDistribution1DCosineItem()
    : FTDistribution1DItem(FTDistribution1DCosineType)
{
    registerProperty(P_CORR_LENGTH, 1.0);
}

IFTDistribution1D *FTDistribution1DCosineItem::createFTDistribution() const
{
    return new FTDistribution1DCosine(
                getRegisteredProperty(P_CORR_LENGTH).toDouble() );
}

// Voigt
FTDistribution1DVoigtItem::FTDistribution1DVoigtItem()
    : FTDistribution1DItem(FTDistribution1DVoigtType)
{
    registerProperty(P_CORR_LENGTH, 1.0);
    registerProperty(P_ETA, 0.5);//.limited(0.0, 1.0);
}

IFTDistribution1D *FTDistribution1DVoigtItem::createFTDistribution() const
{
    return new FTDistribution1DVoigt(
                getRegisteredProperty(P_CORR_LENGTH).toDouble(),
                getRegisteredProperty(P_ETA).toDouble() );
}


//===============2D======================

// Cauchy
FTDistribution2DCauchyItem::FTDistribution2DCauchyItem()
    : FTDistribution2DItem(FTDistribution2DCauchyType)
{
    registerProperty(P_CORR_LENGTH_X, 1.0);
    registerProperty(P_CORR_LENGTH_Y, 1.0);
}

IFTDistribution2D *FTDistribution2DCauchyItem::createFTDistribution() const
{
    auto *p_result = new FTDistribution2DCauchy(
                getRegisteredProperty(P_CORR_LENGTH_X).toDouble(),
                getRegisteredProperty(P_CORR_LENGTH_Y).toDouble()
                );
    double gamma = Units::deg2rad(getRegisteredProperty(P_GAMMA).toDouble() );
    p_result->setGamma(gamma);
    return p_result;
}

// Gauss
FTDistribution2DGaussItem::FTDistribution2DGaussItem()
    : FTDistribution2DItem(FTDistribution2DGaussType)
{
    registerProperty(P_CORR_LENGTH_X, 1.0);
    registerProperty(P_CORR_LENGTH_Y, 1.0);
}

IFTDistribution2D *FTDistribution2DGaussItem::createFTDistribution() const
{
    auto *p_result =  new FTDistribution2DGauss(
                getRegisteredProperty(P_CORR_LENGTH_X).toDouble(),
                getRegisteredProperty(P_CORR_LENGTH_Y).toDouble()
                );
    double gamma = Units::deg2rad(getRegisteredProperty(P_GAMMA).toDouble() );
    p_result->setGamma(gamma);
    return p_result;
}

// Gate
FTDistribution2DGateItem::FTDistribution2DGateItem()
    : FTDistribution2DItem(FTDistribution2DGateType)
{
    registerProperty(P_CORR_LENGTH_X, 1.0);
    registerProperty(P_CORR_LENGTH_Y, 1.0);
}

IFTDistribution2D *FTDistribution2DGateItem::createFTDistribution() const
{
    auto *p_result = new FTDistribution2DGate(
                getRegisteredProperty(P_CORR_LENGTH_X).toDouble(),
                getRegisteredProperty(P_CORR_LENGTH_Y).toDouble()
                );
    double gamma = Units::deg2rad(getRegisteredProperty(P_GAMMA).toDouble() );
    p_result->setGamma(gamma);
    return p_result;
}

// Cone
FTDistribution2DConeItem::FTDistribution2DConeItem()
    : FTDistribution2DItem(FTDistribution2DConeType)
{
    registerProperty(P_CORR_LENGTH_X, 1.0);
    registerProperty(P_CORR_LENGTH_Y, 1.0);
}

IFTDistribution2D *FTDistribution2DConeItem::createFTDistribution() const
{
    auto *p_result = new FTDistribution2DCone(
                getRegisteredProperty(P_CORR_LENGTH_X).toDouble(),
                getRegisteredProperty(P_CORR_LENGTH_Y).toDouble()
                );
    double gamma = Units::deg2rad(getRegisteredProperty(P_GAMMA).toDouble() );
    p_result->setGamma(gamma);
    return p_result;
}

// Voigt
FTDistribution2DVoigtItem::FTDistribution2DVoigtItem()
    : FTDistribution2DItem(FTDistribution2DVoigtType)
{
    registerProperty(P_CORR_LENGTH_X, 1.0);
    registerProperty(P_CORR_LENGTH_Y, 1.0);
    registerProperty(P_ETA, 0.5);//.limited(0.0, 1.0);
}

IFTDistribution2D *FTDistribution2DVoigtItem::createFTDistribution() const
{
    auto *p_result = new FTDistribution2DVoigt(
                getRegisteredProperty(P_CORR_LENGTH_X).toDouble(),
                getRegisteredProperty(P_CORR_LENGTH_Y).toDouble(),
                getRegisteredProperty(P_ETA).toDouble()
                );
    double gamma = Units::deg2rad(getRegisteredProperty(P_GAMMA).toDouble() );
    p_result->setGamma(gamma);
    return p_result;
}
