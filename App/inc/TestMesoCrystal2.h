#ifndef TESTMESOCRYSTAL2_H
#define TESTMESOCRYSTAL2_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   TestMesoCrystal2.h
//! @brief  Definition of Layer class
//! @author Scientific Computing Group at FRM II
//! @date   27.09.2012

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


//- -------------------------------------------------------------------
//! @class TestMesoCrystal2
//! @brief Simulation and fit of 3D ordered particle assemblies
//- -------------------------------------------------------------------
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
