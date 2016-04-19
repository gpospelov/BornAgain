// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FitKernel/ROOTGeneticMinimizer.cpp
//! @brief     Implements class ROOTGeneticMinimizer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ROOTGeneticMinimizer.h"
#include "Math/GenAlgoOptions.h"
#include "MessageService.h"


ROOTGeneticMinimizer::ROOTGeneticMinimizer(const std::string& minimizer_name, const std::string& algo_type)
  : ROOTMinimizer(minimizer_name, algo_type)
{
    m_genetic_minimizer = new BA_ROOT::Math::GeneticMinimizer();
    m_root_minimizer = m_genetic_minimizer;

    m_options.setMaxIterations(40);
    m_options.setTolerance(0.01);

    // getting default values from Genetic minimizer
    BA_ROOT::Math::GeneticMinimizerParameters pars;
    m_options.addValue("PopSize", pars.fPopSize);     // 300
//    m_options.addValue("Steps", pars.fNsteps);        // 100,  via setMaxIterations
    m_options.addValue("Cycles", pars.fCycles);       // 3
    m_options.addValue("SC_steps", pars.fSC_steps);   // 10
    m_options.addValue("SC_rate", pars.fSC_rate);     // 5
    m_options.addValue("SC_factor", pars.fSC_factor); // 0.95
//    m_options.addValue("ConvCrit", pars.fConvCrit);   // 0.001, via setTolerance
    m_options.addValue("RandomSeed", pars.fSeed);     // 0
}


void ROOTGeneticMinimizer::setParameter(size_t index, const FitParameter *par)
{
    if( !par->isFixed() && !par->hasLowerAndUpperLimits()) {
        std::ostringstream ostr;
        ostr << "ROOTGeneticMinimizer::setParameter() -> Error! ";
        ostr << "Genetic minimizer requires either fixed or limited AttLimits::limited(left,right) parameter. ";
        ostr << " Parameter name '" << par->getName() << "', isFixed():" << par->isFixed() << " hasLowerandUpperLimits:" << par->hasLowerAndUpperLimits();
        throw LogicErrorException(ostr.str());
    }
    ROOTMinimizer::setParameter(index, par);
}


// this function serve as a bridge and propagates MinimizerOptions inside GeneticMinimizer
// (which has own messy options)
void ROOTGeneticMinimizer::propagateOptions()
{
    ROOTMinimizer::propagateOptions();

    // setting minimizer parameters
    BA_ROOT::Math::GeneticMinimizerParameters pars;
    pars.fPopSize = m_options.getIntValue("PopSize");
    pars.fNsteps = m_options.getMaxIterations();
    pars.fCycles = m_options.getIntValue("Cycles");
    pars.fSC_steps = m_options.getIntValue("SC_steps");
    pars.fSC_rate = m_options.getIntValue("SC_rate");
    pars.fSC_factor = m_options.getRealValue("SC_factor");
    pars.fConvCrit = 10.*m_options.getTolerance();
    pars.fSeed = m_options.getIntValue("RandomSeed");

    m_genetic_minimizer->SetParameters(pars);
}

