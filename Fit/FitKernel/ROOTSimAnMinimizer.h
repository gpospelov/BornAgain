// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FitKernel/ROOTSimAnMinimizer.h
//! @brief     Declares class ROOTSimAnMinimizer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ROOTSIMANMINIMIZER_H
#define ROOTSIMANMINIMIZER_H

#include "ROOTMinimizer.h"
#include "Math/PatchedGSLSimAnMinimizer.h"


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

    BA_ROOT::Math::GSLSimAnMinimizer *m_siman_minimizer;
};


#endif // ROOTSIMANMINIMIZER_H
