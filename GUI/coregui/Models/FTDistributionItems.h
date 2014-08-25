#ifndef FTDISTRIBUTIONITEMS_H
#define FTDISTRIBUTIONITEMS_H


#include "ParameterizedItem.h"
#include "FTDistributions.h"


class FTDistribution1DItem : public ParameterizedItem
{
    Q_OBJECT
public:
    static const QString P_CORR_LENGTH;
    explicit FTDistribution1DItem(const QString name, ParameterizedItem *parent)
        : ParameterizedItem(name, parent){}
    virtual IFTDistribution1D *createFTDistribution() const { return 0;}
    virtual ~FTDistribution1DItem(){}
};

class FTDistribution1DCauchyItem : public FTDistribution1DItem
{
    Q_OBJECT
public:
    explicit FTDistribution1DCauchyItem(ParameterizedItem *parent=0);
    virtual IFTDistribution1D *createFTDistribution() const;
};

class FTDistribution1DGaussItem : public FTDistribution1DItem
{
    Q_OBJECT
public:
    explicit FTDistribution1DGaussItem(ParameterizedItem *parent=0);
    virtual IFTDistribution1D *createFTDistribution() const;
};

class FTDistribution1DGateItem : public FTDistribution1DItem
{
    Q_OBJECT
public:
    explicit FTDistribution1DGateItem(ParameterizedItem *parent=0);
    virtual IFTDistribution1D *createFTDistribution() const;
};

class FTDistribution1DTriangleItem : public FTDistribution1DItem
{
    Q_OBJECT
public:
    explicit FTDistribution1DTriangleItem(ParameterizedItem *parent=0);
    virtual IFTDistribution1D *createFTDistribution() const;
};

class FTDistribution1DCosineItem : public FTDistribution1DItem
{
    Q_OBJECT
public:
    explicit FTDistribution1DCosineItem(ParameterizedItem *parent=0);
    virtual IFTDistribution1D *createFTDistribution() const;
};

class FTDistribution1DVoigtItem : public FTDistribution1DItem
{
    Q_OBJECT
public:
    static const QString P_ETA;
    explicit FTDistribution1DVoigtItem(ParameterizedItem *parent=0);
    virtual IFTDistribution1D *createFTDistribution() const;
};

class FTDistribution2DItem : public ParameterizedItem
{
    Q_OBJECT
public:
    static const QString P_CORR_LENGTH_X, P_CORR_LENGTH_Y, P_GAMMA;
    explicit FTDistribution2DItem(const QString name, ParameterizedItem *parent)
        : ParameterizedItem(name, parent) {
        registerProperty(P_GAMMA, 0.0);
    }
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


class FTDistribution2DGateItem : public FTDistribution2DItem
{
    Q_OBJECT
public:
    explicit FTDistribution2DGateItem(ParameterizedItem *parent=0);
    virtual IFTDistribution2D *createFTDistribution() const;
};


class FTDistribution2DConeItem : public FTDistribution2DItem
{
    Q_OBJECT
public:
    explicit FTDistribution2DConeItem(ParameterizedItem *parent=0);
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

