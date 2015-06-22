#include "FunctionalTestAssembler.h"
//#include "FileSystem.h"
#include <iostream>

int main(int argc, char **argv)
{
  //    if(argc == 2) Utils::FileSystem::SetReferenceDataDir(argv[1]);
    std::cout << "main() -> argc:" << argc << " " << argv[1] << std::endl;
    return ADVANCED_FUNCTIONAL_TEST("FormFactors");
}
