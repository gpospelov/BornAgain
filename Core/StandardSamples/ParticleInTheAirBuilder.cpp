// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/ParticleInTheAirBuilder.cpp
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
#include "Exceptions.h"
#include "HomogeneousMaterial.h"
#include "Layer.h"
#include "MultiLayer.h"
#include "Particle.h"
#include "ParticleLayout.h"
#include "RealParameter.h"
#include "FormFactors.h"
#include "SampleComponents.h"
#include "Units.h"

ParticleInTheAirBuilder::ParticleInTheAirBuilder()
    : m_ff(new FormFactorFullSphere(5.0*Units::nanometer))
{}

ParticleInTheAirBuilder::~ParticleInTheAirBuilder() = default;

MultiLayer* ParticleInTheAirBuilder::buildSample() const
{
    MultiLayer* result = new MultiLayer;

    HomogeneousMaterial air_material("Air", 0.0, 0.0);
    HomogeneousMaterial particle_material("Particle", 6e-4, 2e-8);

    Layer air_layer(air_material);

    Particle particle(particle_material, *m_ff);
    ParticleLayout particle_layout(particle);
    air_layer.addLayout(particle_layout);

    result->addLayer(air_layer);

    return result;
}

MultiLayer* ParticleInTheAirBuilder::createSample(size_t index)
{
    if(index >= size())
        throw std::runtime_error("ParticleInTheAirBuilder::createSample() -> Error. "
                                 "Sample index is out of range.");

    auto ff_names = ff_components().keys();
    m_ff.reset(ff_components().getItem(ff_names[index])->clone());

    setName(ff_names[index]);

    return buildSample();
}

size_t ParticleInTheAirBuilder::size()
{
    return ff_components().size();
}

FormFactorComponents& ParticleInTheAirBuilder::ff_components()
{
    static FormFactorComponents result = FormFactorComponents();
    return result;
}
