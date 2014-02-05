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


// this function serve as a bridge and propagates MinimizerOptions inside GeneticMinimizer
// (which has own messy options)
void ROOTGeneticMinimizer::propagateOptions()
{
//    m_root_minimizer->SetTolerance(m_options.getTolerance());
//    m_root_minimizer->SetPrecision(m_options.getPrecision());
//    m_root_minimizer->SetMaxFunctionCalls(m_options.getMaxFunctionCalls());
//    m_root_minimizer->SetMaxIterations(m_options.getMaxIterations());

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
//    geneticOpt->SetValue("ConvCrit", m_options.getRealValue("ConvCrit"));
    geneticOpt->SetValue("SC_factor", m_options.getRealValue("SC_factor"));

    std::cout << "XXX" << m_options.getTolerance() << std::endl;

    m_genetic_minimizer->SetOptions(options);
    m_genetic_minimizer->Options().Print();
}

