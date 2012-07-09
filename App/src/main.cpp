#include "TestFactory.h"
#include "DrawHelper.h"
#include "CommandLine.h"
#include "Utils.h"

#include <iostream>
#include <string>
#include "TROOT.h"
#include "TApplication.h"


int main(int argc, char **argv)
{
    std::cout << "Hello Brave New World!" << std::endl;

    // parsing command line arguments
    CommandLine args(argc, argv);
    if( !args.isGood() ) { args.print_help(); return 0; }

    // setting graphics environment
    TApplication theApp("theApp", 0, 0);
    DrawHelper::SetStyle();
    if( args.find("batch") ) gROOT->SetBatch(true);

    // running functional tests
    if( args.find("all") ) {
        // running all registered tests
        TestFactory::instance().execute_all();

    } else {
        // running specified tests
        for(size_t i=0; i<args.size(); i++) {
            if(args.isFunctionalTest( args[i] ))
            TestFactory::instance().execute( args[i] );
        }
    }

    // saving postscript report
    if( args.find("pdfreport") ) {
        DrawHelper::SaveReport();
    }

    // holding graphics if not in the batch mode
    if(gApplication && !gROOT->IsBatch() ) {
        std::cout << "main() -> Info. Holding graphics, press ctrl-C to exit..." << std::endl;
        gApplication->Run();
    }

    return 0;
}
