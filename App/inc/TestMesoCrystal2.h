// ************************************************************************** //
//                                                                           
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/inc/TestMesoCrystal2.h 
//! @brief     Defines class TestMesoCrystal2.
//
//! Homepage:  apps.jcns.fz-juelich.de/BornAgain
//! License:   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef TESTMESOCRYSTAL2_H
#define TESTMESOCRYSTAL2_H

#include "IFunctionalTest.h"
#include "Types.h"
#include "OutputData.h"
#include "ISampleBuilder.h"

class Simulation;
class ISample;
class MesoCrystal;
class IFormFactor;
class Lattice;
class FitSuite;

//! Simulation and fit of 3D ordered particle assemblies.

class TestMesoCrystal2 : public IFunctionalTest
{
public:
    typedef std::vector<std::vector<std::string > > fixplan_t; // to hold sets of fit parameters to fix/release

    TestMesoCrystal2();
    virtual ~TestMesoCrystal2();

    virtual void execute();

    class SampleBuilder : public ISampleBuilder
    {
    public:
        SampleBuilder();
        virtual ~SampleBuilder(){}

        virtual ISample *buildSample() const;
    protected:
        //! initialize pool parameters
        virtual void init_parameters();
    private:
//        MesoCrystal *createMesoCrystal(double particle_radius, complex_t n_particle, const IFormFactor *p_meso_form_factor) const;
//        const Lattice *createLattice(double stacking_radius) const;
        MesoCrystal *createMesoCrystal(double stacking_radius_a, double stacking_radius_c, complex_t n_particle, const IFormFactor *p_meso_form_factor) const;
        const Lattice *createLattice(double stacking_radius_a, double stacking_radius_c) const;
        double m_meso_radius;
        double m_surface_filling_ratio;
        double m_meso_height;
        double m_sigma_meso_height;
        double m_sigma_meso_radius;
        double m_lattice_length_a;
        double m_lattice_length_c;
        double m_nanoparticle_radius;
        double m_sigma_nanoparticle_radius;
        double m_sigma_lattice_length_a;
        double m_roughness;
    };

    void draw_results(); // plot fit results
    void run_fit(); // run fit

    void fitsuite_setup(int nconfig);
    void fitsuite_config1();
    void fitsuite_config2();
    void fitsuite_config3();
    void fitsuite_config4();

private:
    void initializeRealData();
    void initializeSimulation(const OutputData<double> *output_data=0);

    OutputData<double> *m_real_data;
    ISampleBuilder *m_sample_builder;
    Simulation *m_simulation;
    FitSuite *m_fitSuite;
};

#endif // TESTMESOCRYSTAL2_H
