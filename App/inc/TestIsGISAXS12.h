#ifndef TESTISGISAXS12_H
#define TESTISGISAXS12_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   TestIsGISAXS12.h
//! @brief  Definition of TestIsGISAXS12 class for IsGISAXS validation
//! @author Scientific Computing Group at FRM II
//! @date   08.11.2012

#include "IFunctionalTest.h"
#include "OutputData.h"
#include "ISample.h"
#include "ISampleBuilder.h"
#include <string>

class GISASExperiment;
class FitSuite;

//- -------------------------------------------------------------------
//! @class TestIsGISAXS12
//! @brief Comparison with IsGISAXS ex-12: constrained fit example
//- -------------------------------------------------------------------
class TestIsGISAXS12 : public IFunctionalTest
{
public:
    TestIsGISAXS12();
    virtual ~TestIsGISAXS12();
    virtual void execute();

private:
    typedef std::vector<OutputData<double > *> DataScan_t;

    //! builds sample for fitter testing
    class TestSampleBuilder : public ISampleBuilder
    {
    public:
        TestSampleBuilder();
        virtual ~TestSampleBuilder(){}

        virtual ISample *buildSample() const;
    protected:
        //! initialize pool parameters, i.e. register some of class members for later access via parameter pool
        virtual void init_parameters();
        double m_particle_probability;
        double m_particle_radius1;
        double m_particle_radius2;
        double m_dispersion_radius1;
        double m_dispersion_radius2;
        double m_height_aspect_ratio1;
        double m_height_aspect_ratio2;
        double m_interf_distance;
        double m_interf_width;
    };

    //! represent single line stored in isgisaxs *.dat file with data to fit
    class IsgiData {
    public:
        IsgiData() : use_it(true), phif(0), alphaf(0), intensity(0), err(0) {}
        bool use_it;
        double phif;
        double alphaf;
        double intensity;
        double err;
    };

    //! initialize experiment
    void initialiseExperiment();

    //! run standard isgisaxs comparison for the given sample
    void run_isgisaxs_comparison();

    //! run test fit
    void run_test_fit();

    //! run isgisaxs ex-12 style fit
    void run_isgisaxs_fit();

    //! plot isgisaxs data together with test simulation
    void plot_isgisaxs_data();

    //!  read special isgisaxs *.dat file with data to fit
    void read_isgisaxs_datfile(const std::string &filename);

    //! convert isgisaxs 1d scan to output data 2d object
    OutputData<double> *convert_isgi_scan(std::vector<IsgiData > &isgi_data);

    std::string m_data_path;
    GISASExperiment *m_experiment;
    ISampleBuilder *m_sample_builder;
    FitSuite *m_fitSuite;

    DataScan_t m_isgi_scans; //! vector of OutputData's representing isgisaxs scans
    double m_isgi_fixed_alphaf;
    double m_isgi_fixed_phif;
};


#endif // TESTISGISAXS12_H
