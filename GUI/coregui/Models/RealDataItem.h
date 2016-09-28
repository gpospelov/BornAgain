// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/RealDataItem.h
//! @brief     Defines class RealDataItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef REALDATAITEM_H
#define REALDATAITEM_H

#include "SessionItem.h"

template <class T> class OutputData;
class IntensityDataItem;

//! The RealDataItem class represents intensity data imported from file and intended for fitting.

class BA_CORE_API_ RealDataItem : public SessionItem
{
public:
    static const QString T_INTENSITY_DATA;
    explicit RealDataItem();

    IntensityDataItem *intensityDataItem();
    const IntensityDataItem *intensityDataItem() const;

    void setOutputData(OutputData<double> *data);

private:
    void updateIntensityDataFileName();
};

#endif // REALDATAITEM_H


