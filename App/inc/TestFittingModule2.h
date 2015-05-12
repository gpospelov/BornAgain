// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/inc/TestFittingModule2.h
//! @brief     Defines class TestFittingModule2.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef TESTFITTINGMODULE2_H
#define TESTFITTINGMODULE2_H

#include "IApplicationTest.h"
#include "OutputData.h"
#include "ISample.h"
#include "GISASSimulation.h"
#include "ISampleBuilder.h"

class FitSuite;

//! Test different fitting approaches on five-parameter sample.

//! Approaches are
//! (a) sample builder
//! (b) chi2 module
//! (c) different fit strategies
//! (d) mask on data
//!
class TestFittingModule2 : public IApplicationTest
{
public:
    TestFittingModule2();
    virtual ~TestFittingModule2();
    virtual void execute();

    //! builds sample for fitter testing
    class SampleBuilder : public ISampleBuilder
    {
    public:
        SampleBuilder();
        virtual ~SampleBuilder(){}
        virtual ISample *buildSample() const;
    protected:
        virtual void init_parameters();
    private:
        double m_cylinder_height;
        double m_cylinder_radius;
        double m_prism3_length;
        double m_prism3_height;
        double m_cylinder_ratio;
    };

    //! basic fit example
    void fit_example_basics();

    //! fit example with chi2 module adjustment
    void fit_example_chimodule();

    //! fit example with strategies
    void fit_example_strategy_data();
    void fit_example_strategy_parameters();

    //! fit example with data masking
    void fit_example_mask();

private:
    void initializeSimulation();
    void initializeRealData();

    OutputData<double> *mp_real_data;
    OutputData<double> *mp_simulated_data;
    GISASSimulation *mp_simulation;
    SampleBuilder_t mp_sample_builder;
    FitSuite *m_fitSuite;
};

#endif // TESTFITTINGMODULE2_H


