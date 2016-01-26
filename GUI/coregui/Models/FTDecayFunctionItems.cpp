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
#include "Units.h"

const QString FTDecayFunction1DItem::P_DECAY_LENGTH = "Corr_length";
const QString FTDecayFunction1DVoigtItem::P_ETA = "Eta";

//===============1D======================

// Cauchy
FTDecayFunction1DCauchyItem::FTDecayFunction1DCauchyItem(ParameterizedItem *parent)
    : FTDecayFunction1DItem(QString("FTDecayFunction1DCauchy"), parent)
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
    : FTDecayFunction1DItem(QString("FTDecayFunction1DGauss"), parent)
{
    registerProperty(P_DECAY_LENGTH, 1000.0);
}

IFTDecayFunction1D *FTDecayFunction1DGaussItem::createFTDecayFunction() const
{
    return new FTDecayFunction1DGauss(
                getRegisteredProperty(P_DECAY_LENGTH).toDouble() );
}

// Gate
FTDecayFunction1DGateItem::FTDecayFunction1DGateItem(ParameterizedItem *parent)
    : FTDecayFunction1DItem(QString("FTDecayFunction1DGate"), parent)
{
    registerProperty(P_DECAY_LENGTH, 1000.0);
}

IFTDecayFunction1D *FTDecayFunction1DGateItem::createFTDecayFunction() const
{
    return new FTDecayFunction1DGate(
                getRegisteredProperty(P_DECAY_LENGTH).toDouble() );
}

// Triangle
FTDecayFunction1DTriangleItem::FTDecayFunction1DTriangleItem(ParameterizedItem *parent)
    : FTDecayFunction1DItem(QString("FTDecayFunction1DTriangle"), parent)
{
    registerProperty(P_DECAY_LENGTH, 1000.0);
}

IFTDecayFunction1D *FTDecayFunction1DTriangleItem::createFTDecayFunction() const
{
    return new FTDecayFunction1DTriangle(
                getRegisteredProperty(P_DECAY_LENGTH).toDouble() );
}

// Cosine
FTDecayFunction1DCosineItem::FTDecayFunction1DCosineItem(ParameterizedItem *parent)
    : FTDecayFunction1DItem(QString("FTDecayFunction1DCosine"), parent)
{
    registerProperty(P_DECAY_LENGTH, 1000.0);
}

IFTDecayFunction1D *FTDecayFunction1DCosineItem::createFTDecayFunction() const
{
    return new FTDecayFunction1DCosine(
                getRegisteredProperty(P_DECAY_LENGTH).toDouble() );
}

// Voigt
FTDecayFunction1DVoigtItem::FTDecayFunction1DVoigtItem(ParameterizedItem *parent)
    : FTDecayFunction1DItem(QString("FTDecayFunction1DVoigt"), parent)
{
    registerProperty(P_DECAY_LENGTH, 1000.0);
    registerProperty(P_ETA, 0.5, PropertyAttribute(AttLimits::limited(-1.0, 1.0)));
}

IFTDecayFunction1D *FTDecayFunction1DVoigtItem::createFTDecayFunction() const
{
    return new FTDecayFunction1DVoigt(
                getRegisteredProperty(P_DECAY_LENGTH).toDouble(),
                getRegisteredProperty(P_ETA).toDouble() );
}

