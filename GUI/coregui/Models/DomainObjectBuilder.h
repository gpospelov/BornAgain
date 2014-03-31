// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Models/DomainObjectBuilder.h
//! @brief     Defines class DomainObjectBuilder.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef DOMAINOBJECTBUILDER_H
#define DOMAINOBJECTBUILDER_H

#include "Samples.h"
#include "ParameterizedItem.h"

class DomainObjectBuilder
{
public:
    explicit DomainObjectBuilder();
    ~DomainObjectBuilder();

    void buildItem(const ParameterizedItem &item);

    const ISample *getSample() const {
        return mp_sample;
    }

private:
    MultiLayer *buildMultiLayer(const ParameterizedItem &item) const;
    Layer *buildLayer(const ParameterizedItem &item) const;
    ParticleLayout *buildParticleLayout(const ParameterizedItem &item) const;
    ISample *mp_sample;
};

#endif // DOMAINOBJECTBUILDER_H
