// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/IsGISAXS07Builder.cpp
//! @brief     Implements class IsGISAXS07Builder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IsGISAXS07Builder.h"
#include "MultiLayer.h"
#include "ParticleLayout.h"
#include "Materials.h"
#include "FormFactorBox.h"
#include "Simulation.h"
#include "IntensityDataIOFactory.h"
#include "Utils.h"
#include "Units.h"
#include "MathFunctions.h"
#include <iostream>
#include <cmath>

IsGISAXS07Builder::IsGISAXS07Builder()
{
}


ISample *IsGISAXS07Builder::buildSample() const
{
    MultiLayer* multi_layer = new MultiLayer();

    HomogeneousMaterial air_material("Air", 0.0, 0.0);
    HomogeneousMaterial particle_material("Particle", 6e-4, 2e-8);

    Layer air_layer(air_material);

    ParticleLayout particle_layout;

    // add particle number 1:
    FormFactorBox ff1(2.0*Units::nanometer, 2.0*Units::nanometer,
            1.0*Units::nanometer);
    kvector_t pos1(0.0*Units::nanometer, 0.0*Units::nanometer, 0.0);
    Particle p1(particle_material, ff1);
    ParticleInfo particle_info1(p1, pos1, 0.5);
    particle_layout.addParticleInfo(particle_info1);
    // add particle number 2:
    FormFactorBox ff2(2.0*Units::nanometer, 4.0*Units::nanometer,
            1.0*Units::nanometer);
    kvector_t pos2(5.0*Units::nanometer, 5.0*Units::nanometer, 0.0);
    RotationZ m2(10*Units::degree);
    Particle p2(particle_material, ff2, m2);
    ParticleInfo particle_info2(p2, pos2, 0.5);
    particle_layout.addParticleInfo(particle_info2);
    // add particle number 3:
    FormFactorBox ff3(2.0*Units::nanometer, 6.0*Units::nanometer,
            1.0*Units::nanometer);
    kvector_t pos3(-5.0*Units::nanometer, -5.0*Units::nanometer, 0.0);
    RotationZ m3(20*Units::degree);
    Particle p3(particle_material, ff3, m3);
    ParticleInfo particle_info3(p3, pos3, 0.5);
    particle_layout.addParticleInfo(particle_info3);
    // add particle number 4:
    FormFactorBox ff4(2.0*Units::nanometer, 8.0*Units::nanometer,
            1.0*Units::nanometer);
    kvector_t pos4(5.0*Units::nanometer, -5.0*Units::nanometer, 0.0);
    RotationZ m4(30*Units::degree);
    Particle p4(particle_material, ff4, m4);
    ParticleInfo particle_info4(p4, pos4, 0.5);
    particle_layout.addParticleInfo(particle_info4);
    // add particle number 5:
    FormFactorBox ff5(2.0*Units::nanometer, 10.0*Units::nanometer,
            1.0*Units::nanometer);
    kvector_t pos5(-5.0*Units::nanometer, 5.0*Units::nanometer, 0.0);
    RotationZ m5(40*Units::degree);
    Particle p5(particle_material, ff5, m5);
    ParticleInfo particle_info5(p5, pos5, 0.5);
    particle_layout.addParticleInfo(particle_info5);
    // add particle number 6:
    FormFactorBox ff6(2.0*Units::nanometer, 2.0*Units::nanometer,
            1.0*Units::nanometer);
    kvector_t pos6(0.0*Units::nanometer, 0.0*Units::nanometer, 0.0);
    RotationZ m6(50*Units::degree);
    Particle p6(particle_material, ff6, m6);
    ParticleInfo particle_info6(p6, pos6, 0.5);
    particle_layout.addParticleInfo(particle_info6);
    // add particle number 7:
    FormFactorBox ff7(2.0*Units::nanometer, 4.0*Units::nanometer,
            1.0*Units::nanometer);
    kvector_t pos7(5.0*Units::nanometer, 5.0*Units::nanometer, 0.0);
    RotationZ m7(60*Units::degree);
    Particle p7(particle_material, ff7, m7);
    ParticleInfo particle_info7(p7, pos7, 0.5);
    particle_layout.addParticleInfo(particle_info7);
    // add particle number 8:
    FormFactorBox ff8(2.0*Units::nanometer, 6.0*Units::nanometer,
            1.0*Units::nanometer);
    kvector_t pos8(-5.0*Units::nanometer, -5.0*Units::nanometer, 0.0);
    RotationZ m8(70*Units::degree);
    Particle p8(particle_material, ff8, m8);
    ParticleInfo particle_info8(p8, pos8, 0.5);
    particle_layout.addParticleInfo(particle_info8);
    // add particle number 9:
    FormFactorBox ff9(2.0*Units::nanometer, 8.0*Units::nanometer,
            1.0*Units::nanometer);
    kvector_t pos9(5.0*Units::nanometer, -5.0*Units::nanometer, 0.0);
    RotationZ m9(80*Units::degree);
    Particle p9(particle_material, ff9, m9);
    ParticleInfo particle_info9(p9, pos9, 0.5);
    particle_layout.addParticleInfo(particle_info9);
    // add particle number 10:
    FormFactorBox ff10(2.0*Units::nanometer, 10.0*Units::nanometer,
            1.0*Units::nanometer);
    kvector_t pos10(-5.0*Units::nanometer, 5.0*Units::nanometer, 0.0);
    RotationZ m10(90*Units::degree);
    Particle p10(particle_material, ff10, m10);
    ParticleInfo particle_info10(p10, pos10, 0.5);
    particle_layout.addParticleInfo(particle_info10);
    particle_layout.setApproximation(ILayout::ISGISAXSMOR);

    air_layer.addLayout(particle_layout);
    multi_layer->addLayer(air_layer);

    return multi_layer;
}

