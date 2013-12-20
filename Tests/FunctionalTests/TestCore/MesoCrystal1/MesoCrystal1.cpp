#include "FunctionalTestRegistry.h"
#include "FileSystem.h"
#include "SimulationRegistry.h"

int main(int argc, char **argv)
{
    if(argc == 2) Utils::FileSystem::SetReferenceDataDir(argv[1]);

    FunctionalTestRegistry registry;
    FunctionalTest_t test = registry.getTest("mesocrystal01");
    test->runTest();
    test->getSimulation()->normalize();
    return test->analyseResults();
    //return FUNCTIONAL_TEST("mesocrystal01");
}

