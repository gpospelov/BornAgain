// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Minimizer/MinimizerFactory.h
//! @brief     Declares class MinimizerFactory.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MINIMIZERFACTORY_H
#define MINIMIZERFACTORY_H

#include "IMinimizer.h"
#include <string>

//! @class MinimizerFactory
//! @ingroup fitting
//! @brief Factory to create minimizers

class BA_CORE_API_ MinimizerFactory
{
 public:
    static IMinimizer* createMinimizer(
        const std::string& minimizer,
        const std::string& algorithm="",
        const std::string& options="" );
    static void printCatalogue();
    //! Returns copy of minimizer type and settings. No full clone, would be too heavy!
    static IMinimizer* createMinimizer(const IMinimizer* other);
};

#endif // MINIMIZERFACTORY_H
