// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/PyCore/suite/PyPersistenceTest.cpp
//! @brief     Implements class PyPersistenceTest
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "PyPersistenceTest.h"
#include "BAPython.h"
#include "FileSystem.h"
#include "GISASSimulation.h"
#include "IntensityDataFunctions.h"
#include "IntensityDataIOFactory.h"
#include "PythonFormatting.h"
#include "SimulationFactory.h"
#include "Utils.h"
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <map>

PyPersistenceTest::PyPersistenceTest(
    const std::string& directory, const std::string& name)
    : IFunctionalTest(name, "persistence test on script "+name)
    , m_directory(directory)
    , m_threshold(2e-10)
    , m_difference(0)
{}

void PyPersistenceTest::runTest()
{
    // Set output data filename stem, and remove old output files
    std::string dat_stem = Utils::FileSystem::GetJoinPath(PYPERSIST_TMP_DIR, getName());
    for (const std::string& fname: Utils::FileSystem::glob(dat_stem+".*.*")) {
        std::remove( fname.c_str() );
        std::cout << "Removed old result " << fname.c_str() << "." << std::endl/*sic*/;
    }

    // Run Python script
    std::string py_filename = Utils::FileSystem::GetJoinPath(m_directory, getName() + ".py");
    std::string command =
        std::string("PYTHONPATH=") + BUILD_LIB_DIR + " " +
        BORNAGAIN_PYTHON_EXE + " " + py_filename + " " + dat_stem;
    std::cout << "Now running command '" << command << "'." << std::endl/*sic*/;
    int ret = std::system(command.c_str());
    if (ret!=0) {
        std::cerr << "Command returned non-zero value " << ret << ".\n";
        m_result = FAILED;
        return;
    }

    // Read back simulation results
    std::map<const std::string, const std::string> dat;
    std::string dat_pattern = dat_stem + ".*.*";
    for (const std::string& fname: Utils::FileSystem::glob(dat_pattern))
        dat.insert(make_pair(Utils::String::split(fname,".")[1]+"."+
                             Utils::String::split(fname,".")[2],
                             fname));
    if (dat.size()==0) {
        std::cerr << "There is no test output of form " << dat_pattern << "\n";
        m_result = FAILED;
        return;
    }


    // Read reference files
    std::string ref_stem = Utils::FileSystem::GetJoinPath(PYPERSIST_REF_DIR, getName());
    std::map<const std::string, const std::string> ref;
    for (const std::string& fname: Utils::FileSystem::glob(ref_stem+".*.*.gz"))
        ref.insert(make_pair(Utils::String::split(fname,".")[1]+"."+
                             Utils::String::split(fname,".")[2],
                             fname));

    // Compare file lists
    m_result = SUCCESS;
    for( auto const& it: dat ) {
        if( ref.find(it.first)==ref.end() ) {
            std::cerr << "For test output " << it.second
                      << " there is no reference file in " << PYPERSIST_REF_DIR << "\n";
            m_result = FAILED;
        }
    }
    for( auto const& it: ref ) {
        if( dat.find(it.first)==dat.end() ) {
            std::cerr << "For reference file " << it.second
                      << " there is no test output in " << PYPERSIST_TMP_DIR << "\n";
            m_result = FAILED;
        }
    }
    if (m_result==FAILED)
        return;


//    const OutputData<double>* dat = IntensityDataIOFactory::readOutputData( fname );


    /*
    const OutputData<double>* reference;
    try {
        reference = IntensityDataIOFactory::readOutputData( ref_filename );
    } catch(const std::exception& ex) {
        std::cerr << "Cannot read reference file " << ref_filename << "\n";
        m_result = FAILED;
        return;
    }

    // Compare data
    m_difference = IntensityDataFunctions::getRelativeDifference(*data, *reference);
    m_result = m_difference > m_threshold ? FAILED_DIFF : SUCCESS;
    */
}

void PyPersistenceTest::printResults(std::ostream& ostr) const
{
    ostr << getFormattedInfoString();
    ostr << Utils::String::getScientificDoubleString(m_difference);
}
