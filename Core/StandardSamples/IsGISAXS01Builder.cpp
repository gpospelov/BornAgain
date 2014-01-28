// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/IsGISAXS01Builder.cpp
//! @brief     Implements class IsGISAXS01Builder.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IsGISAXS01Builder.h"
#include "MultiLayer.h"
#include "ParticleDecoration.h"
#include "MaterialManager.h"
#include "FormFactorCylinder.h"
#include "FormFactorPrism3.h"
#include "Units.h"
#include "InterferenceFunctionNone.h"

IsGISAXS01Builder::IsGISAXS01Builder()
    : m_cylinder_height(5*Units::nanometer)
    , m_cylinder_radius(5*Units::nanometer)
    , m_prism_height(5*Units::nanometer)
    , m_prism_length(10*Units::nanometer)
    , m_cylinder_weight(0.5)
{
    init_parameters();
}


void IsGISAXS01Builder::init_parameters()
{
    clearParameterPool();
    registerParameter("cylinder_height", &m_cylinder_height);
    registerParameter("cylinder_radius", &m_cylinder_radius);
    registerParameter("prism_height", &m_prism_height);
    registerParameter("prism_length", &m_prism_length);
    registerParameter("cylinder_weight", &m_cylinder_weight);
}


ISample *IsGISAXS01Builder::buildSample() const
{
    MultiLayer *multi_layer = new MultiLayer();
    const IMaterial *p_air_material =
            MaterialManager::getHomogeneousMaterial("Air", 0., 0.);
    const IMaterial *p_substrate_material =
            MaterialManager::getHomogeneousMaterial("Substrate", 6e-6, 2e-8);
    Layer air_layer;
    air_layer.setMaterial(p_air_material);
    Layer substrate_layer;
    substrate_layer.setMaterial(p_substrate_material);

    ParticleDecoration particle_decoration;
    const IMaterial *particle_material = MaterialManager::getHomogeneousMaterial("Particle", 6e-4, 2e-8);

    particle_decoration.addParticle(
                new Particle(particle_material,
                             new FormFactorCylinder(m_cylinder_radius,
                                                    m_cylinder_height)),
                0.0, m_cylinder_weight);
    particle_decoration.addParticle(
                new Particle(particle_material,
                             new FormFactorPrism3(m_prism_length,
                                                  m_prism_height)),
                0.0, 1.0-m_cylinder_weight);
    particle_decoration.addInterferenceFunction(new InterferenceFunctionNone());

    air_layer.setDecoration(particle_decoration);

    multi_layer->addLayer(air_layer);
    multi_layer->addLayer(substrate_layer);
    return multi_layer;
}

