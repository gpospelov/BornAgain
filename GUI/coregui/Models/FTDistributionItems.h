#ifndef FTDISTRIBUTIONITEMS_H
#define FTDISTRIBUTIONITEMS_H


#include "ParameterizedItem.h"
#include "FTDistributions.h"


class FTDistribution2DItem : public ParameterizedItem
{
    Q_OBJECT
public:
    static const QString P_CORR_LENGTH_X, P_CORR_LENGTH_Y;
    explicit FTDistribution2DItem(const QString name, ParameterizedItem *parent) : ParameterizedItem(name, parent){}
    virtual IFTDistribution2D *createFTDistribution() const { return 0;}
    virtual ~FTDistribution2DItem(){}
};


class FTDistribution2DCauchyItem : public FTDistribution2DItem
{
    Q_OBJECT
public:
    explicit FTDistribution2DCauchyItem(ParameterizedItem *parent=0);
    virtual IFTDistribution2D *createFTDistribution() const;
};


class FTDistribution2DGaussItem : public FTDistribution2DItem
{
    Q_OBJECT
public:
    explicit FTDistribution2DGaussItem(ParameterizedItem *parent=0);
    virtual IFTDistribution2D *createFTDistribution() const;
};


class FTDistribution2DVoigtItem : public FTDistribution2DItem
{
    Q_OBJECT
public:
    static const QString P_ETA;
    explicit FTDistribution2DVoigtItem(ParameterizedItem *parent=0);
    virtual IFTDistribution2D *createFTDistribution() const;
};


#endif

