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

//! Returns x-axis range.
BA_CORE_API_ QCPRange itemXrange(const IntensityDataItem* item);

//! Returns x-axis vizible range (zoom).
BA_CORE_API_ QCPRange itemZoomX(const IntensityDataItem* item);

//! Returns y-axis range.
BA_CORE_API_ QCPRange itemYrange(const IntensityDataItem* item);

//! Returns y-axis vizible range (zoom).
BA_CORE_API_ QCPRange itemZoomY(const IntensityDataItem* item);

//! Returns z-axis data range.
BA_CORE_API_ QCPRange itemDataRange(const IntensityDataItem* item);

//! Returns z-axis visible range (zoom).
BA_CORE_API_ QCPRange itemDataZoom(const IntensityDataItem* item);

BA_CORE_API_ void setLogz(QCPColorScale* scale, bool isLogz);
BA_CORE_API_ void setLogz(QCPAxis* axis, bool isLogz);
}

#endif // COLORMAPUTILS_H
