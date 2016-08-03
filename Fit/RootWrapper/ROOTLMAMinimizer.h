// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/RootWrapper/ROOTLMAMinimizer.h
//! @brief     Declares class ROOTLMAMinimizer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ROOTLMAMINIMIZER_H
#define ROOTLMAMINIMIZER_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#include "ROOTMinimizer.h"
#include "Math/PatchedGSLNLSMinimizer.h"
#pragma GCC diagnostic pop

//! @class ROOTLMAMinimizer
//! @ingroup fitting_internal
//! @brief Wrapper for Levenberg Marquard GSL minimizer

class ROOTLMAMinimizer : public ROOTMinimizer
{
public:
    ROOTLMAMinimizer(const std::string& minimizer_name, const std::string& algo_type);
    virtual ~ROOTLMAMinimizer(){}

    virtual bool isGradientBasedAgorithm() { return true; }

protected:
   virtual void propagateOptions();

    BA_ROOT::Math::GSLNLSMinimizer *m_lma_minimizer;
};

#endif // ROOTLMAMINIMIZER_H
