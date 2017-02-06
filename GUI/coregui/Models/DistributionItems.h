// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/DistributionItems.h
//! @brief     Defines class DistributionItem and several subclasses
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef DISTRIBUTIONITEMS_H
#define DISTRIBUTIONITEMS_H

#include "SessionItem.h"

class IDistribution1D;

class BA_CORE_API_ DistributionItem : public SessionItem
{
public:
    static const QString P_NUMBER_OF_SAMPLES;
    static const QString P_SIGMA_FACTOR;
    static const QString P_IS_INITIALIZED;
    static const QString P_LIMITS;
    explicit DistributionItem(const QString& name);

    virtual std::unique_ptr<IDistribution1D> createDistribution(double scale = 1.0) const=0;
    void init_parameters(double);

protected:
    virtual void init_distribution(double){}
    void register_number_of_samples();
    void register_sigma_factor();
    void register_limits();
};

class BA_CORE_API_ DistributionNoneItem : public DistributionItem
{

public:
    static const QString P_VALUE;
    DistributionNoneItem();

    virtual std::unique_ptr<IDistribution1D> createDistribution(double scale = 1.0) const;
    virtual void init_distribution(double value);
};

class BA_CORE_API_ DistributionGateItem : public DistributionItem
{
public:
    static const QString P_MIN;
    static const QString P_MAX;
    DistributionGateItem();

    virtual std::unique_ptr<IDistribution1D> createDistribution(double scale = 1.0) const;
    virtual void init_distribution(double value);
};


class BA_CORE_API_ DistributionLorentzItem : public DistributionItem
{
public:
    static const QString P_MEAN;
    static const QString P_HWHM;
    DistributionLorentzItem();

    virtual std::unique_ptr<IDistribution1D> createDistribution(double scale = 1.0) const;
    virtual void init_distribution(double value);
};

class BA_CORE_API_ DistributionGaussianItem : public DistributionItem
{
public:
    static const QString P_MEAN;
    static const QString P_STD_DEV;
    DistributionGaussianItem();

    virtual std::unique_ptr<IDistribution1D> createDistribution(double scale = 1.0) const;
    virtual void init_distribution(double value);
};

class BA_CORE_API_ DistributionLogNormalItem : public DistributionItem
{

public:
    static const QString P_MEDIAN;
    static const QString P_SCALE_PAR;
    DistributionLogNormalItem();

    virtual std::unique_ptr<IDistribution1D> createDistribution(double scale = 1.0) const;
    virtual void init_distribution(double value);
};


class BA_CORE_API_ DistributionCosineItem : public DistributionItem
{
public:
    static const QString P_MEAN;
    static const QString P_SIGMA;
    DistributionCosineItem();

    virtual std::unique_ptr<IDistribution1D> createDistribution(double scale = 1.0) const;
    virtual void init_distribution(double value);
};

#endif // DISTRIBUTIONITEMS_H
