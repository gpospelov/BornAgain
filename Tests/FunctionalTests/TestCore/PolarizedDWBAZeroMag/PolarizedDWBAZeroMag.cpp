#include "FunctionalTestRegistry.h"
#include "FileSystem.h"

int main(int argc, char **argv)
{
    if(argc == 2) Utils::FileSystem::SetReferenceDataDir(argv[1]);
    return FUNCTIONAL_TEST("PolarizedDWBAZeroMag");
}
