// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/FitKernel/MinimizerFactory.cpp
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
// #include "ScanningMinimizer.h"
#include "TrivialMinimizer.h"
#include "ROOTGeneticMinimizer.h"
#include "ROOTLMAMinimizer.h"
#include "ROOTMinuit2Minimizer.h"
#include "ROOTMultiMinMinimizer.h"
#include "ROOTSimAnMinimizer.h"

// ************************************************************************** //
// auxiliary class MinimizerCatalogue
// ************************************************************************** //

//! Map of minimizer names holding list of defined algorithms for every minimizer.
class MinimizerCatalogue {
public:
    typedef std::map<std::string, std::vector<std::string>> catalogue_t;
    typedef catalogue_t::const_iterator const_iterator;
    MinimizerCatalogue();
    const_iterator begin() const { return m_data.begin(); }
    const_iterator end() const { return m_data.end(); }
    bool isValid(const std::string& minimizer, const std::string& algorithm) const;
    friend std::ostream& operator<<(std::ostream& ostr, const MinimizerCatalogue& m) {
        m.print(ostr); return ostr; }
private:
    void print(std::ostream& ostr) const;
    catalogue_t m_data;
};

// Constructs map of minimizer names holding list of defined algorithms for every minimizer
MinimizerCatalogue::MinimizerCatalogue()
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


void MinimizerCatalogue::print(std::ostream& ostr) const
{
    for(MinimizerCatalogue::const_iterator it=m_data.begin(); it!=m_data.end(); ++it) {
        ostr << std::setw(20) << std::left<< it->first << "  : ";
        for(size_t i=0; i<it->second.size(); ++i ) {
            ostr << it->second[i] << " ";
        }
        ostr << std::endl;
    }
    ostr << std::endl;
}


bool MinimizerCatalogue::isValid(const std::string& minimizer, const std::string& algorithm) const
{
    // check minimizers names
    MinimizerCatalogue::const_iterator it = m_data.find(minimizer);
    if(it != m_data.end() ) {
        // check minimizer's algorithm type
        for(size_t i=0; i<it->second.size(); ++i ) if(it->second[i] == algorithm ) return true;
    }
    return false;
}

// ************************************************************************** //
// class MinimizerFactory
// ************************************************************************** //

static MinimizerCatalogue catalogue;

void MinimizerFactory::printCatalogue()
{
    std::cout << catalogue;
}


IMinimizer* MinimizerFactory::createMinimizer(
    const std::string& minimizer, const std::string& algorithm, const std::string& options)
{
    if( !catalogue.isValid(minimizer, algorithm) ) {
        std::ostringstream ostr;
        ostr << "MinimizerFactory::MinimizerFactory() -> Error! Wrong minimizer name '" <<
            minimizer << "' or algorithm '" << algorithm << "'" << std::endl;
        ostr << "Possible names are:" << std::endl;
        ostr << catalogue;
        throw Exceptions::LogicErrorException(ostr.str());
    }

    IMinimizer* result(0);
    if( minimizer == "Test" ) {
        result = new TrivialMinimizer();

        /* temporarily disabled
    } else if( minimizer == "Scan" ) {
        result = new ScanningMinimizer();
        */

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

    } else
        throw Exceptions::LogicErrorException("MinimizerFactory::createMinimizer() -> Error! "
                                              "Wrong minimizer name '"+minimizer+"'" );

    if( !options.empty() ) {
        try {
            result->setOptionString(options);
        } catch (Exceptions::NotImplementedException& e) {
            std::cout << "MinimizerFactory::createMinimizer() -> Warning! " <<
                "Minimizer doesn't have method implemented" << e.what() << std::endl;
        }
    }

    return result;
}


//! Create minimizer using existing one. Only minimizer type and minimizer settings are propagated.
//! This method serves as a kind of 'shallow' clone for minimizer.
//! The reason why the minimizer doesn't have own clone method is because of complicate structure of
//! ROOT minimizer internals.
IMinimizer* MinimizerFactory::createMinimizer(const IMinimizer* other)
{
    IMinimizer* result = createMinimizer(other->getMinimizerName(), other->getAlgorithmName());
    result->setOptions(*other->getOptions());
    return result;
}
