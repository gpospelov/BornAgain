// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/ColorMapUtils.h
//! @brief     Defines ColorMapUtils namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef COLORMAPUTILS_H
#define COLORMAPUTILS_H

#include "WinDllMacros.h"
#include "qcustomplot.h"
#include <QMap>
#include <QString>

class IntensityDataItem;

//! Provides few helper functions for ColorMapPlot.

namespace ColorMapUtils
{

BA_CORE_API_ QCPColorGradient getGradient(const QString& gradientName);
BA_CORE_API_ QCPColorGradient itemGradient(const IntensityDataItem* item);

BA_CORE_API_ QCPRange itemXrange(const IntensityDataItem* item);
BA_CORE_API_ QCPRange itemYrange(const IntensityDataItem* item);
BA_CORE_API_ QCPRange itemDataRange(const IntensityDataItem* item);
}

#endif // COLORMAPUTILS_H
