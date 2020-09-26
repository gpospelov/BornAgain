// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/LatticeBuilder.cpp
//! @brief     Implements class Lattice1DBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/StandardSamples/LatticeBuilder.h"
#include "Core/Aggregate/InterferenceFunction1DLattice.h"
#include "Core/Aggregate/ParticleLayout.h"
#include "Core/Basics/Units.h"
#include "Core/Correlations/FTDecay1D.h"
#include "Core/Correlations/FTDecay2D.h"
#include "Core/HardParticle/FormFactorCylinder.h"
#include "Core/Material/MaterialFactoryFuncs.h"
#include "Core/Multilayer/Layer.h"
#include "Core/Multilayer/MultiLayer.h"
#include "Core/Parametrization/RealParameter.h"
#include "Core/Particle/Particle.h"

MultiLayer* Lattice1DBuilder::buildSample() const
{
    const double length(20.0 * Units::nanometer);
    const double xi(10.0 * Units::deg);
    const double corr_length(1000.0 * Units::nanometer);
    const double cylinder_height(5 * Units::nanometer);
    const double cylinder_radius(5 * Units::nanometer);

    Material particle_material = HomogeneousMaterial("Particle", 6e-4, 2e-8);
    Material air_material = HomogeneousMaterial("Air", 0.0, 0.0);
    Material substrate_material = HomogeneousMaterial("Substrate", 6e-6, 2e-8);

    Layer air_layer(air_material);
    Layer substrate_layer(substrate_material);

    InterferenceFunction1DLattice interference_function(length, xi);
    FTDecayFunction1DCauchy pdf(corr_length);
    interference_function.setDecayFunction(pdf);

    FormFactorCylinder ff_cylinder(cylinder_radius, cylinder_height);
    Particle cylinder(particle_material, ff_cylinder);

    ParticleLayout particle_layout(cylinder);
    particle_layout.setInterferenceFunction(interference_function);

    air_layer.addLayout(particle_layout);

    MultiLayer* multi_layer = new MultiLayer();
    multi_layer->addLayer(air_layer);
    multi_layer->addLayer(substrate_layer);
    return multi_layer;
}
