// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/IMultiLayerBuilder.h
//! @brief     Defines pure virtual base class IMultiLayerBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_MULTILAYER_IMULTILAYERBUILDER_H
#define BORNAGAIN_CORE_MULTILAYER_IMULTILAYERBUILDER_H

#include "Core/Parametrization/IParameterized.h"

class MultiLayer;

//! Interface to the class capable to build samples to simulate.
//! @ingroup simulation_internal

class IMultiLayerBuilder : public IParameterized
{
public:
    IMultiLayerBuilder();
    virtual ~IMultiLayerBuilder() = default;

    virtual MultiLayer* buildSample() const = 0;

    //! Returns true the freshly created pointer obtained from buildSample() can
    //! be directly assigned to a unique_ptr. Returns false if the object must be cloned.
    //! This method is replaced (i.e. ignored and extended) in the Python wrappers.
    static bool isPythonBuilder() { return false; }

    virtual MultiLayer* createSample(size_t index = 0)
    {
        (void)index;
        return buildSample();
    }
    virtual size_t size() { return 1; }
};

#endif // BORNAGAIN_CORE_MULTILAYER_IMULTILAYERBUILDER_H
