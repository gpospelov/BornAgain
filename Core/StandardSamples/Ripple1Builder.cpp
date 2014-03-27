// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/Ripple1Builder.cpp
//! @brief     Implement class Ripple1Builder.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Ripple1Builder.h"
#include "MultiLayer.h"
#include "ParticleLayout.h"
#include "Materials.h"
#include "FormFactorRipple1.h"
#include "Units.h"
#include "InterferenceFunction1DParaCrystal.h"

Ripple1Builder::Ripple1Builder()
    : m_w(20.0*Units::nanometer)
    , m_h(4.0*Units::nanometer)
    , m_l(100.0*Units::nanometer)
    , m_interf_distance(20.0*Units::nanometer)
    , m_interf_width(4.0*Units::nanometer)
{
    init_parameters();
}


void Ripple1Builder::init_parameters()
{
    clearParameterPool();
    registerParameter("width", &m_w);
    registerParameter("height", &m_h);
    registerParameter("length", &m_l);
    registerParameter("interf_distance", &m_interf_distance);
    registerParameter("interf_width", &m_interf_width);
}


ISample *Ripple1Builder::buildSample() const
{
    MultiLayer *p_multi_layer = new MultiLayer();

    HomogeneousMaterial air_material("Air", 0.0, 0.0);
    HomogeneousMaterial substrate_material("Substrate", 6e-6, 2e-8);
    HomogeneousMaterial particle_material("Particle", 6e-4, 2e-8);

    Layer air_layer(air_material);
    FormFactorRipple1 ff_ripple1(m_l, m_w, m_h);
    Particle ripple(particle_material, ff_ripple1);

    ParticleLayout particle_layout;
	particle_layout.addParticle(ripple,0.0,1.0);
    IInterferenceFunction *p_interference_function = new InterferenceFunction1DParaCrystal(m_interf_distance, m_interf_width, 1e7*Units::nanometer); // peak_distance, width, corr_length
    particle_layout.addInterferenceFunction(p_interference_function);

    air_layer.setLayout(particle_layout);

    p_multi_layer->addLayer(air_layer);

    Layer substrate_layer(substrate_material);
    p_multi_layer->addLayer(substrate_layer);

    return p_multi_layer;
}

