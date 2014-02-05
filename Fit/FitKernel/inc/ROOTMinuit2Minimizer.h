// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FitKernel/inc/ROOTMinuitMinimizer.h
//! @brief     Defines class ROOTMinuitMinimizer.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ROOTMINUIT2MINIMIZER_H
#define ROOTMINUIT2MINIMIZER_H

#include "ROOTMinimizer.h"
#include "Minuit2/Minuit2Minimizer.h"

//! @class ROOTMinuit2Minimizer
//! @ingroup fitting_internal
//! @brief Wrapper for ROOT Minuit2 minimizer

class ROOTMinuit2Minimizer : public ROOTMinimizer
{
public:
    ROOTMinuit2Minimizer(const std::string& minimizer_name, const std::string& algo_type);
    virtual ~ROOTMinuit2Minimizer(){}

protected:
   virtual void propagateOptions();

   ROOT::Minuit2::Minuit2Minimizer *m_minuit2_minimizer;

};


#endif
