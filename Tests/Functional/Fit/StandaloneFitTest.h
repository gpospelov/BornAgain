// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/StandaloneFitTest.h
//! @brief     Declares class StandaloneFitTest.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef STANDALONEFITTEST_H
#define STANDALONEFITTEST_H

#include "IMinimizerTest.h"

//! @class StandaloneFitTest
//! @ingroup standard_samples
//! @brief Collection of standalone tests for fitting library.

class StandaloneFitTest : public IFunctionalTest
{
public:
    StandaloneFitTest();

    bool runTest();
};

#endif
