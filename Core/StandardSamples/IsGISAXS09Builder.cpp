// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/IsGISAXS09Builder.cpp
//! @brief     Implements classes IsGISAXS09ABuilder and IsGISAXS09BBuilder.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IsGISAXS09Builder.h"
#include "FormFactorPyramid.h"
#include "InterferenceFunctionNone.h"
#include "MaterialManager.h"
#include "MultiLayer.h"
#include "ParticleDecoration.h"
#include "Units.h"


// ----------------------------------------------------------------------------
// Pyramids on top of substrate
// ----------------------------------------------------------------------------
IsGISAXS09ABuilder::IsGISAXS09ABuilder()
    : m_height(5*Units::nanometer)
    , m_half_side(5*Units::nanometer)
    , m_alpha(Units::deg2rad(54.73 ))
{
    init_parameters();
}


void IsGISAXS09ABuilder::init_parameters()
{
    clearParameterPool();
    registerParameter("height", &m_height);
    registerParameter("half_side", &m_half_side);
    registerParameter("alpha", &m_alpha);
}


ISample *IsGISAXS09ABuilder::buildSample() const
{
    MultiLayer *multi_layer = new MultiLayer();

    const IMaterial *p_air_material =
        MaterialManager::getHomogeneousMaterial("Air", 0.0, 0.0);
    const IMaterial *p_substrate_material =
        MaterialManager::getHomogeneousMaterial("Substrate", 6e-6, 2e-8);
    Layer air_layer;
    air_layer.setMaterial(p_air_material);
    Layer substrate_layer;
    substrate_layer.setMaterial(p_substrate_material);

    const IMaterial *particle_material = MaterialManager::getHomogeneousMaterial("Particle", 6e-4, 2e-8);

//    complex_t n_particle(1.0-6e-4, 2e-8);
    ParticleDecoration particle_decoration(
        new Particle(particle_material,
                     new FormFactorPyramid(m_height, m_half_side, m_alpha) ) );

    particle_decoration.addInterferenceFunction(new InterferenceFunctionNone());

    air_layer.setDecoration(particle_decoration);

    multi_layer->addLayer(air_layer);
    multi_layer->addLayer(substrate_layer);

    return multi_layer;
}


// ----------------------------------------------------------------------------
// Rotated pyramids on top of substrate
// ----------------------------------------------------------------------------
IsGISAXS09BBuilder::IsGISAXS09BBuilder()
    : m_height(5*Units::nanometer)
    , m_half_side(5*Units::nanometer)
    , m_alpha(Units::deg2rad(54.73 ))
    , m_zangle(45.*Units::degree)
{
    init_parameters();
}


void IsGISAXS09BBuilder::init_parameters()
{
    clearParameterPool();
    registerParameter("height", &m_height);
    registerParameter("half_side", &m_half_side);
    registerParameter("alpha", &m_alpha);
    registerParameter("zangle", &m_zangle);
}


ISample *IsGISAXS09BBuilder::buildSample() const
{
    MultiLayer *multi_layer = new MultiLayer();

    const IMaterial *p_air_material =
        MaterialManager::getHomogeneousMaterial("Air", 0.0, 0.0);
    const IMaterial *p_substrate_material =
        MaterialManager::getHomogeneousMaterial("Substrate", 6e-6, 2e-8);
    Layer air_layer;
    air_layer.setMaterial(p_air_material);
    Layer substrate_layer;
    substrate_layer.setMaterial(p_substrate_material);

//    complex_t n_particle(1.0-6e-4, 2e-8);
    const IMaterial *particle_material = MaterialManager::getHomogeneousMaterial("Particle", 6e-4, 2e-8);
    Particle *pyramid = new Particle(
        particle_material,
        new FormFactorPyramid(m_height, m_half_side, m_alpha)
                );

    Geometry::Transform3D transform =
            Geometry::Transform3D::createRotateZ(m_zangle);

    ParticleDecoration particle_decoration;
    particle_decoration.addParticle(pyramid, transform);
    particle_decoration.addInterferenceFunction(new InterferenceFunctionNone());

    air_layer.setDecoration(particle_decoration);

    multi_layer->addLayer(air_layer);
    multi_layer->addLayer(substrate_layer);


    return multi_layer;
}

