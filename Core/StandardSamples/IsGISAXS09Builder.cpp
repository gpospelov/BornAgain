// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/IsGISAXS09Builder.cpp
//! @brief     Implements classes IsGISAXS09ABuilder and IsGISAXS09BBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IsGISAXS09Builder.h"
#include "FormFactorPyramid.h"
#include "InterferenceFunctionNone.h"
#include "Materials.h"
#include "MultiLayer.h"
#include "ParticleLayout.h"
#include "Units.h"


// ----------------------------------------------------------------------------
// Pyramids on top of substrate
// ----------------------------------------------------------------------------
IsGISAXS09ABuilder::IsGISAXS09ABuilder()
    : m_length(10*Units::nanometer)
    , m_height(5*Units::nanometer)
    , m_alpha(Units::deg2rad(54.73 ))
{
    init_parameters();
}


void IsGISAXS09ABuilder::init_parameters()
{
    clearParameterPool();
    registerParameter("length", &m_length);
    registerParameter("height", &m_height);
    registerParameter("alpha", &m_alpha);
}


ISample *IsGISAXS09ABuilder::buildSample() const
{
    MultiLayer *multi_layer = new MultiLayer();

    HomogeneousMaterial air_material("Air", 0.0, 0.0);
    HomogeneousMaterial substrate_material("Substrate", 6e-6, 2e-8);
    HomogeneousMaterial particle_material("Particle", 6e-4, 2e-8);

    Layer air_layer(air_material);
    Layer substrate_layer(substrate_material);

    FormFactorPyramid ff_pyramid(m_length, m_height, m_alpha);

    Particle particle(particle_material, ff_pyramid);
    ParticleLayout particle_layout(particle);

    particle_layout.addInterferenceFunction(new InterferenceFunctionNone());

    air_layer.addLayout(particle_layout);

    multi_layer->addLayer(air_layer);
    multi_layer->addLayer(substrate_layer);

    return multi_layer;
}


// ----------------------------------------------------------------------------
// Rotated pyramids on top of substrate
// ----------------------------------------------------------------------------
IsGISAXS09BBuilder::IsGISAXS09BBuilder()
    : m_length(10*Units::nanometer)
    , m_height(5*Units::nanometer)
    , m_alpha(Units::deg2rad(54.73 ))
    , m_zangle(45.*Units::degree)
{
    init_parameters();
}


void IsGISAXS09BBuilder::init_parameters()
{
    clearParameterPool();
    registerParameter("length", &m_length);
    registerParameter("height", &m_height);
    registerParameter("alpha", &m_alpha);
    registerParameter("zangle", &m_zangle);
}


ISample *IsGISAXS09BBuilder::buildSample() const
{
    MultiLayer *multi_layer = new MultiLayer();

    HomogeneousMaterial air_material("Air", 0.0, 0.0);
    HomogeneousMaterial substrate_material("Substrate", 6e-6, 2e-8);
    HomogeneousMaterial particle_material("Particle", 6e-4, 2e-8);

    Layer air_layer(air_material);
    Layer substrate_layer(substrate_material);

    FormFactorPyramid ff_pyramid(m_length, m_height, m_alpha);

    Particle pyramid(particle_material, ff_pyramid);

    Geometry::Transform3D transform =
            Geometry::Transform3D::createRotateZ(m_zangle);

    ParticleLayout particle_layout;
    particle_layout.addParticle(pyramid, transform);
    particle_layout.addInterferenceFunction(new InterferenceFunctionNone());

    air_layer.addLayout(particle_layout);

    multi_layer->addLayer(air_layer);
    multi_layer->addLayer(substrate_layer);


    return multi_layer;
}

