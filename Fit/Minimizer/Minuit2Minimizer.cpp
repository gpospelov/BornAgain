// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Minimizer/Minuit2Minimizer.cpp
//! @brief     Declares class Minuit2Minimizer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Minuit2Minimizer.h"
#include "AlgorithmNames.h"

namespace {
const std::string O_STRATEGY = "Strategy";
const std::string O_ERRORDEF = "ErrorDef";
const std::string O_TOLERANCE = "Tolerance";
const std::string O_PRECISION = "Precision";
const std::string O_PRINTLEVEL = "PrintLevel";
}

Minuit2Minimizer::Minuit2Minimizer()
    : BasicMinimizer(MinimizerNames::Minuit, AlgorithmNames::Migrad)
    , m_minuit2_minimizer(new BA_ROOT::Minuit2::Minuit2Minimizer("xxx"))
{
    addOption(O_STRATEGY, 1,
              "Minimization strategy (0-low, 1-medium, 2-high quality)");
    addOption(O_ERRORDEF, 1.0,
              "Error definition factor for parameter error calculation.");
    addOption(O_TOLERANCE, 0.01,
              "Tolerance on the function value at the minimum.");
    addOption(O_PRECISION, -1.0,
              "Relative floating point arithmetic precision.");
    addOption(O_PRINTLEVEL, 0,
              "Minimizer internal print level.");

}

Minuit2Minimizer::~Minuit2Minimizer()
{

}

void Minuit2Minimizer::setStrategy(int value)
{
    setOptionValue(O_STRATEGY, value);
}

int Minuit2Minimizer::strategy() const
{
    return optionValue<int>(O_STRATEGY);
}

void Minuit2Minimizer::setErrorDefinition(double value)
{
    setOptionValue(O_ERRORDEF, value);
}

double Minuit2Minimizer::errorDefinition() const
{
    return optionValue<double>(O_ERRORDEF);
}

void Minuit2Minimizer::setTolerance(double value)
{
    setOptionValue(O_TOLERANCE, value);
}

double Minuit2Minimizer::tolerance() const
{
    return optionValue<double>(O_TOLERANCE);
}

void Minuit2Minimizer::setPrecision(double value)
{
    setOptionValue(O_PRECISION, value);
}

double Minuit2Minimizer::precision() const
{
    return optionValue<double>(O_PRECISION);
}

void Minuit2Minimizer::setPrintLevel(int value)
{
    setOptionValue(O_PRINTLEVEL, value);
}

int Minuit2Minimizer::printLevel() const
{
    return optionValue<int>(O_PRINTLEVEL);
}

//! Propagate options down to ROOT's Minuit2Minimizer.

void Minuit2Minimizer::propagateOptions()
{
    m_minuit2_minimizer->SetStrategy(strategy());
    m_minuit2_minimizer->SetErrorDef(errorDefinition());
    m_minuit2_minimizer->SetTolerance(tolerance());
    m_minuit2_minimizer->SetPrecision(precision());
    m_minuit2_minimizer->SetPrintLevel(printLevel());
}

const BasicMinimizer::root_minimizer_t *Minuit2Minimizer::rootMinimizer() const
{
    return m_minuit2_minimizer.get();
}

