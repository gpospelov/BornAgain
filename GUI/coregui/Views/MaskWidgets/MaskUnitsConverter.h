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
//! I.e. masks in 'mm' into masks in 'deg'.

class BA_CORE_API_ MaskUnitsConverter
{
public:

    void convertToNbins(IntensityDataItem *intensityData);
    void convertFromNbins(IntensityDataItem *intensityData);

private:
    void convertMaskToNbins(SessionItem *maskItem, const OutputData<double> *data);
    void convertMaskFromNbins(SessionItem *maskItem, const OutputData<double> *data);

    void convertToBinf(SessionItem *maskItem, const QString &xname,
                       const QString &yname, const OutputData<double> *data);

    void convertFromBinf(SessionItem *maskItem, const QString &xname,
                         const QString &yname, const OutputData<double> *data);
};


#endif
