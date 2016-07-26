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

namespace AlgorithmNames {

const std::string MinuitMinimizerType = "MinuitMinimizer";
const std::string GSLMinimizerType = "GSLMinimizer";
const std::string GeneticMinimizerType = "GeneticMinimizer";

const std::string MigradAlgorithmType = "Migrad";
const std::string SimplexAlgorithmType = "Simplex";
const std::string CombinedAlgorithmType = "Combined";
const std::string ScanAlgorithmType = "Scan";
const std::string FumiliAlgorithmType = "Fumili";

const std::string ConjugateFRAlgorithmType = "ConjugateFR";
const std::string ConjugatePRAlgorithmType = "ConjugatePR";
const std::string BFGSAlgorithmType = "BFGS";
const std::string BFGS2AlgorithmType = "BFGS2";
const std::string LMAAlgorithmType = "LMA";
const std::string SimAnAlgorithmType = "SimAn";

const std::string GeneticAlgorithmType = "Genetic";

} // namespace AlgorithmNames

#endif // ALGORITHMNAMES_H
