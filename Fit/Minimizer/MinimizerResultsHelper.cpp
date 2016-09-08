// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Minimizer/MinimizerResultsHelper.cpp
//! @brief     Implements class MinimizerResultsHelper.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MinimizerResultsHelper.h"
#include "BasicMinimizer.h"
#include "FitSuiteParameters.h"
#include "FitParameter.h"
#include <boost/format.hpp>

namespace {

const int report_width = 80;
const int column_width = 18;

template<typename T>
std::string reportValue(const std::string &name, T value)
{
    std::ostringstream result;
    result << std::setw(column_width) << std::left << name  << ": " << value << std::endl;
    return result.str();
}

}


std::string MinimizerResultsHelper::reportResults(const BasicMinimizer *minimizer) const
{
    std::ostringstream result;

    result << section();
    result << reportDescription(minimizer);
    result << reportOption(minimizer);
    result << reportStatus(minimizer);

    return result.str();
}

std::string MinimizerResultsHelper::reportResults(const FitSuiteParameters *parameters) const
{
    std::ostringstream result;

    result << section("FitParameters");

    result << "Npar Name        StartValue  Limits           FitValue  Error" << std::endl;

    // FIXME
//    int npar(0);
//    for(const FitParameter *par : parameters->getFitParameters()) {
//        result << boost::format("#%-2d  %-10s  %-6.4f      %-15s  %-6.4f    %5.4f \n")
//                  % npar
//                  % par->getName()
//                  % par->getStartValue()
//                  % par->limits().toString()
//                  % par->getValue()
//                  % par->getError();

//        ++npar;
//    }

    // FIXME !!!
//    FitParameterSet::corr_matrix_t matrix = parameters->correlationMatrix();
//    if(matrix.size()) {
//        result << section("Correlations");
//        for(size_t i=0; i<matrix.size(); ++i) {
//            result << boost::format("#%-2d       ") %i;
//            for(size_t j=0; j<matrix[i].size(); ++j) {
//                result << boost::format("%_7.4f    ") % matrix[i][j];
//            }
//            result << std::endl;
//        }

//    }

    return result.str();

}

std::string MinimizerResultsHelper::reportDescription(const BasicMinimizer *minimizer) const
{
    std::ostringstream result;
    result << reportValue("MinimizerType", minimizer->minimizerName());
    result << reportValue("AlgorithmName", minimizer->algorithmName());
    return result.str();
}

std::string MinimizerResultsHelper::reportOption(const BasicMinimizer *minimizer) const
{
    if(minimizer->options().size() == 0)
        return std::string();

    std::ostringstream result;
    result << section("Options");
    for(auto option : minimizer->options()) {
        std::ostringstream opt;
        opt << std::setw(5) << std::left << option->value() << option->description();
        result << reportValue(option->name(), opt.str());
    }
    result << section("OptionString");
    result << minimizer->options().toOptionString() << std::endl;

    return result.str();
}

std::string MinimizerResultsHelper::reportStatus(const BasicMinimizer *minimizer) const
{
    std::ostringstream result;
    result << section("Status");

    auto status = minimizer->statusMap();
    for(auto it : status) {
        result << reportValue(it.first, it.second);
    }

    return result.str();
}

//! Returns horizontal line of 80 characters length with section name in it.
std::string MinimizerResultsHelper::section(const std::string &sectionName) const
{
    std::ostringstream result;
    if(sectionName.empty()) {
        result << std::string(report_width, '-') << std::endl;
    } else {
        // to make "--- SectionName ------------------------------"
        std::string prefix(3, '-');
        std::string body = std::string(" ") + sectionName + std::string(" ");
        std::string postfix(report_width - body.size() - prefix.size(), '-');
        result << prefix << body << postfix << std::endl;
    }
    return result.str();
}
