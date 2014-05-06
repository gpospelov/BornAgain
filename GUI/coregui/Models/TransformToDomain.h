// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Models/TransformToDomain.h
//! @brief     Defines functions to transform items to domain objects.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef TRANSFORMTODOMAIN_H
#define TRANSFORMTODOMAIN_H

#include "Samples.h"
#include "InterferenceFunctions.h"
#include "ParameterizedItem.h"

namespace TransformToDomain
{
IMaterial *createDomainMaterial(const ParameterizedItem &item);
MultiLayer *createMultiLayer(const ParameterizedItem &item);
Layer *createLayer(const ParameterizedItem &item);
ParticleLayout *createParticleLayout(const ParameterizedItem &item);
Particle *createParticle(const ParameterizedItem &item, double &depth, double &abundance);
IFormFactor *createFormFactor(const ParameterizedItem &item);
IInterferenceFunction *createInterferenceFunction(const ParameterizedItem &item);
}

#endif // TRANSFORMTODOMAIN_H
