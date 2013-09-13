// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/src/TestPolarizedMeso.cpp
//! @brief     Implements class TestPolarizedMeso.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "TestPolarizedMeso.h"
#include "Units.h"
#include "IsGISAXSTools.h"
#include "MaterialManager.h"
#include "InterferenceFunctionNone.h"
#include "Rotate3D.h"
#include "FormFactors.h"
#include "MesoCrystal.h"


TestPolarizedMeso::TestPolarizedMeso()
: mp_sample(0)
, m_meso_width(3e+3*Units::nanometer)
, m_surface_filling_ratio(0.03)
, m_meso_size_steps(1e+3*Units::nanometer)
//, m_sigma_meso_height(10*Units::nanometer)
//, m_sigma_meso_radius(10*Units::nanometer)
, m_lattice_length_a(13.5*Units::nanometer)
, m_lattice_length_c(23.8*Units::nanometer)
, m_nanoparticle_size(9.6*Units::nanometer)
//, m_sigma_nanoparticle_size(6.8688e-02*Units::nanometer)
//, m_sigma_lattice_length_a(2.3596*Units::nanometer)
, m_roughness(0.6517*Units::nanometer)
{
    std::cout << "TestPolarizedMeso::TestPolarizedMeso() -> Info."
            << std::endl;
}

TestPolarizedMeso::~TestPolarizedMeso()
{
}

void TestPolarizedMeso::execute()
{
    std::cout << "TestPolarizedMeso::execute() -> Info." << std::endl;

    // create sample
    mp_sample = createSample();

    // calculate scattered intensity from sample
    Simulation simulation(mp_options);
    simulation.setDetectorParameters(
        100, 0.0*Units::degree, 2.0*Units::degree, 100,
        0.0*Units::degree, 2.0*Units::degree);
    simulation.setBeamParameters(
        1.0*Units::angstrom, 0.2*Units::degree, 0.0*Units::degree);
    simulation.setBeamIntensity(1e8);

    // Run simulation
    simulation.setSample(*mp_sample);
    simulation.runSimulation();

    simulation.normalize();

    IsGISAXSTools::drawLogOutputDataPol(*simulation.getPolarizedOutputData(),
            "c1_polMeso", "Polarized Mesocrystal", "CONT4 Z",
            "Polarized Mesocrystal");
//    IsGISAXSTools::drawLogOutputData(*simulation.getOutputData(), "c1_test_meso_crystal", "mesocrystal",
//            "CONT4 Z", "mesocrystal");

    delete mp_sample;
}

MultiLayer* TestPolarizedMeso::createSample() const
{
    // create mesocrystal
    double surface_density =
        m_surface_filling_ratio/m_meso_width/m_meso_width;
    kvector_t magnetic_field(3.4, 3.4, 3.4);
    const IMaterial *p_particle_material =
            MaterialManager::getHomogeneousMagneticMaterial("nanoparticle",
                    2.84e-5, 4.7e-7, magnetic_field);
//    const IMaterial *p_particle_material =
//            MaterialManager::getHomogeneousMaterial("nanoparticle",
//                    2.84e-5, 4.7e-7);
//    FormFactorDecoratorDebyeWaller
//        ff_meso(ff_cyl.clone(),
//                m_sigma_meso_height*m_sigma_meso_height/2.0,
//                m_sigma_meso_radius*m_sigma_meso_radius/2.0);

    // Create multilayer
    MultiLayer *p_multi_layer = new MultiLayer();

    const IMaterial *p_air_material =
        MaterialManager::getHomogeneousMaterial("Air", 0.0, 0.0);
    const IMaterial *p_substrate_material =
        MaterialManager::getHomogeneousMaterial("Substrate", 7.57e-6, 1.73e-7);
    Layer air_layer;
    air_layer.setMaterial(p_air_material);
    Layer substrate_layer;
    substrate_layer.setMaterial(p_substrate_material);
    IInterferenceFunction *p_interference_funtion =
        new InterferenceFunctionNone();
    ParticleDecoration particle_decoration;
    size_t n_max_phi_rotation_steps = 11;
    size_t n_sizes = 4;

    double phi_step = M_PI/4.0/n_max_phi_rotation_steps;
    double phi_start = 0.0;
    Geometry::PTransform3D trafo;
    for (size_t i=0; i<n_max_phi_rotation_steps; ++i) {
        for (size_t j=0; j<n_sizes; ++j) {
            trafo = Geometry::PTransform3D(new
                Geometry::RotateZ_3D(phi_start + i*phi_step));
            double meso_size = m_meso_width + j*m_meso_size_steps;
            FormFactorBox ff_box(meso_size, meso_size, meso_size);
            particle_decoration.addParticle(
                createMeso(m_lattice_length_a, m_lattice_length_c,
                        p_particle_material, m_nanoparticle_size, &ff_box),
                trafo);
        }
    }

    particle_decoration.setTotalParticleSurfaceDensity(surface_density);
    particle_decoration.addInterferenceFunction(p_interference_funtion);

    air_layer.setDecoration(particle_decoration);

    LayerRoughness roughness(m_roughness, 0.3, 500.0*Units::nanometer);

    p_multi_layer->addLayer(air_layer);
    p_multi_layer->addLayerWithTopRoughness(substrate_layer, roughness);

    return p_multi_layer;
}

MesoCrystal* TestPolarizedMeso::createMeso(double a, double c,
        const IMaterial *p_material, double cube_size,
        const IFormFactor* p_meso_form_factor) const
{
    const Lattice *p_lat = createLattice(a, c);
    kvector_t bas_a = p_lat->getBasisVectorA();
    kvector_t bas_b = p_lat->getBasisVectorB();
    kvector_t bas_c = p_lat->getBasisVectorC();


    Particle particle(p_material, new FormFactorBox(cube_size, cube_size, cube_size));
    kvector_t position_0 = kvector_t(0.0, 0.0, 0.0);
    kvector_t position_1 = 1.0/2.0*(bas_a + bas_b + bas_c);
    std::vector<kvector_t> pos_vector;
    pos_vector.push_back(position_0);
    pos_vector.push_back(position_1);
    LatticeBasis basis(particle, pos_vector);

    Crystal npc(basis, *p_lat);
    delete p_lat;
//    double dw_factor = m_sigma_lattice_length_a*m_sigma_lattice_length_a/6.0;
//    npc.setDWFactor(dw_factor);
    return new MesoCrystal(npc.clone(), p_meso_form_factor->clone());
}

const Lattice *TestPolarizedMeso::createLattice(double a, double c) const
{
    kvector_t a_vec(a, 0.0, 0.0);
    kvector_t b_vec(0.0, a, 0.0);
    kvector_t c_vec(0.0, 0.0, c);

    Lattice *p_result = new Lattice(a_vec, b_vec, c_vec);
    return p_result;
}

