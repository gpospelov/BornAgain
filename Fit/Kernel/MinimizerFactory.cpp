// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Minimizer/MinimizerFactory.cpp
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
                                              const std::string& )
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

//! Create minimizer using existing one. Only minimizer type and minimizer settings are propagated.
//! This method serves as a kind of 'shallow' clone for minimizer.
//! The reason why the minimizer doesn't have own clone method is because of complicate structure of
//! ROOT minimizer internals.
IMinimizer* MinimizerFactory::createMinimizer(const IMinimizer* other)
{
    IMinimizer *result = createMinimizer(other->minimizerName(), other->algorithmName());
//    if(other->getOptions())
//        result->setOptions(*other->getOptions());
    return result;
}

const MinimizerCatalogue& MinimizerFactory::catalogue()
{
    static MinimizerCatalogue s_catalogue = MinimizerCatalogue();
    return s_catalogue;
}
