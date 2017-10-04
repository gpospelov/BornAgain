// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/MesoCrystalBuilder.cpp
//! @brief     Implements class MesoCrystalBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MesoCrystalBuilder.h"
#include "BornAgainNamespace.h"
#include "Crystal.h"
#include "FormFactorCylinder.h"
#include "FormFactorDecoratorDebyeWaller.h"
#include "FormFactorSphereGaussianRadius.h"
#include "HomogeneousMaterial.h"
#include "ISelectionRule.h"
#include "Layer.h"
#include "LayerInterface.h"
#include "LayerRoughness.h"
#include "MesoCrystal.h"
#include "MultiLayer.h"
#include "Particle.h"
#include "ParticleComposition.h"
#include "ParticleLayout.h"
#include "MathConstants.h"
#include "RealParameter.h"
#include "Units.h"

MesoCrystalBuilder::MesoCrystalBuilder()
{}

MultiLayer* MesoCrystalBuilder::buildSample() const
{
    MultiLayer* p_multi_layer = new MultiLayer();

    // defining materials
    auto air_material = HomogeneousMaterial("Air", 0.0, 0.0);
    auto substrate_material = HomogeneousMaterial("Substrate", 6e-6, 2e-8);
    auto particle_material = HomogeneousMaterial("Particle", 6e-4, 2e-8);

    // mesocrystal lattice
    kvector_t lattice_basis_a(5.0, 0.0, 0.0);
    kvector_t lattice_basis_b(0.0, 5.0, 0.0);
    kvector_t lattice_basis_c(0.0, 0.0, 5.0);
    Lattice lattice(lattice_basis_a, lattice_basis_b, lattice_basis_c);

    // spherical particle that forms the base of the mesocrystal
    FormFactorFullSphere sphere_ff(2.0);
    Particle sphere(particle_material, sphere_ff);

    // crystal structure
    Crystal crystal(sphere, lattice);

    // mesocrystal
    FormFactorCylinder meso_ff(20.0, 50.0);
    MesoCrystal meso(crystal, meso_ff);

    ParticleLayout particle_layout;
    particle_layout.addParticle(meso);

    Layer air_layer(air_material);
    air_layer.addLayout(particle_layout);
    Layer substrate_layer(substrate_material);

    p_multi_layer->addLayer(air_layer);
    p_multi_layer->addLayer(substrate_layer);
    return p_multi_layer;
}
