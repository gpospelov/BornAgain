// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Models/DistributionItem.cpp
//! @brief     Implements class DistributionItem.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "DistributionItem.h"
#include "ComboProperty.h"

/* ------------------------------------------------ */

const QString DistributionGateItem::P_MIN = "Minimum";
const QString DistributionGateItem::P_MAX = "Maximum";

DistributionGateItem::DistributionGateItem(ParameterizedItem *parent)
    : DistributionItem(Constants::DistributionGateType, parent)
{
    setItemName(Constants::DistributionGateType);
    registerProperty(P_MIN, 0.0);
    registerProperty(P_MAX, 1.0);
}

/* ------------------------------------------------ */

const QString DistributionLorentzItem::P_MEAN = "Mean";
const QString DistributionLorentzItem::P_HWHM = "Half width half maximum";

DistributionLorentzItem::DistributionLorentzItem(ParameterizedItem *parent)
    : DistributionItem(Constants::DistributionLorentzType, parent)
{
    setItemName(Constants::DistributionLorentzType);
    registerProperty(P_MEAN, 0.0);
    registerProperty(P_HWHM, 1.0);
}

/* ------------------------------------------------ */

const QString DistributionGaussianItem::P_MEAN = "Mean";
const QString DistributionGaussianItem::P_STD_DEV = "Standard deviation";

DistributionGaussianItem::DistributionGaussianItem(ParameterizedItem *parent)
    : DistributionItem(Constants::DistributionGaussianType, parent)
{
    setItemName(Constants::DistributionGaussianType);
    registerProperty(P_MEAN, 0.0);
    registerProperty(P_STD_DEV, 1.0);
}

/* ------------------------------------------------ */

const QString DistributionLogNormalItem::P_MEDIAN = "Median";
const QString DistributionLogNormalItem::P_SCALE_PAR = "Scale parameter";

DistributionLogNormalItem::DistributionLogNormalItem(ParameterizedItem *parent)
    : DistributionItem(Constants::DistributionLogNormalType, parent)
{
    setItemName(Constants::DistributionLogNormalType);
    registerProperty(P_MEDIAN, 1.0);
    registerProperty(P_SCALE_PAR, 1.0);
}

/* ------------------------------------------------ */

const QString DistributionCosineItem::P_MEAN = "Mean";
const QString DistributionCosineItem::P_SIGMA = "Sigma";

DistributionCosineItem::DistributionCosineItem(ParameterizedItem *parent)
    : DistributionItem(Constants::DistributionCosineType, parent)
{
    setItemName(Constants::DistributionCosineType);
    registerProperty(P_MEAN, 0.0);
    registerProperty(P_SIGMA, 1.0);
}
