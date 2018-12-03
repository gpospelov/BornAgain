// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/DepthProbeInstrumentItem.h
//! @brief     Defines DepthProbeInstrumentItem class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef DEPTHPROBEINSTRUMENTITEM_H
#define DEPTHPROBEINSTRUMENTITEM_H

#include "InstrumentItems.h"

//! Depth probe instrument.

class BA_CORE_API_ DepthProbeInstrumentItem : public InstrumentItem
{
public:
    static const QString P_BEAM;
    static const QString P_ZAXIS;

    DepthProbeInstrumentItem();

    SpecularBeamItem* beamItem() const override;

    std::unique_ptr<Instrument> createInstrument() const override;
    std::vector<int> shape() const override;
    void setShape(const std::vector<int>&) override;
};

#endif
