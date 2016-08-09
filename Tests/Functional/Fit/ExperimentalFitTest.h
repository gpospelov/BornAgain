// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/ExperimentalFitTest.h
//! @brief     Declares class ExperimentalFitTest.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef EXPERIMENTALFITTEST_H
#define EXPERIMENTALFITTEST_H

#include "IMinimizerTest.h"

//! @class ExperimentalFitTest
//! @ingroup standard_samples
//! @brief Experimental test on the way to refactored minimizers

class ExperimentalFitTest : public IMinimizerTest
{
public:
    ExperimentalFitTest();

protected:
    virtual std::unique_ptr<FitSuite> createFitSuite();

};

#endif // EXPERIMENTALFITTEST_H
