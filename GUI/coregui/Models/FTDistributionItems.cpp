#include "FTDistributionItems.h"


FTDistribution2DCauchyItem::FTDistribution2DCauchyItem(ParameterizedItem *parent)
    : FTDistribution2DItem(QString("FTDistribution2DCauchy"), parent)
{
    setItemName("FTDistribution2DCauchy");
    setProperty("Corr_length_x", 1.0);
    setProperty("Corr_length_y", 1.0);
}

IFTDistribution2D *FTDistribution2DCauchyItem::createFTDistribution() const
{
    return new FTDistribution2DCauchy(
                property("Corr_length_x").toDouble(),
                property("Corr_length_y").toDouble()
                );
}


FTDistribution2DGaussItem::FTDistribution2DGaussItem(ParameterizedItem *parent)
    : FTDistribution2DItem(QString("FTDistribution2DGauss"), parent)
{
    setItemName("FTDistribution2DGauss");
    setProperty("Corr_length_x", 1.0);
    setProperty("Corr_length_y", 1.0);
}

IFTDistribution2D *FTDistribution2DGaussItem::createFTDistribution() const
{
    return new FTDistribution2DGauss(
                property("Corr_length_x").toDouble(),
                property("Corr_length_y").toDouble()
                );
}


FTDistribution2DVoigtItem::FTDistribution2DVoigtItem(ParameterizedItem *parent)
    : FTDistribution2DItem(QString("FTDistribution2DVoigt"), parent)
{
    setItemName("FTDistribution2DVoigt");
    setProperty("Corr_length_x", 1.0);
    setProperty("Corr_length_y", 1.0);
    setProperty("Eta", 0.0);
}

IFTDistribution2D *FTDistribution2DVoigtItem::createFTDistribution() const
{
    return new FTDistribution2DVoigt(
                property("Corr_length_x").toDouble(),
                property("Corr_length_y").toDouble(),
                property("Eta").toDouble()
                );
}

