// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/CoreShellParticleBuilder.cpp
//! @brief     Implements class CoreShellParticleBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "CoreShellParticleBuilder.h"
#include "MultiLayer.h"
#include "ParticleLayout.h"
#include "Materials.h"
#include "Units.h"
#include "FormFactorBox.h"
#include "InterferenceFunctionNone.h"
#include "ParticleCoreShell.h"

CoreShellParticleBuilder::CoreShellParticleBuilder()
{
}


ISample *CoreShellParticleBuilder::buildSample() const
{
    MultiLayer *multi_layer = new MultiLayer();

    HomogeneousMaterial air_material("Air", 0.0, 0.0);

    complex_t n_particle_shell(1.0-1e-4, 2e-8);
    complex_t n_particle_core(1.0-6e-5, 2e-8);

    HomogeneousMaterial shell_material("Shell", n_particle_shell);
    HomogeneousMaterial core_material("Core", n_particle_core);

    Layer air_layer(air_material);

    FormFactorBox ff_box1(16*Units::nanometer, 16*Units::nanometer, 8*Units::nanometer);
    Particle shell_particle(shell_material, ff_box1);

    FormFactorBox ff_box2(12*Units::nanometer, 12*Units::nanometer, 7*Units::nanometer);
    Particle core_particle(core_material, ff_box2);

    kvector_t core_position(0.0, 0.0, 0.0);
    ParticleCoreShell particle(shell_particle, core_particle, core_position);
    ParticleLayout particle_layout(particle);
    particle_layout.addInterferenceFunction(new InterferenceFunctionNone());

    air_layer.addLayout(particle_layout);

    multi_layer->addLayer(air_layer);
    return multi_layer;
}

