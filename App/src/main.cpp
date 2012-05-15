#include "TestFactory.h"
#include "DrawHelper.h"
#include "CommandLine.h"

#include <iostream>
#include <string>
#include "TApplication.h"



int main(int argc, char **argv)
{
    std::cout << "Hello Brave New World!" << std::endl;

    CommandLine args(argc, argv); // parsing command line arguments

    TApplication theApp("theApp", &argc, argv);
    DrawHelper::SetStyle();

    // running functional tests
    if( args.find("all") ) {
        // running all registered tests
        TestFactory::instance().execute_all();
    } else {
        // running specified tests
        for(size_t i=0; i<args.size(); i++) TestFactory::instance().execute( args[i] );
    }

    // saving postscript report
    if( args.find("report") ) {
        DrawHelper::SaveReport();
    }

    // holding graphics if not in the batch mode
    if(gApplication && !args.find("-b") ) {
        std::cout << "main() -> Info. Holding graphics, press ctrl-C to exit..." << std::endl;
        gApplication->Run();
    }

    return 0;
}
