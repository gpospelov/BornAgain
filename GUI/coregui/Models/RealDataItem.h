// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/RealDataItem.h
//! @brief     Defines class RealDataItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef REALDATAITEM_H
#define REALDATAITEM_H

#include "SessionItem.h"

template <class T> class OutputData;
class IntensityDataItem;
class InstrumentItem;
class GISASInstrumentItem;

//! The RealDataItem class represents intensity data imported from file and intended for fitting.

class BA_CORE_API_ RealDataItem : public SessionItem
{
public:
    static const QString P_INSTRUMENT_ID;
    static const QString P_INSTRUMENT_NAME;
    static const QString T_INTENSITY_DATA;
    RealDataItem();

    IntensityDataItem *intensityDataItem();
    const IntensityDataItem *intensityDataItem() const;

    void setOutputData(OutputData<double> *data);

    void linkToInstrument(const InstrumentItem *instrument, bool make_update = true);

private:
    void updateIntensityDataFileName();
    void updateToInstrument();
    const InstrumentItem *m_linkedInstrument;
};

#endif // REALDATAITEM_H


