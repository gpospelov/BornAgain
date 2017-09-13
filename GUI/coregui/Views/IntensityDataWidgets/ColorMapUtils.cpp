// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/ColorMapUtils.cpp
//! @brief     Implements ColorMapUtils namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ColorMapUtils.h"
#include "GUIHelpers.h"
#include "IntensityDataItem.h"
#include "item_constants.h"

using gradient_map_t = QMap<QString, QCPColorGradient::GradientPreset>;

namespace {
gradient_map_t createGradientMap() {
    gradient_map_t result;

    result[Constants::GRADIENT_GRAYSCALE] = QCPColorGradient::gpGrayscale;
    result[Constants::GRADIENT_HOT] = QCPColorGradient::gpHot;
    result[Constants::GRADIENT_COLD] = QCPColorGradient::gpCold;
    result[Constants::GRADIENT_NIGHT] = QCPColorGradient::gpNight;
    result[Constants::GRADIENT_CANDY] = QCPColorGradient::gpCandy;
    result[Constants::GRADIENT_GEOGRAPHY] = QCPColorGradient::gpGeography;
    result[Constants::GRADIENT_ION] = QCPColorGradient::gpIon;
    result[Constants::GRADIENT_THERMAL] = QCPColorGradient::gpThermal;
    result[Constants::GRADIENT_POLAR] = QCPColorGradient::gpPolar;
    result[Constants::GRADIENT_SPECTRUM] = QCPColorGradient::gpSpectrum;
    result[Constants::GRADIENT_JET] = QCPColorGradient::gpJet;
    result[Constants::GRADIENT_HUES] = QCPColorGradient::gpHues;

    return result;
}

// Converts xmin (low edge of first bin) and xmax (upper edge of last bin) to the
// range expected by QCPColorMapData::setRange.
QCPRange qcpRange(double xmin, double xmax, int nbins) {
    double dx = (xmax-xmin)/nbins;
    return QCPRange(xmin+dx/2., xmax-dx/2.);
}

}

QCPColorGradient ColorMapUtils::getGradient(const QString& gradientName)
{
    static gradient_map_t gradient_map = createGradientMap();

    auto it = gradient_map.find(gradientName);
    if (it == gradient_map.end()) {
        throw GUIHelpers::Error("ColorMapHelper::getGradient() -> Error. No such gradient"
                                + gradientName);
    }
    return QCPColorGradient(it.value());
}

QCPColorGradient ColorMapUtils::itemGradient(const IntensityDataItem* item)
{
    return getGradient(item->getGradient());
}

QCPRange ColorMapUtils::itemXrange(const IntensityDataItem* item)
{
    return qcpRange(item->getXmin(), item->getXmax(), item->getNbinsX());
}

QCPRange ColorMapUtils::itemZoomX(const IntensityDataItem* item)
{
    return QCPRange(item->getLowerX(), item->getUpperX());
}

QCPRange ColorMapUtils::itemYrange(const IntensityDataItem* item)
{
    return qcpRange(item->getYmin(), item->getYmax(), item->getNbinsY());
}

QCPRange ColorMapUtils::itemZoomY(const IntensityDataItem* item)
{
    return QCPRange(item->getLowerY(), item->getUpperY());
}

QCPRange ColorMapUtils::itemDataRange(const IntensityDataItem* item)
{
    QPair<double, double> range = item->dataRange();
    return QCPRange(range.first, range.second);
}

QCPRange ColorMapUtils::itemDataZoom(const IntensityDataItem* item)
{
    return QCPRange(item->getLowerZ(), item->getUpperZ());
}

void ColorMapUtils::setLogz(QCPColorScale* scale, bool isLogz)
{
    if (isLogz && scale->dataScaleType() != QCPAxis::stLogarithmic)
        scale->setDataScaleType(QCPAxis::stLogarithmic);

    else if (!isLogz && scale->dataScaleType() != QCPAxis::stLinear)
        scale->setDataScaleType(QCPAxis::stLinear);

    setLogz(scale->axis(), isLogz);
}

void ColorMapUtils::setLogz(QCPAxis* axis, bool isLogz)
{
    if (isLogz) {
        axis->setNumberFormat("eb");
        axis->setNumberPrecision(0);
        axis->setScaleType(QCPAxis::stLogarithmic);
        QSharedPointer<QCPAxisTicker> ticker(new QCPAxisTickerLog);
        axis->setTicker(ticker);
    } else  {
        axis->setNumberFormat("f");
        axis->setNumberPrecision(0);
        axis->setScaleType(QCPAxis::stLinear);
        QSharedPointer<QCPAxisTicker> ticker(new QCPAxisTicker);
        axis->setTicker(ticker);
    }
}
