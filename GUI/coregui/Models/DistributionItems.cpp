// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/DistributionItems.cpp
//! @brief     Implements class DistributionItem and several subclasses
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "DistributionItems.h"
#include "Distributions.h"
#include "GUIHelpers.h"
#include "BornAgainNamespace.h"
#include "RealLimitsItems.h"
#include <cmath>

const QString DistributionItem::P_NUMBER_OF_SAMPLES = "Number of samples";
const QString DistributionItem::P_SIGMA_FACTOR = Constants::DistributionSigmaFactor;
const QString DistributionItem::P_IS_INITIALIZED = "is initialized";
const QString DistributionItem::P_LIMITS = "Limits";

DistributionItem::DistributionItem(const QString& name) : SessionItem(name)
{
    addProperty(P_IS_INITIALIZED, false)->setVisible(false);
}

//! Provides initialization of the distribution with some reasonable parameters around given value.
//! Used by beamDistributionItem to propagate value from DistributionNone to the distribution
//! currently selected by GroupItem.

void DistributionItem::init_parameters(double value, const RealLimits& limits)
{
    if (getItemValue(P_IS_INITIALIZED).toBool())
        return;

    init_distribution(value);
    init_limits_group(limits);
    setItemValue(P_IS_INITIALIZED, true);
}

void DistributionItem::init_limits_group(const RealLimits& limits, double factor)
{
    if (!isTag(P_LIMITS))
        return;

    if (limits.isLimitless()) {
        setGroupProperty(P_LIMITS, Constants::RealLimitsLimitlessType);

    }

    else if (limits.isPositive()) {
        setGroupProperty(P_LIMITS, Constants::RealLimitsPositiveType);
    }

    else if (limits.isNonnegative()) {
        setGroupProperty(P_LIMITS, Constants::RealLimitsNonnegativeType);
    }

    else if (limits.isLowerLimited()) {
        SessionItem* lim = setGroupProperty(P_LIMITS, Constants::RealLimitsLowerLimitedType);
        lim->setItemValue(RealLimitsItem::P_XMIN, limits.getLowerLimit()*factor);
    }

    else if (limits.isUpperLimited()) {
        SessionItem* lim = setGroupProperty(P_LIMITS, Constants::RealLimitsUpperLimitedType);
        lim->setItemValue(RealLimitsItem::P_XMAX, limits.getUpperLimit()*factor);
    }

    else if (limits.isLimited()) {
        SessionItem* lim = setGroupProperty(P_LIMITS, Constants::RealLimitsLimitedType);
        lim->setItemValue(RealLimitsItem::P_XMIN, limits.getLowerLimit()*factor);
        lim->setItemValue(RealLimitsItem::P_XMAX, limits.getUpperLimit()*factor);
    }
}

void DistributionItem::register_number_of_samples()
{
    addProperty(P_NUMBER_OF_SAMPLES, 5)->setLimits(RealLimits::lowerLimited(1.0));
}

void DistributionItem::register_sigma_factor()
{
    addProperty(P_SIGMA_FACTOR, 2.0);
}

void DistributionItem::register_limits()
{
    addGroupProperty(P_LIMITS, Constants::RealLimitsGroup);
    setGroupProperty(P_LIMITS, Constants::RealLimitsLimitlessType);
}

// --------------------------------------------------------------------------------------------- //

const QString DistributionNoneItem::P_VALUE = "Value";

DistributionNoneItem::DistributionNoneItem() : DistributionItem(Constants::DistributionNoneType)
{
    addProperty(P_VALUE, 0.1)->setLimits(RealLimits::limitless());
    getItem(P_VALUE)->setDecimals(4);
}

std::unique_ptr<IDistribution1D> DistributionNoneItem::createDistribution(double scale) const
{
    Q_UNUSED(scale);
    return nullptr;
}

void DistributionNoneItem::init_distribution(double value)
{
    setItemValue(DistributionNoneItem::P_VALUE, value);
}

// --------------------------------------------------------------------------------------------- //

const QString DistributionGateItem::P_MIN = QString::fromStdString(BornAgain::Minimum);
const QString DistributionGateItem::P_MAX = QString::fromStdString(BornAgain::Maximum);

DistributionGateItem::DistributionGateItem() : DistributionItem(Constants::DistributionGateType)
{
    addProperty(P_MIN, 0.0)->setLimits(RealLimits::limitless());
    addProperty(P_MAX, 1.0)->setLimits(RealLimits::limitless());
    register_number_of_samples();
    register_limits();
    getItem(P_LIMITS)->setVisible(false);
}

std::unique_ptr<IDistribution1D> DistributionGateItem::createDistribution(double scale) const
{
    double min = getItemValue(P_MIN).toDouble();
    double max = getItemValue(P_MAX).toDouble();
    return GUIHelpers::make_unique<DistributionGate>(scale*min, scale*max);
}

void DistributionGateItem::init_distribution(double value)
{
    double sigma(0.1 * std::abs(value));
    if (sigma == 0.0)
        sigma = 0.1;
    setItemValue(P_MIN, value - sigma);
    setItemValue(P_MAX, value + sigma);
}

// --------------------------------------------------------------------------------------------- //

const QString DistributionLorentzItem::P_MEAN = QString::fromStdString(BornAgain::Mean);
const QString DistributionLorentzItem::P_HWHM = QString::fromStdString(BornAgain::HWHM);

DistributionLorentzItem::DistributionLorentzItem()
    : DistributionItem(Constants::DistributionLorentzType)
{
    addProperty(P_MEAN, 1.0)->setLimits(RealLimits::limitless());
    addProperty(P_HWHM, 1.0);
    register_number_of_samples();
    register_sigma_factor();
    register_limits();
}

std::unique_ptr<IDistribution1D> DistributionLorentzItem::createDistribution(double scale) const
{
    double mean = getItemValue(P_MEAN).toDouble();
    double hwhm = getItemValue(P_HWHM).toDouble();
    return GUIHelpers::make_unique<DistributionLorentz>(scale*mean, scale*hwhm);
}

void DistributionLorentzItem::init_distribution(double value)
{
    double sigma(0.1 * std::abs(value));
    if (sigma == 0.0)
        sigma = 0.1;

    setItemValue(P_MEAN, value);
    setItemValue(P_HWHM, sigma);
    getItem(P_HWHM)->setLimits(RealLimits::lowerLimited(0.0));
}

// --------------------------------------------------------------------------------------------- //

const QString DistributionGaussianItem::P_MEAN = QString::fromStdString(BornAgain::Mean);
const QString DistributionGaussianItem::P_STD_DEV = QString::fromStdString(BornAgain::StdDeviation);

DistributionGaussianItem::DistributionGaussianItem()
    : DistributionItem(Constants::DistributionGaussianType)
{
    addProperty(P_MEAN, 1.0)->setLimits(RealLimits::limitless());
    addProperty(P_STD_DEV, 1.0);
    register_number_of_samples();
    register_sigma_factor();
    register_limits();
}

std::unique_ptr<IDistribution1D> DistributionGaussianItem::createDistribution(double scale) const
{
    double mean = getItemValue(P_MEAN).toDouble();
    double std_dev = getItemValue(P_STD_DEV).toDouble();
    return GUIHelpers::make_unique<DistributionGaussian>(scale*mean, scale*std_dev);
}

void DistributionGaussianItem::init_distribution(double value)
{
    double sigma(0.1 * std::abs(value));
    if (sigma == 0.0)
        sigma = 0.1;

    setItemValue(P_MEAN, value);
    setItemValue(P_STD_DEV, sigma);
    getItem(P_STD_DEV)->setLimits(RealLimits::lowerLimited(0.0));
}

// --------------------------------------------------------------------------------------------- //

const QString DistributionLogNormalItem::P_MEDIAN = QString::fromStdString(BornAgain::Median);
const QString DistributionLogNormalItem::P_SCALE_PAR
    = QString::fromStdString(BornAgain::ScaleParameter);

DistributionLogNormalItem::DistributionLogNormalItem()
    : DistributionItem(Constants::DistributionLogNormalType)
{
    addProperty(P_MEDIAN, 1.0);
    addProperty(P_SCALE_PAR, 1.0);
    register_number_of_samples();
    register_sigma_factor();
    register_limits();
}

std::unique_ptr<IDistribution1D> DistributionLogNormalItem::createDistribution(double scale) const
{
    double median = getItemValue(P_MEDIAN).toDouble();
    double scale_par = getItemValue(P_SCALE_PAR).toDouble();
    return GUIHelpers::make_unique<DistributionLogNormal>(scale*median, scale_par);
}

void DistributionLogNormalItem::init_distribution(double value)
{
    double sigma(0.1 * std::abs(value));
    if (sigma == 0.0)
        sigma = 0.1;

    setItemValue(P_MEDIAN, value);
    setItemValue(P_SCALE_PAR, sigma);
    getItem(P_SCALE_PAR)->setLimits(RealLimits::lowerLimited(0.0));
}

// --------------------------------------------------------------------------------------------- //

const QString DistributionCosineItem::P_MEAN = QString::fromStdString(BornAgain::Mean);
const QString DistributionCosineItem::P_SIGMA = QString::fromStdString(BornAgain::Sigma);

DistributionCosineItem::DistributionCosineItem()
    : DistributionItem(Constants::DistributionCosineType)
{
    addProperty(P_MEAN, 1.0)->setLimits(RealLimits::limitless());
    addProperty(P_SIGMA, 1.0);
    register_number_of_samples();
    register_sigma_factor();
    register_limits();
}

std::unique_ptr<IDistribution1D> DistributionCosineItem::createDistribution(double scale) const
{
    double mean = getItemValue(P_MEAN).toDouble();
    double sigma = getItemValue(P_SIGMA).toDouble();
    return GUIHelpers::make_unique<DistributionCosine>(scale*mean, scale*sigma);
}

void DistributionCosineItem::init_distribution(double value)
{
    double sigma(0.1 * std::abs(value));
    if (sigma == 0.0)
        sigma = 0.1;

    setItemValue(P_MEAN, value);
    setItemValue(P_SIGMA, sigma);
    getItem(P_SIGMA)->setLimits(RealLimits::lowerLimited(0.0));
}
