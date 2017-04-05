// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/SlicedParticleBuilder.h
//! @brief     Defines classes to build various particles crossing interfaces.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "SlicedParticleBuilder.h"
#include "MultiLayer.h"
#include "Layer.h"
#include "FormFactorFullSphere.h"
#include "FormFactorTruncatedSphere.h"
#include "ParticleComposition.h"
#include "Particle.h"
#include "ParticleLayout.h"
#include "HomogeneousMaterial.h"
#include "Transform3D.h"
#include "Units.h"

MultiLayer* SlicedCompositionBuilder::buildSample() const
{
    MultiLayer* p_multi_layer = new MultiLayer();

    HomogeneousMaterial air_material("Air", 0.0, 0.0);
    HomogeneousMaterial substrate_material("Substrate", 3.212e-6, 3.244e-8);
    HomogeneousMaterial topCupMaterial("Ag", 1.245e-5, 5.419e-7);
    HomogeneousMaterial bottomCupMaterial("Teflon", 2.900e-6, 6.019e-9);

    const double sphere_radius = 10.0;
    const double bottom_cup_height = 4.0;
    const double composition_shift = bottom_cup_height;

    Particle topCup(topCupMaterial, FormFactorTruncatedSphere(sphere_radius, sphere_radius*2 - bottom_cup_height));
    Particle bottomCup(bottomCupMaterial, FormFactorTruncatedSphere(sphere_radius, bottom_cup_height));
    bottomCup.setRotation(RotationX(180*Units::deg));

    ParticleComposition composition;
    composition.addParticle(topCup, kvector_t(0.0, 0.0, bottom_cup_height));
    composition.addParticle(bottomCup, kvector_t(0.0, 0.0, bottom_cup_height));
    composition.setPosition(0, 0, -composition_shift);

    ParticleLayout particle_layout;
    particle_layout.addParticle(composition);

    Layer air_layer(air_material);
    air_layer.addLayout(particle_layout);

    Layer substrate_layer(substrate_material);

    p_multi_layer->addLayer(air_layer);
    p_multi_layer->addLayer(substrate_layer);

    return p_multi_layer;

}
