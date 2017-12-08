// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/SpecularFitTest.h
//! @brief     Defines class SpecularFitTest.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

//! @class SpecularFitTest
//! @ingroup standard_samples
//! @brief Fit of specular data.

#ifndef SPECULARFITTEST_H_
#define SPECULARFITTEST_H_

#include "IFittingTest.h"

class SpecularFitTest : public IFittingTest
{
public:
    SpecularFitTest();
    virtual ~SpecularFitTest();

protected:
    virtual void initParameterPlan() override;
};

#endif /* SPECULARFITTEST_H_ */
