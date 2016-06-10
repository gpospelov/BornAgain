// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/CoreFutestSuite.h
//! @brief     Declares class CoreFutestSuite.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef COREFUNCTIONALTESTCOMPONENTSERVICE_H
#define COREFUNCTIONALTESTCOMPONENTSERVICE_H

#include "FutestSuite.h"

class FunctionalTestInfo;

//! @class CoreFutestSuite
//! @ingroup standard_samples
//! @brief Contains all necessary information to compose core functional test.

class BA_CORE_API_ CoreFutestSuite : public FutestSuite
{
public:
    CoreFutestSuite(const FunctionalTestInfo* info);

    IFunctionalTest* getFunctionalTest() const;
};

#endif
