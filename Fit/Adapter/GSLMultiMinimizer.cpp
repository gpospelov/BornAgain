//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      Fit/Adapter/GSLMultiMinimizer.cpp
//! @brief     Implements class GSLMultiMinimizer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Fit/Adapter/GSLMultiMinimizer.h"
#include "Fit/Tools/MinimizerUtils.h"
#include <string>

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable : 4267)
#include <Math/GSLMinimizer.h>
#pragma warning(pop)
#else
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#include <Math/GSLMinimizer.h>
#pragma GCC diagnostic pop
#endif

GSLMultiMinimizer::GSLMultiMinimizer(const std::string& algorithmName)
    : MinimizerAdapter(MinimizerInfo::buildGSLMultiMinInfo(algorithmName))
    , m_gsl_minimizer(new ROOT::Math::GSLMinimizer(algorithmName.c_str())) {
    addOption("PrintLevel", 0, "Minimizer internal print level");
    addOption("MaxIterations", 0, "Maximum number of iterations");
}

GSLMultiMinimizer::~GSLMultiMinimizer() = default;

void GSLMultiMinimizer::setPrintLevel(int value) {
    setOptionValue("PrintLevel", value);
}

int GSLMultiMinimizer::printLevel() const {
    return optionValue<int>("PrintLevel");
}

void GSLMultiMinimizer::setMaxIterations(int value) {
    setOptionValue("MaxIterations", value);
}

int GSLMultiMinimizer::maxIterations() const {
    return optionValue<int>("MaxIterations");
}

std::string GSLMultiMinimizer::statusToString() const {
    return mumufit::utils::gslErrorDescription(rootMinimizer()->Status());
}

void GSLMultiMinimizer::propagateOptions() {
    m_gsl_minimizer->SetPrintLevel(printLevel());
    m_gsl_minimizer->SetMaxIterations(static_cast<unsigned int>(maxIterations()));
}

const MinimizerAdapter::root_minimizer_t* GSLMultiMinimizer::rootMinimizer() const {
    return m_gsl_minimizer.get();
}
