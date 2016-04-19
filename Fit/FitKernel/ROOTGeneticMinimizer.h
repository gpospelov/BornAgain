// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FitKernel/ROOTGeneticMinimizer.h
//! @brief     Defines class ROOTGeneticMinimizer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ROOTGENETICMINIMIZER_H
#define ROOTGENETICMINIMIZER_H

#include "ROOTMinimizer.h"
#include "Math/GeneticMinimizer.h"

//! @class ROOTGeneticMinimizer
//! @ingroup fitting_internal
//! @brief Wrapper for ROOT Genetic minimizer

class ROOTGeneticMinimizer : public ROOTMinimizer
{
public:
    ROOTGeneticMinimizer(const std::string& minimizer_name, const std::string& algo_type);
    virtual ~ROOTGeneticMinimizer(){}

    virtual void setParameter(size_t index, const FitParameter *par);

protected:
   virtual void propagateOptions();

   BA_ROOT::Math::GeneticMinimizer *m_genetic_minimizer;

};

#endif // ROOTGENETICMINIMIZER_H


