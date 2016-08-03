// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/RootWrapper/ROOTMinimizerHelper.cpp
//! @brief     Implements class ROOTMinimizerHelper.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ROOTMinimizerHelper.h"
#include "Math/GenAlgoOptions.h"
#include "Math/Minimizer.h"
#include "StringUtils.h"

// ----------------------------------------------------------------------------
// translate text with options into appropriate calls of minimizer's set method
// "tolerance=0.1:precision=0.001" ->setTolerance(0.1), ->setPrecision(0.001)
// ----------------------------------------------------------------------------
//void ROOTMinimizerHelper::setOptions(ROOT::Math::Minimizer *minimizer, const std::string& options)
//{
//    const std::string delimeter(":");
//    std::vector<std::string> tokens = Utils::String::Split(options, delimeter);
//    for(size_t i=0; i<tokens.size(); ++i) processCommand(minimizer, tokens[i]);
//}


//// ----------------------------------------------------------------------------
//// process single command
//// command "tolerance=0.1" will cause minimizer->SetTolerance(0.1)
//// ----------------------------------------------------------------------------
//bool ROOTMinimizerHelper::processCommand(ROOT::Math::Minimizer *minimizer, const std::string& command)
//{
//    bool success(false);
//    success = processCommandAll(minimizer, command);

//    ROOT::Patch::GSLSimAnMinimizer *gslSimAn = dynamic_cast<ROOT::Patch::GSLSimAnMinimizer *>(minimizer);
//    if(gslSimAn) {
//        success = processCommandGSLSimAn(gslSimAn, command);
//    }

//    if( !success ) {
//        throw std::runtime_error("ROOTMinimizerOptionsHelper::processCommand() -> Error! Can't parse command '"+command+"'");
//    }

//    return success;
//}


//// process single command common for all minimizers
//bool ROOTMinimizerHelper::processCommandAll(ROOT::Math::Minimizer *minimizer, const std::string& command)
//{
//    std::vector<std::string> tokens = Utils::String::Split(command, "=");
//    assert(tokens.size() ==2);
//    std::string name = tokens[0];
//    std::string number = tokens[1];

//    bool success(true);
//    if(name == "tolerance") {
//        minimizer->SetTolerance( boost::lexical_cast<double>(number) );

//    } else if(name == "precision") {
//        minimizer->SetPrecision( boost::lexical_cast<double>(number) );

//    } else if(name == "strategy") {
//        minimizer->SetStrategy( boost::lexical_cast<int>(number) );

//    } else if(name == "print") {
//        minimizer->SetPrintLevel( boost::lexical_cast<int>(number) );

//    } else if(name == "functioncalls") {
//        minimizer->SetMaxFunctionCalls(boost::lexical_cast<int>(number) );

//    } else if(name == "iterations") {
//        minimizer->SetMaxIterations(boost::lexical_cast<int>(number) );

//    } else {
//        success=false;
//    }
//    return success;
//}


// process single command specific for GSL simulated annealing minimizer
//bool ROOTMinimizerHelper::processCommandGSLSimAn(ROOT::Patch::GSLSimAnMinimizer *minimizer, const std::string& command)
//{
//    std::vector<std::string> tokens = Utils::String::Split(command, "=");
//    assert(tokens.size() ==2);
//    std::string name = tokens[0];
//    std::string number = tokens[1];

//    ROOT::Math::GSLSimAnParams& pars = minimizer->getSolver().Params();
//    bool success(true);

//    if(name == "ntries") {
//        pars.n_tries = boost::lexical_cast<int>(number);

//    } else if( name == "niters") {
//        pars.iters_fixed_T = boost::lexical_cast<int>(number);

//    } else if( name == "step_size") {
//        pars.step_size = boost::lexical_cast<double>(number);

//    } else if( name == "k" ) {
//        pars.k = boost::lexical_cast<double>(number);

//    } else if( name == "t_initial" ) {
//        pars.t_initial = boost::lexical_cast<double>(number);

//    } else if( name == "mu" ) {
//        pars.mu = boost::lexical_cast<double>(number);

//    } else if( name == "t_min" ) {
//        pars.t_min = boost::lexical_cast<double>(number);

//    } else {
//        success=false;
//    }

//    return success;
//}

// Printing minimizer results on the screen
void ROOTMinimizerHelper::printResults(const ROOTMinimizer *minimizer)
{
    std::cout << "--------------------------------------------------------------------------------" << std::endl;
    std::cout << std::setw(25) << std::left << "  MinimizerType"      << ": " << minimizer->getMinimizerName() << std::endl;
    std::cout << std::setw(25) << std::left << "  MinimizerAlgorithm" << ": " << minimizer->getAlgorithmName() << std::endl;
    //printOptions(minimizer->getROOTMinimizer());
    std::cout << "--- Options --------------------------------------------------------------------" << std::endl;
    minimizer->getOptions()->print();
    printStatus(minimizer->getROOTMinimizer());
    printVariables(minimizer->getROOTMinimizer());
    // own print method of the minimizer
    //m_root_minimizer->PrintResults();
}


// print minimizer description
void ROOTMinimizerHelper::printOptions(const BA_ROOT::Math::Minimizer *minimizer)
{
    std::cout << "--- Options --------------------------------------------------------------------" << std::endl;
    BA_ROOT::Math::MinimizerOptions opt = minimizer->Options();
    std::cout << std::setw(25) << std::left << "  Strategy"           << ": " << minimizer->Strategy() << std::endl;
    std::cout << std::setw(25) << std::left << "  Tolerance"          << ": " << minimizer->Tolerance() << std::endl;
    std::cout << std::setw(25) << std::left << "  MaxFunctionCalls"   << ": " << minimizer->MaxFunctionCalls() << std::endl;
    std::cout << std::setw(25) << std::left << "  MaxIterations"      << ": " << minimizer->MaxIterations() << std::endl;
    std::cout << std::setw(25) << std::left << "  Precision"          << ": " << minimizer->Precision() << std::endl;
    std::cout << std::setw(25) << std::left << "  ErrorDefinition"    << ": " << minimizer->ErrorDef() << " (1-chi2, 0.5 likelihood)" << std::endl;
    //std::cout << std::setw(25) << std::left << "  ExtraOptions"       << ": " << opt.ExtraOptions() << std::endl;
    if(opt.ExtraOptions()) {
        std::cout << "--- Extra Options --------------------------------------------------------------" << std::endl;
        opt.ExtraOptions()->Print();
    }

}


void ROOTMinimizerHelper::printStatus(const BA_ROOT::Math::Minimizer *minimizer)
{
    std::cout << "--- Status --------------------------------------------------------------------- " << std::endl;
    std::map<int, std::string> minimizerStatus;
    minimizerStatus[0] = std::string("OK, valid minimum");
    minimizerStatus[1] = std::string("Didn't converge, covariance was made pos defined");
    minimizerStatus[2] = std::string("Didn't converge, Hesse is invalid");
    minimizerStatus[3] = std::string("Didn't converge, Edm is above max");
    minimizerStatus[4] = std::string("Didn't converge, reached call limit");
    minimizerStatus[5] = std::string("Didn't converge, unknown failure");
    std::map<int, std::string> validErrorStatus;
    validErrorStatus[0] = std::string("No detailed error validation");
    validErrorStatus[1] = std::string("Performed detailed error validation"); // true if Minimizer has performed a detailed error validation (e.g. run Hesse for Minuit)
    std::map<int, std::string> covMatrixStatus;
    covMatrixStatus[-1] = std::string("not available (inversion failed or Hesse failed)");
    covMatrixStatus[0] = std::string("available but not positive defined");
    covMatrixStatus[1] = std::string("covariance only approximate");
    covMatrixStatus[2] = std::string("full matrix but forced pos def");
    covMatrixStatus[3] = std::string("full accurate");
    std::cout << std::setw(25) << std::left << "  Status           "      << ": " << minimizer->Status() << " '" << minimizerStatus[minimizer->Status()] << "'" << std::endl;
    std::cout << std::setw(25) << std::left << "  IsValidError     "      << ": " << minimizer->IsValidError() << " '" << validErrorStatus[minimizer->Status()] << "'" <<std::endl;
    std::cout << std::setw(25) << std::left << "  CovMatrixStatus"        << ": " << minimizer->CovMatrixStatus() << " '" << covMatrixStatus[minimizer->CovMatrixStatus()] << "'" << std::endl;
    std::cout << std::setw(25) << std::left << "  NCalls"                 << ": " << minimizer->NCalls() << std::endl;
//    if(m_gradient_func) {
//        std::cout << std::setw(25) << std::left << "  NCallsGradient "                 << ": " << m_gradient_func->NCalls() << std::endl;
//    }
//    if(m_chi2_func) {
//        std::cout << std::setw(25) << std::left << "  NCallsChi2 "                 << ": " << m_chi2_func->NCalls() << std::endl;
//    }
    std::cout << std::setw(25) << std::left << "  MinValue"
              << ": " << std::scientific << std::setprecision(8)
              << minimizer->MinValue() << std::endl;
    std::cout << std::setw(25) << std::left << "  Edm"
              << ": " << std::scientific << std::setprecision(8)
              << minimizer->Edm() << std::endl;
//     Status code of minimizer is updated according to the following convention (in case Hesse failed)
//     status += 100*hesseStatus where hesse status is:
//     status = 1 : hesse failed
//     status = 2 : matrix inversion failed
//     status = 3 : matrix is not pos defined
}


void ROOTMinimizerHelper::printVariables(const BA_ROOT::Math::Minimizer *minimizer)
{
    std::cout
        << "--- Variables ------------------------------------------------------------------\n";
    std::cout << std::setw(25) << std::left << "  NumberOfVariables"      << ": "
              << minimizer->NFree() << " (free), " << minimizer->NDim() << " (total) " << std::endl;
    std::cout << std::setw(25) << std::left << "  Errors"
              << ": " << (minimizer->Errors() ? "yes, see below" : "no access") << std::endl;
    std::cout << "      " << std::setw(5) << std::left << "Npar"
              << std::setw(39) << std::left << " Name"
              << std::setw(14) << "Value"
              << std::setw(14) << "Error"
              << std::setw(14) << "GlobalCC" << std::endl;

    for(size_t i=0; i<minimizer->NDim(); ++i) {
        double error = (minimizer->Errors() ? minimizer->Errors()[i] : 0.0);
        std::cout << "      " << std::setw(5) << std::left << i
                  << std::setw(38) << std::left
                  << StringUtils::padRight(minimizer->VariableName((int)i), 38) << " "
                  << std::setw(14) << std::left << std::scientific << std::setprecision(6)
                  << std::left << minimizer->X()[i]
                  << std::left << error
                  << minimizer->GlobalCC((int)i) << std::endl;
    }
    // correlation between parameters
    std::cout << "--- Correlations----------------------------------------------------------------" << std::endl;
    for(unsigned int i=0; i<minimizer->NDim(); ++i) {
        std::cout << "      ";
        for(unsigned int j=0; j<minimizer->NDim(); ++j) {
            std::cout << std::setw(14) << std::scientific << std::setprecision(6)  << minimizer->Correlation(i,j);
        }
        std::cout << std::endl;
    }
}
