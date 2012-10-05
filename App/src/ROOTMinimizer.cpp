#include "ROOTMinimizer.h"

ROOTMinimizer::ROOTMinimizer(const std::string &minimizer_name, const std::string &algo_type)
{
    m_root_minimizer = ROOT::Math::Factory::CreateMinimizer(minimizer_name.c_str(), algo_type.c_str() );
}


ROOTMinimizer::~ROOTMinimizer()
{
    delete m_root_minimizer;
}
