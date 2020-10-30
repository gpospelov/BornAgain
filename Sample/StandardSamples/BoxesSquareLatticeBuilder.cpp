// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/StandardSamples/BoxesSquareLatticeBuilder.cpp
//! @brief     Implements class BoxesSquareLatticeBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Sample/StandardSamples/BoxesSquareLatticeBuilder.h"
#include "Base/Const/Units.h"
#include "Sample/Aggregate/InterferenceFunction2DLattice.h"
#include "Sample/Aggregate/ParticleLayout.h"
#include "Sample/HardParticle/FormFactorBox.h"
#include "Sample/Multilayer/Layer.h"
#include "Sample/Multilayer/MultiLayer.h"
#include "Sample/Particle/Particle.h"
#include "Sample/StandardSamples/ReferenceMaterials.h"

MultiLayer* BoxesSquareLatticeBuilder::buildSample() const
{
    const double length = 5 * Units::nanometer;
    const double height = 10 * Units::nanometer;

    Layer vacuum_layer(refMat::Vacuum);
    Layer substrate_layer(refMat::Substrate);

    std::unique_ptr<InterferenceFunction2DLattice> P_interference_function(
        InterferenceFunction2DLattice::createSquare(8 * Units::nanometer, 0));

    FTDecayFunction2DCauchy pdf(100.0 * Units::nanometer, 100.0 * Units::nanometer, 0);
    P_interference_function->setDecayFunction(pdf);

    // particles
    ParticleLayout particle_layout;
    FormFactorBox ff_box(length, length, height);
    Particle particle(refMat::Particle, ff_box);
    particle_layout.addParticle(particle, 1.0);

    particle_layout.setInterferenceFunction(*P_interference_function);

    vacuum_layer.addLayout(particle_layout);

    MultiLayer* multi_layer = new MultiLayer();
    multi_layer->addLayer(vacuum_layer);
    multi_layer->addLayer(substrate_layer);
    return multi_layer;
}
