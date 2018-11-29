// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/DepthProbeInstrumentItem.cpp
//! @brief     Implements DepthProbeInstrumentItem class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "DepthProbeInstrumentItem.h"

const QString DepthProbeInstrumentItem::P_BEAM = "Beam";
const QString DepthProbeInstrumentItem::P_ZAXIS = "Z axis";

DepthProbeInstrumentItem::DepthProbeInstrumentItem()
    : SessionItem(Constants::DepthProbeInstrumentType)
{
    setItemName(Constants::DepthProbeInstrumentType);

    addGroupProperty(P_BEAM, Constants::SpecularBeamType);

}
