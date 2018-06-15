// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/DepthProbeComputationTerm.h
//! @brief     Defines functor DepthProbeComputationTerm.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef DEPTHPROBECOMPUTATIONTERM_H
#define DEPTHPROBECOMPUTATIONTERM_H

#include <vector>

class IFresnelMap;
class MultiLayer;
class ProgressHandler;
class DepthProbeElement;

class DepthProbeComputationTerm
{
public:
    DepthProbeComputationTerm(const MultiLayer* p_multi_layer, const IFresnelMap* p_fresnel_map);

    void operator()(DepthProbeElement& elem) const;

private:
    const MultiLayer* mp_multilayer;
    const IFresnelMap* mp_fresnel_map;
};

#endif // DEPTHPROBECOMPUTATIONTERM_H
