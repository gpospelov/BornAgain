// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/MultiPatternFitTest.h
//! @brief     Defines class MultiPatternFitTest.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MULTIPATTERNFITTEST_H
#define MULTIPATTERNFITTEST_H

#include "IMinimizerTest.h"

//! @class MultiPatternFitTest
//! @ingroup standard_samples
//! @brief Fit with one fit parameter steering few sample parameters via multiple pattern mechanism.

class MultiPatternFitTest : public IMinimizerTest
{
public:
    MultiPatternFitTest();

protected:
    virtual void initParameterPlan();
    virtual std::unique_ptr<MultiLayer> createSample();
};

#endif // MULTIPATTERNFITTEST_H
