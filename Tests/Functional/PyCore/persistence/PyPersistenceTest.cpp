// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/PyCore/persistence/PyPersistenceTest.cpp
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
#include <sstream>
#include <map>

PyPersistenceTest::PyPersistenceTest(
    const std::string& directory, const std::string& name)
    : IReferencedTest(name, "persistence test on script "+name, 2e-10)
    , m_directory(directory)
{}

void PyPersistenceTest::runTest()
{
    // Set output data filename stem, and remove old output files
    std::string dat_stem = FileSystem::GetJoinPath(PYPERSIST_OUT_DIR, getName());
    for (const std::string& fname: FileSystem::glob(dat_stem+".*.*")) {
        std::remove( fname.c_str() );
        std::cout << "Removed old output " << fname.c_str() << ".\n";
    }

    // Run Python script
    std::string py_filename = FileSystem::GetJoinPath(m_directory, getName() + ".py");
    std::string command = std::string("PYTHONPATH=") + BUILD_LIB_DIR + " " +
        BORNAGAIN_PYTHON_EXE + " " + py_filename + " " + dat_stem;
    std::cout << command << std::endl/*sic*/; // flush output before calling std::system
    int ret = std::system(command.c_str());
    if (ret!=0) {
        std::cerr << "Command returned non-zero value " << ret << ".\n";
        m_result = FAILED;
        return;
    }

    // Glob simulation results
    std::map<const std::string, const std::string> dat;
    std::string dat_pattern = dat_stem + ".*.*";
    for (const std::string& fpath: FileSystem::glob(dat_pattern)) {
        std::vector<std::string> fname_segments =
            Utils::String::split(FileSystem::filename(fpath), ".");
        dat.insert(make_pair(fname_segments[1]+"."+fname_segments[2], fpath));
    }
    if (dat.size()==0) {
        std::cerr << "There is no test output of form " << dat_pattern << "\n";
        m_result = FAILED;
        return;
    }

    // Glob reference files
    std::string ref_stem = FileSystem::GetJoinPath(PYPERSIST_REF_DIR, getName());
    std::map<const std::string, const std::string> ref;
    for (const std::string& fpath: FileSystem::glob(ref_stem+".*.*")) {
        std::vector<std::string> fname_segments =
            Utils::String::split(FileSystem::filename(fpath), ".");
        ref.insert(make_pair(fname_segments[1]+"."+fname_segments[2], fpath));
    }
    // Compare file lists
    m_result = SUCCESS;
    for (auto const& it: dat) {
        if (ref.find(it.first)==ref.end()) {
            std::cerr << "For test output " << it.second
                      << " there is no reference file in " << PYPERSIST_REF_DIR << "\n";
            m_result = FAILED;
        }
    }
    for (auto const& it: ref) {
        if (dat.find(it.first)==dat.end()) {
            std::cerr << "For reference file " << it.second
                      << " there is no test output in " << PYPERSIST_OUT_DIR << "\n";
            m_result = FAILED;
        }
    }
    if (m_result==FAILED)
        return;

    // Compare file pairs
    for (auto const& it: dat)
        if (!compareFilePair( it.second, ref[it.first] ) )
            m_result = FAILED_DIFF;
}

//! Returns true if test output and reference file agree.
bool PyPersistenceTest::compareFilePair(const std::string& dat_fpath, const std::string& ref_fpath)
{
    std::cout << "Comparing dat='" << dat_fpath << "' with ref='" << ref_fpath << "':\n";
    const std::string extension = Utils::String::split(FileSystem::filename(dat_fpath), ".")[2];
    if      ( extension=="int" )
        return compareIntensityPair( dat_fpath, ref_fpath );
    if ( extension=="yaml" )
        return compareYamlPair( dat_fpath, ref_fpath );
    std::cerr << "Failed: Unsupported file type '" << extension << "'.\n";
    return false;
}

//! Returns true if intensity maps from test output and reference file agree reasonably.
bool PyPersistenceTest::compareIntensityPair(
    const std::string& dat_fpath, const std::string& ref_fpath)
{
    const OutputData<double>* dat = IntensityDataIOFactory::readOutputData( dat_fpath );
    const OutputData<double>* ref = IntensityDataIOFactory::readOutputData( ref_fpath );
    return compareIntensityMaps(*dat, *ref)==SUCCESS;
}

//! Returns true if YAML files from test output and reference agree.
bool PyPersistenceTest::compareYamlPair(const std::string& dat_fpath, const std::string& ref_fpath)
{
    std::fstream fdat(dat_fpath);
    std::fstream fref(ref_fpath);
    const YAML::Node& dat = YAML::Load(fdat);
    const YAML::Node& ref = YAML::Load(fref);
    return compareYamlNode( YAML::Load(fdat), YAML::Load(fref) );
}

    for (size_t i = 1; ; ++i) {
        std::string datline;
        std::string refline;
        std::getline(fdat, datline);
        std::getline(fref, refline);
        if (datline!=refline) {
            std::cerr << "Line " << i << " of " << dat_fpath << " and " << ref_fpath
                      << " differs:\n";
            std::cerr << "dat: '" << datline << "'\n";
            std::cerr << "ref: '" << refline << "'\n";
            return false;
        }
        if (fdat.eof() && fref.eof())
            break;
        if (fdat.eof() || fref.eof()) {
            std::cerr << "File length of " << dat_fpath << " and " << ref_fpath << " differs.\n";
            return false;
        }
    }
    std::cout << "Files fully agree.\n";
    return true;
}
