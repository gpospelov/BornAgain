// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Kernel/MinimizerFactory.cpp
//! @brief     Implements class MinimizerFactory.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MinimizerFactory.h"
#include "TestMinimizer.h"
#include "Minuit2Minimizer.h"
#include "GSLLevenbergMarquardtMinimizer.h"
#include "GSLMultiMinimizer.h"
#include "SimAnMinimizer.h"
#include "GeneticMinimizer.h"
#include "MinimizerCatalogue.h"
#include <sstream>
#include <iostream>

IMinimizer* MinimizerFactory::createMinimizer(const std::string& minimizerName,
                                              const std::string& algorithmType,
                                              const std::string& optionString)
{
    IMinimizer* result(0);

    if(minimizerName == MinimizerNames::Minuit2) {
        result = new Minuit2Minimizer(algorithmType);
    }

    else if(minimizerName == MinimizerNames::GSLLMA) {
        result = new GSLLevenbergMarquardtMinimizer();
    }

    else if(minimizerName == MinimizerNames::GSLSimAn) {
        result = new SimAnMinimizer();
    }

    else if(minimizerName == MinimizerNames::GSLMultiMin) {
        result = new GSLMultiMinimizer(algorithmType);
    }

    else if(minimizerName == MinimizerNames::Genetic) {
        result = new GeneticMinimizer();
    }

    if(!result) {
        std::ostringstream ostr;
        ostr << "MinimizerFactory::MinimizerFactory() -> Error! Can't create minimizer for given "
                "collection name '" << minimizerName
        << "' or algorithm '" << algorithmType << "'" << std::endl;
        ostr << "Possible names are:" << std::endl;

        ostr << catalogue().toString();
        throw std::runtime_error(ostr.str());
    }

    if(!optionString.empty())
        result->setOptions(optionString);

    return result;
}

void MinimizerFactory::printCatalogue()
{
    std::cout << catalogueToString() << std::endl;
}

std::string MinimizerFactory::catalogueToString()
{
    return catalogue().toString();
}

const MinimizerCatalogue& MinimizerFactory::catalogue()
{
    static MinimizerCatalogue s_catalogue = MinimizerCatalogue();
    return s_catalogue;
}
