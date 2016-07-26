// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/FitKernel/AlgorithmNames.h
//! @brief     Declares namespace AlgorithmNames.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ALGORITHMNAMES_H
#define ALGORITHMNAMES_H

namespace MinimizerNames {

const std::string Minuit = "MinuitMinimizer";
const std::string GSL = "GSLMinimizer";
const std::string Genetic = "GeneticMinimizer";

} // namespace MinimizerNames

namespace AlgorithmNames {

const std::string Migrad = "Migrad";
const std::string Simplex = "Simplex";
const std::string Combined = "Combined";
const std::string Scan = "Scan";
const std::string Fumili = "Fumili";

const std::string ConjugateFR = "ConjugateFR";
const std::string ConjugatePR = "ConjugatePR";
const std::string BFGS = "BFGS";
const std::string BFGS2 = "BFGS2";
const std::string LMA = "LMA";
const std::string SimAn = "SimAn";

const std::string Genetic = "Genetic";

} // namespace AlgorithmNames

#endif // ALGORITHMNAMES_H
