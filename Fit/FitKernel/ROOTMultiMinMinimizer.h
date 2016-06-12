// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FitKernel/ROOTMultiMinMinimizer.h
//! @brief     Declares class ROOTMultiMinMinimizer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ROOTMULTIMINMINIMIZER_H
#define ROOTMULTIMINMINIMIZER_H

#include "ROOTMinimizer.h"
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#include "Math/GSLMinimizer.h"
#pragma GCC diagnostic pop

//! @class ROOTMultiMinMinimizer
//! @ingroup fitting_internal
//! @brief Wrapper for GSL gradiend descent minimizer family

class ROOTMultiMinMinimizer : public ROOTMinimizer
{
public:
    ROOTMultiMinMinimizer(const std::string& minimizer_name, const std::string& algo_type);
    virtual ~ROOTMultiMinMinimizer(){}

protected:
   virtual void propagateOptions();

   BA_ROOT::Math::GSLMinimizer *m_gsl_minimizer;

};

#endif // ROOTMULTIMINMINIMIZER_H
