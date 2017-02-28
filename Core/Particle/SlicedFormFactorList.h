// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Shapes/SlicedFormFactorList.h
//! @brief     Defines class SlicedFormFactorList.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   J. Burle, J. M. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef SLICEDFORMFACTORLIST_H
#define SLICEDFORMFACTORLIST_H

#include "IFormFactor.h"
#include <memory>

class MultiLayer;

//! Class that contains and owns a list of form factors and the index of their containing layer.
//! This class also handles the slicing of form factors if they cross layer interfaces.
//!
//! @ingroup intern

class SlicedFormFactorList
{
public:
    SlicedFormFactorList() = default;
    SlicedFormFactorList(SlicedFormFactorList&& other) = default;
    SlicedFormFactorList& operator=(SlicedFormFactorList&& other) = default;
    ~SlicedFormFactorList() = default;

    void addFormFactor(const IFormFactor& formfactor, const MultiLayer& multilayer,
                       size_t ref_layer_index);

    size_t size() const;

    std::pair<const IFormFactor*, size_t> operator[](size_t index) const;
private:
    std::vector<std::pair<std::unique_ptr<IFormFactor>, size_t>> m_ff_list;
};

//! Global function that creates a SlicedFormFactorList from an IParticle in a multilayer
//!
//! @ingroup intern
SlicedFormFactorList CreateSlicedFormFactors(const IParticle& particle,
                                             const MultiLayer& multilayer,
                                             size_t ref_layer_index);


#endif // SLICEDFORMFACTORLIST_H
