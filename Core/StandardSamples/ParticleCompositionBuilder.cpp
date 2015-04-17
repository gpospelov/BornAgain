// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/ParticleCompositionBuilder.cpp
//! @brief     Implements class ParticleCompositionBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ParticleCompositionBuilder.h"
#include "FormFactorPyramid.h"
#include "InterferenceFunctionNone.h"
#include "Materials.h"
#include "MultiLayer.h"
#include "ParticleLayout.h"
#include "Units.h"


// ----------------------------------------------------------------------------
// Pyramids on top of substrate
// ----------------------------------------------------------------------------
ParticleCompositionBuilder::ParticleCompositionBuilder()
{
}


ISample *ParticleCompositionBuilder::buildSample() const
{
    MultiLayer *multi_layer = new MultiLayer();

    HomogeneousMaterial air_material("Air", 0.0, 0.0);
    HomogeneousMaterial substrate_material("Substrate", 6e-6, 2e-8);
    HomogeneousMaterial particle_material("Particle", 6e-4, 2e-8);

    Layer air_layer(air_material);
    Layer substrate_layer(substrate_material);

    FormFactorPyramid ff_pyramid(1.0, 1.0, 0.12);

    Particle particle(particle_material, ff_pyramid);
    ParticleLayout particle_layout(particle);

    particle_layout.addInterferenceFunction(new InterferenceFunctionNone());

    air_layer.addLayout(particle_layout);

    multi_layer->addLayer(air_layer);
    multi_layer->addLayer(substrate_layer);

    return multi_layer;
}
