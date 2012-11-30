#include "ROOTMinimizer.h"
#include "Exceptions.h"
#include "Utils.h"
#include <iomanip>
#include <sstream>

ROOTMinimizer::ROOTMinimizer(const std::string &minimizer_name, const std::string &algo_type) : m_fcn(0)
{
    m_root_minimizer = ROOT::Math::Factory::CreateMinimizer(minimizer_name.c_str(), algo_type.c_str() );
    m_root_minimizer->SetMaxFunctionCalls(20000);
    m_root_minimizer->SetMaxIterations(20000);
    printOptions();
    if( m_root_minimizer == 0 ) {
        throw NullPointerException("ROOTMinimizer::ROOTMinimizer() -> Error! Can't build minimizer");
    }
}


ROOTMinimizer::~ROOTMinimizer()
{
    delete m_root_minimizer;
    delete m_fcn;
}


void ROOTMinimizer::setVariable(int index, const FitParameter *par)
{
    bool success;
    if( par->isFixed() ) {
        success=m_root_minimizer->SetFixedVariable(index, par->getName().c_str(), par->getValue());
    }else if(par->hasLowerAndUpperLimits() ) {
        success=m_root_minimizer->SetLimitedVariable(index, par->getName().c_str(), par->getValue(), par->getStep(), par->getLowerLimit(), par->getUpperLimit());
    } else if(par->hasLowerLimit() && !par->hasUpperLimit() ) {
        success=m_root_minimizer->SetLowerLimitedVariable(index, par->getName().c_str(), par->getValue(), par->getStep(), par->getLowerLimit());
    } else if( par->hasUpperLimit() && !par->hasLowerLimit() ) {
        success=m_root_minimizer->SetUpperLimitedVariable(index, par->getName().c_str(), par->getValue(), par->getStep(), par->getUpperLimit());
    } else if( !par->hasUpperLimit() && !par->hasLowerLimit() && !par->isFixed() ) {
        success=m_root_minimizer->SetVariable(index, par->getName().c_str(), par->getValue(), par->getStep());
    } else {
        throw LogicErrorException("ROOTMinimizer::setVariable() -> Strange place... I wish I knew how I got here.");
    }
    if( !success ) {
        std::ostringstream ostr;
        ostr << "ROOTMinimizer::setVariable() -> Error! Minimizer returned false while setting the variable." << std::endl;
        ostr << "                                Probably given index has been already used for another variable name." << std::endl;
        ostr << "                                Index:" << index << " name '" << par->getName().c_str() << std::endl;
        throw LogicErrorException(ostr.str());
    }
}


void ROOTMinimizer::minimize()
{
    m_root_minimizer->Minimize();
}


/* ************************************************************************* */
// set fcn function for minimizer
/* ************************************************************************* */
void ROOTMinimizer::setFunction(boost::function<double(const double *)> fcn, int ndim)
{
    m_fcn = new ROOT::Math::Functor(fcn, ndim);
//    m_fcn = new ROOT::Math::GradFunctor(fcn, ndim);
    m_root_minimizer->SetFunction(*m_fcn);
}


/* ************************************************************************* */
// print fit results
/* ************************************************************************* */
void ROOTMinimizer::printResults() const
{
    // explanations of minimizer's status
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

//     Status code of minimizer is updated according to the following convention (in case Hesse failed)
//     status += 100*hesseStatus where hesse status is:
//     status = 1 : hesse failed
//     status = 2 : matrix inversion failed
//     status = 3 : matrix is not pos defined

    // print initial mimimizer options
    printOptions();
    std::cout << "--- ROOTMinimizer::printResults() ---------------- " << std::endl;

    // final status of the minimizer
    std::cout << std::setw(25) << std::left << "  Status           "      << ": " << m_root_minimizer->Status() << " '" << minimizerStatus[m_root_minimizer->Status()] << "'" << std::endl;
    std::cout << std::setw(25) << std::left << "  IsValidError     "      << ": " << m_root_minimizer->IsValidError() << " '" << validErrorStatus[m_root_minimizer->Status()] << "'" <<std::endl;
    std::cout << std::setw(25) << std::left << "  NCalls"                 << ": " << m_root_minimizer->NCalls() << std::endl;
    std::cout << std::setw(25) << std::left << "  MinValue"               << ": " << std::scientific << std::setprecision(8) << getMinValue() << std::endl;
    std::cout << std::setw(25) << std::left << "  Edm"                    << ": " << std::scientific << std::setprecision(8) << m_root_minimizer->Edm() << std::endl;
    std::cout << std::setw(25) << std::left << "  CovMatrixStatus"        << ": " << m_root_minimizer->CovMatrixStatus() << " '" << covMatrixStatus[m_root_minimizer->CovMatrixStatus()] << "'" << std::endl;

    // variables found
    std::cout << std::setw(25) << std::left << "  NumberOfVariables"      << ": "
              << m_root_minimizer->NFree() << " (free), " << m_root_minimizer->NDim() << " (total) " << std::endl;
    if( !m_root_minimizer->Errors() ) {
        std::cout << "Warning! No access to parameter errors" << std::endl;
    }
    std::cout << std::endl;
    std::cout << "  Variables at minimum:" << std::endl;
    std::cout << "      " << std::setw(5) << std::left << "Npar"
              << std::setw(39) << std::left << " Name"
              << std::setw(14) << "Value"
              << std::setw(14) << "Error"
              << std::setw(14) << "GlobalCC" << std::endl;
    for(size_t i=0; i<getNumberOfVariables(); ++i) {
        std::cout << "      " << std::setw(5) << std::left << i
                  << std::setw(38) << std::left << Utils::AdjustStringLength(m_root_minimizer->VariableName(i), 38) << " "
                  << std::setw(14) << std::left << std::scientific << std::setprecision(6) << std::left << getValueOfVariableAtMinimum(i)
                  << std::setw(14) << std::left << std::scientific << std::setprecision(6) << std::left << getErrorOfVariable(i)
                  << std::setw(14) << std::left << std::scientific << std::setprecision(6) << std::left << m_root_minimizer->GlobalCC(i) << std::endl;
    }

    // correlation between parameters
    std::cout << std::endl;
    std::cout << "  Correlation between variables:" << std::endl;
    for(size_t i=0; i<getNumberOfVariables(); ++i) {
        std::cout << "      ";
        for(size_t j=0; j<getNumberOfVariables(); ++j) {
            std::cout << std::setw(14) << std::scientific << std::setprecision(6)  << m_root_minimizer->Correlation(i,j);
        }
        std::cout << std::endl;
    }

    // own print method of the minimizer
    //m_root_minimizer->PrintResults();
}


/* ************************************************************************* */
// print minimizer description
/* ************************************************************************* */
void ROOTMinimizer::printOptions() const
{
    std::cout << "--- ROOTMinimizer::printOptions() -------------- " << std::endl;
    //std::cout << typeid(m_root_minimizer).name() << std::endl;
    // minimizer options
    ROOT::Math::MinimizerOptions opt = m_root_minimizer->Options();
    std::cout << std::setw(25) << std::left << "  MinimizerType"      << ": " << opt.MinimizerType() << std::endl;
    std::cout << std::setw(25) << std::left << "  MinimizerAlgorithm" << ": " << opt.MinimizerAlgorithm() << std::endl;
    std::cout << std::setw(25) << std::left << "  Strategy"           << ": " << opt.Strategy() << std::endl;
    std::cout << std::setw(25) << std::left << "  Tolerance"          << ": " << opt.Tolerance() << std::endl;
    std::cout << std::setw(25) << std::left << "  MaxFunctionCalls"   << ": " << opt.MaxFunctionCalls() << std::endl;
    std::cout << std::setw(25) << std::left << "  MaxIterations"      << ": " << opt.MaxIterations() << std::endl;
    std::cout << std::setw(25) << std::left << "  Precision"          << ": " << opt.Precision() << std::endl;
    std::cout << std::setw(25) << std::left << "  ErrorDefinition"    << ": " << opt.ErrorDef() << " (1-chi2, 0.5 likelihood)" << std::endl;
    std::cout << std::setw(25) << std::left << "  ExtraOptions"       << ": " << opt.ExtraOptions() << std::endl;
    //opt.Print();
}



