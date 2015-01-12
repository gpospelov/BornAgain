// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Models/DistributionItem.h
//! @brief     Defines class DistributionItem.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef DISTRIBUTIONITEM_H
#define DISTRIBUTIONITEM_H

#include "ParameterizedItem.h"
#include "Distributions.h"

class BA_CORE_API_ DistributionItem : public ParameterizedItem
{
    Q_OBJECT
public:
    explicit DistributionItem(const QString name, ParameterizedItem *parent=0)
        : ParameterizedItem(name, parent) {}
    virtual ~DistributionItem() {}

    virtual IDistribution1D *createDistribution() const=0;
};


class BA_CORE_API_ DistributionGateItem : public DistributionItem
{
    Q_OBJECT
public:
    static const QString P_MIN;
    static const QString P_MAX;
    explicit DistributionGateItem(ParameterizedItem *parent=0);

    virtual IDistribution1D *createDistribution() const;
};


class BA_CORE_API_ DistributionLorentzItem : public DistributionItem
{
    Q_OBJECT
public:
    static const QString P_MEAN;
    static const QString P_HWHM;
    explicit DistributionLorentzItem(ParameterizedItem *parent=0);

    virtual IDistribution1D *createDistribution() const;
};


class BA_CORE_API_ DistributionGaussianItem : public DistributionItem
{
    Q_OBJECT
public:
    static const QString P_MEAN;
    static const QString P_STD_DEV;
    explicit DistributionGaussianItem(ParameterizedItem *parent=0);

    virtual IDistribution1D *createDistribution() const;
};


class BA_CORE_API_ DistributionLogNormalItem : public DistributionItem
{
    Q_OBJECT
public:
    static const QString P_MEDIAN;
    static const QString P_SCALE_PAR;
    explicit DistributionLogNormalItem(ParameterizedItem *parent=0);

    virtual IDistribution1D *createDistribution() const;
};


class BA_CORE_API_ DistributionCosineItem : public DistributionItem
{
    Q_OBJECT
public:
    static const QString P_MEAN;
    static const QString P_SIGMA;
    explicit DistributionCosineItem(ParameterizedItem *parent=0);

    virtual IDistribution1D *createDistribution() const;
};

#endif // DISTRIBUTIONITEM_H

