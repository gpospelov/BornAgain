// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/FullFresnelMap.h
//! @brief     Defines class FullFresnelMap.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   J. Burle, J. M. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FULLFRESNELMAP_H
#define FULLFRESNELMAP_H

#include "SafePointerVector.h"

class ILayerSpecularInfo;

class FullFresnelMap
{
public:
    FullFresnelMap();
    ~FullFresnelMap();

    void push_back(ILayerSpecularInfo* layer_map);

    size_t size() const;

    const ILayerSpecularInfo* layerFresnelMap(size_t index) const;
private:
    SafePointerVector<ILayerSpecularInfo> m_full_map;
};

#endif // FULLFRESNELMAP_H
