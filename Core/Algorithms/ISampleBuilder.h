// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Algorithms/ISampleBuilder.h
//! @brief     Declares pure virtual base class ISampleBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ISAMPLEBUILDER_H_
#define ISAMPLEBUILDER_H_

#include "IParameterized.h"
#include "FTDistributions.h"
#include "IFormFactor.h"

//! @class ISampleBuilder
//! @ingroup simulation_internal
//! @brief Interface to the class capable to build samples to simulate

class BA_CORE_API_ ISampleBuilder : public IParameterized
{
public:
    ISampleBuilder() : IParameterized("SampleBuilder") {}
    virtual ~ISampleBuilder() {}

    virtual class ISample* buildSample() const = 0;

    void set_subtest(class IParameterized* subtest_item) { m_subtest_item = subtest_item; }
    const class IParameterized* m_subtest_item;

    const IFormFactor* getFormFactor() const {
        return dynamic_cast<const IFormFactor*>(m_subtest_item); }

    const IFTDistribution2D* getFTDistribution2D() const {
        return dynamic_cast<const IFTDistribution2D*>(m_subtest_item); }
};

#endif // ISAMPLEBUILDER_H_
