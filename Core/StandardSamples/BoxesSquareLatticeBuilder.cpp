// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/BoxesSquareLatticeBuilder.cpp
//! @brief     Implements class BoxesSquareLatticeBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   J. Burle, J. M. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "BoxesSquareLatticeBuilder.h"
#include "BornAgainNamespace.h"
#include "FormFactorBox.h"
#include "HomogeneousMaterial.h"
#include "InterferenceFunction2DLattice.h"
#include "Layer.h"
#include "MultiLayer.h"
#include "Particle.h"
#include "ParticleLayout.h"
#include "RealParameter.h"
#include "Units.h"

// -----------------------------------------------------------------------------
// Boxes in square lattice
// -----------------------------------------------------------------------------

BoxesSquareLatticeBuilder::BoxesSquareLatticeBuilder()
    : m_length(5*Units::nanometer)
    , m_height(10*Units::nanometer)
{
    init_parameters();
}

MultiLayer* BoxesSquareLatticeBuilder::buildSample() const
{
    MultiLayer* multi_layer = new MultiLayer();

    HomogeneousMaterial particle_material("Particle", 6e-4, 2e-8);
    HomogeneousMaterial air_material("Air", 0.0, 0.0);
    HomogeneousMaterial substrate_material("Substrate", 6e-6, 2e-8);

    Layer air_layer(air_material);
    Layer substrate_layer(substrate_material);

    std::unique_ptr<InterferenceFunction2DLattice> P_interference_function(
                InterferenceFunction2DLattice::createSquare(8*Units::nanometer));

    FTDecayFunction2DCauchy pdf(100.0*Units::nanometer, 100.0*Units::nanometer);
    P_interference_function->setDecayFunction(pdf);

    // particles
    ParticleLayout particle_layout;
    FormFactorBox ff_box(m_length, m_length, m_height);
    Particle particle(particle_material, ff_box);
    particle_layout.addParticle(particle, 1.0);

    particle_layout.setInterferenceFunction(*P_interference_function);

    air_layer.addLayout(particle_layout);

    multi_layer->addLayer(air_layer);
    multi_layer->addLayer(substrate_layer);

    return multi_layer;
}

void BoxesSquareLatticeBuilder::init_parameters()
{
    registerParameter(BornAgain::Length, &m_length).setUnit("nm").setNonnegative();
    registerParameter(BornAgain::Height, &m_height).setUnit("nm").setNonnegative();
}
