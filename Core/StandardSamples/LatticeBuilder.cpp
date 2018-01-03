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

#include "LatticeBuilder.h"
#include "MaterialFactoryFuncs.h"
#include "BornAgainNamespace.h"
#include "FTDecayFunctions.h"
#include "FormFactorCylinder.h"
#include "InterferenceFunction1DLattice.h"
#include "Layer.h"
#include "MultiLayer.h"
#include "Particle.h"
#include "ParticleLayout.h"
#include "RealParameter.h"
#include "Units.h"

Lattice1DBuilder::Lattice1DBuilder()
    : m_length(20.0*Units::nanometer)
    , m_xi(10.0*Units::deg)
    , m_corr_length(1000.0*Units::nanometer)
    , m_cylinder_height(5*Units::nanometer)
    , m_cylinder_radius(5*Units::nanometer)
{}

MultiLayer* Lattice1DBuilder::buildSample() const
{
    MultiLayer* multi_layer = new MultiLayer();

    Material particle_material = HomogeneousMaterial("Particle", 6e-4, 2e-8);
    Material air_material = HomogeneousMaterial("Air", 0.0, 0.0);
    Material substrate_material = HomogeneousMaterial("Substrate", 6e-6, 2e-8);

    Layer air_layer(air_material);
    Layer substrate_layer(substrate_material);

    InterferenceFunction1DLattice interference_function(m_length, m_xi);
    FTDecayFunction1DCauchy pdf(m_corr_length);
    interference_function.setDecayFunction(pdf);

    FormFactorCylinder ff_cylinder(m_cylinder_radius, m_cylinder_height);
    Particle cylinder(particle_material, ff_cylinder);

    ParticleLayout particle_layout(cylinder);
    particle_layout.setInterferenceFunction(interference_function);

    air_layer.addLayout(particle_layout);

    multi_layer->addLayer(air_layer);
    multi_layer->addLayer(substrate_layer);

    return multi_layer;
}
