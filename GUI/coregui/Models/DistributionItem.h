// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/DistributionItem.h
//! @brief     Declares class DistributionItem and several subclasses
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef DISTRIBUTIONITEM_H
#define DISTRIBUTIONITEM_H

#include "SessionItem.h"


class IDistribution1D;

class BA_CORE_API_ DistributionItem : public SessionItem
{

public:
    static const QString P_NUMBER_OF_SAMPLES;
    static const QString P_SIGMA_FACTOR;
    static const QString P_IS_INITIALIZED;
    explicit DistributionItem(const QString name);
    virtual std::unique_ptr<IDistribution1D> createDistribution() const=0;

    void init_parameters(double);
protected:
    virtual void init_distribution(double){}
    void register_number_of_samples();
    void register_sigma_factor();
};

class BA_CORE_API_ DistributionNoneItem : public DistributionItem
{

public:
    static const QString P_VALUE;
    explicit DistributionNoneItem();
    virtual std::unique_ptr<IDistribution1D> createDistribution() const;
    virtual void init_distribution(double value);
};


class BA_CORE_API_ DistributionGateItem : public DistributionItem
{

public:
    static const QString P_MIN;
    static const QString P_MAX;
    explicit DistributionGateItem();

    virtual std::unique_ptr<IDistribution1D> createDistribution() const;
    virtual void init_distribution(double value);
};


class BA_CORE_API_ DistributionLorentzItem : public DistributionItem
{

public:
    static const QString P_MEAN;
    static const QString P_HWHM;
    explicit DistributionLorentzItem();

    virtual std::unique_ptr<IDistribution1D> createDistribution() const;
    virtual void init_distribution(double value);
};


class BA_CORE_API_ DistributionGaussianItem : public DistributionItem
{

public:
    static const QString P_MEAN;
    static const QString P_STD_DEV;
    explicit DistributionGaussianItem();

    virtual std::unique_ptr<IDistribution1D> createDistribution() const;
    virtual void init_distribution(double value);
};


class BA_CORE_API_ DistributionLogNormalItem : public DistributionItem
{

public:
    static const QString P_MEDIAN;
    static const QString P_SCALE_PAR;
    explicit DistributionLogNormalItem();

    virtual std::unique_ptr<IDistribution1D> createDistribution() const;
    virtual void init_distribution(double value);
};


class BA_CORE_API_ DistributionCosineItem : public DistributionItem
{

public:
    static const QString P_MEAN;
    static const QString P_SIGMA;
    explicit DistributionCosineItem();

    virtual std::unique_ptr<IDistribution1D> createDistribution() const;
    virtual void init_distribution(double value);
};

#endif // DISTRIBUTIONITEM_H
