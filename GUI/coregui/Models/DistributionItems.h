// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/DistributionItems.h
//! @brief     Defines class DistributionItem and several subclasses
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
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

    virtual std::unique_ptr<IDistribution1D> createDistribution(double scale = 1.0) const = 0;
    void init_parameters(double value, const RealLimits& limits=RealLimits::limitless());
    void init_limits_group(const RealLimits& limits, double factor = 1.0);
    virtual void showMean(bool) {}

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

    std::unique_ptr<IDistribution1D> createDistribution(double scale = 1.0) const override;
    void init_distribution(double value) override;
    void showMean(bool flag) override;
};

class BA_CORE_API_ DistributionGateItem : public DistributionItem
{
public:
    static const QString P_MIN;
    static const QString P_MAX;
    DistributionGateItem();

    std::unique_ptr<IDistribution1D> createDistribution(double scale = 1.0) const override;
    void init_distribution(double value) override;
};


class BA_CORE_API_ DistributionLorentzItem : public DistributionItem
{
public:
    static const QString P_MEAN;
    static const QString P_HWHM;
    DistributionLorentzItem();

    std::unique_ptr<IDistribution1D> createDistribution(double scale = 1.0) const override;
    void init_distribution(double value) override;
    void showMean(bool flag) override;
};

class BA_CORE_API_ DistributionGaussianItem : public DistributionItem
{
public:
    static const QString P_MEAN;
    static const QString P_STD_DEV;
    DistributionGaussianItem();

    std::unique_ptr<IDistribution1D> createDistribution(double scale = 1.0) const override;
    void init_distribution(double value) override;
    void showMean(bool flag) override;
};

class BA_CORE_API_ DistributionLogNormalItem : public DistributionItem
{

public:
    static const QString P_MEDIAN;
    static const QString P_SCALE_PAR;
    DistributionLogNormalItem();

    std::unique_ptr<IDistribution1D> createDistribution(double scale = 1.0) const override;
    void init_distribution(double value) override;
    void showMean(bool flag) override;
};


class BA_CORE_API_ DistributionCosineItem : public DistributionItem
{
public:
    static const QString P_MEAN;
    static const QString P_SIGMA;
    DistributionCosineItem();

    std::unique_ptr<IDistribution1D> createDistribution(double scale = 1.0) const override;
    void init_distribution(double value) override;
    void showMean(bool flag) override;
};

class BA_CORE_API_ DistributionTrapezoidItem : public DistributionItem
{
public:
    static const QString P_CENTER;
    static const QString P_LEFTWIDTH;
    static const QString P_MIDDLEWIDTH;
    static const QString P_RIGHTWIDTH;
    DistributionTrapezoidItem();

    std::unique_ptr<IDistribution1D> createDistribution(double scale = 1.0) const override;
    void init_distribution(double value) override;
    void showMean(bool flag) override;
};

#endif // DISTRIBUTIONITEMS_H
