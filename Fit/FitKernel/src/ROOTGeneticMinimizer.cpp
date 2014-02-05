// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FitKernel/src/ROOTGeneticMinimizer.cpp
//! @brief     Implements class ROOTGeneticMinimizer.
//
//! Homepage:  apps.jcns.fz-juelich.de/BornAgain
//! License:   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ROOTGeneticMinimizer.h"
#include "Math/GenAlgoOptions.h"
#include "MessageService.h"


ROOTGeneticMinimizer::ROOTGeneticMinimizer(const std::string& minimizer_name, const std::string& algo_type)
  : ROOTMinimizer(minimizer_name, algo_type)
{
    m_genetic_minimizer = new ROOT::Math::GeneticMinimizer();
    m_root_minimizer = m_genetic_minimizer;

    m_options.addValue("Cycles",3);
    m_options.addValue("PopSize",300);
    m_options.addValue("SC_rate",5);
    m_options.addValue("SC_steps",10);
    m_options.addValue("Steps",40);
//    m_options.addValue("ConvCrit",0.1); // It's defined from tolerance inside GeneticMinimizer (ConvCrit=10*Tolerance())
    m_options.addValue("SC_factor",0.95);
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
    m_root_minimizer->SetTolerance(m_options.getTolerance());
    m_root_minimizer->SetPrecision(m_options.getPrecision());
    m_root_minimizer->SetMaxFunctionCalls(m_options.getMaxFunctionCalls());
    m_root_minimizer->SetMaxIterations(m_options.getMaxIterations());

    if( m_options.getMaxIterations() > 0 && m_options.getMaxIterations() < m_options.getIntValue("Steps")) {
        msglog(MSG::WARNING) << "ROOTGeneticMinimizer::propagateOptions() -> Warning. Max iterations smaller than Steps";
        msglog(MSG::WARNING) << "Setting equal to steps " << m_options.getIntValue("Steps");
        m_options.setMaxIterations(m_options.getIntValue("Steps"));
    }

    // accessing minimizer
    ROOT::Math::MinimizerOptions options = m_genetic_minimizer->Options();

    options.SetTolerance(m_options.getTolerance());
    options.SetPrecision(m_options.getPrecision());
    options.SetMaxFunctionCalls(m_options.getMaxFunctionCalls());
    options.SetMaxIterations(m_options.getMaxIterations());

    ROOT::Math::IOptions *geneticOpt = options.ExtraOptions();
    geneticOpt->SetValue("Cycles", m_options.getIntValue("Cycles"));
    geneticOpt->SetValue("PopSize", m_options.getIntValue("PopSize"));
    geneticOpt->SetValue("SC_rate", m_options.getIntValue("SC_rate"));
    geneticOpt->SetValue("SC_steps", m_options.getIntValue("SC_steps"));
    geneticOpt->SetValue("Steps", m_options.getIntValue("Steps") );
    geneticOpt->SetValue("ConvCrit", 10.*m_options.getTolerance());
    geneticOpt->SetValue("SC_factor", m_options.getRealValue("SC_factor"));

}

