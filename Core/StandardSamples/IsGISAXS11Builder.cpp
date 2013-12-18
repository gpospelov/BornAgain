// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/IsGISAXS11Builder.cpp
//! @brief     Implements class IsGISAXS11Builder.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IsGISAXS11Builder.h"
#include "MultiLayer.h"
#include "ParticleDecoration.h"
#include "MaterialManager.h"
#include "Units.h"
#include "FormFactorParallelepiped.h"
#include "InterferenceFunctionNone.h"
#include "ParticleCoreShell.h"

IsGISAXS11Builder::IsGISAXS11Builder()
{
}


ISample *IsGISAXS11Builder::buildSample() const
{
    MultiLayer *multi_layer = new MultiLayer();

	const IMaterial *p_air_material =
            MaterialManager::getHomogeneousMaterial("Air", 0.0, 0.0);
    Layer air_layer;
    air_layer.setMaterial(p_air_material);

    complex_t n_particle_shell(1.0-1e-4, 2e-8);
    complex_t n_particle_core(1.0-6e-5, 2e-8);

    const IMaterial *shell_material =
            MaterialManager::getHomogeneousMaterial("Shell", n_particle_shell);
    const IMaterial *core_material =
            MaterialManager::getHomogeneousMaterial("Core", n_particle_core);

    Particle shell_particle(shell_material, new FormFactorParallelepiped(
            8*Units::nanometer, 8*Units::nanometer));
    Particle core_particle(core_material, new FormFactorParallelepiped(
            7*Units::nanometer, 6*Units::nanometer));
    kvector_t core_position(0.0, 0.0, 0.0);
    ParticleCoreShell particle(shell_particle, core_particle, core_position);
    ParticleDecoration particle_decoration(particle.clone());
    particle_decoration.addInterferenceFunction(new InterferenceFunctionNone());

    air_layer.setDecoration(particle_decoration);

    multi_layer->addLayer(air_layer);
    return multi_layer;
}

