// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/ParticleInTheAirBuilder.cpp
//! @brief     Implements class ParticleInTheAirBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ParticleInTheAirBuilder.h"
#include "MultiLayer.h"
#include "HomogeneousMaterial.h"
#include "Particle.h"
#include "ParticleLayout.h"
#include "FutestSuite.h"
#include "Exceptions.h"

ParticleInTheAirBuilder::ParticleInTheAirBuilder()
    : m_form_factor(0)
{
}

ParticleInTheAirBuilder::~ParticleInTheAirBuilder()
{
}

void ParticleInTheAirBuilder::init_from(const FutestSuite* service)
{
    delete m_form_factor;
    m_form_factor = service->getFormFactor();
}

ISample* ParticleInTheAirBuilder::buildSample() const
{
    if(!m_form_factor)
        throw NullPointerException("ParticleInTheAirBuilder::buildSample() -> Error. "
                                   "Form factor is not initialized.");
    MultiLayer* result = new MultiLayer;

    HomogeneousMaterial air_material("Air", 0.0, 0.0);
    HomogeneousMaterial particle_material("Particle", 6e-4, 2e-8);

    Layer air_layer;
    air_layer.setMaterial(air_material);

    Particle particle(particle_material, *m_form_factor);
    ParticleLayout particle_layout(particle);
    air_layer.addLayout(particle_layout);

    result->addLayer(air_layer);

    return result;
}
