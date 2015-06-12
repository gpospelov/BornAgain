#include "FunctionalTestAssembler.h"
//#include "FileSystem.h"
#include <iostream>

int main(int argc, char **argv)
{
  //    if(argc == 2) Utils::FileSystem::SetReferenceDataDir(argv[1]);
    std::cout << "XXX" << argc << std::endl;
    return ADVANCED_FUNCTIONAL_TEST("isgisaxs01");
}
