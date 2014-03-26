// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/IsGISAXS15Builder.cpp
//! @brief     Implements class IsGISAXS15Builder.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IsGISAXS15Builder.h"
#include "MultiLayer.h"
#include "ParticleLayout.h"
#include "MaterialManager.h"
#include "Units.h"
#include "InterferenceFunction1DParaCrystal.h"
#include "FormFactorCylinder.h"
#include "StochasticGaussian.h"
#include "StochasticSampledParameter.h"
#include "ParticleBuilder.h"


IsGISAXS15Builder::IsGISAXS15Builder()
{
}

ISample *IsGISAXS15Builder::buildSample() const
{
    MultiLayer *multi_layer = new MultiLayer();

    complex_t n_particle(1.0-6e-4, 2e-8);
    const IMaterial *p_air_material =
            MaterialManager::getHomogeneousMaterial("Air", 0.0, 0.0);
    const IMaterial *particle_material =
            MaterialManager::getHomogeneousMaterial("Particle", n_particle);

    Layer air_layer;
    air_layer.setMaterial(*p_air_material);
    InterferenceFunction1DParaCrystal *p_interference_function =
            new InterferenceFunction1DParaCrystal(15.0*Units::nanometer,
                    5*Units::nanometer, 1e3*Units::nanometer);
    p_interference_function->setKappa(4.02698);
    ParticleLayout particle_layout;
    Particle particle_prototype(*particle_material, FormFactorCylinder(
            5.0*Units::nanometer, 5.0*Units::nanometer));
    StochasticDoubleGaussian sg(5.0*Units::nanometer, 1.25*Units::nanometer);
    StochasticSampledParameter stochastic_radius(sg,30, 2);
    ParticleBuilder particle_builder;
    particle_builder.setPrototype(particle_prototype,
            "/Particle/FormFactorCylinder/radius", stochastic_radius);
    particle_builder.plantParticles(particle_layout);

    // Set height of each particle to its radius (H/R fixed)
    ParameterPool *p_parameters = particle_layout.createParameterTree();
    p_parameters->fixRatioBetweenParameters("height", "radius", 1.0);

    particle_layout.addInterferenceFunction(p_interference_function);

    air_layer.setLayout(particle_layout);

    multi_layer->addLayer(air_layer);
    return multi_layer;
}

