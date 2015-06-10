#ifndef _TESTFIT01_H
#define _TESTFIT01_H

#include <string>
#include <vector>
class ISample;
class GISASSimulation;

namespace FunctionalTests {

//! functional test: two parameter fit using variety of minimizers
//
//! In this test we are using simple geometry: cylinders without interference in
//! air layer with two parameters (radius and height of cylinders), describing
//! the sample. Our "real" data is 2D intensity map obtained from the simulation of
//! the same geometry for fixed values height = 5nm and radius = 5nm.
//! Then we run our minimization consequently using different minimization engines,
//! with height=4nm, radius=6nm as starting fit parameter values.

class TestFit01
{
public:
    TestFit01();
    ~TestFit01();

    //! run several minimization rounds using different minimizers
    int run();

private:
    //! run fitting using specified minimizer, return true in the case of success
    bool run_fitting(const std::string &minimizer_name, const std::string &minimizer_algorithm);

    ISample *buildSample();
    GISASSimulation *createSimulation();

    //! represent minimizer name and type of minimization algorithm
    class Minimizer {
      public:
        Minimizer(const std::string &_name, const std::string &_algorithm)
            : name(_name), algorithm(_algorithm) {}
        std::string name;
        std::string algorithm;
    };

    std::string m_test_name;
    std::string m_test_description;
    std::vector<Minimizer > m_minimizers;
    double m_cylinder_height; //! value we are going to find
    double m_cylinder_radius; //! value we are going to find
};

}


#endif
