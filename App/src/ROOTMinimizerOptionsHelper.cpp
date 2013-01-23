#include "ROOTMinimizerOptionsHelper.h"
#include "ROOTGSLSimAnMinimizer.h"
#include "Utils.h"
#include <boost/lexical_cast.hpp>


// ----------------------------------------------------------------------------
// translate text with options into appropriate calls of minimizer's set method
// "tolerance=0.1:precision=0.001" ->setTolerance(), ->setPrecision()
// ----------------------------------------------------------------------------
void ROOTMinimizerOptionsHelper::setOptions(ROOT::Math::Minimizer *minimizer, const std::string &options)
{
    const std::string delimeter(":");
    std::vector<std::string> tokens = Utils::String::Split(options, delimeter);
    for(size_t i=0; i<tokens.size(); ++i) processCommand(minimizer, tokens[i]);
}


// ----------------------------------------------------------------------------
// process single command
// command "tolerance=0.1" will cause minimizer->SetTolerance(0.1)
// ----------------------------------------------------------------------------
bool ROOTMinimizerOptionsHelper::processCommand(ROOT::Math::Minimizer *minimizer, const std::string &command)
{
    bool success(false);
    success = processCommandAll(minimizer, command);

    ROOT::Patch::GSLSimAnMinimizer *gslSimAn = dynamic_cast<ROOT::Patch::GSLSimAnMinimizer *>(minimizer);
    if(gslSimAn) {
        success = processCommandGSLSimAn(gslSimAn, command);
    }

    if( !success ) {
        throw LogicErrorException("ROOTMinimizerOptionsHelper::processCommand() -> Error! Can't parse command '"+command+"'");
    }

    return success;
}


// process single command common for all minimizers
bool ROOTMinimizerOptionsHelper::processCommandAll(ROOT::Math::Minimizer *minimizer, const std::string &command)
{
    std::vector<std::string> tokens = Utils::String::Split(command, "=");
    assert(tokens.size() ==2);
    std::string name = tokens[0];
    std::string number = tokens[1];

    bool success(true);
    if(name == "tolerance") {
        minimizer->SetTolerance( boost::lexical_cast<double>(number) );

    } else if(name == "precision") {
        minimizer->SetPrecision( boost::lexical_cast<double>(number) );

    } else if(name == "strategy") {
        minimizer->SetStrategy( boost::lexical_cast<int>(number) );

    } else if(name == "print") {
        minimizer->SetPrintLevel( boost::lexical_cast<int>(number) );

    } else if(name == "functioncalls") {
        minimizer->SetMaxFunctionCalls(boost::lexical_cast<int>(number) );

    } else if(name == "iterations") {
        minimizer->SetMaxIterations(boost::lexical_cast<int>(number) );

    } else {
        success=false;
    }
    return success;
}


// process single command specific for GSL simulated annealing minimizer
bool ROOTMinimizerOptionsHelper::processCommandGSLSimAn(ROOT::Patch::GSLSimAnMinimizer *minimizer, const std::string &command)
{
    std::vector<std::string> tokens = Utils::String::Split(command, "=");
    assert(tokens.size() ==2);
    std::string name = tokens[0];
    std::string number = tokens[1];

    ROOT::Math::GSLSimAnParams &pars = minimizer->getSolver().Params();
    bool success(true);

    if(name == "ntries") {
        pars.n_tries = boost::lexical_cast<int>(number);

    } else if( name == "niters") {
        pars.iters_fixed_T = boost::lexical_cast<int>(number);

    } else if( name == "step_size") {
        pars.step_size = boost::lexical_cast<double>(number);

    } else if( name == "k" ) {
        pars.k = boost::lexical_cast<double>(number);

    } else if( name == "t_initial" ) {
        pars.t_initial = boost::lexical_cast<double>(number);

    } else if( name == "mu" ) {
        pars.mu = boost::lexical_cast<double>(number);

    } else if( name == "t_min" ) {
        pars.t_min = boost::lexical_cast<double>(number);

    } else {
        success=false;
    }

    return success;
}


