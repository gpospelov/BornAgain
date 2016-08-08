// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Minimizer/Minuit2Minimizer.h
//! @brief     Declares class Minuit2Minimizer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MINUIT2MINIMIZER_H
#define MINUIT2MINIMIZER_H

#include "BasicMinimizer.h"

//! @class Minuit2Minimizer
//! @ingroup fitting_internal
//! @brief The Minuit2Minimizer class is a wrapper for ROOT Minuit2 minimizer

class BA_CORE_API_ Minuit2Minimizer : public BasicMinimizer
{
public:
    Minuit2Minimizer();


private:

};

#endif
