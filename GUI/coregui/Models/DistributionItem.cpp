// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/DistributionItem.cpp
//! @brief     Implements class DistributionItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "DistributionItem.h"
#include "Distributions.h"
#include "ComboProperty.h"
#include "GUIHelpers.h"

#include <QDebug>

const QString DistributionItem::P_NUMBER_OF_SAMPLES = "Number of samples";
const QString DistributionItem::P_SIGMA_FACTOR = "Sigma factor";

DistributionItem::DistributionItem(const QString name)
    : SessionItem(name)
{
}

void DistributionItem::register_number_of_samples()
{
    registerProperty(P_NUMBER_OF_SAMPLES, 5);
}

void DistributionItem::register_sigma_factor()
{
    registerProperty(P_SIGMA_FACTOR, 2.0);
}

/* ------------------------------------------------ */

const QString DistributionNoneItem::P_VALUE = "Value";

DistributionNoneItem::DistributionNoneItem()
    : DistributionItem(Constants::DistributionNoneType)
{
    registerProperty(P_VALUE, 0.1)->setLimits(AttLimits::limitless());
}

std::unique_ptr<IDistribution1D> DistributionNoneItem::createDistribution() const
{
    return nullptr;
}

void DistributionNoneItem::init_parameters(double value, PropertyAttribute attribute)
{
    setRegisteredProperty(DistributionNoneItem::P_VALUE, value);
//    setPropertyAttribute(DistributionNoneItem::P_VALUE, attribute);
}

/* ------------------------------------------------ */

const QString DistributionGateItem::P_MIN = "Minimum";
const QString DistributionGateItem::P_MAX = "Maximum";

DistributionGateItem::DistributionGateItem()
    : DistributionItem(Constants::DistributionGateType)
{
    registerProperty(P_MIN, 0.0)->setLimits(AttLimits::limitless());
    registerProperty(P_MAX, 1.0)->setLimits(AttLimits::limitless());
    register_number_of_samples();
    register_sigma_factor();
}

std::unique_ptr<IDistribution1D> DistributionGateItem::createDistribution() const
{
    double min = getRegisteredProperty(P_MIN).toDouble();
    double max = getRegisteredProperty(P_MAX).toDouble();
    return GUIHelpers::make_unique<DistributionGate>(min, max);
}

void DistributionGateItem::init_parameters(double value, PropertyAttribute attribute)
{
    double sigma(0.1*std::abs(value));
    if(sigma == 0.0) sigma = 0.1;
    setRegisteredProperty(P_MIN, value - sigma);
//    setPropertyAttribute(P_MIN, attribute);
    setRegisteredProperty(P_MAX, value + sigma);
//    setPropertyAttribute(P_MAX, attribute);
}

/* ------------------------------------------------ */

const QString DistributionLorentzItem::P_MEAN = "Mean";
const QString DistributionLorentzItem::P_HWHM = "HWHM";

DistributionLorentzItem::DistributionLorentzItem()
    : DistributionItem(Constants::DistributionLorentzType)
{
    registerProperty(P_MEAN, 0.0)->setLimits(AttLimits::limitless());
    registerProperty(P_HWHM, 1.0);
    register_number_of_samples();
    register_sigma_factor();
}

std::unique_ptr<IDistribution1D> DistributionLorentzItem::createDistribution() const
{
    double mean = getRegisteredProperty(P_MEAN).toDouble();
    double hwhm = getRegisteredProperty(P_HWHM).toDouble();
    return GUIHelpers::make_unique<DistributionLorentz>(mean, hwhm);
}

void DistributionLorentzItem::init_parameters(double value, PropertyAttribute attribute)
{
    double sigma(0.1*std::abs(value));
    if(sigma == 0.0) sigma = 0.1;

    setRegisteredProperty(P_MEAN, value);
//    setPropertyAttribute(P_MEAN, attribute);
    setRegisteredProperty(P_HWHM, sigma);
    getItem(P_HWHM)->setLimits(AttLimits::lowerLimited(0.0));
}

/* ------------------------------------------------ */

const QString DistributionGaussianItem::P_MEAN = "Mean";
const QString DistributionGaussianItem::P_STD_DEV = "Standard deviation";

DistributionGaussianItem::DistributionGaussianItem()
    : DistributionItem(Constants::DistributionGaussianType)
{
    registerProperty(P_MEAN, 0.0)->setLimits(AttLimits::limitless());
    registerProperty(P_STD_DEV, 1.0);
    register_number_of_samples();
    register_sigma_factor();
}

std::unique_ptr<IDistribution1D> DistributionGaussianItem::createDistribution() const
{
    double mean = getRegisteredProperty(P_MEAN).toDouble();
    double std_dev = getRegisteredProperty(P_STD_DEV).toDouble();
    return GUIHelpers::make_unique<DistributionGaussian>(mean, std_dev);
}

void DistributionGaussianItem::init_parameters(double value, PropertyAttribute attribute)
{
    double sigma(0.1*std::abs(value));
    if(sigma == 0.0) sigma = 0.1;

    setRegisteredProperty(P_MEAN, value);
//    setPropertyAttribute(P_MEAN, attribute);
    setRegisteredProperty(P_STD_DEV, sigma);
    getItem(P_STD_DEV)->setLimits(AttLimits::lowerLimited(0.0));
}

/* ------------------------------------------------ */

const QString DistributionLogNormalItem::P_MEDIAN = "Median";
const QString DistributionLogNormalItem::P_SCALE_PAR = "Scale parameter";

DistributionLogNormalItem::DistributionLogNormalItem()
    : DistributionItem(Constants::DistributionLogNormalType)
{
    registerProperty(P_MEDIAN, 1.0);
    registerProperty(P_SCALE_PAR, 1.0);
    register_number_of_samples();
    register_sigma_factor();
}

std::unique_ptr<IDistribution1D> DistributionLogNormalItem::createDistribution() const
{
    double median = getRegisteredProperty(P_MEDIAN).toDouble();
    double scale_par = getRegisteredProperty(P_SCALE_PAR).toDouble();
    return GUIHelpers::make_unique<DistributionLogNormal>(median, scale_par);
}

void DistributionLogNormalItem::init_parameters(double value, PropertyAttribute attribute)
{
    double sigma(0.1*std::abs(value));
    if(sigma == 0.0) sigma = 0.1;

    setRegisteredProperty(P_MEDIAN, value);
//    setPropertyAttribute(P_MEDIAN, attribute);
    setRegisteredProperty(P_SCALE_PAR, sigma);
    getItem(P_SCALE_PAR)->setLimits(AttLimits::lowerLimited(0.0));
}

/* ------------------------------------------------ */

const QString DistributionCosineItem::P_MEAN = "Mean";
const QString DistributionCosineItem::P_SIGMA = "Sigma";

DistributionCosineItem::DistributionCosineItem()
    : DistributionItem(Constants::DistributionCosineType)
{
    registerProperty(P_MEAN, 0.0)->setLimits(AttLimits::limitless());
    registerProperty(P_SIGMA, 1.0);
    register_number_of_samples();
    register_sigma_factor();
}

std::unique_ptr<IDistribution1D> DistributionCosineItem::createDistribution() const
{
    double mean = getRegisteredProperty(P_MEAN).toDouble();
    double sigma = getRegisteredProperty(P_SIGMA).toDouble();
    return GUIHelpers::make_unique<DistributionCosine>(mean, sigma);
}

void DistributionCosineItem::init_parameters(double value, PropertyAttribute attribute)
{
    double sigma(0.1*std::abs(value));
    if(sigma == 0.0) sigma = 0.1;

    setRegisteredProperty(P_MEAN, value);
//    setPropertyAttribute(P_MEAN, attribute);
    setRegisteredProperty(P_SIGMA, sigma);
    getItem(P_SIGMA)->setLimits(AttLimits::lowerLimited(0.0));
}
