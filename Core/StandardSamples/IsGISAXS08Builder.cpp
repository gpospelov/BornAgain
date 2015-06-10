// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/IsGISAXS08Builder.cpp
//! @brief     Implements classes IsGISAXS08ABuilder, IsGISAXS08BBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IsGISAXS08Builder.h"
#include "MultiLayer.h"
#include "ParticleLayout.h"
#include "Materials.h"
#include "InterferenceFunction2DParaCrystal.h"
#include "FormFactorCylinder.h"
#include "Units.h"

IsGISAXS08ABuilder::IsGISAXS08ABuilder()
{
}

ISample *IsGISAXS08ABuilder::buildSample() const
{
    MultiLayer *multi_layer = new MultiLayer();

    HomogeneousMaterial air_material("Air", 0.0, 0.0);
    HomogeneousMaterial substrate_material("Substrate", 6e-6, 2e-8);
    HomogeneousMaterial particle_material("Particle", 6e-4, 2e-8);

    Layer air_layer(air_material);
    Layer substrate_layer(substrate_material);

    InterferenceFunction2DParaCrystal *p_interference_function =
            new InterferenceFunction2DParaCrystal(10.0*Units::nanometer,
                    10.0*Units::nanometer, Units::PI/2.0, 0.0, 0.0);
    p_interference_function->setDomainSizes(20.0*Units::micrometer,
            20.0*Units::micrometer);
    FTDistribution2DCauchy pdf1(0.5*Units::nanometer, 2.0*Units::nanometer);
    FTDistribution2DCauchy pdf2(0.5*Units::nanometer, 2.0*Units::nanometer);
    p_interference_function->setProbabilityDistributions(pdf1, pdf2);

    FormFactorCylinder ff_cylinder(5.0*Units::nanometer, 5.0*Units::nanometer);

    Particle particle(particle_material, ff_cylinder);
    ParticleLayout particle_layout(particle);
    particle_layout.addInterferenceFunction(p_interference_function);

    air_layer.addLayout(particle_layout);

    multi_layer->addLayer(air_layer);
    multi_layer->addLayer(substrate_layer);

    return multi_layer;
}


// -----------------------------------------------------------------------------
//

IsGISAXS08BBuilder::IsGISAXS08BBuilder()
{
}

// IsGISAXS8 functional test: 2D paracrystal lattice with isotropic pdfs
ISample *IsGISAXS08BBuilder::buildSample() const
{
    MultiLayer *multi_layer = new MultiLayer();

    HomogeneousMaterial air_material("Air", 0.0, 0.0);
    HomogeneousMaterial substrate_material("Substrate", 6e-6, 2e-8);
    HomogeneousMaterial particle_material("Particle", 6e-4, 2e-8);

    Layer air_layer(air_material);
    Layer substrate_layer(substrate_material);

    InterferenceFunction2DParaCrystal *p_interference_function =
            new InterferenceFunction2DParaCrystal(10.0*Units::nanometer,
                    10.0*Units::nanometer, Units::PI/2.0, 0.0, 0.0);
    p_interference_function->setDomainSizes(20.0*Units::micrometer,
            20.0*Units::micrometer);
    FTDistribution2DCauchy pdf1(0.5*Units::nanometer, 0.5*Units::nanometer);
    FTDistribution2DCauchy pdf2(0.5*Units::nanometer, 0.5*Units::nanometer);
    p_interference_function->setProbabilityDistributions(pdf1, pdf2);

    FormFactorCylinder ff_cylinder(5*Units::nanometer, 5*Units::nanometer);

    Particle particle(particle_material, ff_cylinder);
    ParticleLayout particle_layout(particle);
    particle_layout.addInterferenceFunction(p_interference_function);

    air_layer.addLayout(particle_layout);

    multi_layer->addLayer(air_layer);
    multi_layer->addLayer(substrate_layer);

    return multi_layer;
}
