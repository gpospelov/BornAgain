// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaskWidgets/MaskUnitsConverter.h
//! @brief     Defines class MaskUnitsConverter
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef MASKUNITSCONVERTER_H
#define MASKUNITSCONVERTER_H

#include "WinDllMacros.h"

class IntensityDataItem;
class SessionItem;
class IAxis;
template<class T> class OutputData;
class QString;

//! The MaskUnitsConverter converts coordinates of all masks from one units to anoter.
//! I.e. masks in 'mm' into masks in 'deg'. This is done in two steps.
//! On first step masks are converted from native coordinates (as given by axes of OutputData)
//! into bin-fraction coordinates.
//! On second step masks are converted from bin-fraction coordinates into current axes of OutputData.

class BA_CORE_API_ MaskUnitsConverter
{
public:
    enum EConvertionDirection {TO_NBINS, FROM_NBINS, UNDEFINED};

    MaskUnitsConverter();

    void convertToNbins(IntensityDataItem *intensityData);
    void convertFromNbins(IntensityDataItem *intensityData);

private:
    void convertIntensityDataItem(IntensityDataItem *intensityData);
    void convertMask(SessionItem *maskItem);

    void convertCoordinate(SessionItem *maskItem, const QString &xname,
                       const QString &yname);

    double convert(double value, int axis_index);

    const OutputData<double> *mp_data;
    EConvertionDirection m_direction;
};

#endif // MASKUNITSCONVERTER_H
