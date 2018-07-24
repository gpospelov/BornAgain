// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/SpecularFitTest.h
//! @brief     Defines class SpecularFitTest.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

//! @class SpecularFitTest
//! @ingroup standard_samples
//! @brief Fit of specular data.

#ifndef SPECULARFITTEST_H_
#define SPECULARFITTEST_H_

#include "IObsoleteFittingTest.h"

class SpecularFitTest : public IObsoleteFittingTest
{
public:
    SpecularFitTest();
    virtual ~SpecularFitTest();

protected:
    void initParameterPlan() override;
};

#endif /* SPECULARFITTEST_H_ */
