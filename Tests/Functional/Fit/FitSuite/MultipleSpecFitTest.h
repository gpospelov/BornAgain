// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/FitSuite/MultipleSpecFitTest.h
//! @brief     Defines class MultipleSpecFitTest.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

//! @class MultipleSpecFitTest
//! @ingroup standard_samples
//! @brief Fit of two identical specular datasets.

#ifndef MULTIPLESPECFITTEST_H
#define MULTIPLESPECFITTEST_H

#include "SpecularFitTest.h"

class MultipleSpecFitTest : public SpecularFitTest
{
public:
    MultipleSpecFitTest();
    virtual ~MultipleSpecFitTest();

    bool runTest() override;
};

#endif // MULTIPLESPECFITTEST_H
