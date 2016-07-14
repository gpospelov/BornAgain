// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/DistributionItem.cpp
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

#include "DistributionItem.h"
#include "Distributions.h"
#include "GUIHelpers.h"


const QString DistributionItem::P_NUMBER_OF_SAMPLES = "Number of samples";
const QString DistributionItem::P_SIGMA_FACTOR = "Sigma factor";
const QString DistributionItem::P_IS_INITIALIZED = "is initialized";

DistributionItem::DistributionItem(const QString name)
    : SessionItem(name)
{
    addProperty(P_IS_INITIALIZED, false)->setVisible(false);
}

//! Provides initialization of the distribution with some reasonable parameters around given value.
//! Used by beamDistributionItem to propagate value from DistributionNone to the distribution
//! currently selected by GroupItem.

void DistributionItem::init_parameters(double value)
{
    if(getItemValue(P_IS_INITIALIZED).toBool())
        return;

    init_distribution(value);
    setItemValue(P_IS_INITIALIZED, true);
}

void DistributionItem::register_number_of_samples()
{
    addProperty(P_NUMBER_OF_SAMPLES, 5);
}

void DistributionItem::register_sigma_factor()
{
    addProperty(P_SIGMA_FACTOR, 2.0);
}

/* ------------------------------------------------ */

const QString DistributionNoneItem::P_VALUE = "Value";

DistributionNoneItem::DistributionNoneItem()
    : DistributionItem(Constants::DistributionNoneType)
{
    addProperty(P_VALUE, 0.1)->setLimits(AttLimits::lowerLimited(1e-4));
    getItem(P_VALUE)->setDecimals(4);
}

std::unique_ptr<IDistribution1D> DistributionNoneItem::createDistribution() const
{
    return nullptr;
}

void DistributionNoneItem::init_distribution(double value)
{
    setItemValue(DistributionNoneItem::P_VALUE, value);
}

/* ------------------------------------------------ */

const QString DistributionGateItem::P_MIN = "Minimum";
const QString DistributionGateItem::P_MAX = "Maximum";

DistributionGateItem::DistributionGateItem()
    : DistributionItem(Constants::DistributionGateType)
{
    addProperty(P_MIN, 0.0)->setLimits(AttLimits::limitless());
    addProperty(P_MAX, 1.0)->setLimits(AttLimits::limitless());
    register_number_of_samples();
    register_sigma_factor();
}

std::unique_ptr<IDistribution1D> DistributionGateItem::createDistribution() const
{
    double min = getItemValue(P_MIN).toDouble();
    double max = getItemValue(P_MAX).toDouble();
    return GUIHelpers::make_unique<DistributionGate>(min, max);
}

void DistributionGateItem::init_distribution(double value)
{
    double sigma(0.1*std::abs(value));
    if(sigma == 0.0) sigma = 0.1;
    setItemValue(P_MIN, value - sigma);
    setItemValue(P_MAX, value + sigma);
}

/* ------------------------------------------------ */

const QString DistributionLorentzItem::P_MEAN = "Mean";
const QString DistributionLorentzItem::P_HWHM = "HWHM";

DistributionLorentzItem::DistributionLorentzItem()
    : DistributionItem(Constants::DistributionLorentzType)
{
    addProperty(P_MEAN, 0.0)->setLimits(AttLimits::limitless());
    addProperty(P_HWHM, 1.0);
    register_number_of_samples();
    register_sigma_factor();
}

std::unique_ptr<IDistribution1D> DistributionLorentzItem::createDistribution() const
{
    double mean = getItemValue(P_MEAN).toDouble();
    double hwhm = getItemValue(P_HWHM).toDouble();
    return GUIHelpers::make_unique<DistributionLorentz>(mean, hwhm);
}

void DistributionLorentzItem::init_distribution(double value)
{
    double sigma(0.1*std::abs(value));
    if(sigma == 0.0) sigma = 0.1;

    setItemValue(P_MEAN, value);
    setItemValue(P_HWHM, sigma);
    getItem(P_HWHM)->setLimits(AttLimits::lowerLimited(0.0));
}

/* ------------------------------------------------ */

const QString DistributionGaussianItem::P_MEAN = "Mean";
const QString DistributionGaussianItem::P_STD_DEV = "Standard deviation";

DistributionGaussianItem::DistributionGaussianItem()
    : DistributionItem(Constants::DistributionGaussianType)
{
    addProperty(P_MEAN, 0.0)->setLimits(AttLimits::limitless());
    addProperty(P_STD_DEV, 1.0);
    register_number_of_samples();
    register_sigma_factor();
}

std::unique_ptr<IDistribution1D> DistributionGaussianItem::createDistribution() const
{
    double mean = getItemValue(P_MEAN).toDouble();
    double std_dev = getItemValue(P_STD_DEV).toDouble();
    return GUIHelpers::make_unique<DistributionGaussian>(mean, std_dev);
}

void DistributionGaussianItem::init_distribution(double value)
{
    double sigma(0.1*std::abs(value));
    if(sigma == 0.0) sigma = 0.1;

    setItemValue(P_MEAN, value);
    setItemValue(P_STD_DEV, sigma);
    getItem(P_STD_DEV)->setLimits(AttLimits::lowerLimited(0.0));
}

/* ------------------------------------------------ */

const QString DistributionLogNormalItem::P_MEDIAN = "Median";
const QString DistributionLogNormalItem::P_SCALE_PAR = "Scale parameter";

DistributionLogNormalItem::DistributionLogNormalItem()
    : DistributionItem(Constants::DistributionLogNormalType)
{
    addProperty(P_MEDIAN, 1.0);
    addProperty(P_SCALE_PAR, 1.0);
    register_number_of_samples();
    register_sigma_factor();
}

std::unique_ptr<IDistribution1D> DistributionLogNormalItem::createDistribution() const
{
    double median = getItemValue(P_MEDIAN).toDouble();
    double scale_par = getItemValue(P_SCALE_PAR).toDouble();
    return GUIHelpers::make_unique<DistributionLogNormal>(median, scale_par);
}

void DistributionLogNormalItem::init_distribution(double value)
{
    double sigma(0.1*std::abs(value));
    if(sigma == 0.0) sigma = 0.1;

    setItemValue(P_MEDIAN, value);
    setItemValue(P_SCALE_PAR, sigma);
    getItem(P_SCALE_PAR)->setLimits(AttLimits::lowerLimited(0.0));
}

/* ------------------------------------------------ */

const QString DistributionCosineItem::P_MEAN = "Mean";
const QString DistributionCosineItem::P_SIGMA = "Sigma";

DistributionCosineItem::DistributionCosineItem()
    : DistributionItem(Constants::DistributionCosineType)
{
    addProperty(P_MEAN, 0.0)->setLimits(AttLimits::limitless());
    addProperty(P_SIGMA, 1.0);
    register_number_of_samples();
    register_sigma_factor();
}

std::unique_ptr<IDistribution1D> DistributionCosineItem::createDistribution() const
{
    double mean = getItemValue(P_MEAN).toDouble();
    double sigma = getItemValue(P_SIGMA).toDouble();
    return GUIHelpers::make_unique<DistributionCosine>(mean, sigma);
}

void DistributionCosineItem::init_distribution(double value)
{
    double sigma(0.1*std::abs(value));
    if(sigma == 0.0) sigma = 0.1;

    setItemValue(P_MEAN, value);
    setItemValue(P_SIGMA, sigma);
    getItem(P_SIGMA)->setLimits(AttLimits::lowerLimited(0.0));
}
