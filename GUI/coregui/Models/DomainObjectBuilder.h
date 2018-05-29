// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/DomainObjectBuilder.h
//! @brief     Defines DomainObjectBuilder namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef DOMAINOBJECTBUILDER_H
#define DOMAINOBJECTBUILDER_H

#include "WinDllMacros.h"
#include <memory>

class MultiLayer;
class Layer;
class Instrument;
class ParticleLayout;
class IInterferenceFunction;
class SessionItem;
class InstrumentItem;
class IUnitConverter;

namespace DomainObjectBuilder
{
BA_CORE_API_ std::unique_ptr<MultiLayer> buildMultiLayer(const SessionItem& multilayer_item);
BA_CORE_API_ std::unique_ptr<Layer> buildLayer(const SessionItem& item);
BA_CORE_API_ std::unique_ptr<ParticleLayout> buildParticleLayout(const SessionItem& item);
BA_CORE_API_ std::unique_ptr<IInterferenceFunction>
buildInterferenceFunction(const SessionItem& item);
BA_CORE_API_ std::unique_ptr<Instrument> buildInstrument(const InstrumentItem& instrumentItem);

//! Creates a unit converter corresponding to the given instrument item
BA_CORE_API_ std::unique_ptr<IUnitConverter>
createUnitConverter(const InstrumentItem* instrumentItem);
};

#endif // DOMAINOBJECTBUILDER_H
