// ************************************************************************** //
//                                                                         
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/inc/TestMesoCrystal1.h
//! @brief     Defines class TestMesoCrystal1.
//
//! Homepage:  apps.jcns.fz-juelich.de/BornAgain
//! License:   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef TESTMESOCRYSTAL1_H_
#define TESTMESOCRYSTAL1_H_

#include "IFunctionalTest.h"
#include "OutputData.h"
#include "FormFactors.h"
#include "ISample.h"
#include "ISampleBuilder.h"
#include "InterferenceFunction1DParaCrystal.h"
#include "InterferenceFunctionNone.h"
#include "MesoCrystal.h"
#include "Lattice.h"

//! Simulation of 3D ordered particle assemblies.

class TestMesoCrystal1 : public IFunctionalTest
{
 public:
    TestMesoCrystal1();
    virtual ~TestMesoCrystal1();
    virtual void execute();

    class SampleBuilder : public ISampleBuilder
    {
    public:
        SampleBuilder();
        virtual ~SampleBuilder(){}

        virtual ISample *buildSample() const;
    protected:
        //! Initializes pool parameters
        virtual void init_parameters();
    private:
        MesoCrystal *createMesoCrystal(double particle_radius, complex_t n_particle,
                const IFormFactor *p_meso_form_factor) const;
        const Lattice *createLattice(double stacking_radius) const;
        double m_meso_radius;
        double m_surface_filling_ratio;
        double m_meso_height;
        double m_sigma_meso_height;
        double m_sigma_meso_radius;
        double m_lattice_length_a;
        double m_nanoparticle_radius;
        double m_sigma_nanoparticle_radius;
        double m_sigma_lattice_length_a;
        double m_roughness;
    };

 private:
    OutputData<double> *mp_intensity_output;
    ISampleBuilder *mp_sample_builder;
};

#endif /* TESTMESOCRYSTAL1_H_ */


