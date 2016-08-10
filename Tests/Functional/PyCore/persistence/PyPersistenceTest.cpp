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
#include "FileSystem.h"
#include "GISASSimulation.h"
#include "IntensityDataFunctions.h"
#include "IntensityDataIOFactory.h"
#include "PythonFormatting.h"
#include "SimulationFactory.h"
#include "Numeric.h"
#include "Utils.h"
#include <yaml-cpp/yaml.h>
#include <cstdio>
#include <fstream>
#include <sstream>

PyPersistenceTest::PyPersistenceTest(
    const std::string& directory, const std::string& name)
    : IReferencedTest(name, "persistence test on script "+name, 2e-10)
    , m_directory(directory)
{}

//! Runs a Python script, and returns true if the output of the script agrees with reference data.
bool PyPersistenceTest::runTest()
{
    std::string dat_stem = FileSystem::GetJoinPath(PYPERSIST_OUT_DIR, getName());
    std::string ref_stem = FileSystem::GetJoinPath(PYPERSIST_REF_DIR, getName());

    // Remove old output
    for (const std::string& fname: FileSystem::glob(dat_stem+".*.*")) {
        std::remove( fname.c_str() );
        std::cout << "Removed old output " << fname.c_str() << "\n";
    }

    // Run Python script
    std::string pyscript_filename = FileSystem::GetJoinPath(m_directory, getName()+".py");
    if (!runPython(pyscript_filename + " " + dat_stem))
        return false;

    // Retrieve new output and reference files
    std::map<const std::string, const std::string> dat = glob2map(dat_stem);
    std::map<const std::string, const std::string> ref = glob2map(ref_stem);
    if (dat.size()==0) {
        std::cerr << "There is no test output of form " << dat_stem << ".*.*\n";
        return false;
    }
    if (!compareFileMaps(dat, ref))
        return false;

    // Compare files one by one
    for (auto const& it: dat)
        if (!compareFilePair( it.second, ref[it.first] ) )
            return false;
    return true;
}

//! Globs for files of form *.<key1>.<key2>[.*], and returns a map with keys of the form
//! <key1>.<key2>, and values containing full file paths.
std::map<const std::string, const std::string>
PyPersistenceTest::glob2map(const std::string& stem)
{
    std::map<const std::string, const std::string> ret;
    for (const std::string& fpath: FileSystem::glob(stem+".*.*")) {
        std::vector<std::string> fname_segments =
            Utils::String::split(FileSystem::filename(fpath), ".");
        ret.insert(make_pair(fname_segments[1]+"."+fname_segments[2], fpath));
    }
    return ret;
}

//! Returns true if two file maps have the same set of keys.
bool PyPersistenceTest::compareFileMaps(
    const std::map<const std::string, const std::string>& dat,
    const std::map<const std::string, const std::string>& ref)
{
    bool success = true;
    // All dat files present in ref?
    for (auto const& it: dat) {
        if (ref.find(it.first)==ref.end()) {
            std::cerr << "For test output " << it.second
                      << " there is no reference file in " << PYPERSIST_REF_DIR << "\n";
            success = false;
        }
    }
    // All ref files present in dat?
    for (auto const& it: ref) {
        if (dat.find(it.first)==dat.end()) {
            std::cerr << "For reference file " << it.second
                      << " there is no test output in " << PYPERSIST_OUT_DIR << "\n";
            success = false;
        }
    }
    return success;
}

//! Returns true if test output and reference file agree.
bool PyPersistenceTest::compareFilePair(
    const std::string& dat_fpath, const std::string& ref_fpath)
{
    std::cout << "Comparing dat='" << dat_fpath << "' with ref='" << ref_fpath << "':\n";
    const std::string extension = Utils::String::split(FileSystem::filename(dat_fpath), ".")[2];
    if      ( extension=="int" )
        return compareIntensityPair( dat_fpath, ref_fpath );
    if ( extension=="yaml" )
        return compareYamlPair( dat_fpath, ref_fpath );
    std::cerr << "Failed: Unsupported file type '" << extension << "'\n";
    return false;
}

//! Returns true if intensity maps from test output and reference file agree reasonably.
bool PyPersistenceTest::compareIntensityPair(
    const std::string& dat_fpath, const std::string& ref_fpath)
{
    const OutputData<double>* dat = IntensityDataIOFactory::readOutputData( dat_fpath );
    const OutputData<double>* ref = IntensityDataIOFactory::readOutputData( ref_fpath );
    return compareIntensityMaps(*dat, *ref);
}

//! Returns true if YAML files from test output and reference agree.
bool PyPersistenceTest::compareYamlPair(
    const std::string& dat_fpath, const std::string& ref_fpath)
{
    std::fstream fdat(dat_fpath);
    std::fstream fref(ref_fpath);
    return compareYamlNode( YAML::Load(fdat), YAML::Load(fref) );
}

//! Returns true if all entries of the two YAML files agree.
//! Floating-point entries must agree within a certain tolerance.
//! The investigation is performed recursively, iterating over all lists and maps.
bool PyPersistenceTest::compareYamlNode(const YAML::Node& dat, const YAML::Node& ref)
{
//    std::cout << "DEBUG: " << dat.as<std::string>() << " vs " << ref.as<std::string>() << "\n";
    if (dat.Type() != ref.Type()) {
        std::cerr << "YAML node type differs: " << dat.Type() << " vs " << ref.Type() << "\n";
        return false;
    }
    if      (dat.Type()==YAML::NodeType::Undefined)
        throw std::runtime_error("Invalid node type 'Undefined' in YAML tree");
    else if (dat.Type()==YAML::NodeType::Null)
        throw std::runtime_error("Invalid node type 'Null' in YAML tree");
    else if (dat.Type()==YAML::NodeType::Sequence) {
        auto it_dat=dat.begin();
        auto it_ref=ref.begin();
        for (size_t idx=0; ; ++it_dat, ++it_ref, ++idx) {
            if (it_dat==dat.end() || it_ref==ref.end()) {
                if (!(it_dat==dat.end() && it_ref==ref.end())) {
                    std::cerr << "lists have different length\n";
                    return false;
                }
                return true; // regular exit
            }
            // now recurse into the node
            if (!compareYamlNode(*it_dat, *it_ref)) {
                std::cerr << "at list position " << idx << "\n";
                return false;
            }
        }
    } else if (dat.Type()==YAML::NodeType::Map) {
        auto it_dat=dat.begin();
        auto it_ref=ref.begin();
        for ( ; ; ++it_dat, ++it_ref) {
            if (it_dat==dat.end() || it_ref==ref.end()) {
                if (!(it_dat==dat.end() && it_ref==ref.end())) {
                    std::cerr << "maps have different length\n";
                    return false;
                }
                return true; // regular exit
            }
            // now recurse into the node
            if (!compareYamlNode(it_dat->second, it_ref->second)) {
                std::cerr << "at map entry [" << it_dat->first << "]\n";
                return false;
            }
        }
    } else if (dat.Type()==YAML::NodeType::Scalar) {
        if (dat.as<std::string>() == ref.as<std::string>())
            return true;
        try {
            if (!Numeric::areAlmostEqual( dat.as<double>(), ref.as<double>(), 1e-1 )) {
                std::cerr << "numbers differ: " << dat << " vs " << ref << "\n";
                return false;
            }
            return true;
        } catch(...) {
            std::cerr << "scalar entries differ: '" << dat << "' vs '" << ref << "'\n";
            return false;
        }
    } else
        throw std::runtime_error("Bug in PyPersistenceTest::compareYamlNode: unexpected node type");
    return true;
}
