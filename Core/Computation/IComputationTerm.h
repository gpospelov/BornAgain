// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/IComputationTerm.h
//! @brief     Defines interface IComputationTerm.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef ICOMPUTATIONTERM_H
#define ICOMPUTATIONTERM_H

class IFresnelMap;
class MultiLayer;

//! Computes an independent term of the scattering intensity.
//! Used by DWBAComputation, which adds up all contributions from subclasses
//! of IComputationTerm
//! @ingroup algorithms_internal

class IComputationTerm
{
public:
    IComputationTerm(const MultiLayer* p_multilayer, const IFresnelMap* p_fresnel_map);
    virtual ~IComputationTerm();

    const MultiLayer* mp_multilayer;
    const IFresnelMap* mp_fresnel_map;
};

#endif // ICOMPUTATIONTERM_H
