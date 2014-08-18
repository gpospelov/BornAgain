// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FitKernel/inc/ROOTLMAMinimizer.h
//! @brief     Defines class ROOTLMAMinimizer.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ROOTMULTIFITMINIMIZER_H
#define ROOTMULTIFITMINIMIZER_H

#include "ROOTMinimizer.h"
#include "Math/PatchedGSLNLSMinimizer.h"

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

    ROOT::Math::GSLNLSMinimizer *m_lma_minimizer;

};

#endif // ROOTMULTIFITMINIMIZER_H



