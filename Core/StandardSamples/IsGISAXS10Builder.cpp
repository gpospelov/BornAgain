// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/IsGISAXS10Builder.cpp
//! @brief     Implement class IsGISAXS10Builder.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IsGISAXS10Builder.h"
#include "MultiLayer.h"
#include "ParticleLayout.h"
#include "MaterialManager.h"
#include "FormFactorCylinder.h"
#include "InterferenceFunction1DParaCrystal.h"
#include "Units.h"

IsGISAXS10Builder::IsGISAXS10Builder()
    : m_cylinder_height(5*Units::nanometer)
    , m_cylinder_radius(5*Units::nanometer)
{
    init_parameters();
}


void IsGISAXS10Builder::init_parameters()
{
    clearParameterPool();
    registerParameter("cylinder_height", &m_cylinder_height);
    registerParameter("cylinder_radius", &m_cylinder_radius);
}


ISample *IsGISAXS10Builder::buildSample() const
{
    MultiLayer *multi_layer = new MultiLayer();

	const IMaterial *p_air_material =
            MaterialManager::getHomogeneousMaterial("Air10", 0.0, 0.0);
    const IMaterial *p_substrate_material =
            MaterialManager::getHomogeneousMaterial("Substrate10", 5e-6, 2e-8);
    Layer air_layer;
    air_layer.setMaterial(*p_air_material);
    Layer substrate_layer;
    substrate_layer.setMaterial(*p_substrate_material);

    IInterferenceFunction *p_interference_function =
            new InterferenceFunction1DParaCrystal(20.0*Units::nanometer,
                    7*Units::nanometer, 1e7*Units::nanometer);
    const IMaterial *particle_material = MaterialManager::getHomogeneousMaterial("Particle", 5e-5, 2e-8);

    ParticleLayout particle_layout(new Particle(particle_material,
            new FormFactorCylinder(m_cylinder_radius, m_cylinder_height)));
    particle_layout.addInterferenceFunction(p_interference_function);

    air_layer.setLayout(particle_layout);

    multi_layer->addLayer(air_layer);
    multi_layer->addLayer(substrate_layer);
    return multi_layer;
}

