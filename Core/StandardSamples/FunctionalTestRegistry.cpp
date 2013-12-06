#include "FunctionalTestRegistry.h"
#include "Exceptions.h"
#include "SimulationRegistry.h"
#include "FileSystem.h"
#include "OutputDataIOFactory.h"
#include "OutputDataFunctions.h"
#include <iostream>
#include <iomanip>

FunctionalTestRegistry::Catalogue FunctionalTestRegistry::m_catalogue = FunctionalTestRegistry::Catalogue();


FunctionalTestRegistry::Catalogue::Catalogue()
{
    add("isgisaxs01",
        "Mixture of cylinders and prisms without interference",
        "isgisaxs01_reference.ima.gz", 2e-10);
}


void FunctionalTestRegistry::Catalogue::add(const std::string &name,
    const std::string &description, const std::string &reference, double threshold)
{
    catalogue_t::iterator it = m_data.find(name);
    if( it != m_data.end() ) {
        throw ExistingClassRegistrationException("FunctionalTestRegistry::Catalogue::add() -> "
                                                 "Error. Existing item " +name);
    }

    m_data[name] = TestInfo(name, description, reference, threshold);

}


void FunctionalTestRegistry::TestInfo::print()
{
    std::cout << std::setw(12) << std::left << m_name << " | "
              << std::setw(24) << std::left << m_description << " | "
              << std::setw(12) << std::left << m_reference << " | "
              << std::setw(6) << std::left  << m_threshold << std::endl;
}


void FunctionalTestRegistry::Catalogue::print()
{
    std::cout << "--- FunctionalTestRegistry::Catalogue::print() ---" << std::endl;
    for(catalogue_t::iterator it = m_data.begin(); it!= m_data.end(); ++it) {
        (*it).second.print();
    }
}

FunctionalTestRegistry::TestInfo FunctionalTestRegistry::Catalogue::getInfo(const std::string &name)
{
    catalogue_t::iterator it = m_data.find(name);
    if( it == m_data.end() ) {
        std::ostringstream ostr;
        ostr << "FunctionalTestRegistry::Catalogue::getInfo() -> Error. "
             << "Not existing test name '" << name << "'. "
             << "Existing items are:" << std::endl;
        for(catalogue_t::iterator it2 = m_data.begin(); it2!=m_data.end(); ++it2) {
            ostr << (*it2).first << std::endl;
        }
        throw ExistingClassRegistrationException(ostr.str());
    }
    return m_data[name];
}


bool FunctionalTestRegistry::isRegisteredName(const std::string &name)
{
    if( m_catalogue.m_data.find(name) == m_catalogue.m_data.end() ) {
        return false;
    } else {
        return true;
    }
}


int FunctionalTestRegistry::runTest(const std::string &name)
{
    TestInfo test_info = m_catalogue.getInfo(name);

    SimulationRegistry sim_registry;
    Simulation *simulation = sim_registry.createSimulation(name);

    std::string filename = Utils::FileSystem::GetReferenceDataDir() + test_info.m_reference;
    OutputData<double> *reference = OutputDataIOFactory::readIntensityData(filename);

    simulation->runSimulation();

    OutputData<double> *result = simulation->getIntensityData();

    double diff = OutputDataFunctions::GetDifference(*result,*reference);
    bool status_ok(true);
    if( diff > test_info.m_threshold ) status_ok=false;


    std::cout << test_info.m_name << " " << test_info.m_description
              << " " << diff
            << " " << (status_ok ? "[OK]" : "[FAILED]") << std::endl;

    delete reference;
    delete result;
    delete simulation;

    return (status_ok ? 0 : 1);
}


int FUNCTIONAL_TEST(const std::string &name)
{
    FunctionalTestRegistry tests;
    return tests.runTest(name);
}


