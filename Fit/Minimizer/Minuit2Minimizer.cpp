// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Minimizer/Minuit2Minimizer.h
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
{
    addOption(O_STRATEGY, 1,
              "Minimization strategy (0-low, 1-medium, 2-high quality)");
    addOption(O_ERRORDEF, 1.0,
              "Error definition factor for parameter error calculation.");
    addOption(O_TOLERANCE, 0.01,
              "Tolerance on the function value at the minimum.");
    addOption(O_PRECISION, -1.0,
              "Relative floating point arithmetic precision.");

}

void Minuit2Minimizer::setStrategy(int value)
{
    setOptionValue(O_STRATEGY, value);
}

void Minuit2Minimizer::setErrorDefinition(double value)
{
    setOptionValue(O_ERRORDEF, value);
}

void Minuit2Minimizer::setTolerance(double value)
{
    setOptionValue(O_TOLERANCE, value);
}

void Minuit2Minimizer::setPrecision(double value)
{
    setOptionValue(O_PRECISION, value);
}

