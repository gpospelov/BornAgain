#include "FTDistributionItems.h"


const QString FTDistribution2DItem::P_CORR_LENGTH_X = "Corr_length_x";
const QString FTDistribution2DItem::P_CORR_LENGTH_Y = "Corr_length_y";
const QString FTDistribution2DVoigtItem::P_ETA = "Eta";


FTDistribution2DCauchyItem::FTDistribution2DCauchyItem(ParameterizedItem *parent)
    : FTDistribution2DItem(QString("FTDistribution2DCauchy"), parent)
{
    setItemName("FTDistribution2DCauchy");
    registerProperty(P_CORR_LENGTH_X, 1.0);
    registerProperty(P_CORR_LENGTH_Y, 1.0);
}

IFTDistribution2D *FTDistribution2DCauchyItem::createFTDistribution() const
{
    return new FTDistribution2DCauchy(
                getRegisteredProperty(P_CORR_LENGTH_X).toDouble(),
                getRegisteredProperty(P_CORR_LENGTH_Y).toDouble()
                );
}


FTDistribution2DGaussItem::FTDistribution2DGaussItem(ParameterizedItem *parent)
    : FTDistribution2DItem(QString("FTDistribution2DGauss"), parent)
{
    setItemName("FTDistribution2DGauss");
    registerProperty(P_CORR_LENGTH_X, 1.0);
    registerProperty(P_CORR_LENGTH_Y, 1.0);
}

IFTDistribution2D *FTDistribution2DGaussItem::createFTDistribution() const
{
    return new FTDistribution2DGauss(
                getRegisteredProperty(P_CORR_LENGTH_X).toDouble(),
                getRegisteredProperty(P_CORR_LENGTH_Y).toDouble()
                );
}


FTDistribution2DGateItem::FTDistribution2DGateItem(ParameterizedItem *parent)
    : FTDistribution2DItem(QString("FTDistribution2DGate"), parent)
{
    setItemName("FTDistribution2DGate");
    registerProperty(P_CORR_LENGTH_X, 1.0);
    registerProperty(P_CORR_LENGTH_Y, 1.0);
}

IFTDistribution2D *FTDistribution2DGateItem::createFTDistribution() const
{
    return new FTDistribution2DGate(
                getRegisteredProperty(P_CORR_LENGTH_X).toDouble(),
                getRegisteredProperty(P_CORR_LENGTH_Y).toDouble()
                );
}


FTDistribution2DConeItem::FTDistribution2DConeItem(ParameterizedItem *parent)
    : FTDistribution2DItem(QString("FTDistribution2DCone"), parent)
{
    setItemName("FTDistribution2DCone");
    registerProperty(P_CORR_LENGTH_X, 1.0);
    registerProperty(P_CORR_LENGTH_Y, 1.0);
}

IFTDistribution2D *FTDistribution2DConeItem::createFTDistribution() const
{
    return new FTDistribution2DCone(
                getRegisteredProperty(P_CORR_LENGTH_X).toDouble(),
                getRegisteredProperty(P_CORR_LENGTH_Y).toDouble()
                );
}


FTDistribution2DVoigtItem::FTDistribution2DVoigtItem(ParameterizedItem *parent)
    : FTDistribution2DItem(QString("FTDistribution2DVoigt"), parent)
{
    setItemName("FTDistribution2DVoigt");
    registerProperty(P_CORR_LENGTH_X, 1.0);
    registerProperty(P_CORR_LENGTH_Y, 1.0);
    registerProperty(P_ETA, 0.5);
}

IFTDistribution2D *FTDistribution2DVoigtItem::createFTDistribution() const
{
    return new FTDistribution2DVoigt(
                getRegisteredProperty(P_CORR_LENGTH_X).toDouble(),
                getRegisteredProperty(P_CORR_LENGTH_Y).toDouble(),
                getRegisteredProperty(P_ETA).toDouble()
                );
}

