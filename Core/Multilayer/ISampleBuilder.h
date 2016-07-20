// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/ISampleBuilder.h
//! @brief     Declares pure virtual base class ISampleBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ISAMPLEBUILDER_H
#define ISAMPLEBUILDER_H

#include "IParameterized.h" // inheriting from

class ISample;
class IFormFactor;
class IFTDistribution2D;

//! @class ISampleBuilder
//! @ingroup simulation_internal
//! @brief Interface to the class capable to build samples to simulate

class BA_CORE_API_ ISampleBuilder : public IParameterized
{
public:
    ISampleBuilder() : IParameterized("SampleBuilder") {}
    virtual ~ISampleBuilder() {}

    virtual ISample* buildSample() const = 0;

    void set_subtest(const IParameterized* subtest_item) { m_subtest_item = subtest_item; }
    const IParameterized* m_subtest_item;

    const IFormFactor* getFormFactor() const;
    const IFTDistribution2D* getFTDistribution2D() const;
};

#endif // ISAMPLEBUILDER_H
