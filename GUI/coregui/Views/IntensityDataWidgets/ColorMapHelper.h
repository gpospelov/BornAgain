// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/ColorMapHelper.h
//! @brief     Declares class ColorMapHelper
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef COLORMAPHELPER_H
#define COLORMAPHELPER_H

#include <QMap>
#include <QString>
#include "WinDllMacros.h"
#include "qcustomplot.h"

class IntensityDataItem;

//! The ColorMapHelper class provides few helper functions for ColorMapPlot.

class BA_CORE_API_ ColorMapHelper
{
public:
    typedef QMap<QString, QCPColorGradient::GradientPreset> gradient_map_t;

    static QCPColorGradient getGradient(const QString &gradientName);
    static QCPColorGradient itemGradient(const IntensityDataItem *item);

    static QCPRange itemXrange(const IntensityDataItem *item);
    static QCPRange itemYrange(const IntensityDataItem *item);
    static QCPRange itemDataRange(const IntensityDataItem *item);


private:
    //!< GUI name of the gradient to QCPColorGradient::GradientPreset;
    static gradient_map_t m_gradient_map;
};

#endif // COLORMAPHELPER_H
