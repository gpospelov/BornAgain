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
#include "ComboProperty.h"
#include <QDebug>

const QString DistributionItem::P_NUMBER_OF_SAMPLES = "Number of samples";
const QString DistributionItem::P_SIGMA_FACTOR = "Sigma factor";

DistributionItem::DistributionItem(const QString name, ParameterizedItem *parent)
    : ParameterizedItem(name, parent)
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

DistributionNoneItem::DistributionNoneItem(ParameterizedItem *parent)
    : DistributionItem(Constants::DistributionNoneType, parent)
{
    setItemName(Constants::DistributionNoneType);
    registerProperty(P_VALUE, 0.1);
}

IDistribution1D *DistributionNoneItem::createDistribution() const
{
    return 0;
}

void DistributionNoneItem::init_parameters(double value, PropertyAttribute attribute)
{
    setRegisteredProperty(DistributionNoneItem::P_VALUE, value);
    setPropertyAttribute(DistributionNoneItem::P_VALUE, attribute);
}

/* ------------------------------------------------ */

const QString DistributionGateItem::P_MIN = "Minimum";
const QString DistributionGateItem::P_MAX = "Maximum";

DistributionGateItem::DistributionGateItem(ParameterizedItem *parent)
    : DistributionItem(Constants::DistributionGateType, parent)
{
    setItemName(Constants::DistributionGateType);
    registerProperty(P_MIN, 0.0);
    registerProperty(P_MAX, 1.0);
    register_number_of_samples();
}

IDistribution1D *DistributionGateItem::createDistribution() const
{
    double min = getRegisteredProperty(P_MIN).toDouble();
    double max = getRegisteredProperty(P_MAX).toDouble();
    return new DistributionGate(min, max);
}

void DistributionGateItem::init_parameters(double value, PropertyAttribute attribute)
{
    setRegisteredProperty(P_MIN, value - 0.1*value);
    setPropertyAttribute(P_MIN, attribute);
    setRegisteredProperty(P_MAX, value + 0.1*value);
    setPropertyAttribute(P_MAX, attribute);
}

/* ------------------------------------------------ */

const QString DistributionLorentzItem::P_MEAN = "Mean";
const QString DistributionLorentzItem::P_HWHM = "HWHM";

DistributionLorentzItem::DistributionLorentzItem(ParameterizedItem *parent)
    : DistributionItem(Constants::DistributionLorentzType, parent)
{
    setItemName(Constants::DistributionLorentzType);
    registerProperty(P_MEAN, 0.0);
    registerProperty(P_HWHM, 1.0);
    register_number_of_samples();
    register_sigma_factor();
}

IDistribution1D *DistributionLorentzItem::createDistribution() const
{
    double mean = getRegisteredProperty(P_MEAN).toDouble();
    double hwhm = getRegisteredProperty(P_HWHM).toDouble();
    return new DistributionLorentz(mean, hwhm);
}

void DistributionLorentzItem::init_parameters(double value, PropertyAttribute attribute)
{
    setRegisteredProperty(P_MEAN, value);
    setPropertyAttribute(P_MEAN, attribute);
    setRegisteredProperty(P_HWHM, 0.1*value);
    setPropertyAttribute(P_HWHM, attribute);
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
    register_number_of_samples();
    register_sigma_factor();
}

IDistribution1D *DistributionGaussianItem::createDistribution() const
{
    double mean = getRegisteredProperty(P_MEAN).toDouble();
    double std_dev = getRegisteredProperty(P_STD_DEV).toDouble();
    return new DistributionGaussian(mean, std_dev);
}

void DistributionGaussianItem::init_parameters(double value, PropertyAttribute attribute)
{
    setRegisteredProperty(P_MEAN, value);
    setPropertyAttribute(P_MEAN, attribute);
    setRegisteredProperty(P_STD_DEV, 0.1*value);
    setPropertyAttribute(P_STD_DEV, attribute);
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
    register_number_of_samples();
    register_sigma_factor();
}

IDistribution1D *DistributionLogNormalItem::createDistribution() const
{
    double median = getRegisteredProperty(P_MEDIAN).toDouble();
    double scale_par = getRegisteredProperty(P_SCALE_PAR).toDouble();
    return new DistributionLogNormal(median, scale_par);
}

void DistributionLogNormalItem::init_parameters(double value, PropertyAttribute attribute)
{
    setRegisteredProperty(P_MEDIAN, value);
    setPropertyAttribute(P_MEDIAN, attribute);
    setRegisteredProperty(P_SCALE_PAR, 0.1*value);
    setPropertyAttribute(P_SCALE_PAR, attribute);
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
    register_number_of_samples();
    register_sigma_factor();
}

IDistribution1D *DistributionCosineItem::createDistribution() const
{
    double mean = getRegisteredProperty(P_MEAN).toDouble();
    double sigma = getRegisteredProperty(P_SIGMA).toDouble();
    return new DistributionCosine(mean, sigma);
}

void DistributionCosineItem::init_parameters(double value, PropertyAttribute attribute)
{
    setRegisteredProperty(P_MEAN, value);
    setPropertyAttribute(P_MEAN, attribute);
    setRegisteredProperty(P_SIGMA, 0.1*value);
    setPropertyAttribute(P_SIGMA, attribute);
}
