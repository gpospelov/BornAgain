// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FitKernel/src/MinimizerFactory.cpp
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
#include "MinimizerTest.h"
#include "MinimizerScan.h"
#include "ROOTMinuit2Minimizer.h"
#include "ROOTMultiMinMinimizer.h"
#include "ROOTSimAnMinimizer.h"
#include "ROOTLMAMinimizer.h"
#include "ROOTGeneticMinimizer.h"
#include <iomanip>

MinimizerFactory::Catalogue MinimizerFactory::m_catalogue =
        MinimizerFactory::Catalogue();

// constructing map of minimizer names holding list of defined algorithms
// for every minimizer
MinimizerFactory::Catalogue::Catalogue()
{
    // our minimizers
    //m_data["Test"]        = {""};
    //m_data["Scan"]        = {""};
    // ROOT minimizers
    //m_data["Minuit"]      = {"Migrad", "Simplex", "Combined", "Scan"};
    m_data["Minuit2"]     = {"Migrad", "Simplex", "Combined", "Scan", "Fumili"};
    m_data["GSLMultiMin"] = {"ConjugateFR", "ConjugatePR", "BFGS", "BFGS2", "SteepestDescent"};
    m_data["GSLLMA"]      = {""};
    m_data["GSLSimAn"]    = {""};
    m_data["Genetic"]     = {""}; // available only with ROOT libraries
}


void MinimizerFactory::Catalogue::print(std::ostream& ostr) const
{
    for(MinimizerFactory::Catalogue::const_iterator it=m_data.begin(); it!=m_data.end(); ++it) {
        ostr << std::setw(20) << std::left<< it->first << "  : ";
        for(size_t i=0; i<it->second.size(); ++i ) {
            ostr << it->second[i] << " ";
        }
        ostr << std::endl;
    }
    ostr << std::endl;
}


bool MinimizerFactory::Catalogue::isValid(const std::string& minimizer, const std::string& algorithm) const
{
    // check minimizers names
    MinimizerFactory::Catalogue::const_iterator it = m_data.find(minimizer);
    if(it != m_data.end() ) {
        // check minimizer's algorithm type
        for(size_t i=0; i<it->second.size(); ++i ) if(it->second[i] == algorithm ) return true;
    }
    return false;
}

void MinimizerFactory::printCatalogue()
{
    std::cout << m_catalogue;
}


IMinimizer *MinimizerFactory::createMinimizer(const std::string& minimizer, const std::string& algorithm, const std::string& options)
{
    if( !m_catalogue.isValid(minimizer, algorithm) ) {
        std::ostringstream ostr;
        ostr << "MinimizerFactory::MinimizerFactory() -> Error! Wrong minimizer name '" << minimizer << "' or algorithm '" << algorithm << "'" << std::endl;
        ostr << "Possible names are:" << std::endl;
        ostr << m_catalogue;
        throw LogicErrorException(ostr.str());
    }

    IMinimizer *result(0);
    if( minimizer == "Test" ) {
        result = new MinimizerTest();

    } else if( minimizer == "Scan" ) {
        result = new MinimizerScan();

    } else if( minimizer == "Minuit2" ) {
        result = new ROOTMinuit2Minimizer(minimizer, algorithm);

    } else if( minimizer == "GSLMultiMin" ) {
        result = new ROOTMultiMinMinimizer(minimizer, algorithm);

    } else if( minimizer == "GSLLMA" ) {
        result = new ROOTLMAMinimizer(minimizer, algorithm);

    } else if( minimizer == "GSLSimAn" ) {
        result = new ROOTSimAnMinimizer(minimizer, algorithm);

    } else if( minimizer == "Genetic" ) {
        result = new ROOTGeneticMinimizer(minimizer, algorithm);

    }

    if(!result) {
        throw LogicErrorException("MinimizerFactory::createMinimizer() -> Error! Wrong minimizer name '"+minimizer+"'");
    }

    if( !options.empty() ) {
        try {
            result->setOptionString(options);
        } catch (NotImplementedException& e) {
            std::cout << "MinimizerFactory::createMinimizer() -> Warning! Minimizer doesn't have method implemented" << e.what() << std::endl;
        }
    }

    return result;
}



//! Create minimizer using existing one. Only minimizer type and minimizer settings are propagated.
//! This method serves as a kind of 'shallow' clone for minimizer.
//! The reason why the minimizer doesn't have own clone method is because of complicate structure of
//! ROOT minimizer internals.
IMinimizer *MinimizerFactory::createMinimizer(const IMinimizer *minimizer)
{
    IMinimizer *result = createMinimizer(minimizer->getMinimizerName(), minimizer->getAlgorithmName());
    result->setOptions(*minimizer->getOptions());
    return result;
}

