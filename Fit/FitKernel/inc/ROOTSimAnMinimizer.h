// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FitKernel/inc/ROOTSimAnMinimizer.h
//! @brief     Defines class ROOTSimAnMinimizer.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ROOTSIMANMINIMIZER_H
#define ROOTSIMANMINIMIZER_H

#include "ROOTMinimizer.h"
#include "PatchedGSLSimAnMinimizer.h"


//! @class ROOTSimAnMinimizer
//! @ingroup fitting_internal
//! @brief Wrapper for ROOT GSL simmulated annealing minimizer

class ROOTSimAnMinimizer : public ROOTMinimizer
{
public:
    ROOTSimAnMinimizer(const std::string& minimizer_name, const std::string& algo_type);
    virtual ~ROOTSimAnMinimizer(){}

protected:
   virtual void propagateOptions();

   ROOT::Patch::GSLSimAnMinimizer *m_siman_minimizer;
};


#endif // ROOTSIMANMINIMIZER_H
